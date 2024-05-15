#pragma once

#include "libretro-common/include/libretro.h"

extern "C"
{
#include "lua_gamewave/include/lauxlib.h"
#include "lua_gamewave/include/lua.h"
#include "lua_gamewave/include/lualib.h"
}

#include "global.h"

/*
- `iframe`
  - `int Load(int i, str s)`
  - `Unload(int i)`
  - `Show(int i)`
  - `ShowPredefined(int i)` - i==0 is different than the rest
  - `Clear()`
*/
namespace zlua::IFrame
{
    // TODO: what type should iFrame be? We could basically store images here
    extern std::vector<void *> iFrames;
    extern int currentID;

    extern "C"
    {
        int zlua_iframe_loadlibrary(lua_State *L);

        int zlua_iframe_load(lua_State *L);

        int zlua_iframe_unload(lua_State *L);

        int zlua_iframe_show(lua_State *L);

        int zlua_iframe_show_predefined(lua_State *L);

        int zlua_iframe_clear(lua_State *L);
    }
}
