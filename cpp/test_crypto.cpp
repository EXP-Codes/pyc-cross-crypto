/***************************************************\
 * -*- coding: GBK -*-
 * @Author : EXP
 * @Time   : 2022/11/15 23:56
 * -----------------------------------------------
 * AES/DES 跨平台加解密测试
\***************************************************/

#include "crypto.hpp"
#include "aes_crypto.hpp"
#include "des_crypto.hpp"
#include "file_utils.hpp"
#include <iostream>
using namespace std;

const string TESTED_PLAINTEXT = "特殊字符 $%^!@# 数字 123890 中文\tOK";
const string TESTED_FILEPATH = "'../../test_crypto.cpp";
const string TESTED_ENCODING = "GBK";                    // 被测文件原本的 or 解密后的编码（暂时没用，C 读写是字节码，与编码无关）
const string CIPHERTEXT_ENCODING = "ISO-8859-1";         // 加密后的文件编码（因为是 base64， 统一用 ISO-8859-1 即可）
const string OUT_DIR = "./out";


void interactive(string key, string iv);
void defavlt(string key, string iv);

void encryption_test(string key, string iv);
void decryption_test(string key, string iv);
Crypto* get_algorithm(string option, string key, string iv);

void test_cache(Crypto* crypto, string type);
void test_file(Crypto* crypto, string type);


int main() {
    string key = "EXP-BLOG";
    string iv = "https://exp-blog.com";

    cout << "请选择以下测试模式：" << endl;
    cout << "1. 交互模式" << endl;
    cout << "2. 默认模式" << endl;
    string option;
    cin >> option;
    if (option == "1") {
        interactive(key, iv);
        
    } else {
        defavlt(key, iv);
    }
    return 0;
}


void interactive(string key, string iv) {
    while (true) {
        cout << "请选择操作：" << endl;
        cout << "1. 加密测试" << endl;
        cout << "2. 解密测试" << endl;
        cout << "3. 退出" << endl;
        cout << "请输入选项编号：" << endl;
        string option;
        cin >> option;
        if (option == "1") {
            encryption_test(key, iv);

        } else if (option == "2") {
            decryption_test(key, iv);

        } else if (option == "3") {
            break;

        } else {
            cout << "未知选项，请重新输入！" << endl;
        }
    }
}


void encryption_test(string key, string iv) {
    cout << "请选择加密算法：" << endl;
    cout << "1. AES" << endl;
    cout << "2. DES" << endl;
    cout << "请输入选项编号：" << endl;
    string algorithm_option;
    cin >> algorithm_option;

    cout << "请选择加密类型：" << endl;
    cout << "1. 字符串" << endl;
    cout << "2. 文件" << endl;
    cout << "请输入选项编号：" << endl;
    string type_option;
    cin >> type_option;

    string data;
    if (type_option == "1") {
        cout << "请输入要加密的字符串：" << endl;
        cin >> data;

    } else if (type_option == "2") {
        cout << "请输入要加密的文件路径：" << endl;
        string filepath;
        cin >> filepath;
        data = file_read(filepath);

    } else {
        cout << "未知选项，返回主菜单！" << endl;
        return;
    }

    string name = (algorithm_option == "1" ? "AES" : "DES");
    Crypto* algorithm = get_algorithm(algorithm_option, key, iv);
    string ciphertext = algorithm->encrypt(data);

    if (type_option == "2") {
        string cipherfile = OUT_DIR + "/" + name + "_ciphertext.cro";
        file_write(cipherfile, ciphertext);
        cout << "[" << name << "] 已加密: " << cipherfile << endl << endl;
        
    } else {
        cout << "[" << name << "] 密文: " << ciphertext << endl << endl;
    }
}


void decryption_test(string key, string iv) {
    cout << "请选择解密算法：" << endl;
    cout << "1. AES" << endl;
    cout << "2. DES" << endl;
    cout << "请输入选项编号：" << endl;
    string algorithm_option;
    cin >> algorithm_option;

    cout << "请选择解密类型：" << endl;
    cout << "1. 字符串" << endl;
    cout << "2. 文件" << endl;
    cout << "请输入选项编号：" << endl;
    string type_option;
    cin >> type_option;

    string data;
    if (type_option == "1") {
        cout << "请输入要解密的字符串：" << endl;
        cin >> data;

    } else if (type_option == "2") {
        cout << "请输入要解密的文件路径：" << endl;
        string filepath;
        cin >> filepath;
        data = file_read(filepath);

    } else {
        cout << "未知选项，返回主菜单！" << endl;
        return;
    }

    string name = (algorithm_option == "1" ? "AES" : "DES");
    Crypto* algorithm = get_algorithm(algorithm_option, key, iv);
    string plaintext = algorithm->decrypt(data);
    
    if (type_option == "2") {
        string plainfile = OUT_DIR + "/" + name + "_plaintext.txt";
        file_write(plainfile, plaintext);
        cout << "[" << name << "] 已解密: " << plainfile << endl << endl;

    } else {
        cout << "[" << name << "] 解密: " << plaintext << endl << endl;
    }
}


Crypto* get_algorithm(string option, string key, string iv) {
    Crypto* algorithm;
    if (option == "1") {
        algorithm = new AESCrypto(key, iv);
    } else {
        algorithm = new DESCrypto(key);
    }
    return algorithm;
}



void defavlt(string key, string iv) {
    DESCrypto* des = new DESCrypto(key);
    test_cache(des, "DES");
    test_file(des, "DES");

    AESCrypto* aes = new AESCrypto(key, iv);
    test_cache(aes, "AES");
    test_file(aes, "AES");
}


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


void test_file(Crypto* crypto, string type) {
    cout << "[" << type << "] 测试文件字符串加解密 ..." << endl;

    string plaintext = file_read(TESTED_FILEPATH);
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
