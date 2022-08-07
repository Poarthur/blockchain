#pragma once
#include <string>

namespace Block
{
class Key
{
public:
    void generate(size_t key_size = 1024);
    const std::string& get_public_key() const {return _public_key;}
    const std::string& get_private_key() const {return _private_key;}
    void set_public_key(std::string_view key);
    void set_private_key(std::string_view key);
    bool save_public_key(std::string_view file_name);
    bool save_private_key(std::string_view file_name);
    bool load_public_key(std::string_view file_name);
    bool load_private_key(std::string_view file_name);
    bool is_empty() const noexcept;
private:
    std::string _public_key;
    std::string _private_key;
};
}//namespace Block
