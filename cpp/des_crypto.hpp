#ifndef DES_ECB_H
#define DES_ECB_H
#include <string>
#include "hex.h"
#include "filters.h"
#include "des.h"
#include "osrng.h"
#include <sstream>
#include <iomanip>
#include <string>
#include <sha.h>
#include <base64.h>
#include <aes.h>
#include <modes.h>
using namespace std;


class DESCrypto
{
public:

	/*
	 * ???? DES ????
	 * @param key ?????????8 ????
	 */
	DESCrypto(string key);

	/*
	 * DES ????
	 * @param plaintext ????
	 * @return ?????base64 ????
	 */
	string encrypt(string plaintext);

	/*
	 * DES ????
	 * @param ciphertext ?????base64 ????
	 * @return ????
	 */
	string decrypt(string ciphertext);

private:
	string desKey;	// ?????????8 ????

	/*
	 * DES ?????: PKCS5
	 * @param plaintext ????
	 * @return ??????????
	 */
	char* padding_PKCS5(string plaintext);

	string unpadding_PKCS5(vector<unsigned char>& plain_bytes);
};


#endif