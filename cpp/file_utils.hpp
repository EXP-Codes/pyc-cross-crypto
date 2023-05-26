#ifndef FILE_UTILS_H
#define FILE_UTILS_H
#include <iostream>
#include <string>
using namespace std;


/**
 * @brief 读取文件内容
 * @param string filepath - 文件路径
 * @return char* - 返回读取到的文件内容
 */
string file_read(string filepath);

/**
 * @brief 将数据写入文件
 * @param string filepath - 文件路径
 * @param string filedata - 需要写入的数据
 */
void file_write(string filepath, string filedata);


/**
 * @brief 检查文件名是否以指定后缀结尾
 * @param char* filename - 文件名
 * @param char* suffix - 指定后缀
 * @return bool - 如果文件名以指定后缀结尾，则返回true，否则返回false
 */
bool endswith(char* filename, char* suffix);


#endif