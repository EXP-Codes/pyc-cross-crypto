#!/usr/bin/env python
# -*- coding: utf-8 -*-
# @Author : EXP
# @Time   : 2022/11/09 23:56
# -----------------------------------------------

import os
import chardet
DEFAULT_ENCODING = "UTF-8"


def judge_encoding(filepath) :
    '''
    判断文件编码
    :params: filepath 目标文件
    :return: 文件编码
    '''
    encoding = DEFAULT_ENCODING
    with open(filepath, 'rb') as file :
        data = file.read()
        encoding = chardet.detect(data)['encoding']
    return encoding


def file_read(filepath, encoding=DEFAULT_ENCODING) :
    content = ''
    if not os.path.exists(filepath) :
        return content
    with open(filepath, 'r', encoding=encoding) as file :
        content = file.read()
    return content


def file_write(filepath, content, encoding=DEFAULT_ENCODING) :
    with open(filepath, 'w+', encoding=encoding) as file :
        file.write(content)
    
