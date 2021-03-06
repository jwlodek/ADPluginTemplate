#!/usr/bin/env python3

"""
This script will initialzie the plugin template for development,
and set up a version control system using git.
"""

__author__      = "Jakub Wlodek"
__copyright__   = "Copyright June 2019, Brookhaven Science Associates"
__version__     = "R0.5"


import argparse
import subprocess
import update_name
import os


# ------------ Helper functions -------------

def parse_user_args():
    parser = argparse.ArgumentParser(description="Initialize ADPlugin boilerplate code from template")
    required = parser.add_argument_group('required arguments')
    required.add_argument('-n', '--name', required=True, help="Flag representing new plugin's name, without 'AD' at the start. ex. EmergentVision")
    parser.add_argument('-o', '--onlyupdate', action='store_true', help='Flag that forces initPlugin.py to only apply the update names script, not initialize version control.')
    arguments = vars(parser.parse_args())
    return arguments['name'], arguments['onlyupdate']



# -------------- Run script ------------------


name, only_update = parse_user_args()
if name.startswith('ADPlugin'):
    print('Detected name starting with ADPlugin')
    name = name[8:]
elif name.startswith('AD'):
    print('Detected name starting with AD.')
    name = name[2:]

name = name.lower()
name = name.capitalize()

print("+----------------------------------------------------------------+")
print("+ ADPluginTemplate, version: {}                                +".format(__version__))
print("+ Author: Jakub Wlodek                                           +")
print("+ Copyright (c): Brookhaven National Laboratory 2018-2019        +")
print("+ This software comes with NO warranty!                          +")
print("+----------------------------------------------------------------+")
print()


print("Updating ADPluginTemplate with name: {}".format(name))

update_name.run_all(name)

if only_update:
    print('Only update option selected, exiting...')
    exit()

os.chdir('..')

print('Updating .gitignore')
gitignore_fp = open('.gitignore', 'a')
gitignore_fp.write('\nscripts/\n')
gitignore_fp.close()

print('Initializing new ADPlugin' + name + ' README.md file')
os.rename('README.md', 'TemplateReadme.md')

readme_fp = open('README.md', 'w')
readme_fp.write('# ADPlugin' + name + '\n\n')
readme_fp.write('This plugin is currently under development\n\n')
readme_fp.write('This plugin was built with the help of [ADPluginTemplate](https://github.com/epicsNSLS2-areaDetector/ADPluginTemplate)\n\n')
readme_fp.close()

print('Initializing git version control with initial commit...')
print('Remember to add a remote and push.')
subprocess.call(['git', 'init'])
subprocess.call(['git', 'add', '-A'])
subprocess.call(['git', 'commit', '-m', 'Initial Commit for ADPlugin' + name])

print('ADPlugin' + name + ' initialized from ADPluginTemplate successfully.')