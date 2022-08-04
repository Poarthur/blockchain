#include "Blockchain.h"
#include "Signature.h"
#include <algorithm>
#include <filesystem>
#include <fstream>
#include <sstream>
#include <nlohmann/json.hpp>

namespace Block
{
Blockchain::Blockchain()
{
    read_blocks_from_files();
    read_users_from_files();
    init_current_block();
}

void Blockchain::init_current_block()
{
    _current_block.get_header().set_index(_blocks.size());
    if(!_blocks.empty())
    {
        _current_block.get_header().set_prev_hash(_blocks.back().get_header().get_hash());
    } else
    {
        std::string null(Sha256::sha256_size*2, '0');
        _current_block.get_header().set_prev_hash(null);
    }
    _current_block.get_header().set_nonce(0);
}

void Blockchain::read_blocks_from_files()
{
    namespace fs = std::filesystem;
    fs::path path = dir_name.data();
    if(!exists(path))
    {
        if(!fs::create_directories(path))
        throw std::logic_error("Cannot create a dir, please check the permissions");
    }
    uint32_t index = 1;
    for(; true; ++index)
    {
        std::string file_name = path.c_str() + std::string("/") + std::to_string(index) + file_extention.data();
        std::ifstream file(file_name);
        if(!file) break;
        Block block;
        file >> block;
        if(!_blocks.empty())
        {
            if(block.get_header().get_prev_hash() != _blocks.back().get_header().get_hash())
            break;
        }
        if(!add_block(block))
        {
            std::cerr << "Block " << file_name << " was corrupted!" << std::endl;
            break;
        }
    }
}

void Blockchain::read_users_from_files()
{
    namespace fs = std::filesystem;
    fs::path path = User::dir_name.data();
    if(!exists(path)) return;
    std::set<std::string> user_names;
    for (const auto & file : fs::directory_iterator(path))
    {
        user_names.insert(file.path().stem());
    }
    for(const auto& i : user_names)
    {
        User user(i);
        if(!user.load_user()) continue;
        _users.insert(user);
    }
}

bool Blockchain::add_block(const Block& block)
{
    namespace fs = std::filesystem;
    if(!block.validate()) return false;
    if(!block.get_count_of_transactions()) return false;
    _blocks.push_back(block);
    fs::path path = dir_name.data();
    std::string file_name = path.c_str() + std::string("/") + std::to_string(_blocks.size()) + file_extention.data();
    if(exists(path))
    {
        std::ofstream file(file_name);
        if(!file) throw std::logic_error("Cannot create a file, please check the permissions");
        file << block;
        file.close();
    }
    _current_block.clear();
    init_current_block();
    return true;
}

const Block& Blockchain::get_block(size_t index) const
{
    if(index >= _blocks.size())
    {
        throw std::logic_error("Incorrect index");
    }
    return _blocks[index];
}

std::string Blockchain::get_readable_block(size_t index) const
{
    if(index >= _blocks.size())
    {
        throw std::logic_error("Incorrect index");
    }
    return _blocks[index].convert_to_readfble(_users);
}

std::string Blockchain::get_readable_current_block() const
{
    return _current_block.convert_to_readfble(_users);
}

const User& Blockchain::find_user(std::string_view name) const
{
    const auto user = _users.find(User(name));
    if(user == _users.cend())
    {
        throw std::logic_error("out of range");
    }
    return *user;
}

void Blockchain::set_user(const User& user)
{
    _users.insert(user);
}

const std::set<User>& Blockchain::get_users() const
{
    return _users;
}

bool Blockchain::validate_transaction(std::string_view from, double amount) const
{
    bool valid = false;
    double credit = 0.0;
    double debet = 0.0;

    std::for_each(_blocks.crbegin(),_blocks.crend(),[&](const Block& block)
    {
        auto validate_blocks = block.find_to(from);
        std::for_each(validate_blocks.crbegin(),validate_blocks.crend(),[&](const auto& transaction)
        {
            credit += std::get<Block::Block::i_amount>(transaction);
        });
    });
    auto to_blocks = _current_block.find_to(from);
    std::for_each(to_blocks.crbegin(),to_blocks.crend(),[&](const auto& transaction)
    {
        credit += std::get<Block::Block::i_amount>(transaction);
    });
    std::for_each(_blocks.crbegin(),_blocks.crend(),[&](const Block& block)
    {
        auto validate_blocks = block.find_from(from);
        std::for_each(validate_blocks.crbegin(),validate_blocks.crend(),[&](const auto& transaction)
        {
            debet += std::get<Block::Block::i_amount>(transaction);
        });
    });
    auto from_blocks = _current_block.find_from(from);
    std::for_each(from_blocks.crbegin(),from_blocks.crend(),[&](const auto& transaction)
    {
        debet += std::get<Block::Block::i_amount>(transaction);
    });
    return (credit - debet) >= amount;
}

bool Blockchain::new_transaction(std::string_view from, std::string_view to, double amount, std::string_view sig)
{
    if(from.compare(coinbase) == 0)
    {
        _current_block.add_transaction(from,to,amount,sig);
        return true;
    }
    if(!validate_transaction(from,amount)) return false;
    std::string message = Signature::create_message(from,to,amount);
    if(!Signature().verify(message,from,sig)) return false;
    _current_block.add_transaction(from,to,amount,sig);
    return true;
}

} // namespace Block
