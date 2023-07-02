/***************************************************\
 * -*- coding: GBK -*-
 * @Author : EXP
 * @Time   : 2022/11/15 23:56
 * -----------------------------------------------
 * AES �ӽ��ܹ���
 * �㷨 CBC�� ���ģʽ PKCS7
\***************************************************/
#include "aes_crypto.hpp"
#include <iostream>


AESCrypto::AESCrypto(std::string key, std::string iv) {
    using namespace CryptoPP;
    SHA256 hash;
    byte digestKey[SHA256::DIGESTSIZE];
    hash.CalculateDigest(digestKey, (byte*)key.c_str(), key.length());
    this->key = std::string((char*)digestKey, SHA256::DIGESTSIZE);

    byte digestIv[SHA256::DIGESTSIZE];
    hash.CalculateDigest(digestIv, (byte*)iv.c_str(), iv.length());
    this->iv = std::string((char*)digestIv, SHA256::DIGESTSIZE).substr(0, AES::BLOCKSIZE);
}

std::string AESCrypto::encrypt(std::string plaintext) NOEXCEPT {
    using namespace CryptoPP;
    CBC_Mode< AES >::Encryption aes;
    aes.SetKeyWithIV((byte*)this->key.c_str(), this->key.size(), (byte*)this->iv.c_str());

    // �������
    std::string paded_plaintext = pad_pkcs7(plaintext);

    // ��������
    std::string ciphertext;
    StringSource p2c(paded_plaintext, true,
        new StreamTransformationFilter(aes,
            new StringSink(ciphertext)
        )
    );

    // �����Ľ��� base64 ����
    std::string base64_ciphertext;
    StringSource c2b(ciphertext, true,
        new Base64Encoder(
            new StringSink(base64_ciphertext),
            false // don't append a newline
        )
    );
    return base64_ciphertext;
}

std::string AESCrypto::decrypt(std::string ciphertext) NOEXCEPT {
    using namespace CryptoPP;
    CBC_Mode< AES >::Decryption aes;
    aes.SetKeyWithIV((byte*)this->key.c_str(), this->key.size(), (byte*)this->iv.c_str());

    // �����Ľ��� base64 ����
    std::string unbase64_ciphertext;
    StringSource b2c(ciphertext, true,
        new Base64Decoder(
            new StringSink(unbase64_ciphertext)
        )
    );

    // ��������
    std::string paded_plaintext;
    try {
        StringSource c2p(unbase64_ciphertext, true,
            new StreamTransformationFilter(aes,
                new StringSink(paded_plaintext)
            )
        );
    } catch (const Exception& e) {
        return "fail to decrypt";
    }

    // ȥ�����ĵ�����ֽ�
    std::string plaintext = unpad_pkcs7(paded_plaintext);
    return plaintext;
}

std::string AESCrypto::pad_pkcs7(const std::string& str) {
    using namespace CryptoPP;
    int padding = AES::BLOCKSIZE - (str.size() % AES::BLOCKSIZE);
    std::string result = str;
    result.append(padding, (char) padding);
    return result;
}

std::string AESCrypto::unpad_pkcs7(const std::string& str) {
    using namespace CryptoPP;

    size_t str_len = str.size();
    if (str_len == 0) {
        return str;
    }

    // ��������ַ����ĳ����Ƿ�Ϊ���С����������
    // ������ǣ�˵�������ַ���û�б���ȷ����䣬ֱ�ӷ���ԭ��
    if (str_len % AES::BLOCKSIZE != 0) {
        return str;
    }
    
    // ��ȡ�����ַ��������һ���ַ�������ַ���ʾ���ĳ���
    unsigned char lastChar = str.back();
    if (lastChar < 1 || lastChar > AES::BLOCKSIZE) {
        // ��Щ���ԣ��� python��������㷨����������ܴ��ĳ��ȸպ�Ϊ BLOCKSIZE �����������������һ�� BLOCK
        // Ϊ�˱��������쳣������������ BLOCK ��������ʱ�򣬲����κβ���
        return str;
    }
    
    // ɾ����������ַ����Ӷ��õ�ԭʼ���ַ���
    std::string result = str;
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

