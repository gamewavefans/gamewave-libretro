#include "zlua/engine.h"

namespace zlua::Engine
{
    static const luaL_reg zlua_engine_lib[] = {
        // {"CloseTray", engine_},
        // {"DR_AddPairCapping", engine_},
        // {"DR_ClearPairCappings", engine_},
        // {"DR_SetAbsoluteCapping", engine_},
        // {"DR_SetDebug", engine_},
        // {"DR_SetEnable", engine_},
        // {"EjectTray", engine_},
        // {"GetLineTraceMode", engine_},
        // {"GetNumOverlays", engine_},
        // {"GetNumTextures", engine_},
        // {"GetTrayState", engine_},
        // {"OpenTray", engine_},
        // {"SetLineTraceMode", engine_},
        // {"SoftwareReset", engine_},
        {"Version", zlua_engine_version},
        // {"WaitForDisk", engine_},
        // {"ZMM_GetMaxFreeMemory", engine_},
        // {"ZMM_GetTotalAllocMemory", engine_},
        {"ZMM_GetTotalFreeMemory", zlua_engine_zmm_get_total_free_memory},
        // {"ZMM_SetCheckPoint", engine_},
        // {"ZMM_SetLeakDebugMode", engine_},
        // {"ZMM_VerifyCheckPoint", engine_},
        {nullptr, nullptr}};

    int zlua_engine_loadlibrary(lua_State *L)
    {
        luaL_openlib(L, "engine", zlua_engine_lib, 0);
        return 1;
    }

    int zlua_engine_version(lua_State *L)
    {
        log_cb(RETRO_LOG_DEBUG, "\tcalled engine.Version() -> 0.0.1.emuwave - UNIMPLEMENTED\n");
        lua_pushstring(L, "0.0.1.emuwave");
        return 1;
    }

    // TODO:
    int zlua_engine_zmm_get_total_free_memory(lua_State *L)
    {
        log_cb(RETRO_LOG_DEBUG, "\tcalled engine.GetTotalFreeMemory() -> 1234 - UNIMPLEMENTED\n");
        lua_pushnumber(L, (lua_Number)1234);
        return 1;
    }

}
