/**
 * A basic template for implementing areaDetector plugins.
 * 
 * Author:{{ cookiecutter.author }} 
 * Created on: {% now 'local', '%m/%d/%Y' %}
 * 
 */

#ifndef NDPlugin{{ cookiecutter.plugin_name }}_H
#define NDPlugin{{ cookiecutter.plugin_name }}_H

//Define necessary includes here

using namespace std;

//include base plugin driver
#include "NDPluginDriver.h"

//version numbers
#define {{ cookiecutter.plugin_name.upper() }}_VERSION          0
#define {{ cookiecutter.plugin_name.upper() }}_REVISION         0
#define {{ cookiecutter.plugin_name.upper() }}_MODIFICATION     1



// Define the PVStrings for all of your PV values here in the following format
//#define NDPlugin{{ cookiecutter.plugin_name }}PVNameString    "{{ cookiecutter.plugin_name.upper() }}_PVNAME"  //DTYP (ex. asynInt32, asynFloat64, asynOctet)


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

        // Define the Param index variables here. Ex:
        // int NDPlugin{{ cookiecutter.plugin_name }}PVName;

        // Define these two variables as the first and last param indexes.
        #define ND_{{ cookiecutter.plugin_name.upper() }}_FIRST_PARAM 0
        #define ND_{{ cookiecutter.plugin_name.upper() }}_LAST_PARAM 0 

    private:

        // init all global variables here

        // init all plugin additional functions here

};

// Def that computes the number of params specific to the plugin
#define NUM_{{ cookiecutter.plugin_name.upper() }}_PARAMS ((int)(&ND_{{ cookiecutter.plugin_name.upper() }}_LAST_PARAM - &ND_{{ cookiecutter.plugin_name.upper() }}_FIRST_PARAM + 1))

#endif
