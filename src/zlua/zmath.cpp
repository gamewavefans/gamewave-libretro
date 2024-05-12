#include "zlua/zmath.h"
namespace zlua::ZMath
{

    static const luaL_reg zlua_zmath_lib[] = {
        {"Mod", zlua_zmath_mod},
        {"Rand", zlua_zmath_rand},
        {"RandSeed", zlua_zmath_rand_seed},
        {nullptr, nullptr}};

    int zlua_zmath_loadlibrary(lua_State *L)
    {
        luaL_openlib(L, "zmath", zlua_zmath_lib, 0);
        return 1;
    }

    int zlua_zmath_mod(lua_State *L)
    {
        int i = luaL_checkint(L, 1);
        int j = luaL_checkint(L, 2);
        int ret = i % j;
        log_cb(RETRO_LOG_DEBUG, "\tcalled zmath.Mod(%d, %d) -> %d\n", i, j, ret);
        lua_pushnumber(L, (lua_Number)ret);
        return 1;
    }

    int zlua_zmath_rand(lua_State *L)
    {
        int min = luaL_checkint(L, 1);
        int max = luaL_checkint(L, 2);
        int ret = min + (rand() % (max + 1 - min));
        log_cb(RETRO_LOG_DEBUG, "\tcalled zmath.Rand(%d, %d) -> %d\n", min, max, ret);
        lua_pushnumber(L, (lua_Number)ret);
        return 1;
    }

    int zlua_zmath_rand_seed(lua_State *L)
    {
        int seed = luaL_checkint(L, 1);
        srand(seed);
        log_cb(RETRO_LOG_DEBUG, "\tcalled zmath.RandSeed(%d)\n", seed);
        return 0;
    }
}
