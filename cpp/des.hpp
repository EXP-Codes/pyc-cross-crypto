#ifndef DES_ECB_H
#define DES_ECB_H
#include <string>
using namespace std;


class DESCrypto
{
public:

	/*
	 * ���� DES ����
	 * @param key ������Կ��8 �ֽڣ�
	 */
	DESCrypto(string key);

	/*
	 * DES ����
	 * @param plaintext ����
	 * @return ���ģ�base64 ���룩
	 */
	string encrypt(string plaintext);

	/*
	 * DES ����
	 * @param ciphertext ���ģ�base64 ���룩
	 * @return ����
	 */
	string decrypt(string ciphertext);

private:
	string desKey;	// ������Կ��8 �ֽڣ�

	/*
	 * DES ����㷨: PKCS5
	 * @param plaintext ����
	 * @return ����ַ�����
	 */
	char* padding_PKCS5(string plaintext);
};


#endif
