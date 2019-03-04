#!/bin/bash

# This script will initialzie the plugin template for development,
# and set up a version control system using git.

if [ "$#" -ne 1 ]; then
    echo "Please enter one command line arg for the name of the plugin"
    exit
fi

echo "------------------------------------"
echo "Updating ADPluginTemplate with name:"
echo $1

python3 update_names.py -n $1

cd ..

echo "update_names.py" >> .gitignore
echo "initializePlugin.sh" >> .gitignore

git init
git add -A

PluginName="${1,,}"
PluginName="${PluginName^}"

git commit -m "Initial Commit for ADPlugin$PluginName"

