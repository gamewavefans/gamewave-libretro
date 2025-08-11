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

#include "global.h"

extern std::filesystem::path GameBasePath;
// TODO: keep RM or rename to ResourceManager?
namespace zlua::RM
{
    namespace fs = std::filesystem;

    // for now we add stuff into the vector, we may remove values, but never keys, until the console restart
    // extern int currentID;

    extern std::vector<std::shared_ptr<fs::path>> resources;
    extern std::vector<std::shared_ptr<fs::path>> files;

    extern "C"
    {
        int zlua_rm_loadlibrary(lua_State *L);

        int zlua_rm_open_resource(lua_State *L);

        int zlua_rm_close_resource(lua_State *L);

        // only used in "Letter Zap!""
        int zlua_rm_load_file(lua_State *L);

        // unused
        int zlua_rm_unload_file(lua_State *L);

        void reset();
    }

    std::shared_ptr<fs::path> getResourcePath(int i);
}
