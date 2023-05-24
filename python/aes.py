#!/usr/bin/env python
# -*- coding: utf-8 -*-
# @Author : EXP
# @Time   : 2023/05/24 23:56
# -----------------------------------------------
# AES 加解密工具
# 算法 CBC（含 IV）， 填充模式 PKCS7
# -----------------------------------------------

import hashlib
import base64
from Crypto.Cipher import AES
from Crypto.Util.Padding import pad, unpad
PLAINTEXT_ENCODING = 'UTF-8'
AES_IV = "https://exp-blog.com"


class AESCrypto :

    def __init__(self, key: str, iv=AES_IV, encoding=PLAINTEXT_ENCODING) :
        self.block_size = AES.block_size
        self.encoding = encoding
        self.ISO_8859_1 = "ISO-8859-1"

        # 使用 sha256 处理 key 和 IV
        # 使其满足 AES 密钥长度要求（AES 仅接受 16、24、32 字节长度的密钥）
        self.key = hashlib.sha256(key.encode(self.ISO_8859_1)).digest()
        self.iv = hashlib.sha256(iv.encode(self.ISO_8859_1)).digest()[:16]


    def encrypt(self, plaintext: str) -> str :
        # AES 在加密/解密一次之后，IV 随机向量会改变，不能复用同一个对象
        aes = AES.new(self.key, AES.MODE_CBC, self.iv)

        plain_bytes = plaintext.encode(self.encoding)
        paded_plain_bytes = pad(plain_bytes, self.block_size)
        cipher_bytes = aes.encrypt(paded_plain_bytes)
        ciphertext = self.to_base64(cipher_bytes)
        return ciphertext
    

    def decrypt(self, ciphertext: str) -> str :
        # AES 在加密/解密一次之后，IV 随机向量会改变，不能复用同一个对象
        aes = AES.new(self.key, AES.MODE_CBC, self.iv)

        cipher_bytes = self.un_base64(ciphertext)
        paded_plain_bytes = aes.decrypt(cipher_bytes)
        plain_bytes = unpad(paded_plain_bytes, self.block_size)
        plaintext = plain_bytes.decode(self.encoding)
        return plaintext
    

    def to_base64(self, text_bytes) :
        base64_bytes = base64.b64encode(text_bytes)
        base64_text = base64_bytes.decode(self.ISO_8859_1)
        return base64_text


    def un_base64(self, base64_text) :
        base64_bytes = base64_text.encode(self.ISO_8859_1)
        text_bytes = base64.b64decode(base64_bytes)
        return text_bytes

