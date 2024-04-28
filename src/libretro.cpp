

#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <memory>
#include <array>

#include "deps/libretro-common/include/libretro.h"
#include "gamewave.h"
#include <src/console_info.h>

std::unique_ptr<Gamewave> gamewave;

// TODO Callbacks
static retro_log_printf_t log_cb;
static retro_video_refresh_t video_cb;
static retro_input_poll_t input_poll_cb;
static retro_input_state_t input_state_cb;
static retro_environment_t env_cb;
// static retro_audio_sample_t audio_cb;
static retro_audio_sample_batch_t audio_batch_cb;

// set libretro environment
void retro_set_environment(retro_environment_t cb)
{
    env_cb = cb;
    if (gamewave != nullptr)
    {
        gamewave->setEnvironmentCallback(cb);
    }
    bool no_rom = true;
    bool no_achivements = true;
    cb(RETRO_ENVIRONMENT_SET_SUPPORT_NO_GAME, &no_rom);
    cb(RETRO_ENVIRONMENT_SET_SUPPORT_ACHIEVEMENTS, &no_achivements);
}

void retro_set_video_refresh(retro_video_refresh_t cb)
{
    video_cb = cb;
}

// only one audio callback can be used at a time
void retro_set_audio_sample([[maybe_unused]] retro_audio_sample_t cb)
{
    // audio_cb = cb;
}

void retro_set_audio_sample_batch(retro_audio_sample_batch_t cb)
{
    audio_batch_cb = cb;
}

void retro_set_input_poll(retro_input_poll_t cb)
{
    input_poll_cb = cb;
}

void retro_set_input_state(retro_input_state_t cb)
{
    input_state_cb = cb;
}

unsigned int retro_api_version(void)
{
    return RETRO_API_VERSION;
}

unsigned int retro_get_region(void)
{
    return RETRO_REGION_NTSC;
}

void retro_get_system_info(struct retro_system_info *info)
{
    *info = {
        .library_name = "emuwave",
        .library_version = "0.1",
        // TODO: expand this to .iso files later with "iso|diz"
        .valid_extensions = "diz",
        // we need access to multiple files, so we need full path instead of jsut loading one file into memory
        .need_fullpath = true,
        .block_extract = false};
}

// TODO
void retro_get_system_av_info(struct retro_system_av_info *info)
{
    *info = {
        .geometry = {
            .base_width = info::screen::WIDTH,
            .base_height = info::screen::HEIGHT,
            .max_width = info::screen::WIDTH,
            .max_height = info::screen::HEIGHT,
            .aspect_ratio = info::screen::RATIO},
        .timing = {// TODO: check if this is correct, as videos are in 29.97 fps
                   .fps = info::screen::REFRESH_RATE,
                   .sample_rate = info::audio::SAMPLE_RATE}};

    int pixelFormat = RETRO_PIXEL_FORMAT_XRGB8888;
    env_cb(RETRO_ENVIRONMENT_SET_PIXEL_FORMAT, &pixelFormat);
}

// TODO implement retro_keyboard_callback

