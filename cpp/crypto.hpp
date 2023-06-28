#ifndef CRYPTO_HPP
#define CRYPTO_HPP


#if defined(_WIN32)
#define NOEXCEPT noexcept
#else
#define NOEXCEPT
#endif


#include <string>

class Crypto {

public:
    virtual std::string encrypt(const std::string plaintext) NOEXCEPT = 0;
    virtual std::string decrypt(const std::string ciphertext) NOEXCEPT = 0;
};


#endif // CRYPTO_HPP
