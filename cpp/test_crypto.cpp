/***************************************************\
 * -*- coding: GBK -*-
 * @Author : EXP
 * @Time   : 2022/11/15 23:56
 * -----------------------------------------------
 * AES/DES ��ƽ̨�ӽ��ܲ���
\***************************************************/

#include "crypto.hpp"
#include "aes_crypto.hpp"
#include "des_crypto.hpp"
#include "file_utils.hpp"
#include <iostream>
using namespace std;

const string TESTED_PLAINTEXT = "�����ַ� $%^!@# ���� 123890 ����\tOK";
const string TESTED_FILEPATH = "'../../test_crypto.cpp";
const string TESTED_ENCODING = "GBK";                    // �����ļ�ԭ���� or ���ܺ�ı��루��ʱû�ã�C ��д���ֽ��룬������޹أ�
const string CIPHERTEXT_ENCODING = "ISO-8859-1";         // ���ܺ���ļ����루��Ϊ�� base64�� ͳһ�� ISO-8859-1 ���ɣ�
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

    cout << "��ѡ�����²���ģʽ��" << endl;
    cout << "1. ����ģʽ" << endl;
    cout << "2. Ĭ��ģʽ" << endl;
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
        cout << "��ѡ�������" << endl;
        cout << "1. ���ܲ���" << endl;
        cout << "2. ���ܲ���" << endl;
        cout << "3. �˳�" << endl;
        cout << "������ѡ���ţ�" << endl;
        string option;
        cin >> option;
        if (option == "1") {
            encryption_test(key, iv);

        } else if (option == "2") {
            decryption_test(key, iv);

        } else if (option == "3") {
            break;

        } else {
            cout << "δ֪ѡ����������룡" << endl;
        }
    }
}


void encryption_test(string key, string iv) {
    cout << "��ѡ������㷨��" << endl;
    cout << "1. AES" << endl;
    cout << "2. DES" << endl;
    cout << "������ѡ���ţ�" << endl;
    string algorithm_option;
    cin >> algorithm_option;

    cout << "��ѡ��������ͣ�" << endl;
    cout << "1. �ַ���" << endl;
    cout << "2. �ļ�" << endl;
    cout << "������ѡ���ţ�" << endl;
    string type_option;
    cin >> type_option;

    string data;
    if (type_option == "1") {
        cout << "������Ҫ���ܵ��ַ�����" << endl;
        cin >> data;

    } else if (type_option == "2") {
        cout << "������Ҫ���ܵ��ļ�·����" << endl;
        string filepath;
        cin >> filepath;
        data = file_read(filepath);

    } else {
        cout << "δ֪ѡ��������˵���" << endl;
        return;
    }

    string name = (algorithm_option == "1" ? "AES" : "DES");
    Crypto* algorithm = get_algorithm(algorithm_option, key, iv);
    string ciphertext = algorithm->encrypt(data);

    if (type_option == "2") {
        string cipherfile = OUT_DIR + "/" + name + "_ciphertext.cro";
        file_write(cipherfile, ciphertext);
        cout << "[" << name << "] �Ѽ���: " << cipherfile << endl << endl;
        
    } else {
        cout << "[" << name << "] ����: " << ciphertext << endl << endl;
    }
}


void decryption_test(string key, string iv) {
    cout << "��ѡ������㷨��" << endl;
    cout << "1. AES" << endl;
    cout << "2. DES" << endl;
    cout << "������ѡ���ţ�" << endl;
    string algorithm_option;
    cin >> algorithm_option;

    cout << "��ѡ��������ͣ�" << endl;
    cout << "1. �ַ���" << endl;
    cout << "2. �ļ�" << endl;
    cout << "������ѡ���ţ�" << endl;
    string type_option;
    cin >> type_option;

    string data;
    if (type_option == "1") {
        cout << "������Ҫ���ܵ��ַ�����" << endl;
        cin >> data;

    } else if (type_option == "2") {
        cout << "������Ҫ���ܵ��ļ�·����" << endl;
        string filepath;
        cin >> filepath;
        data = file_read(filepath);

    } else {
        cout << "δ֪ѡ��������˵���" << endl;
        return;
    }

    string name = (algorithm_option == "1" ? "AES" : "DES");
    Crypto* algorithm = get_algorithm(algorithm_option, key, iv);
    string plaintext = algorithm->decrypt(data);
    
    if (type_option == "2") {
        string plainfile = OUT_DIR + "/" + name + "_plaintext.txt";
        file_write(plainfile, plaintext);
        cout << "[" << name << "] �ѽ���: " << plainfile << endl << endl;

    } else {
        cout << "[" << name << "] ����: " << plaintext << endl << endl;
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
    cout << "[" << type << "] �����ڴ��ַ����ӽ��� ..." << endl;

    string plaintext = TESTED_PLAINTEXT;
    cout << "[" << type << "] ����: " << plaintext << endl;

    string ciphertext = crypto->encrypt(plaintext);
    cout << "[" << type << "] ����: " << ciphertext << endl;

    plaintext = crypto->decrypt(ciphertext);
    cout << "[" << type << "] ����: " << plaintext << endl;
    cout << "[" << type << "] �������" << endl << endl;
}


void test_file(Crypto* crypto, string type) {
    cout << "[" << type << "] �����ļ��ַ����ӽ��� ..." << endl;

    string plaintext = file_read(TESTED_FILEPATH);
    cout << "[" << type << "] �Ѷ�ȡ�����ļ�: " << TESTED_FILEPATH << endl;

    string cipherfile = OUT_DIR + "/" + type + "_ciphertext.cro";
    string ciphertext = crypto->encrypt(plaintext);
    file_write(cipherfile, ciphertext);
    cout << "[" << type << "] �Ѽ���: " << cipherfile << endl;

    string plainfile = OUT_DIR + "/" + type + "_plaintext.txt";
    plaintext = crypto->decrypt(ciphertext);
    file_write(plainfile, plaintext);
    cout << "[" << type << "] �ѽ���: " << plainfile << endl;

    cout << "[" << type << "] �������" << endl << endl;
}
