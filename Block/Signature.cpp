#include "Signature.h"
#include <openssl/evp.h>
#include <openssl/bio.h>
#include <openssl/pem.h>
#include <iostream>

namespace Block
{
    bool Signature::verify(std::string_view message, std::string_view public_key, std::string_view signature) const
    {
        EVP_PKEY* key  = nullptr;
        BIO* pipe = BIO_new(BIO_s_mem()); // Basic Input Output to RAM
        BIO_write(pipe, public_key.cbegin(), public_key.size());
        EVP_MD_CTX* digest_context = EVP_MD_CTX_new();
        key = PEM_read_bio_PUBKEY(pipe, nullptr, nullptr, nullptr);
        if (!key)
        {
            throw std::logic_error("Key argument problems");
        }
        if (!EVP_DigestVerifyInit(digest_context, nullptr, EVP_sha256(), nullptr, key))
        {
            //digest initializing
            return false;
        }
        if (!EVP_DigestVerifyUpdate(digest_context, message.cbegin(), message.size())) {
            //include the data to the digest
            return false;
        }
        int verification_status = EVP_DigestVerifyFinal(digest_context,
                                    reinterpret_cast<const unsigned char*>(signature.cbegin()),
                                    signature.size());
        BIO_free_all(pipe);
        EVP_MD_CTX_free(digest_context);
        EVP_PKEY_free(key);
        return verification_status == 1;
    }
    std::string Signature::sign(std::string_view message, std::string_view private_key) const
    {
        EVP_MD_CTX* digest_context = EVP_MD_CTX_new();
        EVP_PKEY* key  = nullptr;
        BIO* pipe = BIO_new(BIO_s_mem()); // Basic Input Output to RAM
        BIO_write(pipe, private_key.cbegin(), private_key.size());
        unsigned char* signature = nullptr;
        size_t digest_size = 0;
        std::string return_signature;
        key = PEM_read_bio_PrivateKey(pipe, nullptr, nullptr, nullptr);
        try
        {
            if (!key)
            {
                throw std::logic_error("Key argument problems");
            }
            if (!EVP_DigestSignInit(digest_context, nullptr, EVP_sha256(), nullptr ,key))
            {
                throw std::logic_error("Digest initialization problems");
            }
            //
            if (!EVP_DigestSignUpdate(digest_context, message.cbegin(), message.size())) {
                throw std::logic_error("Digest including data problems");
            }
            if (!EVP_DigestSignFinal(digest_context, nullptr, &digest_size))
            {
                throw std::logic_error("Problems with digest size calculation");
            }
            signature = new unsigned char[digest_size];
            if (!EVP_DigestSignFinal(digest_context, signature, &digest_size))
            {
                throw std::logic_error("Digest signing problems");
            }
            return_signature.assign(reinterpret_cast<char*>(signature),digest_size);
        }
        catch(...)
        {
            delete [] signature;
            BIO_free_all(pipe);
            EVP_PKEY_free(key);
            EVP_MD_CTX_free(digest_context);
            throw;
        }
        delete [] signature;
        BIO_free_all(pipe);
        EVP_PKEY_free(key);
        EVP_MD_CTX_free(digest_context);
        return return_signature;
    }
}//namespace Block
