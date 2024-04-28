#include "gamewave.h"

Gamewave::Gamewave(const retro_environment_t env_cb, const retro_log_printf_t log_cb)
{
    this->setEnvironmentCallback(env_cb);
    this->setLogCallback(log_cb);

    // clear framebuffer
    this->framebuffer.fill(0);

    this->coreRunning = true;
    // start Lua threads
    this->luaThread = std::thread(&Gamewave::luaFunction, this);
    this->videoThread = std::thread(&Gamewave::videoFunction, this);
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

bool Gamewave::loadGame(const char *filePath)
{
    DizManager diz = DizManager();
    bool dizLoaded = diz.readFile(filePath);
    if (!dizLoaded)
    {
        log_cb(RETRO_LOG_ERROR, "Could not load %s\n", filePath);
        return false;
    }
    log_cb(RETRO_LOG_DEBUG, "[DIZ] Game name: %s\n", diz.getAppName().c_str());
    log_cb(RETRO_LOG_DEBUG, "[DIZ] Game file: %s\n", diz.getAppFile().c_str());
    log_cb(RETRO_LOG_DEBUG, "[DIZ] Game version: %s\n", diz.getVersion().c_str());

    char mes[128];
    std::sprintf(mes, "loaded a Game Wave game: %s", diz.getAppFile().c_str());
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
std::function<void(lua_State *L, lua_Debug *ar)> Gamewave::getHook()
{
    return [this]([[maybe_unused]] lua_State *L, [[maybe_unused]] lua_Debug *ar)
    {
        if (!this->coreRunning.load())
        {
            log_cb(RETRO_LOG_DEBUG, "got info to stop Lua gracefully-ish\n");
            longjmp(place, 1);
            // TODO remove after testing
            // lua_sethook(L, hook.target<void(lua_State *, lua_Debug *)>(), LUA_MASKLINE, 0);
            // luaL_error(L, "terminate");
        }
    };
    // return hook;
}

std::string Gamewave::dumpLuaStack(lua_State *L)
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
            buffer += std::format("{}", "nil");
            break;
        default:
            buffer += std::format("{}", lua_topointer(L, i));
            break;
        }
        if (i != top)
        {
            buffer += '\n';
        }
    }
    return buffer;
}

void Gamewave::luaFunction()
{
    lua_State *L = lua_open(); /* opens Lua */
    // openstdlibs(L);
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
    auto hook = getHook();
    lua_sethook(L, hook.target<void(lua_State *, lua_Debug *)>(), LUA_MASKCOUNT, 100);

    std::string filename = "/home/halamix2/repos/reverse/gamewave/games/Click! (USA)/data/game.unpack";
    std::string buffer;
    std::ifstream f(filename);
    f.seekg(0, std::ios::end);
    buffer.resize(f.tellg());
    f.seekg(0);
    f.read(buffer.data(), buffer.size());

    int status = luaL_loadbuffer(L, buffer.data(), buffer.size(), filename.c_str());
    log_cb(RETRO_LOG_DEBUG, "%s loaded, status %d\n", filename, status);
    if (status == 0 && setjmp(place) == 0)
    {
        log_cb(RETRO_LOG_DEBUG, "running %s\n======\n\n", filename);
        status = lua_pcall(L, 0, -1, 0);
    }

    printf("\n======\npcall status %d\n", status);
    int err = lua_gettop(L);
    if (err != 0)
    {
        // TODO: watch for core fails, set core running to 0?
        log_cb(RETRO_LOG_ERROR, "Error %d during execution\n", err);

        // flood framebuffer with pink to show fatal error
        // TODOD: think of a better way to show this
        this->framebuffer.fill(packPixel(255, 0, 255));

        auto stacktrace = dumpLuaStack(L);

        char mes[128];
        // TODO: stacktrace here
        std::sprintf(mes, "Critical failure of the Lua thread:\n%s", stacktrace.c_str());

        retro_message_ext mess{
            mes, 5000, 4, RETRO_LOG_ERROR, RETRO_MESSAGE_TARGET_ALL, RETRO_MESSAGE_TYPE_NOTIFICATION, -1};

        // TODO check RETRO_ENVIRONMENT_GET_MESSAGE_INTERFACE_VERSION
        env_cb(RETRO_ENVIRONMENT_SET_MESSAGE_EXT, &mess);

        // log_cb("stacktrace TODO:\n");
        env_cb(RETRO_ENVIRONMENT_SHUTDOWN, nullptr);
    }
    lua_close(L);
}

void Gamewave::videoFunction()
{
}