// TODO
void retro_init(void)
{
    /* set up some logging */
    struct retro_log_callback log;
    if (env_cb(RETRO_ENVIRONMENT_GET_LOG_INTERFACE, &log))
    {
        log_cb = log.log;
        if (gamewave != nullptr)
        {
            gamewave->setLogCallback(log_cb);
        }
    }
    else
    {
        log_cb = NULL;
    }

    // Set the controller descriptor
    // TODO - if this works copy-paste for ID 1-5 for 5 more remotes
    // TODO - look up retro_set_controller_port_device
    std::array desc = std::to_array<retro_input_descriptor>({
        //  SNES -> X360 mapping for ABCD, hopefully
        {0, RETRO_DEVICE_JOYPAD, 0, RETRO_DEVICE_ID_JOYPAD_B, "A"},
        {0, RETRO_DEVICE_JOYPAD, 0, RETRO_DEVICE_ID_JOYPAD_A, "B"},
        {0, RETRO_DEVICE_JOYPAD, 0, RETRO_DEVICE_ID_JOYPAD_Y, "C"},
        {0, RETRO_DEVICE_JOYPAD, 0, RETRO_DEVICE_ID_JOYPAD_X, "D"},
        {0, RETRO_DEVICE_JOYPAD, 0, RETRO_DEVICE_ID_JOYPAD_SELECT, "Setup"},
        {0, RETRO_DEVICE_JOYPAD, 0, RETRO_DEVICE_ID_JOYPAD_START, "Menu"},
        {0, RETRO_DEVICE_ANALOG, RETRO_DEVICE_INDEX_ANALOG_LEFT, RETRO_DEVICE_ID_ANALOG_X, "Arrows"},
        {0, RETRO_DEVICE_ANALOG, RETRO_DEVICE_INDEX_ANALOG_LEFT, RETRO_DEVICE_ID_ANALOG_Y, "Arrows"},
        {0, RETRO_DEVICE_ANALOG, RETRO_DEVICE_INDEX_ANALOG_LEFT, RETRO_DEVICE_INDEX_ANALOG_BUTTON, "Sel/OK"},
        {0, RETRO_DEVICE_ANALOG, RETRO_DEVICE_INDEX_ANALOG_RIGHT, RETRO_DEVICE_ID_ANALOG_X, "Keypad [1-9]"},
        {0, RETRO_DEVICE_ANALOG, RETRO_DEVICE_INDEX_ANALOG_RIGHT, RETRO_DEVICE_ID_ANALOG_Y, "Keypad [1-9]"},
        {0, RETRO_DEVICE_ANALOG, RETRO_DEVICE_INDEX_ANALOG_RIGHT, RETRO_DEVICE_INDEX_ANALOG_BUTTON, "Keypad 5"},
        {0, RETRO_DEVICE_JOYPAD, 0, RETRO_DEVICE_ID_JOYPAD_DOWN, "Keypad 0"},
        {0, RETRO_DEVICE_NONE, 0, 0, nullptr},
    });
    env_cb(RETRO_ENVIRONMENT_SET_INPUT_DESCRIPTORS, desc.data());
}

void retro_deinit(void)
{
    // destroy old gamewave emulator object
    gamewave.reset();
}

void retro_reset(void)
{
}

// each pixel is in RETRO_PIXEL_FORMAT_XRGB8888 format, X is ignored

void retro_run(void)
{
    // refresh inputs
    input_poll_cb();
    video_cb(gamewave->getFramebuffer(), info::screen::WIDTH, info::screen::HEIGHT, sizeof(unsigned int) * info::screen::WIDTH);
}

// TODO: Load a cartridge
bool retro_load_game(const struct retro_game_info *game)
{
    gamewave.reset(new Gamewave(env_cb, log_cb));
    log_cb(RETRO_LOG_DEBUG, "trying to load %s as a game\n", game->path);
    log_cb(RETRO_LOG_DEBUG, "meta: %s\n", game->meta);

    return gamewave->loadGame(game->path);
}

void retro_unload_game(void)
{
}

// stubs
bool retro_load_game_special([[maybe_unused]] unsigned game_type, [[maybe_unused]] const struct retro_game_info *info, [[maybe_unused]] size_t num_info) { return false; }
void retro_set_controller_port_device([[maybe_unused]] unsigned port, [[maybe_unused]] unsigned device) {}
void retro_cheat_reset(void) {}
void retro_cheat_set([[maybe_unused]] unsigned index, [[maybe_unused]] bool enabled, [[maybe_unused]] const char *code) {}

// exposing memory would be needed e.g. for retro achivements
void *retro_get_memory_data([[maybe_unused]] unsigned id) { return NULL; }
size_t retro_get_memory_size([[maybe_unused]] unsigned id) { return 0; }

// Serialisation methods, basically savestate support, unused
size_t retro_serialize_size(void) { return 0; }
bool retro_serialize([[maybe_unused]] void *data, [[maybe_unused]] size_t size) { return false; }
bool retro_unserialize([[maybe_unused]] const void *data, [[maybe_unused]] size_t size) { return false; }
