#pragma once

#include <vector>
#include <fstream>
#include <filesystem>

#include "libretro-common/include/libretro.h"

extern "C"
{
#include "lauxlib.h"
#include "lua.h"
#include "lualib.h"
}

#include "global.h"
#include "zlua/rm.h"
#include "filetypes/iframe.h"

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
  namespace fs = std::filesystem;

  // TODO: what type should iFrame be? Can it be just filetypes::IFrame ?
  extern std::vector<std::shared_ptr<filetypes::IFrame>> iFrames;
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

  int getIframeID();

  int getIframeCount();

  void reset();
}
