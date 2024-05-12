#pragma once

#include <functional>

extern "C"
{
#include "lua_gamewave/include/lua.h"
}

#include "global.h"

namespace zlua
{
    extern "C"
    {
        using luaFunction = int(lua_State *);
        using luaClosure = std::function<luaFunction>;
    }
}
