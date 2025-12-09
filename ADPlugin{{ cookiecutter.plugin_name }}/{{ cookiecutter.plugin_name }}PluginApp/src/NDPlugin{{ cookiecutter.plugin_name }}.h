/**
 * A basic template for implementing areaDetector plugins.
 * 
 * Author:{{ cookiecutter.author }} 
 * Created on: {% now 'local', '%m/%d/%Y' %}
 * 
 */

#ifndef NDPLUGIN{{ cookiecutter.plugin_name.upper() }}_H
#define NDPLUGIN{{ cookiecutter.plugin_name.upper() }}_H


using namespace std;

//include base plugin driver
#include "NDPluginDriver.h"

//version numbers
#define NDPLUGIN{{ cookiecutter.plugin_name.upper() }}_VERSION          0
#define NDPLUGIN{{ cookiecutter.plugin_name.upper() }}_REVISION         0
#define NDPLUGIN{{ cookiecutter.plugin_name.upper() }}_MODIFICATION     1

// Name of the plugin
#define PLUGIN_NAME "NDPlugin{{ cookiecutter.plugin_name }}"

// Error message formatters
#define ERR(msg)                                      \
    if (this->getLogLevel() >= NDPlugin{{ cookiecutter.plugin_name }}LogLevel::ERROR) \
        fprintf(stderr, "ERROR | %s::%s: %s\n", PLUGIN_NAME, __func__, msg);

#define ERR_ARGS(fmt, ...)                            \
    if (this->getLogLevel() >= NDPlugin{{ cookiecutter.plugin_name }}LogLevel::ERROR) \
        fprintf(stderr, "ERROR | %s::%s: " fmt "\n", PLUGIN_NAME, __func__, __VA_ARGS__);

// Warning message formatters
#define WARN(msg)                                       \
    if (this->getLogLevel() >= NDPlugin{{ cookiecutter.plugin_name }}LogLevel::WARNING) \
        fprintf(stderr, "WARNING | %s::%s: %s\n", PLUGIN_NAME, __func__, msg);

#define WARN_ARGS(fmt, ...)                             \
    if (this->getLogLevel() >= NDPlugin{{ cookiecutter.plugin_name }}LogLevel::WARNING) \
        fprintf(stderr, "WARNING | %s::%s: " fmt "\n", PLUGIN_NAME, __func__, __VA_ARGS__);

// Info message formatters. Because there is no ASYN trace for info messages, we just use `fprintf`
// here.
#define INFO(msg)                                    \
    if (this->getLogLevel() >= NDPlugin{{ cookiecutter.plugin_name }}LogLevel::INFO) \
        fprintf(stdout, "INFO | %s::%s: %s\n", PLUGIN_NAME, __func__, msg);

#define INFO_ARGS(fmt, ...)                          \
    if (this->getLogLevel() >= NDPlugin{{ cookiecutter.plugin_name }}LogLevel::INFO) \
        fprintf(stdout, "INFO | %s::%s: " fmt "\n", PLUGIN_NAME, __func__, __VA_ARGS__);

// Debug message formatters
#define DEBUG(msg)                                    \
    if (this->getLogLevel() >= NDPlugin{{ cookiecutter.plugin_name }}LogLevel::DEBUG) \
        fprintf(stdout, "DEBUG | %s::%s: %s\n", PLUGIN_NAME, __func__, msg);

#define DEBUG_ARGS(fmt, ...)                          \
    if (this->getLogLevel() >= NDPlugin{{ cookiecutter.plugin_name }}LogLevel::DEBUG) \
        fprintf(stdout, "DEBUG | %s::%s: " fmt "\n", PLUGIN_NAME, __func__, __VA_ARGS__);


enum class NDPlugin{{ cookiecutter.plugin_name }}LogLevel {
    NONE = 0,      // No logging
    ERROR = 10,    // Error messages only
    WARNING = 20,  // Warnings and errors
    INFO = 30,     // Info, warnings, and errors
    DEBUG = 40     // Debugging information
};

/* Plugin class, extends NDPluginDriver base class */
class NDPlugin{{ cookiecutter.plugin_name }} : public NDPluginDriver {
    public:
        NDPlugin{{ cookiecutter.plugin_name }}(const char *portName, int queueSize, int blockingCallbacks,
            const char* NDArrayPort, int NDArrayAddr, int maxBuffers,
            size_t maxMemory, int priority, int stackSize, int maxThreads);

        void processCallbacks(NDArray *pArray);

        virtual asynStatus writeInt32(asynUser* pasynUser, epicsInt32 value);
        virtual asynStatus writeFloat64(asynUser* pasynUser, epicsFloat64 value);

    protected:

#include "NDPlugin{{ cookiecutter.plugin_name }}ParamDefs.h"

    private:

        // handle logging
        NDPlugin{{ cookiecutter.plugin_name }}LogLevel logLevel = NDPlugin{{ cookiecutter.plugin_name }}LogLevel::DEBUG;
        NDPlugin{{ cookiecutter.plugin_name }}LogLevel getLogLevel() { return logLevel; }
        void setLogLevel(NDPlugin{{ cookiecutter.plugin_name }}LogLevel level) { logLevel = level; }
        void createAllParams();

};

#endif
