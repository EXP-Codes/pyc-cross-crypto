#ifndef FILE_UTILS_H
#define FILE_UTILS_H
#include<string>
using namespace std;

/*
 * ��ȡ�ļ�
 * @param filepath �ļ�·��
 * @return �ļ�����
 */
char* file_read(string filepath);

/*
 * д���ļ�
 * @param filepath �ļ�·��
 * @param filedata д������
 * @return None
 */
void file_write(string filepath, string filedata);


/*
 * ����ļ���׺
 * @param filename �ļ����ƣ���·����
 * @param suffix �������ļ���׺����ʽ����: .txt
 * @return true or false
 */
bool endswith(char* filename, char* suffix);


#endif