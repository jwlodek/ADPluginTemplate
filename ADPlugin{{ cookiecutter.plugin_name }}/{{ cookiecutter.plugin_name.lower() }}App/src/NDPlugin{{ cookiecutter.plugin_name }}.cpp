/**
 * This file is a basic template for implementing areaDetector plugins.
 * You must implement all of the functions already listed here along with any 
 * additional plugin specific functions you require.
 * 
 * Author: {{ cookiecutter.author }}
 * Created on: {% now 'local', '%m/%d/%Y' %}
 * 
 */



//include some standard libraries
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <iostream>
#include <stdio.h>


//include epics/area detector libraries
#include <epicsMutex.h>
#include <epicsString.h>
#include <iocsh.h>
#include "NDArray.h"
// Include your plugin's header file here
#include "NDPlugin{{ cookiecutter.plugin_name }}.h"
#include <epicsExport.h>

// include your external dependency libraries here


//some basic namespaces
using namespace std;


// Name your plugin
static const char *pluginName="NDPlugin{{ cookiecutter.plugin_name }}";



/**
 * Override of NDPluginDriver function. Must be implemented by your plugin
 * 
 * @params[in]: pasynUser	-> pointer to asyn User that initiated the transaction
 * @params[in]: value		-> value PV was set to
 * @return: success if PV was updated correctly, otherwise error
 */
asynStatus NDPlugin{{ cookiecutter.plugin_name }}::writeInt32(asynUser* pasynUser, epicsInt32 value){
    const char* functionName = "writeInt32";
    int function = pasynUser->reason;
    asynStatus status = asynSuccess;

    status = setIntegerParam(function, value);
    asynPrint(this->pasynUserSelf, ASYN_TRACEIO_DRIVER, "%s::%s function = %d value=%d\n", pluginName, functionName, function, value);

    // replace PLUGINNAME with your plugin (ex. BAR)
    if(function < ND_{{ cookiecutter.plugin_name.upper() }}_FIRST_PARAM){
        status = NDPluginDriver::writeInt32(pasynUser, value);
    }
    callParamCallbacks();
    if(status){
        asynPrint(this->pasynUserSelf, ASYN_TRACE_ERROR, "%s::%s Error writing Int32 val to PV\n", pluginName, functionName);
    }
    return status;
}



/* Process callbacks function inherited from NDPluginDriver.
 * You must implement this function for your plugin to accept NDArrays
 *
 * @params[in]: pArray -> NDArray recieved by the plugin from the camera
 * @return: void
*/
void NDPlugin{{ cookiecutter.plugin_name }}::processCallbacks(NDArray *pArray){
    static const char* functionName = "processCallbacks";
    NDArray *pScratch;
    asynStatus status = asynSuccess;
    NDArrayInfo arrayInfo;

    //call base class and get information about frame
    NDPluginDriver::beginProcessCallbacks(pArray);

    // convert to Mat
    pArray->getInfo(&arrayInfo);

    //unlock the mutex for the processing portion
    this->unlock();

    // Process your image here.
    // Access data with pArray->pData
    // DO NOT CALL pArray.release()
    // If used, call pScratch.release()
    // use doCallbacksGenericPointer with pScratch to pass processed image to plugin array port

    this->lock();

    if(status == asynError){
        asynPrint(this->pasynUserSelf, ASYN_TRACE_ERROR, "%s::%s Error, image not processed correctly\n", pluginName, functionName);
        return;
    }

    // This call can push the pScratch array to callbacks for other plugins. If this is required, enter false, true as the two other arguments.
    NDPluginDriver::endProcessCallbacks(pScratch, false, false);

    callParamCallbacks();
}



