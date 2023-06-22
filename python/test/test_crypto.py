#!/usr/bin/env python
# -*- coding: utf-8 -*-
# @Author : EXP
# @Time   : 2023/05/24 23:56
# -----------------------------------------------
# AES/DES 跨平台加解密测试
#   cd python
#   python test/test_crypto.py
# -----------------------------------------------

# ----------------------------------------------------------------------
# 把父级目录（项目根目录）添加到工作路径，以便在终端也可以执行单元测试
import os
import sys
sys.path.append(os.path.dirname(os.path.abspath(__file__)) + '/../')
# ----------------------------------------------------------------------

from des_crypto import DESCrypto
from aes_crypto import AESCrypto
from file_utils import *
from color_log.clog import log

TESTED_PLAINTEXT = "特殊字符 $%^!@# 数字 123890 中文\tOK"
TESTED_FILEPATH = './test/test_crypto.py'
TESTED_ENCODING = judge_encoding(TESTED_FILEPATH)   # 被测文件原本的/解密后的编码
CIPHERTEXT_ENCODING = "ISO-8859-1"                  # 加密后的文件编码（因为是 base64， 统一用 ISO-8859-1 即可）
OUT_DIR = './out'


def main() :
    key = "EXP-BLOG"
    iv = "https://exp-blog.com"

    log.info("请选择以下测试模式：")
    log.info("1. 交互模式")
    log.info("2. 默认模式")
    option = input("请输入选项编号：")
    if option == '1' :
        interactive(key, iv)
    else :
        defavlt(key, iv)
    

def interactive(key, iv) :
    while True:
        log.info("请选择操作：")
        log.info("1. 加密测试")
        log.info("2. 解密测试")
        log.info("3. 退出")

        option = input("请输入选项编号：")
        if option == '1':
            encryption_test(key, iv)
        elif option == '2':
            decryption_test(key, iv)
        elif option == '3':
            break
        else:
            log.warn("未知选项，请重新输入！")


def encryption_test(key, iv):
    log.info("请选择加密算法：")
    log.info("1. AES")
    log.info("2. DES")
    algorithm_option = input("请输入选项编号：")

    log.info("请选择加密类型：")
    log.info("1. 字符串")
    log.info("2. 文件")
    type_option = input("请输入选项编号：")

    if type_option == '1':
        data = input("请输入要加密的字符串：")
        charset = TESTED_ENCODING

    elif type_option == '2':
        filepath = input("请输入要加密的文件路径：")
        charset = judge_encoding(filepath)
        data = file_read(filepath, charset)
    else:
        log.warn("未知选项，返回主菜单！")
        return

    algorithm = get_algorithm(algorithm_option, key, iv, charset)
    ciphertext = algorithm.encrypt(data)

    if type_option == '2':
        name = "AES" if algorithm_option == '1' else "DES"
        cipherfile = f"{OUT_DIR}/{name}_ciphertext.cro"
        file_write(cipherfile, ciphertext, CIPHERTEXT_ENCODING)
        log.info(f"[{name}] 已加密（{CIPHERTEXT_ENCODING}）: {cipherfile}")
        
    else :
        log.info(f"密文: {ciphertext}")


def decryption_test(key, iv):
    log.info("请选择解密算法：")
    log.info("1. AES")
    log.info("2. DES")
    algorithm_option = input("请输入选项编号：")

    log.info("请选择解密类型：")
    log.info("1. 字符串")
    log.info("2. 文件")
    type_option = input("请输入选项编号：")

    if type_option == '1':
        data = input("请输入要解密的字符串：")
        charset = TESTED_ENCODING

    elif type_option == '2':
        filepath = input("请输入要解密的文件路径：")
        data = file_read(filepath, CIPHERTEXT_ENCODING)

        log.info("请选择文件在加密前的编码：")
        log.info("1. UTF-8")
        log.info("2. GBK")
        charset_option = input("请输入选项编号：")
        charset = "UTF-8" if charset_option == '1' else "GBK"
    else:
        log.warn("未知选项，返回主菜单！")
        return

    algorithm = get_algorithm(algorithm_option, key, iv, charset)
    plaintext = algorithm.decrypt(data)

    if type_option == '2':
        name = "AES" if algorithm_option == '1' else "DES"
        plainfile = f"{OUT_DIR}/{name}_plaintext.txt"
        file_write(plainfile, plaintext, charset)
        log.info(f"[{name}] 已解密（{charset}）: {plainfile}")
    else :
        log.info(f"明文: {plaintext}")
    


def get_algorithm(option, key, iv, charset):
    if option == '1':
        return AESCrypto(key, iv=iv, encoding=charset)
    elif option == '2':
        return DESCrypto(key, encoding=charset)
    else:
        log.warn("未知选项，返回主菜单！")
        return



def defavlt(key, iv) :
    des = DESCrypto(key, encoding=TESTED_ENCODING)
    test_cache(des)
    test_file(des)

    aes = AESCrypto(key, iv=iv, encoding=TESTED_ENCODING)
    test_cache(aes)
    test_file(aes)


def test_cache(algorithm) :
    name = "DES" if isinstance(algorithm, DESCrypto) else "AES"
    log.warn(f"[{name}] 测试内存字符串加解密 ...")

    plaintext = TESTED_PLAINTEXT
    log.info(f"[{name}] 明文: {plaintext}")

    ciphertext = algorithm.encrypt(plaintext)
    log.info(f"[{name}] 密文: {ciphertext}")

    plaintext = algorithm.decrypt(ciphertext)
    log.info(f"[{name}] 解密: {plaintext}")

    log.warn(f"[{name}] 测试完成")


def test_file(algorithm) :
    name = "DES" if isinstance(algorithm, DESCrypto) else "AES"

    log.warn(f"[{name}] 测试文件字符串加解密 ...")
    tested_path = TESTED_FILEPATH
    if not os.path.exists(tested_path) :
        os._exit(1)
    elif not os.path.exists(OUT_DIR) :
        os.makedirs(OUT_DIR)

    plaintext = file_read(tested_path, TESTED_ENCODING)
    log.info(f"[{name}] 已读取被测文件（{TESTED_ENCODING}）: {tested_path}")

    cipherfile = f"{OUT_DIR}/{name}_ciphertext.cro"
    ciphertext = algorithm.encrypt(plaintext)
    file_write(cipherfile, ciphertext, CIPHERTEXT_ENCODING)
    log.info(f"[{name}] 已加密（{CIPHERTEXT_ENCODING}）: {cipherfile}")

    plainfile = f"{OUT_DIR}/{name}_plaintext.txt"
    plaintext = algorithm.decrypt(ciphertext)
    file_write(plainfile, plaintext, TESTED_ENCODING)
    log.info(f"[{name}] 已解密（{TESTED_ENCODING}）: {plainfile}")

    log.warn(f"[{name}] 测试完成")
    

if __name__ == '__main__' :
    main()
