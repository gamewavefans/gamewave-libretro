#pragma once

#include <cstdlib>

#include "libretro-common/include/libretro.h"

extern "C"
{
#include "lauxlib.h"
#include "lua.h"
#include "lualib.h"
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
