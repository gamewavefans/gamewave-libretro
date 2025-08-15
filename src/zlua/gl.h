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
- `gl`
  - `SelectOSDMode(str mode)`
    - possible modes: `844`, `655`, `4444`, `4633`
  - `BeginScene()`
  - `EndScene()`
  - `int CreateOverlayFromTexture(int i)`
  - `FreeOverlay(int i)`
  - `int LoadTexture(int i, str s)`
  - `FreeTexture(int i)`
  - `AddTextureToOverlay(int i, int j)`
  - `RemoveTextureFromOverlay(int i, int j)`
  - `SetTextureActiveFrame(int i, int j)`
  - `SetClipInfo(int i, int j, int k, int l, int m)`
  - `SetParameters(int i, int j, int k, int l, int m)`
    - identical to the `SetClipInfo()`
  - `SetZorder(int i, int j)`
  - `SetVisibility(int i, int j)`
  - `SetPosition(int i, int j, int k)`
  - `int GetZorder(int i)`
  - `int GetVisibility(int i)`
  - `int, int GetPosition(int i)`
  - `int, int GetSize(int i)`
  - `ClearOSD()`
  - `Show(int i)`
  - `int HasAnimations(int i)`
  - `DeleteAllAnimations(int i)`
  - `AddPositionAnimation(int i, int j, int k, int l, int m, int n, int o)`
  - `AddVisibilityAnimation(int i, int j, int k)`
  - `AddParabolaAnimation(int i, int j, int k, int l, int m, int n, int o, int p, int q, int r, int s, int t)`
  - `AddBlinkingAnimation(int i, int j, int k, int l, int m)`
  - `AddAlphaAnimation(int i, int j, int k, int l)`
  - `CreateTextureAnimation(int i, int j, int [][]t)`
    - TODO tables, I don't know if I read this correctly
    - expects a table of 11 tables of 3 ints, `int [11][3]`
  - `int CreateEmptyTexture(int i, int j, str s)`
  - `BlitOverlay(int i, int j, int k, int l)`
    - with optional `int m` and `int n`
  - `BlitOverlayWithCR(int i, int j, int k, int l)`
    - with optional `int m`, `int n`, mnopqrstuvw
  - `SetTextureAlphaLevel(int i, int j)`
*/
namespace zlua::GL
{
  extern "C"
  {
    int zlua_gl_loadlibrary(lua_State *L);

    int zlua_gl_select_osd_mode(lua_State *L);
    int zlua_gl_begin_scene(lua_State *L);
    int zlua_gl_end_scene(lua_State *L);
    int zlua_gl_create_overlay_from_texture(lua_State *L);
    int zlua_gl_free_overlay(lua_State *L);
    int zlua_gl_load_texture(lua_State *L);
    int zlua_gl_free_texture(lua_State *L);
    int zlua_gl_add_texture_to_overlay(lua_State *L);
    // int zlua_gl_remove_texture_from_overlay(lua_State *L);
    // int zlua_gl_set_texture_active_frame(lua_State *L);
    int zlua_gl_set_parameters(lua_State *L);
    // int zlua_gl_set_zorder(lua_State *L);
    int zlua_gl_set_visibility(lua_State *L);
    // int zlua_gl_set_position(lua_State *L);
    // int zlua_gl_get_zorder(lua_State *L);
    // int zlua_gl_get_visibility(lua_State *L);
    // int zlua_gl_get_position(lua_State *L);
    // int zlua_gl_get_size(lua_State *L);
    // int zlua_gl_clear_osd(lua_State *L);
    int zlua_gl_show(lua_State *L);
    // int zlua_gl_has_animations(lua_State *L);
    // int zlua_gl_delete_all_animations(lua_State *L);
    // int zlua_gl_add_position_animation(lua_State *L);
    // int zlua_gl_add_visibility_animation(lua_State *L);
    // int zlua_gl_add_parabola_animation(lua_State *L);
    // int zlua_gl_add_blinking_animation(lua_State *L);
    // int zlua_gl_add_alpha_animation(lua_State *L);
    int zlua_gl_create_texture_animation(lua_State *L);
    // int zlua_gl_create_empty_texture(lua_State *L);
    // int zlua_gl_blit_overlay(lua_State *L);
    // int zlua_gl_blit_overlay_with_cr(lua_State *L);
    // int zlua_gl_set_texture_alpha_level(lua_State *L);
  }
}
