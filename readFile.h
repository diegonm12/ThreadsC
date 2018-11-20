#ifndef readFile_H_   /* Include guard */
#define readFile_H_
#include "Bridge.h"

//************************************************************************************************************
struct ParametersStruct{ // structure that handles the information of the parameters of the bridge
    int K; // number of cars to pass
	BrigdeController controlMode; //****************************************+
	int lenghtOfBridge;	 //size of the bridge
	int speedNormalCar;		// speed of a normal car (average)
	int speedAmbulance;		//speed of an ambulance (average)
	int speedRadioactive;	// average speed of a radiactive car
	int semaphoreInGreenTime;	// time semaphore in green 
	float PercentOfAmbulance;	// percent of ambulances to be create
	float PercentOfRadioactive; // percent of radioactive cars to be create
} ;

struct ParametersStruct leftBridge1;
struct ParametersStruct rightBridge1;
struct ParametersStruct leftBridge2;
struct ParametersStruct rightBridge2;
struct ParametersStruct leftBridge3;
struct ParametersStruct rightBridge3;

int SearchSubString(char *configurationFileText, char *param);
struct ParametersStruct getParameterFromFile(char * filedir, struct ParametersStruct params); 
void searchInfoConfig();

//***************************************************************************************************************
#endif // readFile_H_

