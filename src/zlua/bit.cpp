#include "zlua/bit.h"

namespace zlua::Bit
{
    static const luaL_reg zlua_bit_lib[] = {
        {"bnot", zlua_bit_bnot},
        {"band", zlua_bit_band},
        {"bor", zlua_bit_bor},
        {"bxor", zlua_bit_bxor},
        {"lshift", zlua_bit_lshift},
        {"rshift", zlua_bit_rshift},
        {"arshift", zlua_bit_arshift},
        {"mod", zlua::ZMath::zlua_zmath_mod},
        {nullptr, nullptr}};

    int zlua_bit_loadlibrary(lua_State *L)
    {
        luaL_openlib(L, "bit", zlua_bit_lib, 0);
        return 1;
    }

    int zlua_bit_bnot(lua_State *L)
    {
        int i = luaL_checkint(L, 1);
        int ret = ~i;
        log_cb(RETRO_LOG_DEBUG, "\tcalled bit.bnot(%d) -> %d\n", i, ret);
        lua_pushnumber(L, (lua_Number)ret);
        return 1;
    }

    int zlua_bit_band(lua_State *L)
    {
        int top = lua_gettop(L);
        int i = luaL_checkint(L, 1);
        int ret = {i};
        std::string buff{};
        for (int j = 2; j <= top; j++)
        {
            i = luaL_checkint(L, j);
            buff += std::format(", {}", i);
            ret &= i;
        }
        log_cb(RETRO_LOG_DEBUG, "\tcalled bit.band(%d, %d) -> %d\n", i, buff, ret);
        lua_pushnumber(L, (lua_Number)ret);
        return 1;
    }

    int zlua_bit_bor(lua_State *L)
    {
        int top = lua_gettop(L);
        int i = luaL_checkint(L, 1);
        int ret = {i};
        std::string buff{};
        for (int j = 2; j <= top; j++)
        {
            i = luaL_checkint(L, j);
            buff += std::format(", {}", i);
            ret |= i;
        }
        log_cb(RETRO_LOG_DEBUG, "\tcalled bit.bor(%d, %d) -> %d\n", i, buff, ret);
        lua_pushnumber(L, (lua_Number)ret);
        return 1;
    }

    int zlua_bit_bxor(lua_State *L)
    {
        int top = lua_gettop(L);
        int i = luaL_checkint(L, 1);
        int ret = {i};
        std::string buff{};
        for (int j = 2; j <= top; j++)
        {
            i = luaL_checkint(L, j);
            buff += std::format(", {}", i);
            ret ^= i;
        }
        log_cb(RETRO_LOG_DEBUG, "\tcalled bit.bxor(%d, %d) -> %d\n", i, buff, ret);
        lua_pushnumber(L, (lua_Number)ret);
        return 1;
    }

    int zlua_bit_lshift(lua_State *L)
    {
        int i = luaL_checkint(L, 1);
        int j = luaL_checkint(L, 2);
        // this & was in the original engine, dunno why
        int ret = i << (j & 0x1f);
        log_cb(RETRO_LOG_DEBUG, "\tcalled bit.lshift(%d, %d) -> %d\n", i, j, ret);
        lua_pushnumber(L, (lua_Number)ret);
        return 1;
    }

    int zlua_bit_rshift(lua_State *L)
    {
        int i = luaL_checkint(L, 1);
        int j = luaL_checkint(L, 2);
        // this was in the original engine, dunno why
        int ret = i >> (j & 0x1f);
        log_cb(RETRO_LOG_DEBUG, "\tcalled bit.rshift(%d, %d) -> %d\n", i, j, ret);
        lua_pushnumber(L, (lua_Number)ret);
        return 1;
    }

    // TODO: is this the correct way of signed shift?
    int zlua_bit_arshift(lua_State *L)
    {
        int i = luaL_checkint(L, 1);
        int j = luaL_checkint(L, 2);
        // this was in the original engine, dunno why
        int ret = i >> (j & 0x1f);
        log_cb(RETRO_LOG_DEBUG, "\tcalled bit.rshift(%d, %d) -> %d\n", i, j, ret);
        lua_pushnumber(L, (lua_Number)ret);
        return 1;
    }
}
