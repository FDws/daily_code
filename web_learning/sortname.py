#!/usr/bin/python3
# -*- coding: utf-8 -*-

import re
import os
from functools import reduce

def getname(path):
    filelist=[]
    for pa,dirnames,filenames in os.walk(path):
        for filename in filenames:
            if re.match('test.*\.html',filename):
                filelist.append(filename)

    return filelist

def keys(ss):
    return reduce(lambda a,b:int(a)*10+int(b),filter(lambda s:s!='',re.split('[^\d]',ss)))

