#ifndef DES_CRYPTO_HPP
#define DES_CRYPTO_HPP

#include "crypto.hpp"
#include <string>
#include <vector>
#include <des.h>
#include <sha.h>
#include <base64.h>
#include <iostream>
#include <sstream>
#include <filters.h>


class DESCrypto : public Crypto {

private:

    std::string key; // 加密密钥

    /**
     * @brief 对明文进行 PKCS5 填充
     * @param plaintext 需要填充的明文
     * @return 填充后的明文
     */
    char* padding_PKCS5(std::string plaintext);

    /**
     * @brief 对密文进行 PKCS5 解填充
     * @param plain_bytes 需要解填充的密文
     * @return 解填充后的明文
     */
    std::string unpadding_PKCS5(std::vector<unsigned char>& plain_bytes);

public:
    /**
     * @brief 构造函数
     * @param key 用于加密和解密的秘钥
     */
    DESCrypto(std::string key);

    /**
     * @brief 对明文进行加密
     * @param plaintext 明文
     * @return 加密后的密文
     */
    std::string encrypt(std::string plaintext) override;

    /**
     * @brief 对密文进行解密
     * @param ciphertext 密文
     * @return 解密后的明文
     */
    std::string decrypt(std::string ciphertext) override;

};

#endif // DES_CRYPTO_HPP
