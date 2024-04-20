#include "zlua/bit.h"
#include "zlua/zmath.h"

static int bit_bnot(lua_State *L)
{
    int i = luaL_checkint(L, 1);
    int ret = ~i;
    printf("\tcalled bit.bnot(%d) -> %d\n", i, ret);
    lua_pushnumber(L, (lua_Number)ret);
    return 1;
}

static int bit_band(lua_State *L)
{
    int top = lua_gettop(L);
    int i = luaL_checkint(L, 1);
    int ret = i;
    char buff[255] = "";
    for (int j = 2; j <= top; j++)
    {
        int val = luaL_checkint(L, j);
        char tmp[64];
        sprintf(tmp, ", %d", val);
        strcat(buff, tmp);
        ret = ret & val;
    }
    printf("\tcalled bit.band(%d%s) -> %d\n", i, buff, ret);
    lua_pushnumber(L, (lua_Number)ret);
    return 1;
}

static int bit_bor(lua_State *L)
{
    int top = lua_gettop(L);
    int i = luaL_checkint(L, 1);
    int ret = i;
    char buff[255] = "";
    for (int j = 2; j <= top; j++)
    {
        int val = luaL_checkint(L, j);
        char tmp[64];
        sprintf(tmp, ", %d", val);
        strcat(buff, tmp);
        ret = ret | val;
    }
    printf("\tcalled bit.bor(%d%s) -> %d\n", i, buff, ret);
    lua_pushnumber(L, (lua_Number)ret);
    return 1;
}

static int bit_bxor(lua_State *L)
{
    int top = lua_gettop(L);
    int i = luaL_checkint(L, 1);
    int ret = i;
    char buff[255] = "";
    for (int j = 2; j <= top; j++)
    {
        int val = luaL_checkint(L, j);
        char tmp[32];
        sprintf(tmp, ", %d", val);
        strcat(buff, tmp);
        ret = ret ^ val;
    }
    printf("\tcalled bit.bxor(%d%s) -> %d\n", i, buff, ret);
    lua_pushnumber(L, (lua_Number)ret);
    return 1;
}

static int bit_lshift(lua_State *L)
{
    int i = luaL_checkint(L, 1);
    int j = luaL_checkint(L, 2);
    // this & was in the original engine, dunno why
    int ret = i << (j & 0x1f);
    printf("\tcalled bit.lshift(%d, %d) -> %d\n", i, j, ret);
    lua_pushnumber(L, (lua_Number)ret);
    return 1;
}

static int bit_rshift(lua_State *L)
{
    unsigned int i = luaL_checkint(L, 1);
    unsigned int j = luaL_checkint(L, 2);
    // this & was in the original engine, dunno why
    int ret = i >> (j & 0x1f);
    printf("\tcalled bit.rshift(%u, %u) -> %d\n", i, j, ret);
    lua_pushnumber(L, (lua_Number)ret);
    return 1;
}

// TODO is this the correct way of signed shift?
static int bit_arshift(lua_State *L)
{
    int i = luaL_checkint(L, 1);
    unsigned int j = luaL_checkint(L, 2);
    // this & was in the original engine, dunno why
    int ret = i >> (j & 0x1f);
    printf("\tcalled bit.rshift(%d, %u) -> %d\n", i, j, ret);
    lua_pushnumber(L, (lua_Number)ret);
    return 1;
}

static const luaL_reg bitlib[] = {
    {"bnot", bit_bnot},
    {"band", bit_band},
    {"bor", bit_bor},
    {"bxor", bit_bxor},
    {"lshift", bit_lshift},
    {"rshift", bit_rshift},
    {"arshift", bit_arshift},
    // the same as zmath.mod
    {"mod", zmath_mod},
    {NULL, NULL}};

int luaopen_bit(lua_State *L)
{
    printf("loaded bit\n");
    luaL_openlib(L, "bit", bitlib, 0);
    return 1;
}
