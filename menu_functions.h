#pragma once

#include <array>
#include <cstdlib>
#include <iostream>
#include <functional>
#include <limits>

#include <Blockchain.h>

#define DECLARE_FUNC(f_name) void f_name(Block::Blockchain& blockchain)

constexpr unsigned menu_count = 8u;
using function = std::function<void(Block::Blockchain&)>;
using functions = std::array<function,menu_count+1>;

inline void clear_menu()
{
#if defined(_WIN32) || defined(_WIN64)
    std::system("cls");
#else
    std::system("clear");
#endif
}

inline void pause_menu()
{
    std::cout << "\nPress Enter to continue..." << std::endl;
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::cin.get();
}

unsigned show_menu();

DECLARE_FUNC(add_user);
DECLARE_FUNC(add_transaction);
DECLARE_FUNC(add_coinbase_transaction);
DECLARE_FUNC(show_all_users);
DECLARE_FUNC(show_all_blocks);
DECLARE_FUNC(show_one_block);
DECLARE_FUNC(mine_the_block);
DECLARE_FUNC(change_difficulty);

functions init_menu_choices();
