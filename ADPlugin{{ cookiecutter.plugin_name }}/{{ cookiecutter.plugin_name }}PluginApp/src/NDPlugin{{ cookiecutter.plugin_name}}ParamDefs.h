#ifndef NDPLUGIN{{ cookiecutter.plugin_name.upper() }}_PARAM_DEFS_H
#define NDPLUGIN{{ cookiecutter.plugin_name.upper() }}_PARAM_DEFS_H

// This file is auto-generated. Do not edit directly.
// Generated from NDPlugin{{ cookiecutter.plugin_name }}.template

// String definitions for parameters
#define NDPlugin{{ cookiecutter.driver_name }}_LogLevelString "{{ cookiecutter.driver_name.upper() }}_LOG_LEVEL"

// Parameter index definitions
int NDPlugin{{ cookiecutter.driver_name }}_LogLevel;

#define NDPLUGIN{{ cookiecutter.driver_name.upper() }}_FIRST_PARAM NDPlugin{{ cookiecutter.driver_name }}_LogLevel
#define NDPLUGIN{{ cookiecutter.driver_name.upper() }}_LAST_PARAM NDPlugin{{ cookiecutter.driver_name }}_LogLevel

#define NUM_NDPLUGIN{{ cookiecutter.driver_name.upper() }}_PARAMS ((int)(&NDPLUGIN{{ cookiecutter.driver_name.upper() }}_LAST_PARAM - &NDPLUGIN{{ cookiecutter.driver_name.upper() }}_FIRST_PARAM + 1))

#endif // NDPLUGIN{{ cookiecutter.plugin_name.upper() }}_PARAM_DEFS_H