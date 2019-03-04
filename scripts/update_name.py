# Python script used to replace the name of the plugin
# whereever applicable to simplify using the template.
# The script can be run with:
#
# python3 update_name.py -n NAME
#
# where NAME is the name of the plugin you are developing
#

import os
import argparse


def update_dir_names(all_lowercase):
    if os.path.exists("../pluginApp"):
        os.rename("../pluginApp", "../"+all_lowercase+"App")


def update_file_names(standard_name):
    if os.path.exists("../pluginApp/src/NDPlugin___.cpp"):
        os.rename("../pluginApp/src/NDPlugin___.cpp", "../pluginApp/src/NDPlugin"+standard_name+".cpp")
    if os.path.exists("../pluginApp/src/NDPlugin___.h"):
        os.rename("../pluginApp/src/NDPlugin___.h", "../pluginApp/src/NDPlugin"+standard_name+".h")
    if os.path.exists("../pluginApp/src/NDPlugin___.dbd"):
        os.rename("../pluginApp/src/NDPlugin___.dbd", "../pluginApp/src/NDPlugin"+standard_name+".dbd")
    if os.path.exists("../pluginApp/Db/NDPlugin___.template"):
        os.rename("../pluginApp/Db/NDPlugin___.template", "../pluginApp/Db/NDPlugin"+standard_name+".template")
    if os.path.exists("../pluginApp/Db/NDPlugin___settings.req"):
        os.rename("../pluginApp/Db/NDPlugin___settings.req", "../pluginApp/Db/NDPlugin"+standard_name+"_settins.req")


def update_source_file(all_lowercase, all_uppercase, standard_name, file_path):
    os.rename(file_path, file_path+"_OLD")
    oldFile = open(file_path+"_OLD", "r")
    newFile = open(file_path, "r")

    line = oldFile.readline()
    while(line):
        if "___" in line:
            line = line.replace("___", standard_name)
        elif "PLUGINNAME" in line:
            line = line.replace("PLUGINNAME", all_uppercase)
        newFile.write(line)
        line = oldFile.readline()

    oldFile.close()
    newFile.close()
    os.remove(file_path+"_OLD")



def update_sources(all_lowercase, all_uppercase, standard_name):
    if os.path.exists("../"+all_lowercase+"App/src"):
        src_dir = "../"+all_lowercase+"App/src"
        for file in os.listdir(src_dir):
            if(os.path.isfile(src_dir+"/"+file)):
                update_source_file(all_lowercase, all_uppercase, standard_name, src_dir + "/" + file)



def parse_args():
    parser = argparse.ArgumentParser(description="Update plugin names in template")
    parser.add_argument('-n', '--name', help = 'Name of the plugin')
    arguments = vars(parser.parse_args())

    if arguments["name"] is not None:
        name = arguments["name"]
        all_lowercase = name.lower()
        all_uppercase = name.upper()
        standard_name = all_lowercase.capitalize()

        update_dir_names(all_lowercase)
        update_file_names(standard_name)
        update_sources(all_lowercase, all_uppercase, standard_name)

    else:
        print("Error, no plugin name specified")


    

parse_args()