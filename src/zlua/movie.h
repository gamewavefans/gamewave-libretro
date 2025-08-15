#pragma once

#include <vector>
#include <filesystem>

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
movie
    int Load(str path)
        path is a full name, movie doesn't use rm library
    SetLoop(int i)
    Play()
    Stop(int i)
    Resume()
    int GetState()
        returns 0 if it's still playing, needs to be checked in a loop
*/
extern std::filesystem::path GameBasePath;

namespace zlua::Movie
{
    namespace fs = std::filesystem;

    extern "C"
    {
        int zlua_movie_loadlibrary(lua_State *L);
        // int zlua_movie_movie_get_state(lua_State *L);
        int zlua_movie_movie_load(lua_State *L);
        // int zlua_movie_movie_play(lua_State *L);
        // int zlua_movie_movie_resume(lua_State *L);
        // int zlua_movie_movie_set_loop(lua_State *L);
        // int zlua_movie_movie_stop(lua_State *L);
    }
}
