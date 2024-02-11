

// TODO move this info to its respective spaces
namespace info
{
    namespace screen
    {
        static constexpr int WIDTH = 720;
        static constexpr int HEIGHT = 480;

        // static constexpr float RATIO = static_cast<float>(WIDTH) / static_cast<float>(HEIGHT);

        // the image is stored in 3:2 ratio, but the NTSC standard is 4:3 with non-square pixels
        static constexpr float DATA_RATIO = 3.0 / 2.0;
        static constexpr float RATIO = 4.0 / 3.0;

        // movies use 29.97
        static constexpr double REFRESH_RATE = 60.0;

    }
    namespace memory
    {
        // TODO - how much memory is there?
        static constexpr int SIZE = 0;
    }
    namespace audio
    {
        static constexpr double SAMPLE_RATE = 0;
    }
    // memory - 16MB RAM
    // stereo sound
    // 2MB NOR Flash RAM ???

}
