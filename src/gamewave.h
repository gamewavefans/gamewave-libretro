#pragma once

#include <thread>
#include <array>
#include <functional>
#include <format>
#include <filesystem>

#include <csetjmp>
extern "C"
{
#include "lua_gamewave/include/lauxlib.h"
#include "lua_gamewave/include/lua.h"
#include "lua_gamewave/include/lualib.h"
}

#include "libretro-common/include/libretro.h"

#include "filetypes/diz.h"
#include "filetypes/zbc.h"
#include "console_info.h"
#include "helpers.h"

namespace fs = std::filesystem;
using hookFunc = std::function<void(lua_State *L, lua_Debug *ar)>;

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
    lua_State *L;
    void loadLuaLibraries();
    std::string dumpLuaStack();
    std::jmp_buf place;

    std::thread luaThread;
    void luaFunction();
    hookFunc getHook();

    std::thread videoThread;
    void videoFunction();
};
