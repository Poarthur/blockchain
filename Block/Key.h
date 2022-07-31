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
private:
    std::string _public_key;
    std::string _private_key;
};
}//namespace Block
