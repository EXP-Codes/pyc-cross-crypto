/***************************************************\
 * -*- coding: GBK -*-
 * @Author : EXP
 * @Time   : 2022/11/15 23:56
 * -----------------------------------------------
 * AES/DES 跨平台加解密测试
\***************************************************/

#include "aes_crypto.hpp"
#include "des_crypto.hpp"
#include "file_utils.hpp"
#include <iostream>
using namespace std;

const string TESTED_PLAINTEXT = "特殊字符 $%^!@# 数字 123890 中文\tOK";
const string TESTED_FILEPATH = "'../../test_crypto.cpp";
const string TESTED_ENCODING = "GBK";                                   // 被测文件原本的 / 解密后的编码
const string CIPHERTEXT_ENCODING = "ISO-8859-1";                        // 加密后的文件编码（因为是 base64， 统一用 ISO-8859-1 即可）
const string OUT_DIR = "./out";


template <typename Crypto>
void test_cache(Crypto* crypto, string type);

template <typename Crypto>
void test_file(Crypto* crypto, string type);


int main() {
    string key = "EXP-BLOG";
    DESCrypto* des = new DESCrypto(key);
    test_cache(des, "DES");
    test_file(des, "DES");

    string iv = "https://exp-blog.com";
    AESCrypto* aes = new AESCrypto(key, iv);
    test_cache(aes, "AES");
    test_file(aes, "AES");
    return 0;
}


template <typename Crypto>
void test_cache(Crypto* crypto, string type) {
    cout << "[" << type << "] 测试内存字符串加解密 ..." << endl;

    string plaintext = TESTED_PLAINTEXT;
    cout << "[" << type << "] 明文: " << plaintext << endl;

    string ciphertext = crypto->encrypt(plaintext);
    cout << "[" << type << "] 密文: " << ciphertext << endl;

    plaintext = crypto->decrypt(ciphertext);
    cout << "[" << type << "] 解密: " << plaintext << endl;
    cout << "[" << type << "] 测试完成" << endl << endl;
}


template <typename Crypto>
void test_file(Crypto* crypto, string type) {
    cout << "[" << type << "] 测试文件字符串加解密 ..." << endl;

    char* filedata = file_read(TESTED_FILEPATH);
    string plaintext(filedata);
    cout << "[" << type << "] 已读取被测文件: " << TESTED_FILEPATH << endl;

    string cipherfile = OUT_DIR + "/" + type + "_ciphertext.cro";
    string ciphertext = crypto->encrypt(plaintext);
    file_write(cipherfile, ciphertext);
    cout << "[" << type << "] 已加密: " << cipherfile << endl;

    string plainfile = OUT_DIR + "/" + type + "_plaintext.txt";
    plaintext = crypto->decrypt(ciphertext);
    file_write(plainfile, plaintext);
    cout << "[" << type << "] 已解密: " << plainfile << endl;

    cout << "[" << type << "] 测试完成" << endl << endl;
}
