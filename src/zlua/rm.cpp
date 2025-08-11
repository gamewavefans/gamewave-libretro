#include "zlua/rm.h"

namespace zlua::RM
{
    int currentResourceID = {0};
    /// resources keeps array of absolute paths to game resources (usually directories)
    std::vector<std::shared_ptr<fs::path>> resources = {};

    id_t currentFileID = {0};
    /// files keeps array of absolute paths to game files
    std::vector<std::shared_ptr<fs::path>> files = {};

    static const luaL_reg zlua_rm_lib[] = {
        {"CloseResource", zlua_rm_close_resource},
        // {"LoadFile", zlua_rm_load_file},
        {"OpenResource", zlua_rm_open_resource},
        // {"UnloadFile", zlua_rm_unload_file}, - unused
        {nullptr, nullptr}};

    int zlua_rm_loadlibrary(lua_State *L)
    {
        reset();
        luaL_openlib(L, "rm", zlua_rm_lib, 0);
        return 1;
    }

    int zlua_rm_open_resource(lua_State *L)
    {
        // TODO: handle reusing IDs when one of them is a nullptr ?
        std::string name = luaL_checkstring(L, 1);
        auto relativeName = name;
        if (relativeName != "" && relativeName[0] == '/')
        {
            relativeName.erase(0, 1);
        }
        std::shared_ptr<fs::path> path = std::make_shared<fs::path>(GameBasePath);
        *path /= relativeName;
        resources.push_back(path);
        log_cb(RETRO_LOG_DEBUG, "\tcalled rm.OpenResource(\"%s\") -> %d\n", name.c_str(), currentResourceID);
        lua_pushnumber(L, (lua_Number)currentResourceID);
        ++currentResourceID;
        return 1;
    }

    int zlua_rm_close_resource(lua_State *L)
    {
        int i = luaL_checkint(L, 1);
        // TODO: handle the exception when index is out of bound
        resources.at(i) = nullptr;
        return 0;
    }

    int zlua_rm_load_file(lua_State *L)
    {
        return 0;
    }

    int zlua_rm_unload_file(lua_State *L)
    {
        return 0;
    }

    std::shared_ptr<fs::path> getResourcePath(int i)
    {
        return resources.at(i);
    }

    void reset()
    {
        for (auto r : resources)
        {
            r.reset();
        }
        resources.clear();
        // should be always 0, but it's better to be safe than sorry
        currentResourceID = resources.size();

        for (auto f : files)
        {
            f.reset();
        }
        files.clear();
        currentFileID = files.size();
    }
}
