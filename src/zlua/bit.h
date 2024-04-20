#pragma once

#include <stdio.h>
#include <string.h>

extern "C"
{
#include "subprojects/lua_gamewave/include/lauxlib.h"
#include "subprojects/lua_gamewave/include/lua.h"
#include "subprojects/lua_gamewave/include/lualib.h"
}

extern int luaopen_bit(lua_State *L);
