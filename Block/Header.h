#pragma once
#include <cstdint>
#include <string>

namespace Block
{
class Header final
{
    static constexpr uint16_t default_difficulty = 4;
public:
    void set_hash(std::string_view hash);
    void set_prev_hash(std::string_view prev_hash);
    void set_index(uint32_t index);
    void set_nonce(uint64_t nonce);
    void set_difficulty(uint16_t difficulty);
    const std::string& get_hash() const noexcept {return _hash;}
    const std::string& get_prev_hash() const noexcept {return _prev_hash;}
    uint32_t get_index() const noexcept {return _index;}
    uint64_t get_nonce() const noexcept {return _nonce;}
    uint16_t get_difficulty() const noexcept {return _difficulty;}
    bool is_mined() const noexcept;
private:
    uint16_t _difficulty = default_difficulty;
    uint32_t _index = 0;
    uint64_t _nonce = 0;
    std::string _hash;
    std::string _prev_hash;
};
} // namespace Block