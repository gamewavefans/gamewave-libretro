#include "zlua_mock/engine.h"

// {"ZMM_SetLeakDebugMode", engine_},
// {"ZMM_SetCheckPoint", engine_},
// {"ZMM_VerifyCheckPoint", engine_},
// {"ZMM_GetTotalAllocMemory", engine_},

// TODO
static int engine_zmm_get_total_free_memory(lua_State *L)
{
    int free = 1234;
    printf("\tcalled engine.ZMM_GetTotalFreeMemory() -> %d - UNIMPLEMENTED\n", free);
    lua_pushnumber(L, (lua_Number)free);
    return 1;
}

// {"ZMM_GetMaxFreeMemory", engine_},
// {"DR_SetEnable", engine_},
// {"DR_SetDebug", engine_},
// {"DR_SetAbsoluteCapping", engine_},
// {"DR_ClearPairCappings", engine_},
// {"DR_AddPairCapping", engine_},
// {"OpenTray", engine_},
// {"CloseTray", engine_},
// {"EjectTray", engine_},
// {"GetTrayState", engine_},
// {"SoftwareReset", engine_},
// {"WaitForDisk", engine_},
// {"GetNumOverlays", engine_},
// {"GetNumTextures", engine_},

// TODO
static int engine_version(lua_State *L)
{
    // in format if 1.01.3.xxxxxx
    const char *version = "dummyEngineVer"; //"1.01.3.123456";
    printf("\tcalled engine.Version() -> %s - UNIMPLEMENTED\n", version);
    lua_pushstring(L, version);
    return 1;
}
// {"SetLineTraceMode", engine_},
// {"GetLineTraceMode", engine_},

static const luaL_reg enginelib[] = {
    // {"ZMM_SetLeakDebugMode", engine_},
    // {"ZMM_SetCheckPoint", engine_},
    // {"ZMM_VerifyCheckPoint", engine_},
    // {"ZMM_GetTotalAllocMemory", engine_},
    {"ZMM_GetTotalFreeMemory", engine_zmm_get_total_free_memory},
    // {"ZMM_GetMaxFreeMemory", engine_},
    // {"DR_SetEnable", engine_},
    // {"DR_SetDebug", engine_},
    // {"DR_SetAbsoluteCapping", engine_},
    // {"DR_ClearPairCappings", engine_},
    // {"DR_AddPairCapping", engine_},
    // {"OpenTray", engine_},
    // {"CloseTray", engine_},
    // {"EjectTray", engine_},
    // {"GetTrayState", engine_},
    // {"SoftwareReset", engine_},
    // {"WaitForDisk", engine_},
    // {"GetNumOverlays", engine_},
    // {"GetNumTextures", engine_},
    {"Version", engine_version},
    // {"SetLineTraceMode", engine_},
    // {"GetLineTraceMode", engine_},
    {NULL, NULL}};

int luaopen_engine(lua_State *L)
{
    printf("loaded engine\n");
    luaL_openlib(L, "engine", enginelib, 0);
    return 1;
}
