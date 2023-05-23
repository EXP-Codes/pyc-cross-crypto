#ifndef FILE_UTILS_H
#define FILE_UTILS_H
#include<string>
using namespace std;

/*
 * 读取文件
 * @param filepath 文件路径
 * @return 文件内容
 */
char* file_read(string filepath);

/*
 * 写入文件
 * @param filepath 文件路径
 * @param filedata 写入内容
 * @return None
 */
void file_write(string filepath, string filedata);


/*
 * 检查文件后缀
 * @param filename 文件名称（或路径）
 * @param suffix 期望的文件后缀，格式形如: .txt
 * @return true or false
 */
bool endswith(char* filename, char* suffix);


#endif