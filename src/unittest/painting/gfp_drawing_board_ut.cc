#include <limits.h>
#include "gtest/gtest.h"
#include "painting/gfp_drawing_board.h"

TEST(PutTest, PutToConsole_ShouldPass)
{
    gfp::DrawingBoard db;
    db.Put('a');
}

TEST(PutTest, PutToFile_ShouldPass)
{
    gfp::DrawingBoard db("aaa");
    db.Put('a');
    db.Close();

    std::ifstream ifs = std::ifstream("aaa", std::ifstream::in);
    assert(ifs);
    char c;
    ifs.get(c);
    ASSERT_EQ(c, 'a');
    
    remove("aaa");
}



