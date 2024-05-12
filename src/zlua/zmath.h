#pragma once

#include <cstdlib>

#include "libretro-common/include/libretro.h"

extern "C"
{
#include "lua_gamewave/include/lauxlib.h"
#include "lua_gamewave/include/lua.h"
#include "lua_gamewave/include/lualib.h"
}

#include "global.h"

namespace zlua::ZMath
{
    extern "C"
    {
        int zlua_zmath_loadlibrary(lua_State *L);

        int zlua_zmath_mod(lua_State *L);
        int zlua_zmath_rand(lua_State *L);
        int zlua_zmath_rand_seed(lua_State *L);
    }
}
