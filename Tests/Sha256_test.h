#pragma once
#include <Sha256.h>

namespace {
TEST(Sha256, BasicException)
{
    Block::Sha256 sha;
    EXPECT_THROW({
        try
        {
            sha.sha256_from_ascii("123");
        }
        catch(const std::logic_error& e)
        {
            EXPECT_STREQ("Wrong argument", e.what());
            throw;
        }
    }, std::logic_error);
}

TEST(Sha256, sha256TextCheck)
{
    Block::Sha256 sha("Memphis");
    EXPECT_EQ(sha.get_hash().size(),32);
    EXPECT_EQ(sha.sha256_to_ascii(), "034e4554eaa313d27a082af675a6e8d890b9899aaf14dba22f988c8b2f1efa64") << "The hash is considered incorrect";
}

TEST(Sha256, sha256Check)
{
    Block::Sha256 sha("Memphis");
    EXPECT_EQ(sha.get_hash().size(),sha.sha256_from_ascii(sha.sha256_to_ascii()).size());
    EXPECT_EQ(sha.get_hash(),sha.sha256_from_ascii(sha.sha256_to_ascii()));
}
}