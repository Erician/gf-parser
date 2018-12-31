#include <limits.h>
#include "gtest/gtest.h"
#include "utils/gfp_stringutil.h"

/******** split test ********/
TEST(SplitTest, NormalString_ShouldPass)
{
    std::string test_string("1=2");
    std::vector<std::string> pairs = gfp::utils::stringutil::split(test_string, "=");
    ASSERT_EQ(pairs[0], "1");
    ASSERT_EQ(pairs[1], "2");    
    ASSERT_EQ(pairs.size(), 2);
}

TEST(SplitTest, OnePairFormer_ShouldPass)
{
    std::string test_string("1=");
    std::vector<std::string> pairs = gfp::utils::stringutil::split(test_string, "=");
    ASSERT_EQ(pairs[0], "1");    
    ASSERT_EQ(pairs.size(), 1);
}

TEST(SplitTest, OnePairLatter_ShouldPass)
{
    std::string test_string("=1");
    std::vector<std::string> pairs = gfp::utils::stringutil::split(test_string, "=");
    ASSERT_EQ(pairs[0], "1");    
    ASSERT_EQ(pairs.size(), 1);
}

TEST(SplitTest, SplitWithNotAChar_ShouldPass)
{
    std::string test_string("1==2");
    std::vector<std::string> pairs = gfp::utils::stringutil::split(test_string, "==");
    ASSERT_EQ(pairs[0], "1");    
    ASSERT_EQ(pairs[1], "2");    
    ASSERT_EQ(pairs.size(), 2);
}

/******** strip test ********/
TEST(StripTest, SimpleString_ShouldPass)
{
    std::string test_string("  fsfs  ");
    ASSERT_EQ(gfp::utils::stringutil::strip(test_string, ' '), "fsfs");    
}

TEST(StripTest, StringWithLF_ShouldPass)
{
    std::string test_string("fsfs\n");
    ASSERT_EQ(gfp::utils::stringutil::strip(test_string, '\n'), "fsfs");    
}

TEST(StripTest, StringWithNothingToStrip_ShouldPass)
{
    std::string test_string("fsfs ");
    ASSERT_EQ(gfp::utils::stringutil::strip(test_string, ' '), "fsfs");    
}

/******** BytesToIntWithBigEndian test ********/
TEST(BytesToIntWithBigEndianTest, OneToFourBytes_ShouldPass)
{   
    char one_byte[1] = {0x12};
    char two_byte[2] = {0x12,0x34};
    char three_byte[3] = {0x12, 0x34, 0x56};
    char four_byte[4] = {0x12, 0x34, 0x56, 0x78};

    char four_byte_1[4] = {0x00, (char)0xA0, 0x00, 0x00};
    
    ASSERT_EQ(gfp::utils::stringutil::BytesToIntWithBigEndian(one_byte, 0, 1), 0x12);
    ASSERT_EQ(gfp::utils::stringutil::BytesToIntWithBigEndian(two_byte, 0, 2), 0x1234);
    ASSERT_EQ(gfp::utils::stringutil::BytesToIntWithBigEndian(three_byte, 0, 3), 0x123456);
    ASSERT_EQ(gfp::utils::stringutil::BytesToIntWithBigEndian(four_byte, 0, 4), 0x12345678);

    ASSERT_EQ((unsigned int)(gfp::utils::stringutil::BytesToIntWithBigEndian(four_byte_1, 0, 4)), 0x00A00000);

}
