#ifndef CRYPTO_HPP
#define CRYPTO_HPP

#include <string>

class Crypto {

public:
    virtual std::string encrypt(const std::string plaintext) = 0;
    virtual std::string decrypt(const std::string ciphertext) = 0;

    virtual ~Crypto() = default;
};


#endif // CRYPTO_HPP
