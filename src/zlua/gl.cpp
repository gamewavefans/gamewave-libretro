#include "zlua/gl.h"

namespace zlua::GL
{
    static const luaL_reg zlua_gl_lib[] = {
        // {"AddAlphaAnimation", gl_},
        // {"AddBlinkingAnimation", gl_},
        // {"AddParabolaAnimation", gl_},
        // {"AddPositionAnimation", gl_},
        // {"AddTextureToOverlay", gl_add_texture_to_overlay},
        // {"AddVisibilityAnimation", gl_},
        // {"BeginScene", gl_begin_scene},
        // {"BlitOverlay", gl_},
        // {"BlitOverlayWithCR", gl_},
        // {"ClearOSD", gl_},
        // {"CreateEmptyTexture", gl_},
        // {"CreateOverlayFromTexture", gl_create_overlay_from_texture},
        // {"CreateTextureAnimation", gl_create_texture_animation},
        // {"DeleteAllAnimations", gl_},
        // {"EndScene", gl_end_scene},
        // {"FreeOverlay", gl_free_overlay},
        // {"FreeTexture", gl_free_texture},
        // {"GetPosition", gl_},
        // {"GetSize", gl_},
        // {"GetVisibility", gl_},
        // {"GetZorder", gl_},
        {"LoadTexture", zlua_gl_load_texture},
        // {"number HasAnimations", gl_},
        // {"RemoveTextureFromOverlay", gl_},
        {"SelectOSDMode", zlua_gl_select_osd_mode},
        // {"SetClipInfo", gl_set_clip_info},
        // {"SetParameters", gl_set_parameters},
        // {"SetPosition", gl_},
        // {"SetTextureActiveFrame", gl_},
        // {"SetTextureAlphaLevel", gl_},
        // {"SetVisibility", gl_set_visibility},
        // {"SetZorder", gl_set_zorder},
        // {"Show", gl_},
        {nullptr, nullptr}};

    int zlua_gl_loadlibrary(lua_State *L)
    {
        luaL_openlib(L, "gl", zlua_gl_lib, 0);
        return 1;
    }

    int zlua_gl_select_osd_mode(lua_State *L)
    {
        const char *mode = luaL_checkstring(L, 1);
        log_cb(RETRO_LOG_DEBUG, "\tcalled gl.SelectOSDMode(\"%s\") - UNIMPLEMENTED\n", mode);
        return 0;
    }

    int zlua_gl_load_texture(lua_State *L)
    {
        int i = luaL_checkint(L, 1);
        std::string s = luaL_checkstring(L, 2);

        auto location = zlua::RM::getResourcePath(i);
        auto targetPath = *location / s;

        int ret = 0;
        log_cb(RETRO_LOG_DEBUG, "\tcalled gl.LoadTexture(%d, \"%s\") (\"%s\") -> %d - UNIMPLEMENTED\n", i, s.c_str(), targetPath.c_str(), ret);
        // TODO
        lua_pushnumber(L, (lua_Number)ret);
        return 1;
    }

}
