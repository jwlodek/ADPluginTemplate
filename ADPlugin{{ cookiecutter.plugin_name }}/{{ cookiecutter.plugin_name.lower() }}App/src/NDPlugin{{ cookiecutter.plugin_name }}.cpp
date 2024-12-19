/**
 * A basic template for implementing areaDetector plugins.
 * 
 * Author: {{ cookiecutter.author }}
 * Created on: {% now 'local', '%m/%d/%Y' %}
 * 
 */

// Standard library headers
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <stdio.h>


// EPICS/AreaDetector headers
#include <epicsMutex.h>
#include <epicsString.h>
#include <iocsh.h>
#include "NDArray.h"
#include <epicsExport.h>

// Plugin header
#include "NDPlugin{{ cookiecutter.plugin_name }}.hpp"


// Error message formatters
#define ERR(msg)                                                                                 \
    asynPrint(pasynUserSelf, ASYN_TRACE_ERROR, "ERROR | %s::%s: %s\n", pluginName, functionName, \
              msg)

#define ERR_ARGS(fmt, ...)                                                              \
    asynPrint(pasynUserSelf, ASYN_TRACE_ERROR, "ERROR | %s::%s: " fmt "\n", pluginName, \
              functionName, __VA_ARGS__);

// Warning message formatters
#define WARN(msg) \
    asynPrint(pasynUserSelf, ASYN_TRACE_ERROR, "WARN | %s::%s: %s\n", pluginName, functionName, msg)

#define WARN_ARGS(fmt, ...)                                                            \
    asynPrint(pasynUserSelf, ASYN_TRACE_ERROR, "WARN | %s::%s: " fmt "\n", pluginName, \
              functionName, __VA_ARGS__);

// Log message formatters (set to use ERROR level by default they are printed w/ default trace settings.)
#define LOG(msg) \
    asynPrint(pasynUserSelf, ASYN_TRACE_ERROR, "%s::%s: %s\n", pluginName, functionName, msg)

#define LOG_ARGS(fmt, ...)                                                                       \
    asynPrint(pasynUserSelf, ASYN_TRACE_ERROR, "%s::%s: " fmt "\n", pluginName, functionName, \
              __VA_ARGS__);


// Include your external dependency library headers


// Namespaces
using namespace std;


// Name of the plugin
static const char *pluginName="NDPlugin{{ cookiecutter.plugin_name }}";


/**
 * Override of NDPluginDriver function. Must be implemented by your plugin
 *
 * Performs callback when write operation is performed on an asynInt32 record
 * 
 * @params[in]: pasynUser   -> pointer to asyn User that initiated the transaction
 * @params[in]: value       -> value PV was set to
 * @return: success if PV was updated correctly, otherwise error
 */
