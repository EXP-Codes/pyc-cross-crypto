#!/usr/bin/env python
# -*- coding: utf-8 -*-
# @Author : EXP
# @Time   : 2023/05/24 23:56
# -----------------------------------------------
# DES 加解密工具
# 算法 ECB（无 IV）， 填充模式 PKCS5
# -----------------------------------------------

import base64
from pyDes import des, PAD_PKCS5, ECB
PLAINTEXT_ENCODING = 'UTF-8'


class DESCrypto :

    def __init__(self, key: str, encoding=PLAINTEXT_ENCODING) :
        '''
        key: DES 仅接受 8 字节长度的密钥
        '''
        self._des = des(key=key, IV=None, mode=ECB, padmode=PAD_PKCS5)
        self.encoding = encoding
        self.ISO_8859_1 = "ISO-8859-1"


    def encrypt(self, plaintext: str) -> str :
        plain_bytes = plaintext.encode(self.encoding)
        cipher_bytes = self._des.encrypt(plain_bytes)
        ciphertext = self.to_base64(cipher_bytes)
        return ciphertext


    def decrypt(self, ciphertext: str) -> str :
        cipher_bytes = self.un_base64(ciphertext)
        plain_bytes = self._des.decrypt(cipher_bytes)
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
