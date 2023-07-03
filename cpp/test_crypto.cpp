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
#include <fstream>
#include <map>
using namespace std;

const string CRYPTO_ARG_PATH = "../.env";
const string TESTED_PLAINTEXT = "特殊字符 $%^!@# 数字 123890 中文\tOK";
const string TESTED_FILEPATH = "'../../test_crypto.cpp";
const string TESTED_ENCODING = "GBK";                    // 被测文件原本的 or 解密后的编码（暂时没用，C 读写是字节码，与编码无关）
const string CIPHERTEXT_ENCODING = "ISO-8859-1";         // 加密后的文件编码（因为是 base64， 统一用 ISO-8859-1 即可）
const string OUT_DIR = "./out";


map<string, string> load_crypto_args(const string& envpath);

void interactive(string key, string iv);
void defavlt(string key, string iv);

void encryption_test(string key, string iv);
void decryption_test(string key, string iv);
Crypto* get_algorithm(string option, string key, string iv);

void test_cache(Crypto* crypto, string type);
void test_file(Crypto* crypto, string type);


int main() {
    auto args = load_crypto_args(CRYPTO_ARG_PATH);
    string key = args["key"];
    string iv = args["iv"];

    cout << "Please select one of the following test modes:" << endl;
    cout << "1. Interactive mode" << endl;
    cout << "2. Default mode" << endl;
    string option;
    cin >> option;
    if (option == "1") {
        interactive(key, iv);
        
    } else {
        defavlt(key, iv);
    }
    return 0;
}


map<string, string> load_crypto_args(const string& envpath) {
    map<string, string> args;
    ifstream envFile(envpath);
    if (!envFile) {
        cerr << "Can't open .env file: " << envpath << endl;
        return args;
    }

    string line;
    while (getline(envFile, line)) {
        istringstream iss(line);
        string key, equal, value;

        bool ok = getline(iss, key, '=') && getline(iss, value);
        if (ok) {
            args[key] = value;
        } else {
            cerr << "Failed to parse line: " << line << endl;
        }
    }
    return args;
}


void interactive(string key, string iv) {
    while (true) {
        cout << "Please choose an operation:" << endl;
        cout << "1. Encryption test" << endl;
        cout << "2. Decryption test" << endl;
        cout << "3. Exit" << endl;
        cout << "Please enter the option number:" << endl;
        string option;
        cin >> option;
        if (option == "1") {
            encryption_test(key, iv);

        } else if (option == "2") {
            decryption_test(key, iv);

        } else if (option == "3") {
            break;

        } else {
            cout << "Unknown option, please enter again!" << endl;
        }
    }
}


void encryption_test(string key, string iv) {
    cout << "Please choose an encryption algorithm:" << endl;
    cout << "1. AES" << endl;
    cout << "2. DES" << endl;
    cout << "Please enter the option number:" << endl;
    string algorithm_option;
    cin >> algorithm_option;

    cout << "Please choose the type of encryption:" << endl;
    cout << "1. String" << endl;
    cout << "2. File" << endl;
    cout << "Please enter the option number:" << endl;
    string type_option;
    cin >> type_option;

    string data;
    if (type_option == "1") {
        cout << "Please enter the string to be encrypted:" << endl;
        cin >> data;

    } else if (type_option == "2") {
        cout << "Please enter the path of the file to be encrypted:" << endl;
        string filepath;
        cin >> filepath;
        data = file_read(filepath);

    } else {
        cout << "Unknown option, returning to main menu!" << endl;
        return;
    }

    string name = (algorithm_option == "1" ? "AES" : "DES");
    Crypto* algorithm = get_algorithm(algorithm_option, key, iv);
    string ciphertext = algorithm->encrypt(data);

    if (type_option == "2") {
        string cipherfile = OUT_DIR + "/" + name + "_ciphertext.cro";
        file_write(cipherfile, ciphertext);
        cout << "[" << name << "] Encrypted: " << cipherfile << endl << endl;
        
    } else {
        cout << "[" << name << "] Encrypted: " << ciphertext << endl << endl;
    }
}


void decryption_test(string key, string iv) {
    cout << "Please choose a decryption algorithm:" << endl;
    cout << "1. AES" << endl;
    cout << "2. DES" << endl;
    cout << "Please enter the option number:" << endl;
    string algorithm_option;
    cin >> algorithm_option;

    cout << "Please choose the type of decryption:" << endl;
    cout << "1. String" << endl;
    cout << "2. File" << endl;
    cout << "Please enter the option number:" << endl;
    string type_option;
    cin >> type_option;

    string data;
    if (type_option == "1") {
        cout << "Please enter the string to be decrypted:" << endl;
        cin >> data;

    } else if (type_option == "2") {
        cout << "Please enter the path of the file to be decrypted:" << endl;
        string filepath;
        cin >> filepath;
        data = file_read(filepath);

    } else {
        cout << "Unknown option, returning to the main menu!" << endl;
        return;
    }

    string name = (algorithm_option == "1" ? "AES" : "DES");
    Crypto* algorithm = get_algorithm(algorithm_option, key, iv);
    string plaintext = algorithm->decrypt(data);
    
    if (type_option == "2") {
        string plainfile = OUT_DIR + "/" + name + "_plaintext.txt";
        file_write(plainfile, plaintext);
        cout << "[" << name << "] Decrypted: " << plainfile << endl << endl;

    } else {
        cout << "[" << name << "] Decrypted: " << plaintext << endl << endl;
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
    cout << "[" << type << "] Testing encryption and decryption in memory..." << endl;

    string plaintext = TESTED_PLAINTEXT;
    cout << "[" << type << "] Plaintext: " << plaintext << endl;

    string ciphertext = crypto->encrypt(plaintext);
    cout << "[" << type << "] Ciphertext: " << ciphertext << endl;

    plaintext = crypto->decrypt(ciphertext);
    cout << "[" << type << "] Decrypted: " << plaintext << endl;
    cout << "[" << type << "] Test completed" << endl << endl;
}


void test_file(Crypto* crypto, string type) {
    cout << "[" << type << "] Testing encryption and decryption on a file..." << endl;

    string plaintext = file_read(TESTED_FILEPATH);
    cout << "[" << type << "] File read for testing: " << TESTED_FILEPATH << endl;

    string cipherfile = OUT_DIR + "/" + type + "_ciphertext.cro";
    string ciphertext = crypto->encrypt(plaintext);
    file_write(cipherfile, ciphertext);
    cout << "[" << type << "] Encrypted: " << cipherfile << endl;

    string plainfile = OUT_DIR + "/" + type + "_plaintext.txt";
    plaintext = crypto->decrypt(ciphertext);
    file_write(plainfile, plaintext);
    cout << "[" << type << "] Decrypted: " << plainfile << endl;

    cout << "[" << type << "] Test completed" << endl << endl;
}

