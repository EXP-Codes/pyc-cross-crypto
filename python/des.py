#!/usr/bin/env python
# -*- coding: utf-8 -*-
# @Author : EXP
# @Time   : 2023/05/24 23:56
# -----------------------------------------------
# DES 加解密工具
# 算法 ECB（无 IV）， 填充模式 PKCS5
# -----------------------------------------------

import hashlib
import base64
from pyDes import des, PAD_PKCS5, ECB
PLAINTEXT_ENCODING = 'UTF-8'


class DESCrypto :
    """
    使用DES算法进行加密和解密的DESCrypto类。
    """

    def __init__(self, key: str, encoding=PLAINTEXT_ENCODING) :
        """
        DESCrypto 构造函数。

        :param key: 用于对称密码的密钥。处理后长度为8（DES）字节。
        :param encoding: 在对明文进行编码或解码时使用的编码。
        """

        self.encoding = encoding
        self.ISO_8859_1 = "ISO-8859-1"

        # 使用 sha256 处理 key，使其满足 DES 密钥长度要求（8 字节）
        key = hashlib.sha256(key.encode(self.ISO_8859_1)).digest()[:8]
        self._des = des(key=key, IV=None, mode=ECB, padmode=PAD_PKCS5)


    def encrypt(self, plaintext: str) -> str :
        """
        使用 DES 加密对明文进行加密。

        :param plaintext: 需要加密的文本。
        :return: 以 base64 格式的加密文本。
        """

        plain_bytes = plaintext.encode(self.encoding)
        cipher_bytes = self._des.encrypt(plain_bytes)
        ciphertext = self.to_base64(cipher_bytes)
        return ciphertext
    

    def decrypt(self, ciphertext: str) -> str :
        """
        使用 DES 解密对密文进行解密。

        :param ciphertext: 需要解密的文本。
        :return: 解密后的文本。
        """

        cipher_bytes = self.un_base64(ciphertext)
        plain_bytes = self._des.decrypt(cipher_bytes)
        plaintext = plain_bytes.decode(self.encoding)
        return plaintext
    

    def to_base64(self, text_bytes) :
        """
        将字节转换为 base64 字符串。

        :param text_bytes: 需要转换为 base64 字符串的字节。
        :return: base64 字符串。
        """

        base64_bytes = base64.b64encode(text_bytes)
        base64_text = base64_bytes.decode(self.ISO_8859_1)
        return base64_text


    def un_base64(self, base64_text) :
        """
        将 base64 字符串转换为字节。

        :param base64_text: 需要转换为字节的 base64 字符串。
        :return: 转换后的字节。
        """

        base64_bytes = base64_text.encode(self.ISO_8859_1)
        text_bytes = base64.b64decode(base64_bytes)
        return text_bytes
