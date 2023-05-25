#ifndef DES_CRYPTO_HPP
#define DES_CRYPTO_HPP

#include <string>
#include <vector>
#include <des.h>
#include <sha.h>
#include <base64.h>
#include <string>
#include <iostream>
#include <sstream>
#include <filters.h>


class DESCrypto {

private:

    std::string key; // ������Կ

    /**
     * @brief �����Ľ��� PKCS5 ���
     * @param plaintext ��Ҫ��������
     * @return ���������
     */
    char* padding_PKCS5(std::string plaintext);

    /**
     * @brief �����Ľ��� PKCS5 �����
     * @param plain_bytes ��Ҫ����������
     * @return �����������
     */
    std::string unpadding_PKCS5(std::vector<unsigned char>& plain_bytes);

public:
    /**
     * @brief ���캯��
     * @param key ���ڼ��ܺͽ��ܵ���Կ
     */
    DESCrypto(std::string key);

    /**
     * @brief �����Ľ��м���
     * @param plaintext ����
     * @return ���ܺ������
     */
    std::string encrypt(std::string plaintext);

    /**
     * @brief �����Ľ��н���
     * @param ciphertext ����
     * @return ���ܺ������
     */
    std::string decrypt(std::string ciphertext);

};

#endif // DES_CRYPTO_HPP
