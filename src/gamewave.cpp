#include "gamewave.h"

std::filesystem::path GameBasePath = {};
Gamewave::Gamewave(const retro_environment_t env_cb, const retro_log_printf_t log_cb, const char *inputPath)
{
    fs::path path = inputPath;
    GameBasePath = path.parent_path();
    this->setEnvironmentCallback(env_cb);
    this->setLogCallback(log_cb);
    log_cb(RETRO_LOG_INFO, "set gameBasePath to %s\n", GameBasePath.c_str());
    // create Lua machine
    L = lua_open();
    loadLuaLibraries();

    // clear framebuffer
    this->framebuffer.fill(0);

    this->coreRunning = true;

    // this->videoThread = std::thread(&Gamewave::videoFunction, this);
}

// TODO: rework loading libraries
// I've spent to much  time trying to use zluaClosure::target<int(lua_State *)>() with no luck
void Gamewave::loadLuaLibraries()
{
    // load libraries
    // typedef int (*lua_CFunction) (lua_State *L);
    static const luaL_reg lualibs[] = {
        {"base", luaopen_base},
        {"table", luaopen_table},
        {"string", luaopen_string},
        {"debug", luaopen_debug},
        {"engine", zlua::Engine::zlua_engine_loadlibrary},
        {"gl", zlua::GL::zlua_gl_loadlibrary},
        // {"audio", luaopen_audio},
        {"bit", zlua::Bit::zlua_bit_loadlibrary},
        // {"eeprom", luaopen_eeprom},
        {"zlua", zlua::Log::zlua_log_loadlibrary},
        // {"exp_int", luaopen_exp_int},
        // {"font", luaopen_font},
        // {"gl", luaopen_gl},
        {"iframe", zlua::IFrame::zlua_iframe_loadlibrary},
        // {"input", luaopen_input},
        // {"log", *zlogre},
        // {"movie", nullptr},
        // {"pointer", luaopen_pointer},
        {"rm", zlua::RM::zlua_rm_loadlibrary},
        // {"spi", luaopen_spi},
        // {"text", luaopen_text},
        {"time", zlua::Time::zlua_time_loadlibrary},
        // {"uart", luaopen_uart},
        // {"zfile", luaopen_zfile},
        {"zmath", zlua::ZMath::zlua_zmath_loadlibrary},
        {nullptr, nullptr}};

    // load C-style libraries
    const luaL_reg *lib = lualibs;
    for (; lib->func; lib++)
    {
        log_cb(RETRO_LOG_DEBUG, "Loading lua library %s\n", lib->name);
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

    DIZ diz = DIZ();
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
    auto fimgPath = path.parent_path() / diz.getPlatforms().at("3").getSafeEngine();
    log_cb(RETRO_LOG_DEBUG, "trying to load %s as a FIMG\n", fimgPath.c_str());
    fimg = new FIMG(fimgPath);

    // display launching iframe
    auto launch = fimg->getFile("launching.m2v");
    auto movie = IFrame(launch);
    auto image = movie.getFramebuffer();
    std::memcpy(framebuffer.begin(), image->data(), image->size());

    fs::path bytecodePath = path.parent_path() / diz.getSafeAppFile();
    const auto *filename = bytecodePath.stem().c_str();
    // decompress and load the bytecode
    log_cb(RETRO_LOG_DEBUG, "trying to load %s as a game\n", bytecodePath.c_str());
    try
    {
        auto zbcFile = ZBC(bytecodePath);
        auto [gameBytecode, size] = zbcFile.getUncompressed();
        auto status = luaL_loadbuffer(L, gameBytecode, size, filename);
        // setup Lua
        auto hook = getHook();
        // TOOD: won't work, closures with capturing group cannot be converted that way
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
    // TODO: remove this after FIM testing
    std::this_thread::sleep_for(2s);

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
