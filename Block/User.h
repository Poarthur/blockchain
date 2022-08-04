#pragma once
#include "Key.h"

namespace Block
{
class User
{
public:
    static constexpr std::string_view dir_name = "./users";
    static constexpr std::string_view private_extention = ".private";
    static constexpr std::string_view public_extention = ".public";
public:
    User() = default;
    User(std::string_view name);
    bool save_user() const;
    bool load_user();
    void create(std::string_view name);
    const Key& get_key() const noexcept {return _key;}
    const std::string get_name() const noexcept {return _name;}
    bool operator<(const User& user) const;
    operator std::string_view();
private:
    Key _key;
    std::string _name;
};
} // namespace Block
