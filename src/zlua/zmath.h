#pragma once

#include <cstdlib>

extern "C"
{
#include "subprojects/lua_gamewave/include/lauxlib.h"
#include "subprojects/lua_gamewave/include/lua.h"
#include "subprojects/lua_gamewave/include/lualib.h"
}

extern int luaopen_zmath(lua_State *L);
extern int zmath_mod(lua_State *L);
