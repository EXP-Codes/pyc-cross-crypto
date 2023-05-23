#!/usr/bin/env python
# -*- coding: utf-8 -*-
# @Author : EXP
# @Time   : 2022/11/09 23:56
# -----------------------------------------------

import chardet
from common.settings import *


def judge_encoding(filepath) :
    '''
    判断文件编码
    :params: filepath 目标文件
    :return: 文件编码
    '''
    encoding = ENCODING
    with open(filepath, 'rb') as file :
        data = file.read()
        encoding = chardet.detect(data)['encoding']
    return encoding


def concat_path(paths) :
    '''
    拼接文件路径
    :params: paths 部分路径数组
    :return: 文件路径
    '''
    return '/'.join(paths)