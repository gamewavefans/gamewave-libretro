#pragma once

// TODO: move this info to its respective spaces
namespace info
{
    namespace screen
    {
        static constexpr int WIDTH = 720;
        // 540 for 4:3, but probably is 480 stretched to 4:3 proportions on output
        static constexpr int HEIGHT = 480;

        // static constexpr float RATIO = static_cast<float>(WIDTH) / static_cast<float>(HEIGHT);

        // the image is stored in 3:2 ratio, but the NTSC standard is 4:3 with non-square pixels
        // TODO: check which one  is used internally
        static constexpr float DATA_RATIO = 3.0 / 2.0;
        static constexpr float RATIO = 4.0 / 3.0;

        // TODO: check, movies use 29.97002997002997, or simply 30000/1001
        static constexpr double REFRESH_RATE = 30'000 / 1'001;

    }
    // namespace memory
    // {
    //     // TODO: how much memory is there? EEPROM & RAM
    //     // memory - 16MiB RAM ?
    //     static constexpr int SIZE = 0;
    // }
    // namespace eeprom {
    //     // 2MB NOR Flash RAM ???
    //     static constexpr int SIZE = 0;
    // }
    namespace audio
    {
        // TODO: check if correct
        // Movies use sither 44'100 or 48'000
        static constexpr double SAMPLE_RATE = 44'100;
        static constexpr int CHANNELS = 2;
    }
}
