#include "file_utils.h"
#include <iostream>
#include <string>
using namespace std;


char* file_read(string filepath) {
    FILE* fpr;
    errno_t err = fopen_s(&fpr, filepath.c_str(), "r");
    if (err != 0) {
        cout << "[ERROR] Failed to open file: " << filepath << endl;
        exit(1);
    }

    fseek(fpr, 0, SEEK_END);    // ���ļ�ָ���Ƶ��ļ�ĩβ
    long filesize = ftell(fpr); // �����ļ��ĳ���
    fseek(fpr, 0, SEEK_SET);    // ���ļ�ָ���Ƶ��ļ���ͷ 

    // ��ȡ�ļ����ݵ�����
    char* buffer = (char*)malloc(filesize + 1);
    fread(buffer, 1, filesize, fpr);
    *(buffer + filesize) = '\0';

    fclose(fpr);                // �ر��ļ� 
    return buffer;
}


void file_write(string filepath, string filedata) {
    FILE* fpw;
    errno_t err = fopen_s(&fpw, filepath.c_str(), "w+");
    if (err != 0) {
        cout << "[ERROR] Failed to open file: " << filepath << endl;
        exit(1);
    }

    // �ѻ���д���ļ�
    fwrite(filedata.c_str(), 1, filedata.size(), fpw);
    fclose(fpw);
}


bool endswith(char* filename, char* suffix)
{
    char* dot = strrchr(filename, '.');
    if (NULL == dot) {
        return 0;
    }
    return strcmp(dot, suffix) == 0;
}