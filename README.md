# ADPluginTemplate

This repository contains a pre-organized file structure for writing areaDetector plugins.
To use it, start by downloading a zip of one of the releases.

**DO NOT CLONE THIS REPOSITORY WHEN WRITING A NEW PLUGIN**

If you do, the git information will be cloned as well, and version control for your plugin will
contain all changes made to this template.

Once you download and unzip this template, go through the files and update all of the locations
where your plugin's name needs to be updated. (This part may be scripted away at some point).

Once you have done this, you may begin developing the plugin. Start by implementing the
functions in NDPlugin___.cpp, and by instantiating the PV values in the .template file.

Also, make sure to replace this README.md file with one that explains how to use your new plugin!
