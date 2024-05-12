#include "zlua/log.h"
namespace zlua::Log
{
    // default to debug level, just in case
    LogLevel zlua_log_level = LogLevel::LOG_DEBUG;

    static const luaL_reg zlua_log_lib[] = {
        {"Log", zlua_log_log},
        {"SetLevel", zlua_log_setLevel},
        // TODO: implement
        // {"SetModule", log_set_module},
        // {"PrintRaw", log_print_raw},
        // {"PrintLine", log_print_line},
        // {"DebugSetState", log_debug_set_state},
        {nullptr, nullptr}};

    int zlua_log_loadlibrary(lua_State *L)
    {
        luaL_openlib(L, "log", zlua_log_lib, 0);
        return 1;
    }

    int zlua_log_log(lua_State *L)
    {
        int level = luaL_checkint(L, 1);
        const char *line = luaL_checkstring(L, 2);
        // printf("\tcalled log.Log(%s, \"%s\") - UNIMPLEMENTED\n", getLogLevelName(level), line);

        if (level <= static_cast<int>(zlua_log_level))
        {
            log_cb(RETRO_LOG_DEBUG, "[game]\t%s:\t%s", getLogLevelName(level), line);
        }
        else
        {
            // TODO: add flag controlling if we even should show hidden logs
            log_cb(RETRO_LOG_DEBUG, "HIDDEN %s: %s", getLogLevelName(level), line);
        }
        return 0;
    }

    int zlua_log_setLevel(lua_State *L)
    {
        int level = luaL_checkint(L, 1);
        zlua_log_level = static_cast<LogLevel>(level);
        log_cb(RETRO_LOG_DEBUG, "called log.SetLevel(%s)\n", getLogLevelName(level));
        return 0;
    }

    // TODO: use reflections when they get added to the language
    const char *getLogLevelName(int level)
    {
        switch (level)
        {
        case 0:
            return "LOG_NONE";
        case 1:
            return "LOG_CRITICAL";
        case 2:
            return "LOG_IMPORTANT";
        case 3:
            return "LOG_NORMAL";
        case 4:
            return "LOG_VERBOSE";
        case 5:
            return "LOG_DEBUG";

        default:
            return std::format("LOG_UNKNOWN {}", level).c_str();
        }
    }
}
