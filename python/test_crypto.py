#!/usr/bin/env python
# -*- coding: utf-8 -*-
# @Author : EXP
# @Time   : 2022/11/15 23:56
# -----------------------------------------------
# DES 加解密工具测试
# -----------------------------------------------

# ----------------------------------------------------------------------
# 把父级目录（项目根目录）添加到工作路径，以便在终端也可以执行单元测试
import os
import sys
sys.path.append(os.path.dirname(os.path.abspath(__file__)) + '/../')
# ----------------------------------------------------------------------

from color_log.clog import log
from common.des import DESCrypto
from common.aes import AESCrypto
NPC_ENCODING = "GBK"
CIPHERTEXT_ENCODING = "UTF-8"


def main() :
    key = "EXPROkey"
    des = DESCrypto(key, encoding=NPC_ENCODING)
    # test_cache(des)
    # test_file(des)

    iv = "EXP-RO-iv"
    aes = AESCrypto(key, iv=iv, encoding=NPC_ENCODING)
    test_cache(aes)
    # test_file(aes)


def test_cache(algorithm) :
    name = "DES" if isinstance(algorithm, DESCrypto) else "AES"
    log.warn(f"[{name}] 测试内存字符串加解密 ...")

    plaintext = "Starting 中文 asas"
    log.info(f"[{name}] 明文: {plaintext}")

    ciphertext = algorithm.encrypt(plaintext)
    log.info(f"[{name}] 密文: {ciphertext}")

    plaintext = algorithm.decrypt(ciphertext)
    log.info(f"[{name}] 解密: {plaintext}")

    log.warn(f"[{name}] 测试完成")


def test_file(algorithm) :
    name = "DES" if isinstance(algorithm, DESCrypto) else "AES"

    log.warn(f"[{name}] 测试文件字符串加解密 ...")
    npcpath = './covers/npc/merchants/refine.txt'
    if not os.path.exists(npcpath) :
        os._exit(1)

    plaintext = ''
    with open(npcpath, 'r', encoding=NPC_ENCODING) as file :
        plaintext = file.read()
    log.info(f"[{name}] 已读取 NPC 脚本（{NPC_ENCODING}）: {npcpath}")

    cipherfile = f"./out/{name}_ciphertext.nro"
    ciphertext = algorithm.encrypt(plaintext)
    with open(cipherfile, 'w+', encoding=CIPHERTEXT_ENCODING) as file :
        file.write(ciphertext)
    log.info(f"[{name}] 已加密（{CIPHERTEXT_ENCODING}）: {cipherfile}")

    plainfile = f"./out/{name}_plaintext.txt"
    plaintext = algorithm.decrypt(ciphertext)
    with open(plainfile, 'w+', encoding=NPC_ENCODING) as file :
        file.write(plaintext)
    log.info(f"[{name}] 已解密（{NPC_ENCODING}）: {plainfile}")

    log.warn(f"[{name}] 测试完成")
    

if __name__ == '__main__' :
    main()
