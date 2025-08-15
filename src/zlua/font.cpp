#include "zlua/font.h"

namespace zlua::Font
{

    static const luaL_reg zlua_font_lib[] = {
        {"Load", zlua_font_load},
        {"Free", zlua_font_free},
        {"GetBuiltinFontID", zlua_font_get_builtin_font},
        {nullptr, nullptr}};

    int zlua_font_loadlibrary(lua_State *L)
    {
        luaL_openlib(L, "font", zlua_font_lib, 0);
        return 1;
    }

    int zlua_font_load(lua_State *L)
    {
        int i = luaL_checkint(L, 1);
        std::string s = luaL_checkstring(L, 2);

        auto location = zlua::RM::getResourcePath(i);
        auto targetPath = getPath((*location / s).string());

        int ret = 0;
        log_cb(RETRO_LOG_DEBUG, "\tcalled font.Load(%d, \"%s\") (\"%s\") -> %d - UNIMPLEMENTED\n", i, s.c_str(), targetPath.c_str(), ret);
        // TODO
        lua_pushnumber(L, (lua_Number)ret);
        return 1;
    }

    int zlua_font_free(lua_State *L)
    {
        int id = luaL_checkint(L, 1);
        log_cb(RETRO_LOG_DEBUG, "\tcalled font.Free(%d)", id);
        return 0;
    }

    int zlua_font_get_builtin_font(lua_State *L)
    {
        // TODO
        int ret = 1111111;
        log_cb(RETRO_LOG_DEBUG, "\tcalled font.GetBuiltinFontID() -> %d - UNIMPLEMENTED\n", ret);
        lua_pushnumber(L, (lua_Number)ret);
        return 1;
    }
}
