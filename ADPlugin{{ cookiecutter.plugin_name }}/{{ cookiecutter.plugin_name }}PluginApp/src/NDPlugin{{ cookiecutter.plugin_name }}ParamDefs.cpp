#include "NDPlugin{{ cookiecutter.plugin_name }}.h"

void NDPlugin{{ cookiecutter.plugin_name }}::createAllParams(){
    // This function is called during the plugin initialization to create
    // all the parameters defined for this plugin.

    // Example:
    createParam(NDPlugin{{ cookiecutter.plugin_name }}_LogLevelString, asynParamInt32, &NDPlugin{{ cookiecutter.plugin_name }}_LogLevel);
}