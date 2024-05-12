#pragma once

#include <thread>
#include <chrono>

#include <string>
#include <format>

#include "libretro-common/include/libretro.h"

extern "C"
{
#include "lua_gamewave/include/lauxlib.h"
#include "lua_gamewave/include/lua.h"
#include "lua_gamewave/include/lualib.h"
}

#include "global.h"

namespace zlua::Time
{
    extern "C"
    {
        int zlua_time_loadlibrary(lua_State *L);

        /**
         * @brief Get the current real time in milliseconds
         *
         * @param L Lua state
         * @return current UNIX time
         */
        int zlua_time_get_real_time(lua_State *L);

        /**
         * @brief Sleep for a given amount of time in milliseconds
         *
         * @param L Lua state
         * @return 0
         */
        int zlua_time_sleep(lua_State *L);
    }
}
