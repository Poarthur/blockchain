#pragma once
#include <string>

namespace Block
{
class Sha256 final
{
public:
    static constexpr unsigned sha256_size = 32;
    using sha256 = unsigned char[sha256_size];
public:
    Sha256() = default;
    Sha256(const std::string_view buf);
    ~Sha256() = default;
    void make_sha256(const std::string_view buf);
    std::string sha256_to_ascii() const;
    std::string sha256_from_ascii(const std::string_view buf) const;
    operator const std::string&();
    friend std::ostream& operator<<(std::ostream& output, Sha256& sha);
    const std::string& get_hash() const;
private:
    std::string _hash;
};
}//namespace Block
