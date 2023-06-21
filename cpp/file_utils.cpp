#include "file_utils.hpp"
using namespace std;

/**
 * @brief ��ȡ�ļ�����
 * @param string filepath - �ļ�·��
 * @return char* - ���ض�ȡ�����ļ�����
 */
string file_read(string filepath) {
    FILE* fpr;
#ifdef _MSC_VER
    errno_t err = fopen_s(&fpr, filepath.c_str(), "r");
    if (err != 0) {
        cout << "[ERROR] Failed to open file: " << filepath << endl;
        exit(1);
    }
#else
    fpr = fopen(filepath.c_str(), "r");
    if (fpr == NULL) {
        cout << "[ERROR] Failed to open file: " << filepath << endl;
        exit(1);
    }
#endif

    fseek(fpr, 0, SEEK_END);    // ���ļ�ָ���Ƶ��ļ�ĩβ
    long filesize = ftell(fpr); // ��ȡ�ļ��ĳ���
    fseek(fpr, 0, SEEK_SET);    // ���ļ�ָ���Ƶ��ļ���ͷ 

    // ��ȡ�ļ����ݵ�����
    char* buffer = (char*)malloc(filesize + 1);
    fread(buffer, 1, filesize, fpr);
    *(buffer + filesize) = '\0';

    fclose(fpr);                // �ر��ļ� 
    string filedate(buffer);
    return filedate;
}

/**
 * @brief ������д���ļ�
 * @param string filepath - �ļ�·��
 * @param string filedata - ��Ҫд�������
 */
void file_write(string filepath, string filedata) {
    FILE* fpw;
#ifdef _MSC_VER
    errno_t err = fopen_s(&fpw, filepath.c_str(), "w+");
    if (err != 0) {
        cout << "[ERROR] Failed to open file: " << filepath << endl;
        exit(1);
    }
#else
    fpw = fopen(filepath.c_str(), "w+");
    if (fpw == NULL) {
        cout << "[ERROR] Failed to open file: " << filepath << endl;
        exit(1);
    }
#endif

    // ������д���ļ�
    fwrite(filedata.c_str(), 1, filedata.size(), fpw);
    fclose(fpw);
}

/**
 * @brief ����ļ����Ƿ���ָ����׺��β
 * @param char* filename - �ļ���
 * @param char* suffix - ָ����׺
 * @return bool - ����ļ�����ָ����׺��β���򷵻�true�����򷵻�false
 */
bool endswith(char* filename, char* suffix) {
    char* dot = strrchr(filename, '.');
    if (NULL == dot) {
        return 0;
    }
    return strcmp(dot, suffix) == 0;
}
