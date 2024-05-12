#include "zlua_mock/gl.h"

int overlay_number = 1;
int texture_number = 1;
// TODO
static int gl_select_osd_mode(lua_State *L)
{
    const char *mode = luaL_checkstring(L, 1);
    printf("\tcalled gl.SelectOSDMode(\"%s\") - UNIMPLEMENTED\n", mode);
    return 0;
}
// TODO
static int gl_begin_scene(lua_State *L)
{
    printf("\tcalled gl.BeginScene() - UNIMPLEMENTED\n");
    return 0;
}

// TODO
static int gl_end_scene(lua_State *L)
{
    printf("\tcalled gl.EndScene() - UNIMPLEMENTED\n");
    return 0;
}

// TODO
static int gl_create_overlay_from_texture(lua_State *L)
{
    int i = luaL_checkint(L, 1);
    int ret = overlay_number++;
    printf("\tcalled gl.CreateOverlayFromTexture(%d) -> %d - UNIMPLEMENTED\n", i, ret);
    fflush(stdout);
    lua_pushnumber(L, (lua_Number)ret);
    return 1;
}

// TODO
static int gl_free_overlay(lua_State *L)
{
    int i = luaL_checkint(L, 1);
    printf("\tcalled gl.FreeOverlay(%d) - UNIMPLEMENTED\n", i);
    return 0;
}

// TODO
static int gl_load_texture(lua_State *L)
{
    int i = luaL_checkint(L, 1);
    const char *s = luaL_checkstring(L, 2);
    int ret = texture_number++;
    printf("\tcalled gl.LoadTexture(%d, \"%s\") -> %d - UNIMPLEMENTED\n", i, s, ret);
    lua_pushnumber(L, (lua_Number)ret);
    return 1;
}

// TODO
static int gl_free_texture(lua_State *L)
{
    int i = luaL_checkint(L, 1);
    printf("\tcalled gl.FreeTexture(%d) - UNIMPLEMENTED\n", i);
    return 0;
}

// {"AddTextureToOverlay", gl_add_texture_to_overlay},
// TODO
static int gl_add_texture_to_overlay(lua_State *L)
{
    int i = luaL_checkint(L, 1);
    int j = luaL_checkint(L, 2);
    printf("\tcalled gl.AddTextureToOverlay(%d, %d) - UNIMPLEMENTED\n", i, j);
    return 0;
}

// {"RemoveTextureFromOverlay", gl_},
// {"SetTextureActiveFrame", gl_},

// TODO
static int gl_set_parameters(lua_State *L)
{
    int i = luaL_checkint(L, 1);
    int j = luaL_checkint(L, 2);
    int k = luaL_checkint(L, 3);
    int l = luaL_checkint(L, 4);
    int m = luaL_checkint(L, 5);
    printf("\tcalled gl.SetParameters(%d, %d, %d, %d, %d) - UNIMPLEMENTED\n", i, j, k, l, m);
    return 0;
}

// TODO
static int gl_set_clip_info(lua_State *L)
{
    printf("\tcalled gl.SetClipInfo, redirecting to SetParameters\n");
    return gl_set_parameters(L);
}

// TODO
static int gl_set_zorder(lua_State *L)
{
    int i = luaL_checkint(L, 1);
    int j = luaL_checkint(L, 2);
    printf("\tcalled gl.SetZorder(%d, %d) - UNIMPLEMENTED\n", i, j);
    return 0;
}

// TODO
static int gl_set_visibility(lua_State *L)
{
    int i = luaL_checkint(L, 1);
    int j = luaL_checkint(L, 2);
    printf("\tcalled gl.SetVisibility(%d, %d) - UNIMPLEMENTED\n", i, j);
    return 0;
}
// {"SetPosition", gl_},
// {"GetZorder", gl_},
// {"GetVisibility", gl_},
// {"GetPosition", gl_},
// {"GetSize", gl_},
// {"ClearOSD", gl_},
// {"Show", gl_},
// {"number HasAnimations", gl_},
// {"DeleteAllAnimations", gl_},
// {"AddPositionAnimation", gl_},
// {"AddVisibilityAnimation", gl_},
// {"AddParabolaAnimation", gl_},
// {"AddBlinkingAnimation", gl_},
// {"AddAlphaAnimation", gl_},

static void dumpstack(lua_State *L)
{
    int top = lua_gettop(L);
    for (int i = -top; i <= top; i++)
    {
        if (i == 0)
        {
            continue;
        }
        printf("%d\t%s\t", i, lua_typename(L, lua_type(L, i)));
        switch (lua_type(L, i))
        {
        case LUA_TNUMBER:
            printf("%d\n", lua_tonumber(L, i));
            break;
        case LUA_TSTRING:
            printf("%s\n", lua_tostring(L, i));
            break;
        case LUA_TBOOLEAN:
            printf("%s\n", (lua_toboolean(L, i) ? "true" : "false"));
            break;
        case LUA_TNIL:
            printf("%s\n", "nil");
            break;
        default:
            printf("%p\n", lua_topointer(L, i));
            break;
        }
    }
    printf("\n");
}

// TODO
static int gl_create_texture_animation(lua_State *L)
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
    printf("\tcalled gl.CreateTextureAnimation(%d, %d, [%d][%d]int) - UNIMPLEMENTED\n", i, j, cnt_i, cnt_j);
    return 0;
}

// {"CreateEmptyTexture", gl_},
// {"BlitOverlay", gl_},
// {"BlitOverlayWithCR", gl_},
// {"SetTextureAlphaLevel", gl_},

static const luaL_reg gllib[] = {
    {"SelectOSDMode", gl_select_osd_mode},
    {"BeginScene", gl_begin_scene},
    {"EndScene", gl_end_scene},
    {"CreateOverlayFromTexture", gl_create_overlay_from_texture},
    {"FreeOverlay", gl_free_overlay},
    {"LoadTexture", gl_load_texture},
    {"FreeTexture", gl_free_texture},
    {"AddTextureToOverlay", gl_add_texture_to_overlay},
    // {"RemoveTextureFromOverlay", gl_},
    // {"SetTextureActiveFrame", gl_},
    {"SetClipInfo", gl_set_clip_info},
    {"SetParameters", gl_set_parameters},
    {"SetZorder", gl_set_zorder},
    {"SetVisibility", gl_set_visibility},
    // {"SetPosition", gl_},
    // {"GetZorder", gl_},
    // {"GetVisibility", gl_},
    // {"GetPosition", gl_},
    // {"GetSize", gl_},
    // {"ClearOSD", gl_},
    // {"Show", gl_},
    // {"number HasAnimations", gl_},
    // {"DeleteAllAnimations", gl_},
    // {"AddPositionAnimation", gl_},
    // {"AddVisibilityAnimation", gl_},
    // {"AddParabolaAnimation", gl_},
    // {"AddBlinkingAnimation", gl_},
    // {"AddAlphaAnimation", gl_},
    {"CreateTextureAnimation", gl_create_texture_animation},
    // {"CreateEmptyTexture", gl_},
    // {"BlitOverlay", gl_},
    // {"BlitOverlayWithCR", gl_},
    // {"SetTextureAlphaLevel", gl_},
    {NULL, NULL}};

int luaopen_gl(lua_State *L)
{
    printf("loaded gl\n");
    luaL_openlib(L, "gl", gllib, 0);
    return 1;
}
