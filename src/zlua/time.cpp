#include "zlua/time.h"

namespace zlua::Time
{
    static const luaL_reg zlua_time_lib[] = {
        {"GetRealTime", zlua_time_get_real_time},
        {"Sleep", zlua_time_sleep},
        {nullptr, nullptr}};

    int zlua_time_loadlibrary(lua_State *L)
    {
        luaL_openlib(L, "time", zlua_time_lib, 0);
        return 1;
    }

    // TODO: check if this is the format that the games expect
    int zlua_time_get_real_time(lua_State *L)
    {
        using clock = std::chrono::system_clock;
        auto systemClock = clock::now();
        auto currentTime = static_cast<int>(clock::to_time_t(systemClock));
        log_cb(RETRO_LOG_DEBUG, "\tcalled time.GetRealTime() -> %d\n", currentTime);
        lua_pushnumber(L, (lua_Number)currentTime);
        return 1;
    }

    int zlua_time_sleep(lua_State *L)
    {
        int ms = luaL_checkint(L, 1);
        log_cb(RETRO_LOG_DEBUG, "\tcalled time.Sleep(%d)\n", ms);
        std::this_thread::sleep_for(std::chrono::milliseconds(ms));
        return 0;
    }
}
