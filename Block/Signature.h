#pragma once
#include <string>

namespace Block
{
class Signature
{
public:
    bool verify(std::string_view message, std::string_view public_key, std::string_view signature) const;
    std::string sign(std::string_view message, std::string_view private_key) const;
};
}//namespace Block