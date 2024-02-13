#include <diz_manager.h>
#include <gtest/gtest.h>
#include <gmock/gmock.h>

TEST(DizTest, TestLoadFile)
{
    auto dm = DizManager();
    auto success = dm.readFile("data/test.diz");
    EXPECT_TRUE(success);
}

TEST(DizTest, TestLoadAppFile)
{
    auto dm = DizManager();
    auto success = dm.readFile("/home/halamix2/repos/reverse/gamewave/gamewave-libretro/tests/data/test.diz"); // data/test.diz");
    EXPECT_TRUE(success);

    EXPECT_PRED2([](auto a, auto b)
                 { return a == b; },
                 dm.getAppFile(), "/Data/game.zbc");
}
