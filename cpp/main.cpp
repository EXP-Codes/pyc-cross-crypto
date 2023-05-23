/***************************************************\
 * -*- coding: GBK -*-
 * @Author : EXP
 * @Time   : 2022/11/15 23:56
 * -----------------------------------------------
 * DES 加解密工具
 * 算法 ECB， 填充模式 PKCS5
 * -----------------------------------------------
 * 参考文档:
 *  https://blog.csdn.net/suhiymof/article/details/92796811
 *  https://blog.csdn.net/Yonggie/article/details/100592532
\***************************************************/

#include "aes_crypto.cpp"
#include "des_crypto.h"
#include "file_utils.h"
#include <iostream>
using namespace std;


void test_des_cache(DESCrypto* des)
{
    string plaintext = "Starting D:中文a  \n ro 随缘仙境";

    string ciphertext = des->encrypt(plaintext);
    cout << "ciphertext: " << ciphertext << endl;

    plaintext = des->decrypt(ciphertext);
    cout << "plaintext: " << plaintext << endl;

    cout << "Finish [test_cache]" << endl;
}


void test_des_file(DESCrypto* des, string filepath)
{
    char* filedata = file_read(filepath);
    string ciphertext = des->encrypt(filedata);
    file_write("./out/ciphertext.nro", ciphertext);

    string plaintext = des->decrypt(ciphertext);
    file_write("./out/plaintext.txt", plaintext);

    cout << "Finish [test_file]" << endl;
}


void test_des() {
    string key = "EXPROkey";
    DESCrypto* des = new DESCrypto(key);

    test_des_cache(des);

    string filepath = "./out/OX.txt";
    test_des_file(des, filepath);
}



void test_aes() {
    string key = "EXPROkey";
    string iv = "EXP-RO-iv";
    AESCrypto* aes = new AESCrypto(key, iv);

    string plaintext = "Starting 中文 asas";
    string ciphertext = aes->encrypt(plaintext);
    cout << "ciphertext: " << ciphertext << endl;

    plaintext = aes->decrypt(ciphertext);
    cout << "plaintext: " << plaintext << endl;

}

int main()
{
    // test_des();

    test_aes();
    return 0;
}

