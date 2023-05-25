#include "aes_crypto.hpp"


AESCrypto::AESCrypto(std::string key, std::string iv) {
    CryptoPP::SHA256 hash;
    CryptoPP::byte digestKey[CryptoPP::SHA256::DIGESTSIZE];
    hash.CalculateDigest(digestKey, (CryptoPP::byte*)key.c_str(), key.length());
    this->key = std::string((char*)digestKey, CryptoPP::SHA256::DIGESTSIZE);

    CryptoPP::byte digestIv[CryptoPP::SHA256::DIGESTSIZE];
    hash.CalculateDigest(digestIv, (CryptoPP::byte*)iv.c_str(), iv.length());
    this->iv = std::string((char*)digestIv, CryptoPP::SHA256::DIGESTSIZE).substr(0, CryptoPP::AES::BLOCKSIZE);
}

std::string AESCrypto::encrypt(std::string plaintext) {
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

std::string AESCrypto::decrypt(std::string ciphertext) {
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

std::string AESCrypto::pad_pkcs7(const std::string& str) {
    using namespace CryptoPP;
    int padding = AES::BLOCKSIZE - (str.size() % AES::BLOCKSIZE);
    std::string result = str;
    result.append(padding, (char)padding);
    return result;
}

std::string AESCrypto::unpad_pkcs7(const std::string& str) {
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

std::string AESCrypto::to_hex(const std::string& input) {
    std::ostringstream oss;
    for (const auto& c : input) {
        oss << std::hex << std::setw(2) << std::setfill('0') << static_cast<int>(static_cast<unsigned char>(c));
    }
    return oss.str();
}

