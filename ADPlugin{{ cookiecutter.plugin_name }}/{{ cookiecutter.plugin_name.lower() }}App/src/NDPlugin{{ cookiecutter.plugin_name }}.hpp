/**
 * Template header file fo NDPlugins
 * 
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
#define {{ cookiecutter.plugin_name.upper() }}_VERSION      	0
#define {{ cookiecutter.plugin_name.upper() }}_REVISION     	0
#define {{ cookiecutter.plugin_name.upper() }}_MODIFICATION 	0



// Define the PVStrings for all of your PV values here in the following format
//#define NDPlugin{{ cookiecutter.plugin_name }}PVNameString 	"PV_STRING" 		//asynOctet


// define all necessary structs and enums here


/* Plugin class, extends plugin driver */
class NDPlugin{{ cookiecutter.plugin_name }} : public NDPluginDriver {
    public:
        NDPlugin{{ cookiecutter.plugin_name }}(const char *portName, int queueSize, int blockingCallbacks,
            const char* NDArrayPort, int NDArrayAddr, int maxBuffers,
            size_t maxMemory, int priority, int stackSize);


        void processCallbacks(NDArray *pArray);

        virtual asynStatus writeInt32(asynUser* pasynUser, epicsInt32 value);

    protected:

        //in this section i define the coords of database vals

        //Place PV indexes here, define first and last as appropriate, replace PLUGINNAME with name, 
        #define ND_{{ cookiecutter.plugin_name.upper() }}_FIRST_PARAM FIRSTPVINDEX
        #define ND_{{ cookiecutter.plugin_name.upper() }}_LAST_PARAM LASTPVINDEX

    private:

        // init all global variables here

        // init all plugin additional functions here

};

// Replace PLUGINNAME with plugin name ex. BAR
#define NUM_{{ cookiecutter.plugin_name.upper() }}_PARAMS ((int)(&ND_{{ cookiecutter.plugin_name.upper() }}_LAST_PARAM - &ND_{{ cookiecutter.plugin_name.upper() }}_FIRST_PARAM + 1))

#endif
