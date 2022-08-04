#include "Block.h"
#include "Sha256.h"
#include <fstream>
#include <sstream>
#include <algorithm>
#include <nlohmann/json.hpp>
#include <iostream>
#include <map>

namespace Block
{
const Block::Transaction& Block::operator[](size_t i) const
{
    if(i >= _transactions.size())
    {
        throw std::logic_error("Incorrect index");
    }
    return _transactions[i];
}

int Block::check_hash_zeros(std::string_view hash) const
{
    uint16_t count_of_zero = 0;
    uint16_t difficulty = _header.get_difficulty();
    for(uint16_t i = 0; i < difficulty; ++i)
    {
        if(hash[i] == '0')
        {
            ++count_of_zero;
        }
    }
    return count_of_zero;
}

std::string Block::block_to_text(uint64_t nonce) const
{
    std::ostringstream data_for_mining;
    data_for_mining << _header.get_difficulty()
                    << _header.get_index()
                    << nonce
                    << _header.get_prev_hash();
    for(int i = 0; i < _transactions.size(); ++i)
    {
        data_for_mining << std::get<i_from>(_transactions[i])
                        << std::get<i_to>(_transactions[i])
                        << std::get<i_amount>(_transactions[i])
                        << std::get<i_sig>(_transactions[i]);
    }
    return data_for_mining.str();
}

void Block::mine()
{
    Sha256 hash;
    uint64_t nonce = 0;
    while(true)
    {
        hash.make_sha256(block_to_text(nonce));
        std::string current_hash = hash;
        uint16_t count_of_zero = 0;
        count_of_zero = check_hash_zeros(current_hash);
        if(count_of_zero == _header.get_difficulty())
        {
            _header.set_nonce(nonce);
            _header.set_hash(current_hash);
            break;
        }
        ++nonce;
    }
}

bool Block::validate() const
{
    Sha256 hash(block_to_text(_header.get_nonce()));
    return check_hash_zeros(hash.get_hash()) == _header.get_difficulty();
}

void Block::add_transaction(std::string_view from, std::string_view to, double amount, std::string_view sig)
{
    _transactions.emplace_back(from,to,amount,sig);
}

std::vector<Block::Transaction> Block::find_from(std::string_view from) const noexcept
{
    std::vector<Block::Transaction> results;
    for(const auto& i : _transactions)
    {
        if(std::get<i_from>(i) == from.data())
        {
            results.push_back(i);
        }
    }
    return results;
}

std::vector<Block::Transaction> Block::find_to(std::string_view to) const noexcept
{
    std::vector<Block::Transaction> results;
    for(const auto& i : _transactions)
    {
        if(std::get<i_to>(i) == to.data())
        {
            results.push_back(i);
        }
    }
    return results;
}

std::string Block::convert_to_readfble(const std::set<User>& users) const
{
    std::stringstream output;
    output << std::setw(4);
    nlohmann::ordered_json json;
    //Header
    json["difficulty"] = _header.get_difficulty();
    json["index"] = _header.get_index();
    json["nonce"] = _header.get_nonce();
    json["hash"] = _header.get_hash();
    json["prev_hash"] = _header.get_prev_hash();
    //Transactions
    nlohmann::ordered_json lists;
    for(const auto& i : _transactions)
    {
        nlohmann::ordered_json list;
        std::string from;
        std::string to;
        for(const auto& user : users)
        {
            if(user.get_key().get_public_key() == std::get<Block::i_from>(i))
            {
                from = user.get_name();
            }
            if(user.get_key().get_public_key() == std::get<Block::i_to>(i))
            {
                to = user.get_name();
            }
        }
        std::string signature = std::get<Block::i_sig>(i);
        signature.resize(76);
        list.push_back({{"from", from.empty() ? std::get<Block::i_from>(i) : from}});
        list.push_back({{"to", to.empty() ? std::get<Block::i_to>(i) : to}});
        list.push_back({{"amount:",std::get<Block::i_amount>(i)}});
        list.push_back({"signature:",signature + "..."});
        lists.push_back(list);
    }
    json["tx"] = lists;
    output << json;
    return output.str();
}

std::ostream& operator<<(std::ostream& output, const Block& block)
{
    // from the nlohmann/json lib:
    // the setw manipulator was overloaded to set the indentation for pretty printing
    output << std::setw(4);
    nlohmann::ordered_json json;
    //Header
    json["difficulty"] = block._header.get_difficulty();
    json["index"] = block._header.get_index();
    json["nonce"] = block._header.get_nonce();
    json["hash"] = block._header.get_hash();
    json["prev_hash"] = block._header.get_prev_hash();
    //Transactions
    nlohmann::ordered_json lists;
    for(const auto& i : block._transactions)
    {
        nlohmann::ordered_json list;
        list.push_back(std::get<Block::i_from>(i));
        list.push_back(std::get<Block::i_to>(i));
        list.push_back(std::get<Block::i_amount>(i));
        list.push_back(std::get<Block::i_sig>(i));
        lists.push_back(list);
    }
    json["tx"] = lists;
    output << json;
    return output;
}

std::istream& operator>>(std::istream& input, Block& block)
{
    nlohmann::ordered_json json = nlohmann::ordered_json::parse(input);
    //Header
    block._header.set_difficulty(json["difficulty"].get<uint16_t>());
    block._header.set_index(json["index"].get<uint32_t>());
    block._header.set_nonce(json["nonce"].get<uint64_t>());
    block._header.set_hash(json["hash"].get<std::string>());
    block._header.set_prev_hash(json["prev_hash"].get<std::string>());
    //Transactions
    block._transactions = json["tx"].get<std::vector<Block::Transaction>>();
    return input;
}

void Block::set_header(const Header& header)
{
    _header = header;
}

void Block::clear()
{
    _transactions.clear();
}

} // namespace Blockclass Block
