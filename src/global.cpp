#include "global.h"

// TODO Callbacks
retro_log_printf_t log_cb{};
retro_video_refresh_t video_cb{};
retro_input_poll_t input_poll_cb{};
retro_input_state_t input_state_cb{};
retro_environment_t env_cb{};
// static retro_audio_sample_t audio_cb{};
retro_audio_sample_batch_t audio_batch_cb{};
