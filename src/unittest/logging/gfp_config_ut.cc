#include <limits.h>
#include "gtest/gtest.h"
#include "logging/gfp_config.h"
#include "logging/gfp_const.h"

class ConfigTest : public ::testing::Test
{
protected:
    virtual void SetUp() {
        config.Init("logging/gfp_logging.ini");
    }
    virtual void TearDown() {
        ;
    }
    Config config;
};

TEST_F(ConfigTest, IsHave_ShouldPass)
{
    ASSERT_EQ(true, config.IsHave(gfp::config::kLogFilePath));
}

TEST_F(ConfigTest, GetValue_ShouldPass)
{
    ASSERT_EQ("../logs/log.txt", config.GetValue(gfp::config::kLogFilePath));
}


