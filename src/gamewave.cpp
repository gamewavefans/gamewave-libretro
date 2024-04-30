#include "gamewave.h"

Gamewave::Gamewave(const retro_environment_t env_cb, const retro_log_printf_t log_cb)
{
    this->setEnvironmentCallback(env_cb);
    this->setLogCallback(log_cb);

    // create Lua machine
    L = lua_open();
    loadLuaLibraries();

    // clear framebuffer
    this->framebuffer.fill(0);

    this->coreRunning = true;

    // this->videoThread = std::thread(&Gamewave::videoFunction, this);
}

void Gamewave::loadLuaLibraries()
{
    static const luaL_reg lualibs[] = {
        {"base", luaopen_base},
        {"table", luaopen_table},
        //{"io", luaopen_io},
        {"string", luaopen_string},
        //{"math", luaopen_math},
        {"debug", luaopen_debug},
        {nullptr, nullptr}};
    const luaL_reg *lib = lualibs;
    for (; lib->func; lib++)
    {
        lib->func(L);     /* open library */
        lua_settop(L, 0); /* discard any results */
    }
}

Gamewave::~Gamewave()
{
    this->coreRunning = false;
    log_cb(RETRO_LOG_INFO, "destroying Gamewave\n");
    // join threads before destroying to avoid leaking resources
    if (luaThread.joinable())
    {
        luaThread.join();
        log_cb(RETRO_LOG_INFO, "lua thread destroyed\n");
    }

    if (videoThread.joinable())
    {
        videoThread.join();
        log_cb(RETRO_LOG_INFO, "video thread destroyed\n");
    }

    if (L != nullptr)
    {
        lua_close(L);
    }
}

void Gamewave::setEnvironmentCallback(const retro_environment_t env_cb)
{
    this->env_cb = env_cb;
}

void Gamewave::setLogCallback(const retro_log_printf_t log_cb)
{
    this->log_cb = log_cb;
}

unsigned int *Gamewave::getFramebuffer()
{
    return this->framebuffer.data();
}

bool Gamewave::loadGame(const char *inputPath)
{
    fs::path path = inputPath;
    log_cb(RETRO_LOG_DEBUG, "Input name: %s\n", inputPath);
    log_cb(RETRO_LOG_DEBUG, "Base dir: %s\n", path.parent_path().c_str());

    DizManager diz = DizManager();
    bool dizLoaded = diz.readFile(inputPath);
    if (!dizLoaded)
    {
        log_cb(RETRO_LOG_ERROR, "Could not load %s\n", inputPath);
        return false;
    }

    log_cb(RETRO_LOG_DEBUG, "[DIZ] Game name: %s\n", diz.getAppName().c_str());
    log_cb(RETRO_LOG_DEBUG, "[DIZ] Game file: %s\n", diz.getSafeAppFile().c_str());
    if (diz.getVersion() != "")
    {
        log_cb(RETRO_LOG_DEBUG, "[DIZ] Game version: %s\n", diz.getVersion().c_str());
    }

    fs::path bytecodePath = path.parent_path() / diz.getSafeAppFile();
    auto *filename = bytecodePath.stem().c_str();
    // decompress and load the bytecode
    log_cb(RETRO_LOG_DEBUG, "trying to load %s as a game\n", bytecodePath.c_str());
    try
    {
        auto zbcFile = ZBC(bytecodePath);
        auto [gameBytecode, size] = zbcFile.getUncompressed();
        log_cb(RETRO_LOG_ERROR, "Got funky %d bytes of code: %s\n", size, gameBytecode + 1);
        auto status = luaL_loadbuffer(L, gameBytecode, size, filename);
        // setup Lua
        auto hook = getHook();
        lua_sethook(L, hook.target<void(lua_State *, lua_Debug *)>(), LUA_MASKCOUNT, 100);
        // skipcq: CXX-W2015
        if (status != 0 || setjmp(place) != 0)
        {
            throw std::runtime_error("Error loading Lua bytecode");
        }
        log_cb(RETRO_LOG_DEBUG, "%s loaded, status %d\n", bytecodePath.c_str(), status);
        // start Lua threads
        this->luaThread = std::thread(&Gamewave::luaFunction, this);
    }
    catch (std::exception &e)
    {
        log_cb(RETRO_LOG_ERROR, "Error loading ZBC file: %s\n", e.what());
        return false;
    }

    char mes[128];
    std::sprintf(mes, "loaded a Game Wave game: %s", bytecodePath.c_str());
    retro_message_ext mess{
        mes, 3000, 4, RETRO_LOG_DEBUG, RETRO_MESSAGE_TARGET_ALL, RETRO_MESSAGE_TYPE_NOTIFICATION, -1};
    // TODO check RETRO_ENVIRONMENT_GET_MESSAGE_INTERFACE_VERSION
    env_cb(RETRO_ENVIRONMENT_SET_MESSAGE_EXT, &mess);

    return true;
}