asynStatus NDPlugin{{ cookiecutter.plugin_name }}::writeInt32(asynUser* pasynUser, epicsInt32 value){
    const char* functionName = "writeInt32";
    int function = pasynUser->reason;
    asynStatus status = asynSuccess;

    LOG_ARGS("function = %d value=%d", function, value);

    // TODO: Handle callbacks for any integer PV writes as needed here

    status = setIntegerParam(function, value);

    if(function < ND_{{ cookiecutter.plugin_name.upper() }}_FIRST_PARAM){
        status = NDPluginDriver::writeInt32(pasynUser, value);
    }

    callParamCallbacks();

    if(status){
        ERR_ARGS("Failed to write int32 val to parameter: function = %d value=%d", function, value);
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

    // If set to true, downstream plugins will perform callbacks on output pScratch
    // If false, no downstream callbacks will be performed
    bool performCallbacks = true;

    //call base class and get information about frame
    NDPluginDriver::beginProcessCallbacks(pArray);

    pArray->getInfo(&arrayInfo);

    LOG_ARGS("Processing frame w/ ID %d", pArray->uniqueId);

    //unlock the mutex for the processing portion
    this->unlock();

    // This sets the output of the plugin to the input array
    pScratch = pArray;

    // If we are manipulating the image/output, we allocate a new scratch frame
    // You will need to specify dimensions, and data type.

    //pScratch = pNDArrayPool->alloc(ndims, dims, dataType, 0, NULL);
    //if(pScratch == NULL){
    //    ERR("Unable to allocate frame.")
    //    return;
    //}
    

    // Process the image here. pArray is read only, and if any image manipulation is required
    // a copy should be made into pScratch.
    // 
    // Note that this expects any external libraries to be thread safe. If they aren't, move
    // the processing to after this->lock();
    //
    // Access data with pArray->pData.
    // DO NOT CALL pArray.release()

    this->lock();

    // If pScratch was allocated, set the color mode, unique ID, and timestamp here.

    //pScratch->pAttributeList->add("ColorMode", "Color Mode", NDAttrInt32, &colorMode);
    //pScratch->uniqueId = pArray->uniqueId;
    //pScratch->epicsTS = pArray->epicsTS;

    if(status == asynError){
        ERR("Image not processed correctly!");
        return;
    }

    NDPluginDriver::endProcessCallbacks(pScratch, false, performCallbacks);

    // If pScratch was allocated in this function, make sure to release it.
    // pScratch.release()

    callParamCallbacks();
}



//constructror from base class, replace with your plugin name
NDPlugin{{ cookiecutter.plugin_name }}::NDPlugin{{ cookiecutter.plugin_name }}(
        const char *portName, int queueSize, int blockingCallbacks,
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
    const char* functionName = "NDPlugin{{ cookiecutter.plugin_name }}";

    char versionString[25];

    // Initialize Parameters here, using the string vals and indexes from the header. Ex:
    // For asynOctet records (stringin, stringout, waveform)
    // createParam(NDPlugin{{ cookiecutter.plugin_name }}OctetString,   asynParamOctet,   &NDPlugin{{ cookiecutter.plugin_name }}Octet);
    // For asynInt32 records (bo, bi, mbbo, mbbi, ao, ai)
    // createParam(NDPlugin{{ cookiecutter.plugin_name }}IntegerString, asynParamInt32,   &NDPlugin{{ cookiecutter.plugin_name }}Integer);
    // For asynFloat64 records (ao, ai, waveform)
    // createParam(NDPlugin{{ cookiecutter.plugin_name }}FloatString,   asynParamFloat64, &NDPlugin{{ cookiecutter.plugin_name }}Float);


    // Update plugin version number parameter
    setStringParam(NDPluginDriverPluginType, "NDPlugin{{ cookiecutter.plugin_name }}");
    epicsSnprintf(versionString, sizeof(versionString), "%d.%d.%d", 
                  {{ cookiecutter.plugin_name.upper() }}_VERSION, 
                  {{ cookiecutter.plugin_name.upper() }}_REVISION, 
                  {{ cookiecutter.plugin_name.upper() }}_MODIFICATION);
    setStringParam(NDDriverVersion, versionString);

    connectToArrayPort();

    LOG_ARGS("Initialization complete. Version: %s", versionString);
}



/**
 * External configure function. This will be called from the IOC shell of the
 * detector the plugin is attached to, and will create an instance of the plugin and start it
 * 
 * @params[in]	-> all passed to constructor
 */
extern "C" int ND{{ cookiecutter.plugin_name }}Configure(
        const char *portName, int queueSize, int blockingCallbacks,
        const char *NDArrayPort, int NDArrayAddr,
        int maxBuffers, size_t maxMemory,
        int priority, int stackSize, int maxThreads){

    // Initialize instance of our plugin and start it.
    NDPlugin{{ cookiecutter.plugin_name }} *pPlugin = new NDPlugin{{ cookiecutter.plugin_name }}(portName, queueSize, blockingCallbacks, NDArrayPort, NDArrayAddr, maxBuffers, maxMemory, priority, stackSize, maxThreads);
    return pPlugin->start();
}


/* IOC shell arguments passed to the plugin configure function */
static const iocshArg initArg0 = { "portName", iocshArgString };
static const iocshArg initArg1 = { "frame queue size", iocshArgInt };
static const iocshArg initArg2 = { "blocking callbacks", iocshArgInt };
static const iocshArg initArg3 = { "NDArrayPort", iocshArgString };
static const iocshArg initArg4 = { "NDArrayAddr", iocshArgInt };
static const iocshArg initArg5 = { "maxBuffers", iocshArgInt };
static const iocshArg initArg6 = { "maxMemory", iocshArgInt };
static const iocshArg initArg7 = { "priority", iocshArgInt };
static const iocshArg initArg8 = { "stackSize", iocshArgInt };
static const iocshArg initArg9 = { "maxThreads", iocshArgInt };
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
static const iocshFuncDef initFuncDef = { "ND{{ cookiecutter.plugin_name }}Configure", 10, initArgs };


/* link the configure function with the passed args, and call it from the IOC shell */
static void initCallFunc(const iocshArgBuf *args){
    ND{{ cookiecutter.plugin_name }}Configure(
            args[0].sval, args[1].ival, args[2].ival,
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
