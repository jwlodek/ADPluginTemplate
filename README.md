# ADPluginTemplate

This repository contains a cookiecutter template for creating a new AreaDetector plugin.

### Usage

To utilize it, first install `cookiecutter` into your python environment:

```
pip install cookiecutter
```

Then, simply navigate to the director in which you want to develop the plugin (generally your `areaDetector` directory in the EPICS build tree), and execute `cookiecutter` giving the URL to this repository as an argument:

```
cookiecutter https://github.com/jwlodek/ADPluginTemplate
```

You will be prompted to specifiy a few things about your plugin:

Variable | Description
-----|---------------
author | Your first and last name
plugin_name | A name for your plugin (ex. Arrow, Barcode, Edge, ColorConvert etc.)
plugin_acronym | A shorthand name for your plugin (Up to three characters)
institution | Institution to which plugin source copyright will be attributed to.

### Current Plugins Developed with ADPluginTemplate

Below is an expanding list of plugins built with ADPluginTemplate. If you have made a plugin with it and want it listed here, feel free to make a pull request!

* [ADPluginDmtx](https://github.com/epicsNSLS2-areaDetector/ADPluginDmtx) - A data matrix barcode reader
* [ADPluginTimelapse](https://github.com/epicsNSLS2-areaDetector/ADPluginTimelapse) - A timelapse video generator for areaDetector (Still under development)
* [ADPluginArrow](https://github.com/NSLS2/ADPluginArrow) - A (currently experimental) plugin for integrating areaDetector with Apache Arrow data structures.
