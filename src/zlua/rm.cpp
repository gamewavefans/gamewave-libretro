#include "zlua/rm.h"

namespace zlua::RM
{
    int currentID = {0};
    std::vector<fs::path *> resources = {};

    static const luaL_reg zlua_rm_lib[] = {
        {"CloseResource", zlua_rm_close_resource},
        // {"LoadFile", zlua_rm_load_file},
        {"OpenResource", zlua_rm_open_resource},
        // {"UnloadFile", zlua_rm_unload_file},
        {nullptr, nullptr}};

    int zlua_rm_loadlibrary(lua_State *L)
    {
        luaL_openlib(L, "rm", zlua_rm_lib, 0);
        return 1;
    }

    int zlua_rm_open_resource(lua_State *L)
    {
        // TODO: handle reusing IDs when one of them is a nullptr
        std::string name = luaL_checkstring(L, 1);
        fs::path *path = new fs::path{name};
        resources.push_back(path);
        log_cb(RETRO_LOG_DEBUG, "\tcalled rm.OpenResource(\"%s\") -> %d\n", name.c_str(), currentID);
        lua_pushnumber(L, (lua_Number)currentID);
        ++currentID;
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

    fs::path *getResourcePath(int i)
    {
        return resources.at(i);
    }
}
