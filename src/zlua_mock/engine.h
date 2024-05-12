#pragma once

#ifdef __cplusplus
extern "C"
{
#endif
#include "lua_gamewave/include/lauxlib.h"
#include "lua_gamewave/include/lua.h"
#include "lua_gamewave/include/lualib.h"
#ifdef __cplusplus
}
#endif

static int engine_zmm_get_total_free_memory(lua_State *L);
static int engine_version(lua_State *L);

extern int luaopen_engine(lua_State *L);
