#include "Sha256.h"

#include <sstream>
#include <algorithm>
#include <openssl/sha.h>

namespace Block
{
Sha256::Sha256(const std::string_view buf)
{
    make_sha256(buf);
}

void Sha256::make_sha256(const std::string_view value)
{
    char result[sha256_size];
    char buf[value.size() + 1];
    std::strcpy(buf,value.cbegin());
    if(!SHA256(reinterpret_cast<unsigned char*>(buf),value.size(),reinterpret_cast<unsigned char*>(result)))
    {
        throw std::logic_error("Cannot create ssh256");
    }
    _hash.assign(result,sha256_size);
}

std::string Sha256::sha256_to_ascii() const
{
    std::ostringstream stream;
    std::for_each(_hash.cbegin(), _hash.cend(), [&](auto& ch){
        if((int)(unsigned char)ch < 0x10) stream << 0;
        stream << std::hex << (int)(unsigned char)ch;});
    return stream.str();
}
std::string Sha256::sha256_from_ascii(const std::string_view buf) const
{
    constexpr int num_base = 16;
    const unsigned buf_size = buf.size();
    std::string txt;
    txt.reserve(sha256_size);
    if(buf_size == 0)
    {
        return "";
    }
    if(buf_size != sha256_size * 2)
    {
        throw std::logic_error("Wrong argument");
    }
    for(int i = 0; i < buf_size; i+=2)
    {
        std::ostringstream str_hex_num;
        str_hex_num << buf[i] << buf[i+1];
        short hex_num = std::stoul(str_hex_num.str(),nullptr,num_base);
        txt.push_back(hex_num);
    }
    return txt;
}

Sha256::operator std::string()
{
    return sha256_to_ascii();
}

std::ostream& operator<<(std::ostream& output, Sha256& sha)
{
    output << sha.sha256_to_ascii();
    return output;
}

std::string Sha256::get_hash() const
{
    return sha256_to_ascii();
}

const Sha256& Sha256::set_hash(std::string_view hash)
{
    _hash = sha256_from_ascii(hash);
    return *this;
}

}//namespace Block