/**
 * @brief getHook returns simple Lua hook function that looks is the core should end gracefully
 *
 * @return Lua hook function
 */
hookFunc Gamewave::getHook()
{
    return [this]([[maybe_unused]] lua_State *L, [[maybe_unused]] lua_Debug *ar)
    {
        if (!this->coreRunning.load())
        {
            log_cb(RETRO_LOG_DEBUG, "got info to stop Lua gracefully-ish\n");
            // skipcq: CXX-W2015
            longjmp(place, 1);
            // TODO remove after testing
            // lua_sethook(L, hook.target<void(lua_State *, lua_Debug *)>(), LUA_MASKLINE, 0);
            // luaL_error(L, "terminate");
        }
    };
    // return hook;
}

/**
 * @brief dumpLuaStack reads Lua error stack and returns it as a string
 *
 * @return A stacktrace string
 */
std::string Gamewave::dumpLuaStack()
{
    std::string buffer = {};
    int top = lua_gettop(L);
    for (int i = 1; i <= top; i++)
    {
        buffer += std::format("{}\t{}\t", i, lua_typename(L, lua_type(L, i)));
        switch (lua_type(L, i))
        {
        case LUA_TNUMBER:
            buffer += std::format("{}", lua_tonumber(L, i));
            break;
        case LUA_TSTRING:
            buffer += std::format("{}", lua_tostring(L, i));
            break;
        case LUA_TBOOLEAN:
            buffer += std::format("{}", (lua_toboolean(L, i) ? "true" : "false"));
            break;
        case LUA_TNIL:
            buffer += "nil";
            break;
        default:
            buffer += std::format("{}", lua_topointer(L, i));
            break;
            // TODO: consider LUA_TLIGHTUSERDATA, TTABLE, TFUNCTION, TUSERDATA
            // would need to be custom though, do we really need that?
        }

        // add newline, except on the last one
        if (i != top)
        {
            buffer += '\n';
        }
    }
    return buffer;
}

void Gamewave::luaFunction()
{
    auto err = lua_pcall(L, 0, -1, 0);
    if (err != 0)
    {
        // TODO: watch for core fails, set core running to 0?
        auto stacktrace = dumpLuaStack();
        log_cb(RETRO_LOG_ERROR, "Error %d during execution: %s\n", err, stacktrace.c_str());

        char mes[128];
        // TODO: stacktrace here
        std::sprintf(mes, "Critical failure of the Lua thread:\n%s", stacktrace.c_str());

        retro_message_ext mess{
            mes, 5000, 4, RETRO_LOG_ERROR, RETRO_MESSAGE_TARGET_ALL, RETRO_MESSAGE_TYPE_NOTIFICATION, -1};

        // TODO check RETRO_ENVIRONMENT_GET_MESSAGE_INTERFACE_VERSION
        env_cb(RETRO_ENVIRONMENT_SET_MESSAGE_EXT, &mess);

        env_cb(RETRO_ENVIRONMENT_SHUTDOWN, nullptr);
    }
}

void Gamewave::videoFunction()
{
}
