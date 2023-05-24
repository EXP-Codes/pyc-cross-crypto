#!/usr/bin/env python
# -*- coding: utf-8 -*-
# @Author : EXP
# @Time   : 2022/11/09 23:56
# -----------------------------------------------

import chardet

def judge_encoding(filepath) :
    '''
    判断文件编码
    :params: filepath 目标文件
    :return: 文件编码
    '''
    encoding = "UTF-8"
    with open(filepath, 'rb') as file :
        data = file.read()
        encoding = chardet.detect(data)['encoding']
    return encoding
