#ifndef AESCRYPTO_HPP
#define AESCRYPTO_HPP

#include "crypto.hpp"
#include <sstream>
#include <iomanip>
#include <string>
#include <sha.h>
#include <base64.h>
#include <aes.h>
#include <modes.h>


class AESCrypto : public Crypto {

private:
    std::string key;    // 加密密钥
    std::string iv;     // 初始向量

    /**
     * @brief PKCS7填充
     * @param const std::string& str - 需要填充的字符串
     * @return std::string - 填充后的字符串
     */
    std::string pad_pkcs7(const std::string& str);

    /**
     * @brief PKCS7去填充
     * @param const std::string& str - 需要去填充的字符串
     * @return std::string - 去填充后的字符串
     */
    std::string unpad_pkcs7(const std::string& str);

    /**
     * @brief 将字符串转为十六进制
     * @param const std::string& input - 需要转换的字符串
     * @return std::string - 转换后的字符串
     */
    std::string to_hex(const std::string& input);

public:
    /**
     * @brief 构造函数
     * @param std::string key - 用户设定的密钥
     * @param std::string iv - 用户设定的初始向量
     */
    AESCrypto(std::string key, std::string iv);

    /**
     * @brief AES加密
     * @param std::string plaintext - 需要加密的明文
     * @return std::string - 加密后的密文
     */
    std::string encrypt(std::string plaintext) noexcept override;

    /**
     * @brief AES解密
     * @param std::string ciphertext - 需要解密的密文
     * @return std::string - 解密后的明文
     */
    std::string decrypt(std::string ciphertext) noexcept override;

};

#endif // AESCRYPTO_HPP
