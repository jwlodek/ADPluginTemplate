/**
 * Template header file fo NDPlugins
 * 
 * Replace all instances of ___ with your plugin name in the form 'Bar'
 * 
 * Replace all instances of PLUGINNAME with the name of your plugin in the format 'BAR'
 * 
 * Author: 
 * Created on: 
 * 
 */

#ifndef NDPluginPLUGINNAMESTANDARDH
#define NDPluginPLUGINNAMESTANDARDH

//Define necessary includes here

using namespace std;

//include base plugin driver
#include "NDPluginDriver.h"

//version numbers
#define PLUGINNAMEUPPER_VERSION      	0
#define PLUGINNAMEUPPER_REVISION     	0
#define PLUGINNAMEUPPER_MODIFICATION 	0



// Define the PVStrings for all of your PV values here in the following format
//#define NDPluginPLUGINNAMESTANDARDPVNameString 	"PV_STRING" 		//asynOctet


// define all necessary structs and enums here


/* class that does barcode readings */
class NDPluginPLUGINNAMESTANDARD : public NDPluginDriver {
	public:
		NDPluginPLUGINNAMESTANDARD(const char *portName, int queueSize, int blockingCallbacks,
			const char* NDArrayPort, int NDArrayAddr, int maxBuffers,
			size_t maxMemory, int priority, int stackSize);

		//~NDPlugin___();

		void processCallbacks(NDArray *pArray);

		virtual asynStatus writeInt32(asynUser* pasynUser, epicsInt32 value);

	protected:

		//in this section i define the coords of database vals

		//Place PV indexes here, define first and last as appropriate, replace PLUGINNAME with name, 
		#define ND_PLUGINNAMEUPPER_FIRST_PARAM	FIRSTPVINDEX
		#define ND_PLUGINNAMEUPPER_LAST_PARAM LASTPVINDEX

	private:

        // init all global variables here

        // init all plugin additional functions here

};

// Replace PLUGINNAME with plugin name ex. BAR
#define NUM_PLUGINNAMEUPPER_PARAMS ((int)(&ND_PLUGINNAMEUPPER_LAST_PARAM - &ND_PLUGINNAMEUPPER_FIRST_PARAM + 1))

#endif