#ifndef CRYPTO_HPP
#define CRYPTO_HPP

#include <string>

class Crypto {

public:
    virtual ~Crypto() = default;
    
    virtual std::string encrypt(const std::string plaintext) = 0;
    virtual std::string decrypt(const std::string ciphertext) = 0;
};


#endif // CRYPTO_HPP
