#pragma once
#include "Header.h"
#include "User.h"
#include <iostream>
#include <string>
#include <vector>
#include <tuple>
#include <set>

namespace Block
{
class Block
{
    using Transaction = std::tuple<std::string,std::string,double,std::string>;
public:
    static constexpr int i_from = 0;
    static constexpr int i_to = 1;
    static constexpr int i_amount = 2;
    static constexpr int i_sig = 3;
    //using Transaction_ref = std::optional<std::reference_wrapper<const Transaction>>;
private:
    std::string block_to_text(uint64_t nonce) const;
    int check_hash_zeros(std::string_view hash) const;
public:
    void mine();
    void add_transaction(std::string_view from, std::string_view to, double amount, std::string_view sig);
    size_t get_count_of_transactions() const {return _transactions.size();}
    Header& get_header() noexcept {return _header;}
    void set_header(const Header& header);
    bool validate() const;
    void clear();
    std::vector<Transaction> find_from(std::string_view from) const noexcept;
    std::vector<Transaction> find_to(std::string_view to) const noexcept;
    const Transaction& operator[](size_t i) const;
    friend std::ostream& operator<<(std::ostream& output, const Block& block);
    friend std::istream& operator>>(std::istream& input, Block& block);
    std::string convert_to_readfble(const std::set<User>& users) const;
private:
    Header _header;
    std::vector<Transaction> _transactions;
};
} // namespace Block
