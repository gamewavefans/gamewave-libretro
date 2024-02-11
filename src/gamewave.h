#pragma once

#include "deps/libretro-common/include/libretro.h"
#include "diz_manager.h"

class Gamewave
{
public:
    void setEnvironmentCallback(const retro_environment_t env_cb);
    void setLogCallback(const retro_log_printf_t log_cb);
    bool loadGame(const char *filePath);

private:
    retro_log_printf_t log_cb;
    retro_environment_t env_cb;
};
