#!/usr/bin/env python
'''
Program to output a json object that represents the current directory (or a 
directory supplied as the first argument) . Also recursively goes into
subdirectories.

Simple Sample:
".": {
        "name": ".", 
        "path": "."
    }, 
    "json_tree.py": {
        "path": "./json_tree.py", 
        "sha1hash": "05963039d44d1ecfdfd5c73222ba9085967165b7"
    }
}
'''
import os
import errno
import json
import sys
from datetime import datetime
import shutil
import filecmp

today = datetime.today().isoformat()
today_dir = None
file_dir = None
    
def sha1OfFile(filepath):
    '''Direct copy of: http://stackoverflow.com/a/19711609'''
    import hashlib
    sha = hashlib.sha1()
    with open(filepath, 'rb') as f:
        while True:
            block = f.read(2**10) # Magic number: one-megabyte blocks.
            if not block: break
            sha.update(block)
        return sha.hexdigest()

def simple_walk(arg, dirname, names):
    ''' Based on: http://unix.stackexchange.com/a/164612/170306'''
    for f in names:
        path = os.path.join(dirname, f)
        if(os.path.isfile(path)):
            on_file(path, arg)
            
def on_file(fpath, file_dir):
    sha1 = sha1OfFile(fpath);
    dest1 = os.path.join(file_dir, sha1)
    
    if(os.path.isfile(dest1)):
        if(not filecmp.cmp(fpath, dest1)):
            print('ERROR: Diferent os.stat on files ["{0}","{1}"]'.format(fpath, dest1))
            exit(1)
    else:
        shutil.copyfile(fpath, dest1)
        print('cp "{0}" "{1}"'.format(fpath, dest1))
        

def main():
    ''' Based on: http://unix.stackexchange.com/a/164612/170306'''
    try:
        directory = sys.argv[1]
    except IndexError:
        directory = "."

    file_dir = os.path.join('.', 'file')

    if not os.path.exists(file_dir):
        os.mkdir(file_dir)
    
    os.path.walk(directory, simple_walk, file_dir)
    
if __name__ == '__main__':
    main()