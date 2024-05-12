#pragma once

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
#include "zlua/zmath.h"

namespace zlua::Bit
{
    extern "C"
    {
        int zlua_bit_loadlibrary(lua_State *L);

        int zlua_bit_bnot(lua_State *L);
        int zlua_bit_band(lua_State *L);
        int zlua_bit_bor(lua_State *L);
        int zlua_bit_bxor(lua_State *L);
        int zlua_bit_lshift(lua_State *L);
        int zlua_bit_rshift(lua_State *L);
        int zlua_bit_arshift(lua_State *L);
    }
}
