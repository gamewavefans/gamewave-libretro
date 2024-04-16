

#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <memory>

#include "gamewave.h"

std::unique_ptr<Gamewave> gamewave = std::make_unique<Gamewave>();

// TODO Callbacks
static retro_log_printf_t log_cb;
static retro_video_refresh_t video_cb;
static retro_input_poll_t input_poll_cb;
static retro_input_state_t input_state_cb;
static retro_environment_t environ_cb;
// static retro_audio_sample_t audio_cb;
static retro_audio_sample_batch_t audio_batch_cb;

// set libretro environment
void retro_set_environment(retro_environment_t cb)
{
    environ_cb = cb;
    gamewave->setEnvironmentCallback(cb);
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
void retro_set_audio_sample(retro_audio_sample_t cb)
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
    memset(info, 0, sizeof(*info));
    // TODO parametrize these is possible
    info->library_name = "emuwave";
    info->library_version = "0.1";
    info->valid_extensions = "iso|diz";
    info->need_fullpath = true;
}

// TODO
void retro_get_system_av_info(struct retro_system_av_info *info)
{
    memset(info, 0, sizeof(*info));
    info->geometry.base_width = 720;
    info->geometry.base_height = 480;
    info->geometry.max_width = 720;
    info->geometry.max_height = 480;
    info->geometry.aspect_ratio = 1.33F;

    info->timing.fps = 60;
    // movies are in 44100, sounds appear to be 22050
    info->timing.sample_rate = 44100;

    int pixelFormat = RETRO_PIXEL_FORMAT_XRGB8888;
    environ_cb(RETRO_ENVIRONMENT_SET_PIXEL_FORMAT, &pixelFormat);
}

// TODO
void retro_init(void)
{
    /* set up some logging */
    struct retro_log_callback log;
    if (environ_cb(RETRO_ENVIRONMENT_GET_LOG_INTERFACE, &log))
    {
        log_cb = log.log;
        gamewave->setLogCallback(log_cb);
    }
    else
    {
        log_cb = NULL;
    }

    // Set the controller descriptor
    // TODO - if this works copy-paste for ID 1-5 for 5 more remotes
    // TODO - look up retro_set_controller_port_device
    // skipcq: CXX-W2066
    struct retro_input_descriptor desc[] = {
        // SNES -> X360 mapping for ABCD, hopefully
        {0, RETRO_DEVICE_JOYPAD, 0, RETRO_DEVICE_ID_JOYPAD_B, "A"},
        {0, RETRO_DEVICE_JOYPAD, 0, RETRO_DEVICE_ID_JOYPAD_A, "B"},
        {0, RETRO_DEVICE_JOYPAD, 0, RETRO_DEVICE_ID_JOYPAD_Y, "C"},
        {0, RETRO_DEVICE_JOYPAD, 0, RETRO_DEVICE_ID_JOYPAD_X, "D"},
        {0, RETRO_DEVICE_JOYPAD, 0, RETRO_DEVICE_ID_JOYPAD_SELECT, "Setup"},
        {0, RETRO_DEVICE_JOYPAD, 0, RETRO_DEVICE_ID_JOYPAD_START, "Menu"},
        {0, RETRO_DEVICE_JOYPAD, RETRO_DEVICE_INDEX_ANALOG_LEFT, RETRO_DEVICE_ID_ANALOG_X, "Arrows"},
        {0, RETRO_DEVICE_JOYPAD, RETRO_DEVICE_INDEX_ANALOG_LEFT, RETRO_DEVICE_ID_ANALOG_Y, "Arrows"},
        {0, RETRO_DEVICE_JOYPAD, RETRO_DEVICE_INDEX_ANALOG_LEFT, RETRO_DEVICE_INDEX_ANALOG_BUTTON, "Sel/OK"},
        {0, RETRO_DEVICE_JOYPAD, RETRO_DEVICE_INDEX_ANALOG_RIGHT, RETRO_DEVICE_ID_ANALOG_X, "Keypad [1-9]"},
        {0, RETRO_DEVICE_JOYPAD, RETRO_DEVICE_INDEX_ANALOG_RIGHT, RETRO_DEVICE_ID_ANALOG_Y, "Keypad [1-9]"},
        {0, RETRO_DEVICE_JOYPAD, RETRO_DEVICE_INDEX_ANALOG_RIGHT, RETRO_DEVICE_INDEX_ANALOG_BUTTON, "Keypad 5"},
        {0, RETRO_DEVICE_JOYPAD, 0, RETRO_DEVICE_ID_JOYPAD_DOWN, "Keypad 0"},

        {0},
    };
    environ_cb(RETRO_ENVIRONMENT_SET_INPUT_DESCRIPTORS, desc);
}

void retro_deinit(void) {}

void retro_reset(void)
{
}

// TODO
unsigned int framebuffer[720 * 480];

void retro_run(void)
{
    // refresh inputs
    input_poll_cb();

    video_cb(framebuffer, 720, 480, sizeof(unsigned int) * 720);
}

// Load a cartridge
// TODO
bool retro_load_game(const struct retro_game_info *info)
{
    log_cb(RETRO_LOG_DEBUG, "trying to load %s as a game\n", info->path);
    return gamewave->loadGame(info->path);
}

void retro_unload_game(void)
{
}

// stubs
bool retro_load_game_special(unsigned game_type, const struct retro_game_info *info, size_t num_info) { return false; }
void retro_set_controller_port_device(unsigned port, unsigned device) {}
void retro_cheat_reset(void) {}
void retro_cheat_set(unsigned index, bool enabled, const char *code) {}

// exposing memory would be needed e.g. for retro achivements
void *retro_get_memory_data(unsigned id) { return NULL; }
size_t retro_get_memory_size(unsigned id) { return 0; }

// Serialisation methods, basically savestate support, unused
size_t retro_serialize_size(void) { return 0; }
bool retro_serialize(void *data, size_t size) { return false; }
bool retro_unserialize(const void *data, size_t size) { return false; }
