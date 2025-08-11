#include "zlua/iframe.h"

namespace zlua::IFrame
{
    int currentID = {0};
    std::vector<std::shared_ptr<filetypes::IFrame>> iFrames = {};

    static const luaL_reg zlua_iframe_lib[] = {
        // {"Clear", zlua_iframe_clear},
        {"Load", zlua_iframe_load},
        // {"Show", zlua_iframe_show},
        // TODO: add access to FIMG here
        // {"ShowPredefined", zlua_iframe_show_predefined},
        {"Unload", zlua_iframe_unload},
        {nullptr, nullptr}};

    int zlua_iframe_loadlibrary(lua_State *L)
    {
        reset();
        luaL_openlib(L, "iframe", zlua_iframe_lib, 0);
        return 1;
    }

    int zlua_iframe_load(lua_State *L)
    {
        int resource = luaL_checkint(L, 1);
        std::string s = luaL_checkstring(L, 2);

        auto location = zlua::RM::getResourcePath(resource);
        auto targetPath = *location / s;
        // read file data
        // TODO: standalone read function
        std::ifstream videoFile{targetPath, std::ios::binary | std::ios::ate};
        auto size = videoFile.tellg();
        videoFile.seekg(0, std::ios::beg);
        std::vector<char> buffer(size, 0);
        videoFile.read(buffer.data(), size);

        // TODO: won't this leak memory??
        auto iframe = std::make_shared<filetypes::IFrame>(filetypes::IFrame(buffer));
        iFrames.push_back(iframe);

        log_cb(RETRO_LOG_DEBUG, "\tcalled iframe.Load(%d, \"%s\") (\"%s\")-> %d - PARTIALLY IMPLEMENTED\n", resource, s.c_str(), targetPath.c_str(), currentID);
        lua_pushnumber(L, (lua_Number)currentID);
        ++currentID;
        return 1;
    }

    int zlua_iframe_unload(lua_State *L)
    {
        int i = luaL_checkint(L, 1);
        iFrames.at(i) = nullptr;
        log_cb(RETRO_LOG_DEBUG, "\tcalled iframe.Unload(%d) - UNIMPLEMENTED\n", i);
        return 0;
    }

    int zlua_iframe_show(lua_State *L)
    {
        int i = luaL_checkint(L, 1);
        log_cb(RETRO_LOG_DEBUG, "\tcalled iframe.Show(%d) - UNIMPLEMENTED\n", i);
        return 0;
    }

    int zlua_iframe_show_predefined(lua_State *L)
    {
        int i = luaL_checkint(L, 1);
        log_cb(RETRO_LOG_DEBUG, "\tcalled iframe.ShowPredefined(%d) - UNIMPLEMENTED\n", i);
        return 0;
    }

    int zlua_iframe_clear(lua_State *L)
    {
        log_cb(RETRO_LOG_DEBUG, "\tcalled iframe.Clear() - UNIMPLEMENTED\n");
        return 0;
    }

    int getIframeID()
    {
        return currentID;
    }

    int getIframeCount()
    {
        // return number of non-nullptr elements
        return std::count_if(iFrames.begin(), iFrames.end(), [](std::shared_ptr<filetypes::IFrame> iFrame)
                             { return iFrame != nullptr; });
    }

    void reset()
    {
        for (auto f : iFrames)
        {
            f.reset();
        }
        iFrames.clear();
        currentID = iFrames.size();
    }
}
