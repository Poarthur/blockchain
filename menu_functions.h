#pragma once
#include <iostream>
#include <map>
#include <functional>
#include <Blockchain.h>
#include <cstdlib>

using function = std::function<void(Block::Blockchain&, Block::Key&)>;
using functions = std::map<unsigned,function>;

inline void clear()
{
#ifdef _WIN32
std::system("cls");
#elif _WIN64
std::system("cls");
#else
std::system("clear");
#endif
}

void show_menu();

void add_transaction(Block::Blockchain& blockchain, Block::Key& my_key);
void show_all_blocks(Block::Blockchain& blockchain, Block::Key& my_key);
void show_one_block(Block::Blockchain& blockchain, Block::Key& my_key);
void mine_the_block(Block::Blockchain& blockchain, Block::Key& my_key);
void change_difficulty(Block::Blockchain& blockchain, Block::Key& my_key);

functions init_menu_choices();
