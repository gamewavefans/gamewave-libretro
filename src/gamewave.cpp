#include "gamewave.h"

void Gamewave::setEnvironmentCallback(const retro_environment_t env_cb)
{
    this->env_cb = env_cb;
}

void Gamewave::setLogCallback(const retro_log_printf_t log_cb)
{
    this->log_cb = log_cb;
}

bool Gamewave::loadGame(const char *filePath)
{
    DizManager diz = DizManager();
    bool dizLoaded = diz.readFile(filePath);
    if (!dizLoaded)
    {
        log_cb(RETRO_LOG_ERROR, "Could not load %s\n", filePath);
        return false;
    }
    log_cb(RETRO_LOG_DEBUG, "[DIZ] Game name: %s\n", diz.getAppName().c_str());
    log_cb(RETRO_LOG_DEBUG, "[DIZ] Game file: %s\n", diz.getAppFile().c_str());
    log_cb(RETRO_LOG_DEBUG, "[DIZ] Game version: %s\n", diz.getVersion().c_str());

    char mes[128];
    std::sprintf(mes, "loaded a Game Wave game: %s", diz.getAppFile().c_str());
    retro_message_ext mess{
        mes, 5000, 4, RETRO_LOG_DEBUG, RETRO_MESSAGE_TARGET_ALL, RETRO_MESSAGE_TYPE_NOTIFICATION, -1};

    // TODO check RETRO_ENVIRONMENT_GET_MESSAGE_INTERFACE_VERSION
    env_cb(RETRO_ENVIRONMENT_SET_MESSAGE_EXT, &mess);

    return true;
}
