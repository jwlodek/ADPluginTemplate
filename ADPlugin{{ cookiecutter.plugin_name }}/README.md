# ADPlugin{{ cookiecutter.plugin_name }}

Repository containing {{ cookiecutter.plugin_name }} areaDetector plugin source code.

### Installation

To install ADPlugin{{ cookiecutter.plugin_name }}, clone it into your `areaDetector` directory, enter it and run:

```
make
```

Note that `ADSupport`, `ADCore`, and any external dependencies must be built/installed first. 

Next, open `$(AREA_DETECTOR)/configure/RELEASE_PRODS.local`, and add:

```
ADPLUGIN{{ cookiecutter.plugin_name.upper() }}=$(AREA_DETECTOR)/ADPluginName{{ cookiecutter.plugin_name }}
```

Then, add the following to `$(AREA_DETECTOR)/ADCore/ADApp/commonDriverMakefile`

```
ifdef ADPLUGIN{{ cookiecutter.plugin_name.upper() }}
  $(DBD_NAME)_DBD += NDPlugin{{ cookiecutter.plugin_name }}.dbd
  PROD_LIBS += NDPlugin{{ cookiecutter.plugin_name }}
  # Add any external library dependancy links here
  # PROD_SYS_LIBS += ... For system libraries
  # PROD_LIBS += ... For libraries built as part of the plugin build process
endif
```

Next, enter the target `areaDetector` driver directory and rebuild it with `make`.

Finally, in either your IOC `st.cmd` startup file, or in `$(AREA_DETECTOR)/ADCore/iocBoot/commonPlugins.cmd` initialize the plugin for startup:

```
ND{{ cookiecutter.plugin_name }}Configure("{{ cookiecutter.plugin_name.upper()[:3] }}1", $(QSIZE), 0, "$(PORT)", 0, 0, 0, 0, 0, $(MAX_THREADS=5))
dbLoadRecords("$(ADPLUGIN{{ cookiecutter.plugin_name.upper() }})/db/NDPlugin{{ cookiecutter.plugin_name }}.template", "P=$(PREFIX), R={{ cookiecutter.plugin_name.upper()[:3] }}1:, PORT={{ cookiecutter.plugin_name.upper()[:3] }}1, ADDR=0, TIMEOUT=1, NDARRAY_PORT=$(PORT), NAME={{ cookiecutter.plugin_name.upper()[:3] }}1, NCHANS=$(NCHANS)")
set_requestfile_path("$(ADPLUGIN{{ cookiecutter.plugin_name.upper() }})/{{ cookiecutter.plugin_name.lower() }}/Db")
```

### Credits

This plugin was built in part with the help of [ADPluginTemplate](https://github.com/jwlodek/ADPluginTemplate).
