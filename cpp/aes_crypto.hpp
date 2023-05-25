#ifndef AESCRYPTO_HPP
#define AESCRYPTO_HPP

#include <sstream>
#include <iomanip>
#include <string>
#include <sha.h>
#include <base64.h>
#include <aes.h>
#include <modes.h>


class AESCrypto {

private:
    std::string key;    // 加密密钥（不可泄露）
    std::string iv;     // 随机向量（只为确保随机性，泄露不影响密文强度）

    //************************************
    // Method:      pad_pkcs7
    // Description: PKCS7填充（不能使用 Crypto++ 内置的填充算法，否则无法与 python 相互加解密）
    // Parameter:   const std::string& str 需要填充的字符串
    // Returns:     std::string 填充后的字符串
    //************************************
    std::string pad_pkcs7(const std::string& str);

    //************************************
    // Method:      unpad_pkcs7
    // Description: PKCS7去填充（不能使用 Crypto++ 内置的填充算法，否则无法与 python 相互加解密）
    // Parameter:   const std::string& str 需要去填充的字符串
    // Returns:     std::string 去填充后的字符串
    //************************************
    std::string unpad_pkcs7(const std::string& str);

    //************************************
    // Method:      to_hex
    // Description: 将字符串转为十六进制
    // Parameter:   const std::string& input 需要转换的字符串
    // Returns:     std::string 转换后的字符串
    //************************************
    std::string to_hex(const std::string& input);

public:
    //************************************
    // Method:      AESCrypto
    // Description: 构造函数
    // Parameter:   std::string key 用户设定的密钥
    // Parameter:   std::string iv 用户设定的初始向量
    //************************************
    AESCrypto(std::string key, std::string iv);

    //************************************
    // Method:      encrypt
    // Description: AES加密
    // Parameter:   std::string plaintext 需要加密的明文
    // Returns:     std::string 加密后的密文
    //************************************
    std::string encrypt(std::string plaintext);

    //************************************
    // Method:      decrypt
    // Description: AES解密
    // Parameter:   std::string ciphertext 需要解密的密文
    // Returns:     std::string 解密后的明文
    //************************************
    std::string decrypt(std::string ciphertext);

};

#endif // AESCRYPTO_HPP
