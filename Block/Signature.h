#pragma once
#include <string>

namespace Block
{
class Signature
{
    std::string base64_encode(std::string_view signature) const;
    std::string base64_decode(std::string_view message) const;
public:
    bool verify(std::string_view message, std::string_view public_key, std::string_view signature) const;
    std::string sign(std::string_view message, std::string_view private_key) const;
    static std::string create_message(std::string_view from, std::string_view to, double amount);
};
}//namespace Block