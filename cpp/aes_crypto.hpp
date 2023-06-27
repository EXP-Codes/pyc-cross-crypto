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
    std::string key;    // ������Կ
    std::string iv;     // ��ʼ����

    /**
     * @brief PKCS7���
     * @param const std::string& str - ��Ҫ�����ַ���
     * @return std::string - ������ַ���
     */
    std::string pad_pkcs7(const std::string& str);

    /**
     * @brief PKCS7ȥ���
     * @param const std::string& str - ��Ҫȥ�����ַ���
     * @return std::string - ȥ������ַ���
     */
    std::string unpad_pkcs7(const std::string& str);

    /**
     * @brief ���ַ���תΪʮ������
     * @param const std::string& input - ��Ҫת�����ַ���
     * @return std::string - ת������ַ���
     */
    std::string to_hex(const std::string& input);

public:
    /**
     * @brief ���캯��
     * @param std::string key - �û��趨����Կ
     * @param std::string iv - �û��趨�ĳ�ʼ����
     */
    AESCrypto(std::string key, std::string iv);

    /**
     * @brief AES����
     * @param std::string plaintext - ��Ҫ���ܵ�����
     * @return std::string - ���ܺ������
     */
    std::string encrypt(std::string plaintext) noexcept override;

    /**
     * @brief AES����
     * @param std::string ciphertext - ��Ҫ���ܵ�����
     * @return std::string - ���ܺ������
     */
    std::string decrypt(std::string ciphertext) noexcept override;

};

#endif // AESCRYPTO_HPP
