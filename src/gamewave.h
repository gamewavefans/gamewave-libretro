#pragma once

#include <thread>
#include <array>
#include <functional>
#include <format>

#include "deps/libretro-common/include/libretro.h"
#include "diz_manager.h"
#include "console_info.h"
#include "helpers.h"

#include <csetjmp>
extern "C"
{
#include "lauxlib.h"
#include "lua.h"
#include "lualib.h"
}

typedef std::function<void(lua_State *L, lua_Debug *ar)> hookFunc;

class Gamewave
{
public:
    Gamewave(const retro_environment_t env_cb, const retro_log_printf_t log_cb);
    ~Gamewave();
    void setEnvironmentCallback(const retro_environment_t env_cb);
    void setLogCallback(const retro_log_printf_t log_cb);

    unsigned int *getFramebuffer();

    /**
     * @brief loadGame loads and runs a Game Wave file, starting from a .diz file
     *
     * @param filePath path to a .diz file
     * @return true game was loaded succesfully, required by libretro
     * @return false game was unable to load
     */
    bool loadGame(const char *filePath);

private:
    std::array<unsigned int, info::screen::WIDTH * info::screen::HEIGHT> framebuffer;

    // simple flag for threads to check if they should stop
    std::atomic_bool coreRunning;

    retro_log_printf_t log_cb;
    retro_environment_t env_cb;

    // TODO: mov lua stuff to another class maybe?
    std::string dumpLuaStack(lua_State *L);
    std::jmp_buf place;

    std::thread luaThread;
    void luaFunction();
    hookFunc getHook();

    std::thread videoThread;
    void videoFunction();
};
