#include <string>
#include <sstream>
#include <iostream>
#include <iomanip>

#include <sha.h>
#include <base64.h>
#include <aes.h>
#include <modes.h>



class AESCrypto {

private:
    std::string key;    // 加密密钥（不可泄露）
    std::string iv;     // 随机向量（只为确保随机性，泄露不影响密文强度）

public:

    /*
     * 构造函数
     *   使用 sha256 处理 key 和 IV
     *   使其满足 AES 密钥长度要求（AES 仅接受 16、24、32 字节长度的密钥）
     */
    AESCrypto(std::string key, std::string iv) {
        CryptoPP::SHA256 hash;
        CryptoPP::byte digestKey[CryptoPP::SHA256::DIGESTSIZE];
        hash.CalculateDigest(digestKey, (CryptoPP::byte*)key.c_str(), key.length());
        this->key = std::string((char*)digestKey, CryptoPP::SHA256::DIGESTSIZE);

        CryptoPP::byte digestIv[CryptoPP::SHA256::DIGESTSIZE];
        hash.CalculateDigest(digestIv, (CryptoPP::byte*)iv.c_str(), iv.length());
        this->iv = std::string((char*)digestIv, CryptoPP::SHA256::DIGESTSIZE).substr(0, CryptoPP::AES::BLOCKSIZE);
    }

    std::string encrypt(std::string plaintext) {
        using namespace CryptoPP;
        CBC_Mode< AES >::Encryption aes;
        aes.SetKeyWithIV((byte*)this->key.c_str(), this->key.size(), (byte*)this->iv.c_str());

        // 填充明文
        std::string paded_plaintext = pad_pkcs7(plaintext);

        // 加密明文
        std::string ciphertext;
        StringSource p2c(paded_plaintext, true,
            new StreamTransformationFilter(aes,
                new StringSink(ciphertext)
            )
        );

        // 对密文进行 base64 编码
        std::string base64_ciphertext;
        StringSource c2b(ciphertext, true,
            new Base64Encoder(
                new StringSink(base64_ciphertext),
                false // don't append a newline
            )
        );
        return base64_ciphertext;
    }

    std::string decrypt(std::string ciphertext) {
        using namespace CryptoPP;
        CBC_Mode< AES >::Decryption aes;
        aes.SetKeyWithIV((byte*)this->key.c_str(), this->key.size(), (byte*)this->iv.c_str());

        // 对密文进行 base64 解码
        std::string unbase64_ciphertext;
        StringSource b2c(ciphertext, true,
            new Base64Decoder(
                new StringSink(unbase64_ciphertext)
            )
        );

        // 解密密文
        std::string paded_plaintext;
        try {
            StringSource c2p(unbase64_ciphertext, true,
                new StreamTransformationFilter(aes,
                    new StringSink(paded_plaintext)
                )
            );
        }
        catch (const Exception& e) {
            return "fail to decrypt";
        }

        // 去除明文的填充字节
        std::string plaintext = unpad_pkcs7(paded_plaintext);
        return plaintext;
    }

    /*
     * 使用 PKCS7 算法填充字符串
     * （不能使用 Crypto++ 内置的填充算法，否则无法与 python 相互加解密）
     */
    std::string pad_pkcs7(const std::string& str) {
        using namespace CryptoPP;
        int padding = AES::BLOCKSIZE - (str.size() % AES::BLOCKSIZE);
        std::string result = str;
        result.append(padding, (char)padding);
        return result;
    }

    /*
     * 使用 PKCS7 算法移除字符串的填充
     * （不能使用 Crypto++ 内置的填充算法，否则无法与 python 相互加解密）
     */
    std::string unpad_pkcs7(const std::string& str) {
        using namespace CryptoPP;
        std::string result = str;
        unsigned char lastChar = result.at(result.size() - 1);
        if (lastChar <= 0x00 || lastChar > AES::BLOCKSIZE) {
            // 有些语言的填充算法，如果被加密串的长度刚好为 BLOCKSIZE 的整数倍，不会填充一个 BLOCK
            // 为了避免这种异常，当发现最后的 BLOCK 不是填充的时候，不做任何操作
            return str;
        }
        result.erase(result.end() - lastChar, result.end());
        return result;
    }

    /*
     * 打印字符串的十六进制字节串
     * （用于调试时比对内容是否一致）
     */
    std::string to_hex(const std::string& input) {
        std::ostringstream oss;
        for (const auto& c : input) {
            oss << std::hex << std::setw(2) << std::setfill('0') << static_cast<int>(static_cast<unsigned char>(c));
        }
        return oss.str();
    }

};
