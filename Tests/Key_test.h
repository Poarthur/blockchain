#pragma once
#include <Key.h>

namespace {

TEST(RSAKeys, KeysGenerator)
{
    Block::Key key;
    key.generate();
    std::string first_private_key = key.get_private_key();
    std::string first_public_key = key.get_public_key();
    key.generate();
    std::string second_private_key = key.get_private_key();
    std::string second_public_key = key.get_public_key();
    EXPECT_NE(first_private_key,second_private_key);
    EXPECT_NE(first_public_key,second_public_key);
}
}