#pragma once
#include <Signature.h>

namespace {
TEST(Signature, BasicCheck)
{
    Block::Key key;
    key.generate();
    Block::Signature sign;
    std::string signature = sign.sign("Hello",key.get_private_key());
    EXPECT_EQ(true, sign.verify("Hello", key.get_public_key(), signature));
}
}