#include "zlua/audio.h"

namespace zlua::Audio
{
    static const luaL_reg zlua_audio_lib[] = {
        {"Load", zlua_audio_load},
        // {"Unload", zlua_audio_unload},
        // {"Play", zlua_audio_play},
        {nullptr, nullptr}};

    int zlua_audio_loadlibrary(lua_State *L)
    {
        luaL_openlib(L, "audio", zlua_audio_lib, 0);
        return 1;
    }

    int zlua_audio_load(lua_State *L)
    {
        int i = luaL_checkint(L, 1);
        std::string s = luaL_checkstring(L, 2);

        auto location = zlua::RM::getResourcePath(i);
        auto targetPath = getPath((*location / s).string());

        int ret = 0;
        log_cb(RETRO_LOG_DEBUG, "\tcalled audio.Load(%d, \"%s\") (\"%s\") -> %d - UNIMPLEMENTED\n", i, s.c_str(), targetPath.c_str(), ret);
        // TODO
        lua_pushnumber(L, (lua_Number)ret);
        return 1;
    }

    int zlua_audio_unload(lua_State *L)
    {
    }

    int zlua_audio_play(lua_State *L)
    {
    }
}
