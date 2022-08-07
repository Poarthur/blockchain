#pragma once
#include <Block.h>
#include <fstream>

namespace {
TEST(Block, BlockIndex)
{
    Block::Block block;
    EXPECT_THROW({
        try
        {
            block[0];
        }
        catch(const std::logic_error& e)
        {
            EXPECT_STREQ("Incorrect index", e.what());
            throw;
        }
    }, std::logic_error);
}

TEST(Block, Mining)
{
    Block::Block block;
    block.add_transaction("12345","67890",5.1,"435325234");
    block.add_transaction("3543252","67345345890",6.1,"6363456");
    block.add_transaction("43252452","345324646",67.3,"4578709654");
    block.mine();
    EXPECT_EQ(block.get_header().get_nonce(), 19188);
}

TEST(Block, Validate)
{
    Block::Block block;
    block.add_transaction("12345","67890",5.1,"435325234");
    block.add_transaction("3543252","67345345890",6.1,"6363456");
    block.add_transaction("43252452","345324646",67.3,"4578709654");
    block.mine();
    EXPECT_EQ(block.validate(), true);
}

TEST(Block, FindFrom)
{
    Block::Block block;
    block.add_transaction("12345","67890",5.1,"435325234");
    block.add_transaction("3543252","67345345890",6.1,"6363456");
    block.add_transaction("43252452","345324646",67.3,"4578709654");
    block.add_transaction("12345","34242",8.2,"563456475");
    auto f = block.find_from("12345");
    EXPECT_EQ(2,f.size());
}

TEST(Block, FindTo)
{
    Block::Block block;
    block.add_transaction("12345","67890",5.1,"435325234");
    block.add_transaction("3543252","67345345890",6.1,"6363456");
    block.add_transaction("43252452","345324646",67.3,"4578709654");
    block.add_transaction("12345","345324646",8.2,"563456475");
    auto f = block.find_from("12345");
    EXPECT_EQ(2,f.size());
}

TEST(Block, IOManip)
{
    Block::Block block;
    Block::Header header;
    header.set_index(0);
    std::string null_hash(Block::Sha256::sha256_size*2,'0');
    header.set_prev_hash(null_hash);
    block.set_header(header);
    block.add_transaction("12345","67890",5.1,"435325234");
    block.add_transaction("3543252","67345345890",6.1,"6363456");
    block.add_transaction("43252452","345324646",67.3,"4578709654");
    block.add_transaction("12345","345324646",8.2,"563456475");
    block.mine();
    std::string hash = block.get_header().get_hash();
    uint32_t index = 0;
    uint64_t nonce = block.get_header().get_nonce();
    std::ofstream file("test.block");
    file << block;
    file.close();
    std::ifstream ifile("test.block");
    if(ifile)
    {
        ifile >> block;
    }
    file.close();
    EXPECT_EQ(block.get_header().get_difficulty(),4);
    EXPECT_EQ(block.get_header().get_hash(),hash);
    EXPECT_EQ(block.get_header().get_index(),0);
    EXPECT_EQ(block.get_header().get_nonce(),nonce);
    EXPECT_EQ(block.get_header().get_prev_hash(),null_hash);

    EXPECT_EQ(std::get<Block::Block::i_from>(block[0]),"12345");
    EXPECT_EQ(std::get<Block::Block::i_to>(block[0]),"67890");
    EXPECT_EQ(std::get<Block::Block::i_amount>(block[0]),5.1);
    EXPECT_EQ(std::get<Block::Block::i_sig>(block[0]),"435325234");
}

}
