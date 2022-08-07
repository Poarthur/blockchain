#pragma once
#include <Header.h>

namespace {
TEST(Header, MinedCheck)
{
    Block::Header header;
    EXPECT_EQ(header.is_mined(), false);
}
}