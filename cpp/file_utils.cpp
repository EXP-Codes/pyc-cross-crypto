#include "file_utils.hpp"
using namespace std;

/**
 * @brief 读取文件内容
 * @param string filepath - 文件路径
 * @return char* - 返回读取到的文件内容
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

    fseek(fpr, 0, SEEK_END);    // 把文件指针移到文件末尾
    long filesize = ftell(fpr); // 获取文件的长度
    fseek(fpr, 0, SEEK_SET);    // 把文件指针移到文件开头 

    // 读取文件内容到缓存
    char* buffer = (char*)malloc(filesize + 1);
    fread(buffer, 1, filesize, fpr);
    *(buffer + filesize) = '\0';

    fclose(fpr);                // 关闭文件 
    string filedate(buffer);
    return filedate;
}

/**
 * @brief 将数据写入文件
 * @param string filepath - 文件路径
 * @param string filedata - 需要写入的数据
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

    // 将数据写入文件
    fwrite(filedata.c_str(), 1, filedata.size(), fpw);
    fclose(fpw);
}

/**
 * @brief 检查文件名是否以指定后缀结尾
 * @param char* filename - 文件名
 * @param char* suffix - 指定后缀
 * @return bool - 如果文件名以指定后缀结尾，则返回true，否则返回false
 */
bool endswith(char* filename, char* suffix) {
    char* dot = strrchr(filename, '.');
    if (NULL == dot) {
        return 0;
    }
    return strcmp(dot, suffix) == 0;
}
