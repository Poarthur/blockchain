#pragma once
#include <string>

namespace Block
{
class Key
{
public:
    bool generate();
    std::string get_public_key() const;
    std::string get_private_key() const;
private:
    std::string _public_key;
    std::string _private_key;
};
}//namespace Block