//constructror from base class, replace with your plugin name
NDPlugin{{ cookiecutter.plugin_name }}::NDPlugin{{ cookiecutter.plugin_name }}(const char *portName, int queueSize, int blockingCallbacks,
        const char *NDArrayPort, int NDArrayAddr,
        int maxBuffers, size_t maxMemory,
        int priority, int stackSize, int maxThreads)
        /* Invoke the base class constructor */
        : NDPluginDriver(portName, queueSize, blockingCallbacks,
        NDArrayPort, NDArrayAddr, 1, maxBuffers, maxMemory,
        asynInt32ArrayMask | asynFloat64ArrayMask | asynGenericPointerMask,
        asynInt32ArrayMask | asynFloat64ArrayMask | asynGenericPointerMask,
        ASYN_MULTIDEVICE, 1, priority, stackSize, maxThreads)
{

    char versionString[25];

    // Create PV parameters here
    // EXAMPLE:
    // createParam(PVString, 	asynParamOctet, 	&PVIndex);  -> string and waveform records
    // createParam(PVString, 	asynParamInt32, 	&PVIndex);  -> int records
    // createParam(PVString, 	asynParamFloat64, 	&PVIndex);  -> float records

    setStringParam(NDPluginDriverPluginType, "NDPlugin{{ cookiecutter.plugin_name }}");
    epicsSnprintf(versionString, sizeof(versionString), "%d.%d.%d", {{ cookiecutter.plugin_name.upper() }}_VERSION, {{ cookiecutter.plugin_name.upper() }}_REVISION, {{ cookiecutter.plugin_name.upper() }}_MODIFICATION);
    setStringParam(NDDriverVersion, versionString);
    connectToArrayPort();
}



/**
 * External configure function. This will be called from the IOC shell of the
 * detector the plugin is attached to, and will create an instance of the plugin and start it
 * 
 * @params[in]	-> all passed to constructor
 */
extern "C" int ND{{ cookiecutter.plugin_name }}Configure(const char *portName, int queueSize, int blockingCallbacks,
        const char *NDArrayPort, int NDArrayAddr,
        int maxBuffers, size_t maxMemory,
        int priority, int stackSize, int maxThreads){

    NDPlugin{{ cookiecutter.plugin_name }} *pPlugin = new NDPlugin{{ cookiecutter.plugin_name }}(portName, queueSize, blockingCallbacks, NDArrayPort, NDArrayAddr,
        maxBuffers, maxMemory, priority, stackSize, maxThreads);
    return pPlugin->start();
}


/* IOC shell arguments passed to the plugin configure function */
static const iocshArg initArg0 = { "portName",iocshArgString};
static const iocshArg initArg1 = { "frame queue size",iocshArgInt};
static const iocshArg initArg2 = { "blocking callbacks",iocshArgInt};
static const iocshArg initArg3 = { "NDArrayPort",iocshArgString};
static const iocshArg initArg4 = { "NDArrayAddr",iocshArgInt};
static const iocshArg initArg5 = { "maxBuffers",iocshArgInt};
static const iocshArg initArg6 = { "maxMemory",iocshArgInt};
static const iocshArg initArg7 = { "priority",iocshArgInt};
static const iocshArg initArg8 = { "stackSize",iocshArgInt};
static const iocshArg initArg9 = { "maxThreads",iocshArgInt};
static const iocshArg * const initArgs[] = {&initArg0,
                &initArg1,
                &initArg2,
                &initArg3,
                &initArg4,
                &initArg5,
                &initArg6,
                &initArg7,
                &initArg8,
                &initArg9};


// Define the path to your plugin's extern configure function above
static const iocshFuncDef initFuncDef = {"ND{{ cookiecutter.plugin_name }}Configure",10,initArgs};


/* link the configure function with the passed args, and call it from the IOC shell */
static void initCallFunc(const iocshArgBuf *args){
    ND{{ cookiecutter.plugin_name }}Configure(args[0].sval, args[1].ival, args[2].ival,
            args[3].sval, args[4].ival, args[5].ival,
            args[6].ival, args[7].ival, args[8].ival, args[9].ival);
}


/* function to register the configure function in the IOC shell */
extern "C" void ND{{ cookiecutter.plugin_name }}Register(void){
    iocshRegister(&initFuncDef,initCallFunc);
}


/* Exports plugin registration */
extern "C" {
    epicsExportRegistrar(ND{{ cookiecutter.plugin_name }}Register);
}
