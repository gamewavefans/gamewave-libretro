#pragma once

#include <vector>
#include <filesystem>

extern "C"
{
#include "libretro-common/include/libretro.h"
}
extern retro_log_printf_t log_cb;
extern retro_video_refresh_t video_cb;
extern retro_input_poll_t input_poll_cb;
extern retro_input_state_t input_state_cb;
extern retro_environment_t env_cb;
// static retro_audio_sample_t audio_cb;
extern retro_audio_sample_batch_t audio_batch_cb;
// }

namespace zlua::RM
{
    namespace fs = std::filesystem;

    // TODO: check if it's better to use string or path here; we need to join the base path as well
    extern std::vector<fs::path *> resources;
}
