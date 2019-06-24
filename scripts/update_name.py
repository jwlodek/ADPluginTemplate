"""
Python script used to replace the name of the plugin
whereever applicable to simplify using the template.
The script can be run with:
python3 update_name.py -n NAME

where NAME is the name of the plugin you are developing
"""

__author__      = "Jakub Wlodek"
__copyright__   = "Copyright June 2019, Brookhaven Science Associates"
__license__     = "GPL"
__version__     = "R0.4"
__maintainer__  = "Jakub Wlodek"


import os
import argparse
from sys import platform


def update_dir_names(all_lowercase):
    """ Updates the name of the main plugin directory """

    if os.path.exists("../pluginApp"):
        os.rename("../pluginApp", "../"+all_lowercase+"App")


def update_file_names(all_lowercase, standard_name):
    """ Updates the filenames of all of the plugin specific files. Also updates the contents of all files that are not in the src dir """

    if os.path.exists("../"+all_lowercase+"App/src/NDPlugin___.cpp"):
        os.rename("../"+all_lowercase+"App/src/NDPlugin___.cpp", "../"+all_lowercase+"App/src/NDPlugin"+standard_name+".cpp")
    if os.path.exists("../"+all_lowercase+"App/src/NDPlugin___.h"):
        os.rename("../"+all_lowercase+"App/src/NDPlugin___.h", "../"+all_lowercase+"App/src/NDPlugin"+standard_name+".h")
    if os.path.exists("../"+all_lowercase+"App/src/NDPlugin___.dbd"):
        os.rename("../"+all_lowercase+"App/src/NDPlugin___.dbd", "../"+all_lowercase+"App/src/NDPlugin"+standard_name+".dbd")
    if os.path.exists("../"+all_lowercase+"App/Db/NDPlugin___.template"):
        os.rename("../"+all_lowercase+"App/Db/NDPlugin___.template", "../"+all_lowercase+"App/Db/NDPlugin"+standard_name+".template")
    if os.path.exists("../"+all_lowercase+"App/Db/NDPlugin___settings.req"):
        os.rename("../"+all_lowercase+"App/Db/NDPlugin___settings.req", "../"+all_lowercase+"App/Db/NDPlugin"+standard_name+"_settings.req")
    if(os.path.exists("../"+all_lowercase+"App/Db/Makefile")):
        update_source_file(all_lowercase, all_lowercase.upper(), standard_name, "../"+all_lowercase+"App/Db/Makefile")
    if(os.path.exists("../"+all_lowercase+"App/Db/NDPlugin"+standard_name+".template")):
        update_source_file(all_lowercase, all_lowercase.upper(), standard_name, "../"+all_lowercase+"App/Db/NDPlugin"+standard_name+".template")
    if(os.path.exists("../docs/index.html")):
        update_source_file(all_lowercase, all_lowercase.upper(), standard_name, "../docs/index.html")
    if(os.path.exists("../RELEASE.md")):
        update_source_file(all_lowercase, all_lowercase.upper(), standard_name, "../RELEASE.md")
    if(os.path.exists("add_pv.py")):
        update_source_file(all_lowercase, all_lowercase.upper(), standard_name, "add_pv.py")


def update_source_file(all_lowercase, all_uppercase, standard_name, file_path):
    """ Reads file line by line and updates specific locations with correct plugin name """

    os.rename(file_path, file_path+"_OLD")
    oldFile = open(file_path+"_OLD", "r")
    newFile = open(file_path, "w")

    line = oldFile.readline()
    while(line):
        if "PLUGINNAMESTANDARD" in line:
            line = line.replace("PLUGINNAMESTANDARD", standard_name)
        if "PLUGINNAMEUPPER" in line:
            line = line.replace("PLUGINNAMEUPPER", all_uppercase)
        if "PLUGINNAMELOWER" in line:
            line = line.replace("PLUGINNAMELOWER", all_lowercase)
        newFile.write(line)
        line = oldFile.readline()

    oldFile.close()
    newFile.close()
    os.remove(file_path+"_OLD")


def update_sources(all_lowercase, all_uppercase, standard_name):
    """ Updates all of the files located in the src dir """

    if os.path.exists("../"+all_lowercase+"App/src"):
        src_dir = "../"+all_lowercase+"App/src"
        for file in os.listdir(src_dir):
            if(os.path.isfile(src_dir+"/"+file)):
                update_source_file(all_lowercase, all_uppercase, standard_name, src_dir + "/" + file)


def update_root_dir(standard_name):
    """ Renames the plugin root directory to reflect the new plugin name """

    for directory_name in os.listdir("../.."):
        if "ADPluginTemplate" in directory_name:
            os.rename("../../"+directory_name, "../../ADPlugin"+standard_name)


def parse_args():
    """ Parses name from user args in command line - no longer used """

    parser = argparse.ArgumentParser(description="Update plugin names in template")
    parser.add_argument('-n', '--name', help = 'Name of the plugin')
    arguments = vars(parser.parse_args())

    if arguments["name"] is not None:
        name = arguments["name"]
        all_lowercase = name.lower()
        all_uppercase = name.upper()
        standard_name = all_lowercase.capitalize()

        update_dir_names(all_lowercase)
        update_file_names(all_lowercase, standard_name)
        update_sources(all_lowercase, all_uppercase, standard_name)
        update_root_dir(standard_name)

    else:
        print("Error, no plugin name specified")


# calls other functions
#parse_args()

def run_all(name):
    """ updates names """

    all_lowercase = name.lower()
    all_uppercase = name.upper()
    standard_name = all_lowercase.capitalize()

    update_dir_names(all_lowercase)
    update_file_names(all_lowercase, standard_name)
    update_sources(all_lowercase, all_uppercase, standard_name)
    if platform == 'linux':
        update_root_dir(standard_name)
    else:
        print('Your OS does not allow for changing the root directory of the plugin, as this script was run inside of it. Please change it manually.')
