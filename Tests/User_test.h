#pragma once
#include <User.h>

namespace {
TEST(User, SaveLoad)
{
    Block::User user;
    user.create("Jerry");
    user.save_user();
    Block::User another_user("Jerry");
    another_user.load_user();
    EXPECT_EQ(user.get_key().get_private_key(), another_user.get_key().get_private_key());
    EXPECT_EQ(user.get_key().get_public_key(), another_user.get_key().get_public_key());
}
}