#pragma once
#include "Block.h"
#include "User.h"
#include "Sha256.h"
#include "Signature.h"
#include <set>

namespace Block
{
class Blockchain final
{
    static constexpr std::string_view dir_name = "./blockchain";
    static constexpr std::string_view file_extention = ".block";
public:
    static constexpr std::string_view coinbase = "coinbase";
private:
    bool validate_transaction(std::string_view from, double amount) const;
    void init_current_block();
public:
    Blockchain();
    void read_blocks_from_files();
    void read_users_from_files();
    bool new_transaction(std::string_view from, std::string_view to, double amount, std::string_view sig);
    bool add_block(const Block& block);
    const Block& get_block(size_t index) const;
    Block& get_current_block() noexcept {return _current_block;}
    const std::vector<Block>& get_blocks() const {return _blocks;}
    const User& find_user(std::string_view name) const;
    void set_user(const User& user);
    const std::set<User>& get_users() const;
    size_t get_blocks_count() const noexcept {return _blocks.size();}
    size_t get_users_count() const noexcept {return _users.size();}
    std::string get_readable_block(size_t index) const;
    std::string get_readable_current_block() const;
private:
    Block _current_block;
    std::vector<Block> _blocks;
    std::set<User> _users;
};
} // namespace Block
