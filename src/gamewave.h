#pragma once

#include <chrono>
#include <thread>

#include <array>
#include <functional>
#include <format>
#include <filesystem>

#include <csetjmp>

extern "C"
{
#include "lauxlib.h"
#include "lua.h"
#include "lualib.h"
}

#include "libretro-common/include/libretro.h"

#include "filetypes/iframe.h"
#include "console_info.h"
#include "helpers.h"

#include "filetypes/diz.h"
#include "filetypes/fimg.h"
#include "filetypes/zbc.h"

#include "zlua/bit.h"
#include "zlua/engine.h"
#include "zlua/gl.h"
#include "zlua/iframe.h"
#include "zlua/log.h"
#include "zlua/rm.h"
#include "zlua/time.h"
#include "zlua/zmath.h"

using namespace std::chrono_literals;

namespace fs = std::filesystem;
using hookFunc = std::function<void(lua_State *L, lua_Debug *ar)>;

class Gamewave
{
public:
    Gamewave(const retro_environment_t env_cb, const retro_log_printf_t log_cb, const char *inputPath);
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

    FIMG *fimg;

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
