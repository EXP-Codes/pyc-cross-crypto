#ifndef DES_ECB_H
#define DES_ECB_H
#include <string>
using namespace std;


class DESCrypto
{
public:

	/*
	 * 构建 DES 对象
	 * @param key 加密密钥（8 字节）
	 */
	DESCrypto(string key);

	/*
	 * DES 加密
	 * @param plaintext 明文
	 * @return 密文（base64 编码）
	 */
	string encrypt(string plaintext);

	/*
	 * DES 加密
	 * @param ciphertext 密文（base64 编码）
	 * @return 明文
	 */
	string decrypt(string ciphertext);

private:
	string desKey;	// 加密密钥（8 字节）

	/*
	 * DES 填充算法: PKCS5
	 * @param plaintext 明文
	 * @return 填充字符数组
	 */
	char* padding_PKCS5(string plaintext);
};


#endif
