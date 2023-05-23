#include "base64.h"
#include "des_crypto.h"
#include <des.h>
#include <string>
#include <iostream>
using namespace std;


DESCrypto::DESCrypto(string key)
{
    this->desKey = key;
}


char* DESCrypto::padding_PKCS5(string plaintext)
{
    using namespace CryptoPP;

    int plaintext_len = plaintext.size();
    int pad_amount = DES::BLOCKSIZE - plaintext_len % DES::BLOCKSIZE;
    int pad_plain_len = plaintext_len + pad_amount;

    char* pad_plain_bytes = (char*)malloc(pad_plain_len);
    memcpy(pad_plain_bytes, plaintext.c_str(), plaintext_len);
    for (int i = plaintext_len; i < pad_plain_len; i++)
    {
        pad_plain_bytes[i] = pad_amount;
    }
    return pad_plain_bytes;
}


string DESCrypto::encrypt(string plaintext)
{
    using namespace CryptoPP;

    unsigned char key[DES::DEFAULT_KEYLENGTH];
    memcpy(key, this->desKey.c_str(), DES::BLOCKSIZE);

    unsigned char in_cache[DES::BLOCKSIZE];
    unsigned char out_cache[DES::BLOCKSIZE];

    char* plain_bytes = padding_PKCS5(plaintext);           //  π”√ PKCS5 ÃÓ≥‰∂‘∆Î
    int plaintext_len = plaintext.size();
    int pLen = plaintext_len / DES::BLOCKSIZE + 1;
    int cLen = pLen * DES::BLOCKSIZE;
    char* cipher_bytes = new char[cLen];
    memset(cipher_bytes, 0, cLen);

    for (int i = 0; i < pLen; i++)
    {
        memset(in_cache, 0, DES::BLOCKSIZE);
        memset(out_cache, 0, DES::BLOCKSIZE);
        memcpy(in_cache, plain_bytes + (i * DES::BLOCKSIZE), DES::BLOCKSIZE);

        DESEncryption des_encryption;
        des_encryption.SetKey(key, DES::KEYLENGTH);         // …Ë÷√√‹‘ø
        des_encryption.ProcessBlock(in_cache, out_cache);   // º”√‹
        memcpy(cipher_bytes + (i * DES::BLOCKSIZE), out_cache, DES::BLOCKSIZE);
    }

    // base64 ±‡¬Î
    string ciphertext = to_base64(reinterpret_cast<const unsigned char*>(cipher_bytes), cLen);
    return ciphertext;
}


string DESCrypto::decrypt(string ciphertext)
{
    using namespace CryptoPP;

    unsigned char key[DES::DEFAULT_KEYLENGTH];
    memcpy(key, this->desKey.c_str(), DES::BLOCKSIZE);

    ciphertext = un_base64(ciphertext);                     // base64 Ω‚¬Î

    vector<unsigned char> plain_bytes;
    unsigned char in_cache[DES::BLOCKSIZE];
    unsigned char out_cache[DES::BLOCKSIZE];

    const char* cipher_bytes = ciphertext.c_str();
    int ciphertext_len = ciphertext.size();
    int cLen = ciphertext_len / DES::BLOCKSIZE;

    for (int i = 0; i < cLen; i++)
    {
        memset(in_cache, 0, DES::BLOCKSIZE);
        memset(out_cache, 0, DES::BLOCKSIZE);
        memcpy(in_cache, cipher_bytes + (i * DES::BLOCKSIZE), DES::BLOCKSIZE);

        DESDecryption des_decryption;
        des_decryption.SetKey(key, DES::KEYLENGTH);         // …Ë÷√√‹‘ø
        des_decryption.ProcessBlock(in_cache, out_cache);   // Ω‚√‹
        for (int k = 0; k < DES::BLOCKSIZE; k++)
        {
            plain_bytes.push_back(out_cache[k]);
        }
    }

    // »•µÙº”√‹ ±ÃÓ≥‰µƒ◊÷∑˚
    int pad_amount = plain_bytes[ciphertext_len - 1];
    string plaintext;
    plaintext.clear();
    plaintext.assign(plain_bytes.begin(), plain_bytes.end() - pad_amount);
    return plaintext;
}
