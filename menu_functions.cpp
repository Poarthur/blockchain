#include "menu_functions.h"

unsigned show_menu()
{
    clear_menu();
    unsigned result = 0u;
    std::cout << "Enter the appropriate number and press Enter:" << std::endl;
    std::cout << "1 Add new user" << std::endl;
    std::cout << "2 Add transaction" << std::endl;
    std::cout << "3 Add coinbase transaction" << std::endl;
    std::cout << "4 Show all users" << std::endl;
    std::cout << "5 Show all blocks" << std::endl;
    std::cout << "6 Show one block by index" << std::endl;
    std::cout << "7 Mine the block" << std::endl;
    std::cout << "8 Change mining difficulty" << std::endl;
    std::cout << "0 or any other to exit" << std::endl;
    std::cout << "Your choise is: ";
    std::cin >> result;
    clear_menu();
    return result > menu_count ? 0u : result;
}

functions init_menu_choices()
{
    functions list;
    list[1] = add_user;
    list[2] = add_transaction;
    list[3] = add_coinbase_transaction;
    list[4] = show_all_users;
    list[5] = show_all_blocks;
    list[6] = show_one_block;
    list[7] = mine_the_block;
    list[8] = change_difficulty;
    return list;
}

void add_user(Block::Blockchain& blockchain)
{
    std::string name;
    std::cout << "Write username: ";
    std::getline(std::cin >> std::ws, name);
    std::cin.putback('\n');
    Block::User user;
    user.create(name);
    blockchain.set_user(user);
    user.save_user();
    std::cout << "The user was successfully created!" << std::endl;
}

void add_transaction(Block::Blockchain& blockchain)
{
    std::string user_name;
    std::cout << "Enter the name of the person making the transaction:" << std::endl;
    std::getline(std::cin >> std::ws, user_name);
    Block::User user_from;
    Block::User user_to;
    Block::Signature sign;
    double amount = 0.0;
    try
    {
        user_from = blockchain.find_user(user_name);
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
        return;
    }
    std::cout << "Enter the username for which the transaction is being made:" << std::endl;
    std::getline(std::cin >> std::ws, user_name);
    try
    {
        user_to = blockchain.find_user(user_name);
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
        return;
    }
    std::cout << "Enter amount:" << std::endl;
    std::cin >> amount;
    if(amount < 0)
    {
        std::cout << "The amount must be greater than 0" << std::endl;
        return;
    }
    auto msg = Block::Signature::create_message(user_from,user_to,amount);
    std::string signature = sign.sign(msg,user_from.get_key().get_private_key());
    bool result = blockchain.new_transaction(user_from,user_to,amount,signature);
    if(result)
    {
        std::cout << "Transaction completed successfully!" << std::endl;
    } else
    {
        std::cout << "The transaction failed! Check the correctness of the data" << std::endl;
    }
}

void add_coinbase_transaction(Block::Blockchain& blockchain)
{
    std::string user_name;
    std::cout << "Enter the username for which the transaction is being made:" << std::endl;
    std::getline(std::cin >> std::ws, user_name);
    Block::User user;
    Block::Signature sign;
    double amount = 0.0;
    try
    {
        user = blockchain.find_user(user_name);
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
        return;
    }
    std::cout << "Enter amount:" << std::endl;
    std::cin >> amount;
    if(amount < 0)
    {
        std::cout << "The amount must be greater than 0" << std::endl;
        return;
    }
    auto message = Block::Signature::create_message(Block::Blockchain::coinbase,user,amount);
    std::string signature = sign.sign(message,user.get_key().get_private_key());
    bool result = blockchain.new_transaction(Block::Blockchain::coinbase,user,amount,signature);
    if(result)
    {
        std::cout << "Transaction completed successfully!" << std::endl;
    } else
    {
        std::cout << "The transaction failed! Check the correctness of the data" << std::endl;
    }
}

void show_all_users(Block::Blockchain& blockchain)
{
    std::cout << "User list:\n" << std::endl;
    if(!blockchain.get_users_count())
    {
        std::cout << "Is empty" << std::endl;
        return;
    }
    for(const auto& i : blockchain.get_users())
    {
        std::cout << i.get_name() << std::endl;
    }
}

void show_all_blocks(Block::Blockchain& blockchain)
{
    std::cout.flush();
    for(size_t i = 0u, count = blockchain.get_blocks_count(); i < count; ++i)
    std::cout << blockchain.get_readable_block(i) << std::endl;
    std::cout << blockchain.get_current_block().convert_to_readfble(blockchain.get_users()) << std::endl;
}

void show_one_block(Block::Blockchain& blockchain)
{
    std::cout.flush();
    size_t index = 0u;
    std::cout << "Enter block index to output" << std::endl;
    std::cin >> index;
    try
    {
        if(index == blockchain.get_blocks_count())
        std::cout << blockchain.get_current_block().convert_to_readfble(blockchain.get_users()) << std::endl;
        else
        std::cout << blockchain.get_readable_block(index) << std::endl;
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }
}

void mine_the_block(Block::Blockchain& blockchain)
{
    std::cout << "Mining..." << std::endl;
    blockchain.get_current_block().mine();
    if(blockchain.get_current_block().validate())
    {
        std::cout << "Mining completed successfully" << std::endl;
        if(!blockchain.add_block(blockchain.get_current_block()))
        std::cout << "But the block was not added because it has no transactions" << std::endl;
    } else
    {
        std::cout << "The data in the block is not valid, the block was not added" << std::endl;
    }
}

void change_difficulty(Block::Blockchain& blockchain)
{
    std::cout << "Enter a new difficulty value. Current value = "
            << blockchain.get_current_block().get_header().get_difficulty()<< std::endl;
    uint16_t new_difficulty = 0u;
    std::cin >> new_difficulty;
    blockchain.get_current_block().get_header().set_difficulty(new_difficulty);
}
