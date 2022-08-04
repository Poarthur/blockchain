#include "User.h"
#include <filesystem>
#include <fstream>
#include <sstream>
#include <iostream>

namespace Block
{

User::User(std::string_view name)
{
    _name = name.data();
}

bool User::operator<(const User& user) const
{
    return _name < user._name;
}

bool User::save_user() const
{
    namespace fs = std::filesystem;
    if(_key.is_empty() || _name.empty()) return false;
    fs::path path = dir_name.data();
    if(!exists(path))
    {
        if(!fs::create_directories(path))
        throw std::logic_error("Cannot create a dir, please check the permissions");
    }
    if(!_key.get_private_key().empty())
    {
        std::string private_name = path.c_str() + std::string("/") + _name + private_extention.data();
        std::ofstream private_file(private_name);
        if(!private_file) return false;
        private_file << _key.get_private_key();
    }
    if(!_key.get_public_key().empty())
    {
        std::string public_name = path.c_str() + std::string("/") + _name + public_extention.data();
        std::ofstream public_file(public_name);
        if(!public_file) return false;
        public_file << _key.get_public_key();
    }
    return true;
}

bool User::load_user()
{
    namespace fs = std::filesystem;
    fs::path path = dir_name.data();
    if(!exists(path)) return false;

    std::string public_name = path.c_str() + std::string("/") + _name + public_extention.data();
    std::ifstream public_file(public_name);
    if(!public_file) return false;
    std::stringstream public_buffer;
    public_buffer << public_file.rdbuf();
    _key.set_public_key(public_buffer.str());
    public_file.close();

    std::string private_name = path.c_str() + std::string("/") + _name + private_extention.data();
    std::ifstream private_file(private_name);
    if(!private_file) return false;
    std::stringstream private_buffer;
    private_buffer << private_file.rdbuf();
    _key.set_private_key(private_buffer.str());
    return true;
}

void User::create(std::string_view name)
{
    _key.generate();
    _name = name.data();
}

User::operator std::string_view()
{
    return _key.get_public_key();
}

} // namespace Block
