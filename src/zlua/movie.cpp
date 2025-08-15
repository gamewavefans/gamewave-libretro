#include "zlua/movie.h"

namespace zlua::Movie
{
    static const luaL_reg zlua_movie_lib[] = {
        {"Load", zlua_movie_movie_load},
        // {"SetLoop", zlua_movie_movie_set_loop},
        // {"Play", zlua_movie_movie_play},
        // {"Stop", zlua_movie_movie_stop},
        // {"Resume", zlua_movie_movie_resume},
        // {"GetState", zlua_movie_movie_get_state},
        {nullptr, nullptr}};

    int zlua_movie_loadlibrary(lua_State *L)
    {
        luaL_openlib(L, "movie", zlua_movie_lib, 0);
        return 1;
    }

    // int zlua_movie_movie_get_state(lua_State *L);

    int zlua_movie_movie_load(lua_State *L)
    {
        std::string name = luaL_checkstring(L, 1);
        auto relativeName = name;
        if (relativeName != "" && relativeName[0] == '/')
        {
            relativeName.erase(0, 1);
        }
        // TODO: this won't work on Linux, think how to incorporate getPath here
        std::shared_ptr<fs::path> path = std::make_shared<fs::path>(GameBasePath);
        *path /= relativeName;

        // getPath(path);
        int ret = 0;
        log_cb(RETRO_LOG_DEBUG, "\tcalled movie.Load(\"%s\") (%s)-> %d - UNIMPLEMENTED\n", name.c_str(), path.get()->c_str(), ret);
        lua_pushnumber(L, (lua_Number)ret);
        return 1;
    }

    // int zlua_movie_movie_play(lua_State *L);
    // int zlua_movie_movie_resume(lua_State *L);
    // int zlua_movie_movie_set_loop(lua_State *L);
    // int zlua_movie_movie_stop(lua_State *L);
}
