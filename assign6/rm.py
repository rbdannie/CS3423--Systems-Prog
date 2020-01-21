#!/usr/bin/env python3
import os
import sys
import shutil

path = "~/rm_trash"
trash_dir = os.path.expanduser(path)
args = sys.argv[1:]
trashdir_path = os.path.abspath(trash_dir)
r_check = "-r" in sys.argv[1:]

#check for number of arguments
if len(sys.argv) < 2:
    print("Not enough arguments passed to excute")
    sys.exit(1)

#check if rm trash exists
if not os.path.isdir(trash_dir):
    os.mkdir(trash_dir)

for arg in args:
    if arg == "-r":
        continue
    if not os.path.exists(arg):
        print("rm.py: cannot remove " + arg + ": No such file or directory")
    filepath = os.path.abspath(arg)
    file_base= os.path.basename(filepath)
    if os.path.isfile(arg):
        base_name,file_extension = os.path.splitext(file_base)
        delete_path = trashdir_path + "/" + file_base
        if not os.path.exists(delete_path):
            shutil.move(arg,trash_dir)
        else:
            count = 1
            new_arg= base_name + "-" + str(count) + file_extension
            for files in os.listdir(trash_dir):
                if new_arg in os.listdir(trash_dir):
                    count +=1
                    new_arg= base_name+ "-" + str(count) + file_extension
            shutil.move(arg,trash_dir + "/" + new_arg)
    if os.path.isdir(arg):
        deletedir_path = trashdir_path + "/" + file_base
        if not os.path.exists(deletedir_path):
            if r_check is True:
                shutil.move(arg,trash_dir)
            if r_check is False:
                print("cannot remove " + arg + " : Is a directory")
                continue
        else:
            i = 1
            new_dir = file_base + "-" + str(i)
            for directories in os.listdir(trash_dir):
                if new_dir in os.listdir(trash_dir):
                    i +=1 
                    new_dir = file_base + "-" + str(i)
            if r_check is True:   
                shutil.move(arg,trash_dir + "/" + new_dir)
            if r_check is False:
                print("cannot remove " + arg + " : Is a directory")
                continue
