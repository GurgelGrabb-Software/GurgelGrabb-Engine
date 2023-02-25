#include <GG/Common/Helpers/MemUtil.h>
#include <gtest/gtest.h>

TEST(GG_Common_Helpers_MemUtil, AllocAt_Allocates_At)
{
    int t = 0;
    gg::AllocAt<int>(&t, 10);
    EXPECT_EQ( t, 10 );
}

TEST(GG_Common_Helpers_MemUtil, ZeroMem_Zeroes_1_Default)
{
    unsigned int t = 10;
    gg::ZeroMem<unsigned int>(&t);
    EXPECT_EQ(t, 0);
}

TEST(GG_Common_Helpers_MemUtil, ZeroMem_Zeroes_All_Bytes_Provided)
{
    unsigned int t[2];
    t[0] = 10;
    t[1] = 20;
    gg::ZeroMem<unsigned int>(&t, 2);
    EXPECT_EQ(t[0], 0);
    EXPECT_EQ(t[1], 0);
}

TEST(GG_Common_Helpers_MemUtil, ZeroMem_DoesNotZeroOutOfBounds)
{
    unsigned int t[3];
    t[0] = 10;
    t[1] = 20;
    t[2] = 30;
    gg::ZeroMem<unsigned int>(&t, 2);
    EXPECT_EQ(t[0], 0);
    EXPECT_EQ(t[1], 0);
    EXPECT_EQ(t[2], 30);
}