#include <filetypes/diz.h>
#include <gtest/gtest.h>
#include <gmock/gmock.h>

TEST(DizTest, TestLoadFile)
{
    auto dm = DIZ();
    // TODO: make path not so sensitive to build changes
    auto success = dm.readFile("../tests/data/test.diz");
    EXPECT_TRUE(success);
}

TEST(DizTest, TestLoadAppFile)
{
    auto dm = DIZ();
    auto success = dm.readFile("../tests/data/test.diz");
    EXPECT_TRUE(success);

    EXPECT_PRED2([](auto a, auto b)
                 { return a == b; },
                 dm.getAppFile(), "/Data/game.zbc");
}
