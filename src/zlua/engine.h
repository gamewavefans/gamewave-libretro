#pragma once

#include <format>

#include "libretro-common/include/libretro.h"

extern "C"
{
#include "lua_gamewave/include/lauxlib.h"
#include "lua_gamewave/include/lua.h"
#include "lua_gamewave/include/lualib.h"
}

#include "global.h"

/*
- `engine`
  - `ZMM_SetLeakDebugMode(int enabled)`
  - `ZMM_SetCheckPoint()`
  - `ZMM_VerifyCheckPoint()`
  - `int ZMM_GetTotalAllocMemory()`
  - `int ZMM_GetTotalFreeMemory()`
  - `int ZMM_GetMaxFreeMemory()`
  - `DR_SetEnable(int i)`
  - `DR_SetDebug(int i)`
  - `DR_SetAbsoluteCapping(int i, int j, int k)`
  - `DR_ClearPairCappings(int i, int j, int k)`
  - `DR_AddPairCapping()`
  - `OpenTray()`
  - `CloseTray()`
  - `EjectTray()`
    - exactly the same as `OpenTray()`
  - `int GetTrayState()`
  - `SoftwareReset()`
  - `WaitForDisk()`
  - `int GetNumOverlays()`
  - `int GetNumTextures()`
  - `str Version()`
    - returns something like `1.01.3.xxxxxx`
  - `SetLineTraceMode(bool enabled)`
  - `int GetLineTraceMode()`
  */
namespace zlua::Engine
{
    extern "C"
    {
        int zlua_engine_loadlibrary(lua_State *L);

        int zlua_engine_zmm_set_leak_debug_mode(lua_State *L);
        int zlua_engine_zmm_set_check_point(lua_State *L);
        int zlua_engine_zmm_verify_check_point(lua_State *L);
        int zlua_engine_zmm_get_total_alloc_memory(lua_State *L);
        int zlua_engine_zmm_get_total_free_memory(lua_State *L);
        int zlua_engine_zmm_get_max_free_memory(lua_State *L);
        int zlua_engine_dr_set_enable(lua_State *L);
        int zlua_engine_dr_set_debug(lua_State *L);
        int zlua_engine_dr_set_absolute_capping(lua_State *L);
        int zlua_engine_dr_clear_pair_cappings(lua_State *L);
        int zlua_engine_dr_add_pair_capping(lua_State *L);
        int zlua_engine_open_tray(lua_State *L);
        int zlua_engine_close_tray(lua_State *L);
        int zlua_engine_eject_tray(lua_State *L);
        int zlua_engine_get_tray_state(lua_State *L);
        int zlua_engine_software_reset(lua_State *L);
        int zlua_engine_wait_for_disk(lua_State *L);
        int zlua_engine_get_num_overlays(lua_State *L);
        int zlua_engine_get_num_textures(lua_State *L);
        int zlua_engine_version(lua_State *L);
        int zlua_engine_set_line_trace_mode(lua_State *L);
        int zlua_engine_get_line_trace_mode(lua_State *L);
    }
}
