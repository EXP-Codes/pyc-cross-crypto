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


void test_cache(DESCrypto* des);
void test_file(DESCrypto* des);
void test_cache(AESCrypto* aes);
void test_file(AESCrypto* aes);



int main() {
    string key = "EXP-BLOG";
    DESCrypto* des = new DESCrypto(key);
    test_cache(des);
    test_file(des);

    string iv = "https://exp-blog.com";
    AESCrypto* aes = new AESCrypto(key, iv);
    test_cache(aes);
    test_file(aes);
    return 0;
}


void test_cache(DESCrypto* des) {
    cout << "[DES] 测试内存字符串加解密 ..." << endl;

    string plaintext = TESTED_PLAINTEXT;
    cout << "[DES] 明文: " << plaintext << endl;

    string ciphertext = des->encrypt(plaintext);
    cout << "[DES] 密文: " << ciphertext << endl;

    plaintext = des->decrypt(ciphertext);
    cout << "[DES] 测试完成" << endl;
}


void test_file(DESCrypto* des) {
    cout << "[DES] 测试文件字符串加解密 ..." << endl;

    char* filedata = file_read(TESTED_FILEPATH);
    string plaintext(filedata);
    cout << "[DES] 已读取被测文件: " << TESTED_FILEPATH << endl;

    string cipherfile = OUT_DIR + "/DES_ciphertext.cro";
    string ciphertext = des->encrypt(plaintext);
    file_write(cipherfile, ciphertext);
    cout << "[DES] 已加密: " << cipherfile << endl;

    string plainfile = OUT_DIR + "/DES_plaintext.txt";
    plaintext = des->decrypt(ciphertext);
    file_write(plainfile, plaintext);
    cout << "[DES] 已加密: " << plainfile << endl;

    cout << "[DES] 测试完成" << endl;
}


void test_cache(AESCrypto* aes) {
    cout << "[AES] 测试内存字符串加解密 ..." << endl;

    string plaintext = TESTED_PLAINTEXT;
    cout << "[AES] 明文: " << plaintext << endl;

    string ciphertext = aes->encrypt(plaintext);
    cout << "[AES] 密文: " << ciphertext << endl;

    plaintext = aes->decrypt(ciphertext);
    cout << "[AES] 测试完成" << endl;
}


void test_file(AESCrypto* aes) {
    cout << "[AES] 测试文件字符串加解密 ..." << endl;

    char* filedata = file_read(TESTED_FILEPATH);
    string plaintext(filedata);
    cout << "[AES] 已读取被测文件: " << TESTED_FILEPATH << endl;

    string cipherfile = OUT_DIR + "/AES_ciphertext.cro";
    string ciphertext = aes->encrypt(plaintext);
    file_write(cipherfile, ciphertext);
    cout << "[AES] 已加密: " << cipherfile << endl;

    string plainfile = OUT_DIR + "/AES_plaintext.txt";
    plaintext = aes->decrypt(ciphertext);
    file_write(plainfile, plaintext);
    cout << "[AES] 已加密: " << plainfile << endl;

    cout << "[AES] 测试完成" << endl;
}
