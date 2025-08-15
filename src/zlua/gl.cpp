#include "zlua/gl.h"

namespace zlua::GL
{
    int overlay_number = {0};
    static const luaL_reg zlua_gl_lib[] = {
        // {"AddAlphaAnimation", gl_},
        // {"AddBlinkingAnimation", gl_},
        // {"AddParabolaAnimation", gl_},
        // {"AddPositionAnimation", gl_},
        {"AddTextureToOverlay", zlua_gl_add_texture_to_overlay},
        // {"AddVisibilityAnimation", gl_},
        {"BeginScene", zlua_gl_begin_scene},
        // {"BlitOverlay", gl_},
        // {"BlitOverlayWithCR", gl_},
        // {"ClearOSD", gl_},
        // {"CreateEmptyTexture", gl_},
        {"CreateOverlayFromTexture", zlua_gl_create_overlay_from_texture},
        {"CreateTextureAnimation", zlua_gl_create_texture_animation},
        // {"DeleteAllAnimations", gl_},
        {"EndScene", zlua_gl_end_scene},
        {"FreeOverlay", zlua_gl_free_overlay},
        {"FreeTexture", zlua_gl_free_texture},
        // {"GetPosition", gl_},
        // {"GetSize", gl_},
        // {"GetVisibility", gl_},
        // {"GetZorder", gl_},
        {"LoadTexture", zlua_gl_load_texture},
        // {"number HasAnimations", gl_},
        // {"RemoveTextureFromOverlay", gl_},
        {"SelectOSDMode", zlua_gl_select_osd_mode},
        {"SetClipInfo", zlua_gl_set_parameters},
        {"SetParameters", zlua_gl_set_parameters},
        // {"SetPosition", gl_},
        // {"SetTextureActiveFrame", gl_},
        // {"SetTextureAlphaLevel", gl_},
        {"SetVisibility", zlua_gl_set_visibility},
        // {"SetZorder", gl_set_zorder},
        {"Show", zlua_gl_show},
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

    int zlua_gl_begin_scene([[maybe_unused]] lua_State *L)
    {
        log_cb(RETRO_LOG_DEBUG, "\tcalled gl.BeginScene() - UNIMPLEMENTED\n");
        return 0;
    }

    int zlua_gl_end_scene([[maybe_unused]] lua_State *L)
    {
        log_cb(RETRO_LOG_DEBUG, "\tcalled gl.EndScene() - UNIMPLEMENTED\n");
        return 0;
    }

    int zlua_gl_create_overlay_from_texture(lua_State *L)
    {
        int i = luaL_checkint(L, 1);
        int ret = overlay_number++;
        log_cb(RETRO_LOG_DEBUG, "\tcalled gl.CreateOverlayFromTexture(%d) -> %d - UNIMPLEMENTED\n", i, ret);
        lua_pushnumber(L, (lua_Number)ret);
        return 1;
    }

    int zlua_gl_free_overlay(lua_State *L)
    {
        int id = luaL_checkint(L, 1);
        log_cb(RETRO_LOG_DEBUG, "\tcalled gl.FreeOverlay(%d) - UNIMPLEMENTED\n", id);
        return 0;
    }

    int zlua_gl_load_texture(lua_State *L)
    {
        int i = luaL_checkint(L, 1);
        std::string s = luaL_checkstring(L, 2);

        auto location = zlua::RM::getResourcePath(i);
        auto targetPath = getPath((*location / s).string());

        int ret = 0;
        log_cb(RETRO_LOG_DEBUG, "\tcalled gl.LoadTexture(%d, \"%s\") (\"%s\") -> %d - UNIMPLEMENTED\n", i, s.c_str(), targetPath.c_str(), ret);
        // TODO
        lua_pushnumber(L, (lua_Number)ret);
        return 1;
    }

    int zlua_gl_free_texture(lua_State *L)
    {
        int id = luaL_checkint(L, 1);
        log_cb(RETRO_LOG_DEBUG, "\tcalled gl.FreeTexture(%d) - UNIMPLEMENTED\n", id);
        return 0;
    }

    int zlua_gl_add_texture_to_overlay(lua_State *L)
    {
        int i = luaL_checkint(L, 1);
        int j = luaL_checkint(L, 2);
        log_cb(RETRO_LOG_DEBUG, "\tcalled gl.AddTextureToOverlay(%d, %d) - UNIMPLEMENTED\n", i, j);
        return 0;
    }

    int zlua_gl_set_parameters(lua_State *L)
    {
        int i = luaL_checkint(L, 1);
        int j = luaL_checkint(L, 2);
        int k = luaL_checkint(L, 3);
        int l = luaL_checkint(L, 4);
        int m = luaL_checkint(L, 5);

        log_cb(RETRO_LOG_DEBUG, "\tcalled gl.SetParameters(%d, %d, %d, %d, %d) - UNIMPLEMENTED\n", i, j, k, l, m);
        return 0;
    }

    int zlua_gl_set_visibility(lua_State *L)
    {
        int id = luaL_checkint(L, 1);
        int j = luaL_checkint(L, 2);
        log_cb(RETRO_LOG_DEBUG, "\tcalled gl.SetVisibility(%d, %d) - UNIMPLEMENTED\n", id, j);
        return 0;
    }

    int zlua_gl_show(lua_State *L)
    {
        int id = luaL_checkint(L, 1);
        log_cb(RETRO_LOG_DEBUG, "\tcalled gl.Show(%d) - UNIMPLEMENTED\n", id);
        return 0;
    }

    int zlua_gl_create_texture_animation(lua_State *L)
    {
        int top = lua_gettop(L); // 3lua_getfield
        int i = luaL_checkint(L, 1);
        int j = luaL_checkint(L, 2);

        lua_pushnil(L);
        int cnt_i = 0;
        int cnt_j = 0;
        while (lua_next(L, -2) != 0)
        {
            cnt_i++;
            // printf("%d a: %s:%s: %d\n", cnt_i, lua_typename(L, lua_type(L, -2)), lua_typename(L, lua_type(L, -1)), luaL_checkint(L, -2));
            int key = luaL_checkint(L, -2);
            lua_pushnil(L);
            cnt_j = 0;

            while (lua_next(L, -2) != 0)
            {
                cnt_j++;
                // read key and value
                // printf("\t%d b: %d:%d\n", cnt_j++, luaL_checkint(L, -2), luaL_checkint(L, -1));
                lua_pop(L, 1);
            }
            lua_pop(L, 1);
        }
        log_cb(RETRO_LOG_DEBUG, "\tcalled gl.CreateTextureAnimation(%d, %d, [%d][%d]int) - UNIMPLEMENTED\n", i, j, cnt_i, cnt_j);

        return 0;
    }
}
