#pragma once

#include "libretro-common/include/libretro.h"

extern "C"
{
#include "lauxlib.h"
#include "lua.h"
#include "lualib.h"
}

#include "helpers/filepath.h"
#include "global.h"

#include "zlua/rm.h"

/*
font
    int Load(int loc, str filepath)
    Free(int i)
    int GetBuiltinFontID()
        the builtin font is called f_1955_s_22_m_4633_32_128.dat
*/
namespace zlua::Font
{
    extern "C"
    {
        int zlua_font_loadlibrary(lua_State *L);
        int zlua_font_load(lua_State *L);
        int zlua_font_free(lua_State *L);
        int zlua_font_get_builtin_font(lua_State *L);
    }
}
