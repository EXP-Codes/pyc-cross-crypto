#include "base64.hpp"
#include "des_crypto.hpp"
#include <string>
#include <iostream>
#include <sstream>
#include "filters.h"

DESCrypto::DESCrypto(std::string key)
{
    using namespace CryptoPP;
    SHA256 hash;
    std::string digest;
    StringSource s(key, true, new HashFilter(hash, new StringSink(digest)));
    this->desKey = digest.substr(0, DES_EDE2::DEFAULT_KEYLENGTH);
}

char* DESCrypto::padding_PKCS5(std::string plaintext)
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

std::string DESCrypto::encrypt(std::string plaintext)
{
    using namespace CryptoPP;

    unsigned char key[DES::DEFAULT_KEYLENGTH];
    memcpy(key, this->desKey.c_str(), DES::BLOCKSIZE);

    unsigned char in_cache[DES::BLOCKSIZE];
    unsigned char out_cache[DES::BLOCKSIZE];

    char* plain_bytes = padding_PKCS5(plaintext);
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
        des_encryption.SetKey(key, DES::KEYLENGTH);
        des_encryption.ProcessBlock(in_cache, out_cache);
        memcpy(cipher_bytes + (i * DES::BLOCKSIZE), out_cache, DES::BLOCKSIZE);
    }

    // Base64 encoding
    std::string ciphertext = to_base64(reinterpret_cast<const unsigned char*>(cipher_bytes), cLen);
    return ciphertext;
}

std::string DESCrypto::unpadding_PKCS5(std::vector<unsigned char>& plain_bytes)
{
    int pad_amount = plain_bytes[plain_bytes.size() - 1];
    std::string plaintext;
    plaintext.assign(plain_bytes.begin(), plain_bytes.end() - pad_amount);
    return plaintext;
}

std::string DESCrypto::decrypt(std::string ciphertext)
{
    using namespace CryptoPP;

    unsigned char key[DES::DEFAULT_KEYLENGTH];
    memcpy(key, this->desKey.c_str(), DES::BLOCKSIZE);

    ciphertext = un_base64(ciphertext);  // Base64 decoding

    std::vector<unsigned char> plain_bytes;
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
        des_decryption.SetKey(key, DES::KEYLENGTH);
        des_decryption.ProcessBlock(in_cache, out_cache);
        for (int k = 0; k < DES::BLOCKSIZE; k++)
        {
            plain_bytes.push_back(out_cache[k]);
        }
    }

    std::string plaintext = unpadding_PKCS5(plain_bytes);
    return plaintext;
}
