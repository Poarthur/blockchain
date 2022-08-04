#include "Header.h"

namespace Block
{
void Header::set_hash(std::string_view hash)
{
    _hash.assign(hash.data(), hash.size());
}

void Header::set_prev_hash(std::string_view prev_hash)
{
    _prev_hash.assign(prev_hash.data(),prev_hash.size());
}

void Header::set_index(uint32_t index)
{
    _index = index;
}

void Header::set_nonce(uint64_t nonce)
{
    _nonce = nonce;
}

void Header::set_difficulty(uint16_t difficulty)
{
    _difficulty = difficulty;
}

bool Header::is_mined() const noexcept
{
    if(_hash.size() < _difficulty) return false;
    for(uint16_t i = 0; i < _difficulty; ++i)
    {
        if(_hash[i] != '0') return false;
    }
    return true;
}
} // namespace Block
