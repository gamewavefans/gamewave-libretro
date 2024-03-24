#pragma once

#include "deps/libretro-common/include/libretro.h"
#include "diz_manager.h"

class Gamewave
{
public:
    void setEnvironmentCallback(const retro_environment_t env_cb);
    void setLogCallback(const retro_log_printf_t log_cb);

    /**
     * @brief loadGame loads and runs a Game Wave file, starting from a .diz file
     *
     * @param filePath path to a .diz file
     * @return true game was loaded succesfully, required by libretro
     * @return false game was unable to load
     */
    bool loadGame(const char *filePath);

private:
    retro_log_printf_t log_cb;
    retro_environment_t env_cb;
};
