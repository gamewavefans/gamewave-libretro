#pragma once

#include <format>
#include <functional>
#include <array>

// TODO
#include <typeinfo>

#include "libretro-common/include/libretro.h"
extern "C"
{
#include "lua_gamewave/include/lauxlib.h"
#include "lua_gamewave/include/lua.h"
}

#include "zlua/common.h"

namespace zlua::Log
{
  enum class LogLevel : int
  {
    LOG_NONE = 0,
    LOG_CRITICAL = 1,
    LOG_IMPORTANT = 2,
    LOG_NORMAL = 3,
    LOG_VERBOSE = 4,
    LOG_DEBUG = 5,
  };
  extern LogLevel zlua_log_level;

  extern "C"
  {
    int zlua_log_loadlibrary(lua_State *L);

    /**
     * @brief prints if level is lower or equal to currently set log level
     *
     *
     * @param L Lua state
     * @return 0 - no returns to Lua
     */
    int zlua_log_log(lua_State *L);

    /**
     * @brief set the current log level
     *
     *
     * @param L Lua state
     * @return 0 - no returns to Lua
     */
    int zlua_log_setLevel(lua_State *L);
    // int zlua_log_setModule(lua_State *L);
    // int zlua_log_printRaw(lua_State *L);
    // int zlua_log_printLine(lua_State *L);
    // int zlua_log_debugSetState(lua_State *L);
  }
  const char *getLogLevelName(int level);
}

/*
- log
  - SetModule(int i, int j)
  - PrintRaw(str message)
    - prints somewhere if debug state is enabled
  - PrintLine(str message)
    - prints somewhere
  - DebugSetState(int enabled)
    - sets debug state 0/1
    - PrintRaw works only if enabled is non-zero
*/
