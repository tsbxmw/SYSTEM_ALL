#encoding=utf-8

import sys
import os
import time

def curfiledir():
    path = os.getcwd()
    if os.path.isdir(path):
        return path
    elif os.path.isfile(path):
        return os.path.dirname(path)


if __name__=="__main__":
    args = sys.argv
    if len(args) < 7:
        print ("wrong with args ")
        sys.exit()
        
    par_dir = curfiledir()
    
    os.environ["PRODUCT_NAME"] = args[1]
    os.environ["VERSION_PATH_IN_FTP"] = args[2]
    os.environ["VERSIONTARGET_PATH_IN_FTP"] = args[3]
    os.environ["FOTAUP_PATH_IN_FTP"] = args[4]    
    os.environ["FOTADOWN_PATH_IN_FTP"] = args[5]
    os.environ["ROOTAPK_PATH_IN_FTP"] = args[6]

    for i in range(7,len(args)):
        print ("[ -- Stage " +args[i] +" -- ]")
        time.sleep(5)
        os.chdir(par_dir+"\\"+args[i])
        if os.path.exists("cirun.cmd"):
            os.system("cirun.cmd")
        else:
            print ("<* cirun.cmd is missing , please check path*>")
        print ("[ -- Finish -- ]")
    print ("[ ** test finished ** ]")