#include "Key.h"
#include <cstdio>
#include <openssl/bn.h>
#include <openssl/rsa.h>
#include <openssl/pem.h>
#include <openssl/bio.h>
#include <fstream>

namespace Block
{
void Key::generate(size_t key_size)
{
    EVP_PKEY* rsa_key = EVP_RSA_gen(key_size); //Generate pair of keys
    BIO* pipe = BIO_new(BIO_s_mem()); // Basic Input Output to RAM
    try{
        if(!rsa_key)
        {
            throw std::logic_error("RSA generation failed");
        }
        char* private_key_text = nullptr;
        char* public_key_text = nullptr;
        if (!PEM_write_bio_PrivateKey(pipe, rsa_key, nullptr, nullptr, 0, nullptr, nullptr))
        {
            throw std::logic_error("RSA generation private file error");
        }
        BIO_flush(pipe);
        long bio_size = BIO_get_mem_data(pipe, &private_key_text);
        _private_key.assign(private_key_text,bio_size);
        BIO_free_all(pipe);
        pipe = BIO_new(BIO_s_mem());
        if (!PEM_write_bio_PUBKEY(pipe, rsa_key))
        {
            throw std::logic_error("RSA generation public file error");
        }
        BIO_flush(pipe);
        bio_size = BIO_get_mem_data(pipe, &public_key_text);
        _public_key.assign(public_key_text,bio_size);
        BIO_free_all(pipe);
        EVP_PKEY_free(rsa_key);
    }
    catch(...)
    {
        BIO_free_all(pipe);
        EVP_PKEY_free(rsa_key);
        throw;
    }
}

void Key::set_public_key(std::string_view key)
{
    _public_key.assign(key.cbegin(),key.size());
}

void Key::set_private_key(std::string_view key)
{
    _private_key.assign(key.cbegin(),key.size());
}

bool Key::load_public_key(std::string_view file_name)
{
    std::ifstream file(file_name);
    if(!file) return false;
    file >> _public_key;
    return true;
}

bool Key::load_private_key(std::string_view file_name)
{
    std::ifstream file(file_name);
    if(!file) return false;
    file >> _private_key;
    return true;
}

bool Key::save_public_key(std::string_view file_name)
{
    std::ofstream file(file_name);
    if(!file) return false;
    file << _public_key;
    return true;
}

bool Key::save_private_key(std::string_view file_name)
{
    std::ofstream file(file_name);
    if(!file) return false;
    file << _private_key;
    return true;
}

bool Key::is_empty() const noexcept
{
    return _public_key.empty() || _private_key.empty();
}

}//namespace Block
