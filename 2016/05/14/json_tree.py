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

def path_hierarchy(path):
    ''' Based on: http://unix.stackexchange.com/a/164612/170306'''
    hierarchy = {}
    hierarchy['.'] = {
        'path': path,
    }

    try:
        for contents in os.listdir(path):
            hierarchy[contents] = path_hierarchy(os.path.join(path, contents))
    except OSError as e:
        if e.errno != errno.ENOTDIR:
            raise
        hierarchy = hierarchy['.']
        hierarchy['sha1'] = sha1OfFile(path)

    return hierarchy

def main():
    ''' Based on: http://unix.stackexchange.com/a/164612/170306'''
    try:
        directory = sys.argv[1]
    except IndexError:
        directory = "."

    print(json.dumps(path_hierarchy(directory), indent=4, sort_keys=True))
    
if __name__ == '__main__':
    main()