#include "menu_functions.h"

void show_menu()
{
    std::cout << "Enter number:" << std::endl;
    std::cout << "1. Add transaction" << std::endl;
    std::cout << "2. Show all blocks" << std::endl;
    std::cout << "3. Show one block by index" << std::endl;
    std::cout << "4. Mine the block" << std::endl;
    std::cout << "5. Change mining difficulty" << std::endl;
    std::cout << "0. To exit" << std::endl;
}

functions init_menu_choices()
{
    functions list;
    list.emplace(1,add_transaction);
    list.emplace(2,show_all_blocks);
    list.emplace(3,show_one_block);
    list.emplace(4,mine_the_block);
    list.emplace(5,change_difficulty);
    return list;
}

void add_transaction(Block::Blockchain& blockchain, Block::Key& my_key)
{
    std::cout << "1. to do! check the amount" << std::endl;
}

void show_all_blocks(Block::Blockchain& blockchain, Block::Key& my_key)
{
    std::cout << "2. to do! check the amount" << std::endl;
}

void show_one_block(Block::Blockchain& blockchain, Block::Key& my_key)
{
    std::cout << "3. to do! check the amount" << std::endl;
}

void mine_the_block(Block::Blockchain& blockchain, Block::Key& my_key)
{
    std::cout << "4. to do! check the amount" << std::endl;
}

void change_difficulty(Block::Blockchain& blockchain, Block::Key& my_key)
{
    std::cout << "5. to do! check the amount" << std::endl;
}
