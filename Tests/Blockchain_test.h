#pragma once
#include <Blockchain.h>
#include <iostream>

namespace {
TEST(Blockchain, Creating)
{
    EXPECT_NO_THROW(Block::Blockchain blockchain;);
}

TEST(Blockchain, AddTransaction)
{
    Block::Blockchain blockchain;
    Block::User user;
    Block::Signature sign;
    user.create("Nick");
    double amount = 100.0;
    auto message = Block::Signature::create_message(Block::Blockchain::coinbase,user,amount);
    std::string signature = sign.sign(message,user.get_key().get_private_key());
    bool r = blockchain.new_transaction(Block::Blockchain::coinbase,user,amount,signature);
    EXPECT_EQ(r,true);
    
    Block::User to_user;
    to_user.create("Tom");
    auto msg = Block::Signature::create_message(user,to_user,10);
    std::string new_sign = sign.sign(msg,user.get_key().get_private_key());
    bool result = blockchain.new_transaction(user,to_user,10,new_sign);
    EXPECT_EQ(result,true);
}

TEST(Blockchain, Mining)
{
    Block::Blockchain blockchain;
    Block::User nick;
    Block::Signature sign;
    nick.create("Nick");
    blockchain.set_user(nick);
    double amount = 100.0;
    auto message = Block::Signature::create_message(Block::Blockchain::coinbase,nick,amount);
    std::string signature = sign.sign(message,nick.get_key().get_private_key());
    bool r = blockchain.new_transaction(Block::Blockchain::coinbase,nick,amount,signature);
    EXPECT_EQ(r,true);
    
    Block::User tom;
    tom.create("Tom");
    blockchain.set_user(tom);
    auto msg = Block::Signature::create_message(nick,tom,100);
    std::string new_sign = sign.sign(msg,nick.get_key().get_private_key());
    bool result = blockchain.new_transaction(nick,tom,100,new_sign);
    EXPECT_EQ(result,true);

    Block::User bob;
    bob.create("Bob");
    blockchain.set_user(bob);
    msg = Block::Signature::create_message(tom,bob,10);
    new_sign = sign.sign(msg,tom.get_key().get_private_key());
    result = blockchain.new_transaction(tom,bob,10,new_sign);
    EXPECT_EQ(result,true);

    blockchain.get_current_block().mine();
    EXPECT_EQ(blockchain.get_current_block().validate(),true);
    blockchain.add_block(blockchain.get_current_block());

    msg = Block::Signature::create_message(tom,bob,10);
    new_sign = sign.sign(msg,tom.get_key().get_private_key());
    result = blockchain.new_transaction(tom,bob,10,new_sign);
    EXPECT_EQ(result,true);
    blockchain.get_current_block().mine();
    blockchain.add_block(blockchain.get_current_block());

    msg = Block::Signature::create_message(tom,bob,10);
    new_sign = sign.sign(msg,tom.get_key().get_private_key());
    result = blockchain.new_transaction(tom,bob,10,new_sign);
    EXPECT_EQ(result,true);
    blockchain.get_current_block().mine();
    blockchain.add_block(blockchain.get_current_block());

    msg = Block::Signature::create_message(tom,bob,10);
    new_sign = sign.sign(msg,tom.get_key().get_private_key());
    result = blockchain.new_transaction(tom,bob,10,new_sign);
    EXPECT_EQ(result,true);
    blockchain.get_current_block().mine();
    blockchain.add_block(blockchain.get_current_block());

    msg = Block::Signature::create_message(tom,bob,10);
    new_sign = sign.sign(msg,tom.get_key().get_private_key());
    result = blockchain.new_transaction(tom,bob,10,new_sign);
    EXPECT_EQ(result,true);
    std::cout << blockchain.get_readable_current_block();
    
    std::cout << blockchain.get_readable_block(0);
}

TEST(Blockchain, ReadFiles)
{
    Block::Blockchain blockchain;
    EXPECT_NE(blockchain.get_blocks().size(),0);
}

}
