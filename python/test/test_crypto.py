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
from utils import *
from color_log.clog import log

TESTED_PLAINTEXT = "特殊字符 $%^!@# 数字 123890 中文\tOK"
TESTED_FILEPATH = './test/test_crypto.py'
TESTED_ENCODING = judge_encoding(TESTED_FILEPATH)   # 被测文件原本的/解密后的编码
CIPHERTEXT_ENCODING = "ISO-8859-1"                  # 加密后的文件编码（因为是 base64， 统一用 ISO-8859-1 即可）
OUT_DIR = './out'


def main() :
    key = "EXP-BLOG"
    des = DESCrypto(key, encoding=TESTED_ENCODING)
    test_cache(des)
    test_file(des)

    iv = "https://exp-blog.com"
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

    plaintext = ''
    with open(tested_path, 'r', encoding=TESTED_ENCODING) as file :
        plaintext = file.read()
    log.info(f"[{name}] 已读取被测文件（{TESTED_ENCODING}）: {tested_path}")

    cipherfile = f"{OUT_DIR}/{name}_ciphertext.cro"
    ciphertext = algorithm.encrypt(plaintext)
    with open(cipherfile, 'w+', encoding=CIPHERTEXT_ENCODING) as file :
        file.write(ciphertext)
    log.info(f"[{name}] 已加密（{CIPHERTEXT_ENCODING}）: {cipherfile}")

    plainfile = f"{OUT_DIR}/{name}_plaintext.txt"
    plaintext = algorithm.decrypt(ciphertext)
    with open(plainfile, 'w+', encoding=TESTED_ENCODING) as file :
        file.write(plaintext)
    log.info(f"[{name}] 已解密（{TESTED_ENCODING}）: {plainfile}")

    log.warn(f"[{name}] 测试完成")
    

if __name__ == '__main__' :
    main()
