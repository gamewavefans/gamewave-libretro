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
        // {"LoadTexture", gl_load_texture},
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
        printf("\tcalled gl.SelectOSDMode(\"%s\") - UNIMPLEMENTED\n", mode);
        return 0;
    }
}
