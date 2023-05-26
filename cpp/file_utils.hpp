#ifndef FILE_UTILS_H
#define FILE_UTILS_H
#include <iostream>
#include <string>
using namespace std;


/**
 * @brief ��ȡ�ļ�����
 * @param string filepath - �ļ�·��
 * @return char* - ���ض�ȡ�����ļ�����
 */
string file_read(string filepath);

/**
 * @brief ������д���ļ�
 * @param string filepath - �ļ�·��
 * @param string filedata - ��Ҫд�������
 */
void file_write(string filepath, string filedata);


/**
 * @brief ����ļ����Ƿ���ָ����׺��β
 * @param char* filename - �ļ���
 * @param char* suffix - ָ����׺
 * @return bool - ����ļ�����ָ����׺��β���򷵻�true�����򷵻�false
 */
bool endswith(char* filename, char* suffix);


#endif