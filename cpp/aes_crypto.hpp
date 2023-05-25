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
    std::string key;    // ������Կ������й¶��
    std::string iv;     // ���������ֻΪȷ������ԣ�й¶��Ӱ������ǿ�ȣ�

    //************************************
    // Method:      pad_pkcs7
    // Description: PKCS7��䣨����ʹ�� Crypto++ ���õ�����㷨�������޷��� python �໥�ӽ��ܣ�
    // Parameter:   const std::string& str ��Ҫ�����ַ���
    // Returns:     std::string ������ַ���
    //************************************
    std::string pad_pkcs7(const std::string& str);

    //************************************
    // Method:      unpad_pkcs7
    // Description: PKCS7ȥ��䣨����ʹ�� Crypto++ ���õ�����㷨�������޷��� python �໥�ӽ��ܣ�
    // Parameter:   const std::string& str ��Ҫȥ�����ַ���
    // Returns:     std::string ȥ������ַ���
    //************************************
    std::string unpad_pkcs7(const std::string& str);

    //************************************
    // Method:      to_hex
    // Description: ���ַ���תΪʮ������
    // Parameter:   const std::string& input ��Ҫת�����ַ���
    // Returns:     std::string ת������ַ���
    //************************************
    std::string to_hex(const std::string& input);

public:
    //************************************
    // Method:      AESCrypto
    // Description: ���캯��
    // Parameter:   std::string key �û��趨����Կ
    // Parameter:   std::string iv �û��趨�ĳ�ʼ����
    //************************************
    AESCrypto(std::string key, std::string iv);

    //************************************
    // Method:      encrypt
    // Description: AES����
    // Parameter:   std::string plaintext ��Ҫ���ܵ�����
    // Returns:     std::string ���ܺ������
    //************************************
    std::string encrypt(std::string plaintext);

    //************************************
    // Method:      decrypt
    // Description: AES����
    // Parameter:   std::string ciphertext ��Ҫ���ܵ�����
    // Returns:     std::string ���ܺ������
    //************************************
    std::string decrypt(std::string ciphertext);

};

#endif // AESCRYPTO_HPP
