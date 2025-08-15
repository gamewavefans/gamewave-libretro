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
audio
    int Load(int i, str s)
    Unload(int i)
    Play(int i , int j)
*/
namespace zlua::Audio
{
    extern "C"
    {
        int zlua_audio_loadlibrary(lua_State *L);
        int zlua_audio_load(lua_State *L);
        int zlua_audio_unload(lua_State *L);
        int zlua_audio_play(lua_State *L);
    }
}
