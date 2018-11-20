

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "readFile.h"

//*************************************************************************************************************************
int SearchSubString(char *configurationFileText, char *param) // this method search a value of the parameters according to the hot key
{
	int reference = strlen(configurationFileText); // keep a reference in the file
	while(configurationFileText != NULL)  // while there's information to read
	{
		char *textToRead = configurationFileText; // this is the entire text of the file
		char *wordReference = param;	// this is the word that represents a parameter
		if(strlen(textToRead) < strlen(wordReference)) {return -1;} // the word reference needs to be smaller than the full text
		while (*textToRead++ == *wordReference++) {			
			if(*wordReference == '\0' ) {				// this is the end of the text
				return reference - strlen(configurationFileText+1) ;
			}
		}
		wordReference = param;
		configurationFileText ++; // moving the reference to keep reading
	 }
}

//*************************************************************************************************************************

struct ParametersStruct getParameterFromFile(char * filedir, struct ParametersStruct params)// The function get into the corresponding file to
																	//search the information with the help of the function SearchSubString
{
	char *K = "K="; 	// number of cars to pass
	char *controlMode = "controlMode=";
	char *lenghtOfBridge = "lenghtOfBridge="; 	//size of the bridge	
	char *speedNormalCar = "speedNormalCar=";	// speed of a normal car (average)
	char *speedAmbulance = "speedAmbulance=";	//speed of an ambulance (average)
	char *speedRadioactive = "speedRadioactive=";	// average speed of a radiactive car
	char *semaphoreInGreenTime = "semaphoreInGreenTime=";	// time semaphore in green
	char *PercentOfAmbulance = "PercentOfAmbulance%=";	// percent of ambulances to be create
	char *PercentOfRadioactive = "PercentOfRadioactive%=";	// percent of radioactive cars to be create
	char *equal = "=";		// This is define to work as a delimiter
		
	params.K=0;
	params.controlMode=0;
	params.lenghtOfBridge=0;
	params.speedNormalCar=0;
	params.speedAmbulance=0;
	params.speedRadioactive=0;
	params.semaphoreInGreenTime=0;
	params.PercentOfAmbulance=0;
	params.PercentOfRadioactive=0;	
	FILE *ptr_file; // the file to be read
	char read[1000]; // have enough space to read the information
	ptr_file =fopen(filedir,"r"); //the path to read "r"
	int lenData=0;
	int lineLocation=0;
	while (fgets(read,1000, ptr_file)!=NULL) // while is reading information
	{		
		
		int kLine = SearchSubString(read, K); // finding the K in the configuration file
		if( kLine > -1) {		// it was found		
			lineLocation = SearchSubString(read, equal); // save the line Location		
			lenData=strlen(read)-lineLocation;	// reading the line to see the size of the data
			char Kbuff[lenData];	// create the char arrays
			memcpy( Kbuff, &read[lineLocation], lenData); // copy the information to Kbuff
			Kbuff[lenData] = '\0'; // end of the word
			params.K=atoi(Kbuff);	// it is assign to the parameters structure		
		}
		int lenghtOfTheBridgeLine = SearchSubString(read, lenghtOfBridge); // the turn of the lenght of the bridge
		if( lenghtOfTheBridgeLine > -1) {	// if gets into this block,  the lenght was found			
			lineLocation = SearchSubString(read, equal); // save the line Location		
			lenData=strlen(read)-lineLocation;	// reading the line to see the size of the data
			char lenghtbuff[lenData];
			memcpy( lenghtbuff, &read[lineLocation], lenData);
			lenghtbuff[lenData] = '\0';// end of the word
			params.lenghtOfBridge=atoi(lenghtbuff);			// it is assign to the parameters structure	
		}

		int speedCarLine = SearchSubString(read, speedNormalCar);
		if( speedCarLine > -1) {					
			lineLocation = SearchSubString(read, equal); // save the line Location		
			lenData=strlen(read)-lineLocation;	// reading the line to see the size of the data
			char carSpeedbuff[lenData];
			memcpy( carSpeedbuff, &read[lineLocation], lenData); // copy the information to 
			carSpeedbuff[lenData] = '\0';// end of the word
			printf(carSpeedbuff);
			params.speedNormalCar=atoi(carSpeedbuff);		// it is assign to the parameters structure	
		}

	
		int speedAmbulanceLine = SearchSubString(read, speedAmbulance);
		if( speedAmbulanceLine > -1) {				
			lineLocation = SearchSubString(read, equal); // save the line Location		
			lenData=strlen(read)-lineLocation;	// reading the line to see the size of the data	
			char ambulanceSpeedbuff[lenData];
			memcpy( ambulanceSpeedbuff, &read[lineLocation], lenData); // copy the information to 
			ambulanceSpeedbuff[lenData] = '\0';	// end of the word
			printf(ambulanceSpeedbuff);
			
			params.speedAmbulance=atoi(ambulanceSpeedbuff);		// it is assign to the parameters structure		
		}

		int speedRadioactiveLine = SearchSubString(read, speedRadioactive);
		if( speedRadioactiveLine > -1) {			
			lineLocation = SearchSubString(read, equal); // save the line Location		
			lenData=strlen(read)-lineLocation;	// reading the line to see the size of the data
			char speedRadioactivebuff[lenData];
			memcpy( speedRadioactivebuff, &read[lineLocation], lenData);// copy the information to 
			speedRadioactivebuff[lenData] = '\0';	// end of the word
			printf(speedRadioactivebuff);
			
			params.speedRadioactive=atoi(speedRadioactivebuff);		// it is assign to the parameters structure	
		}

		int semaphoreLine = SearchSubString(read, semaphoreInGreenTime);
		if( semaphoreLine > -1) {						
			lineLocation = SearchSubString(read, equal); // save the line Location		
			lenData=strlen(read)-lineLocation;	// reading the line to see the size of the data
			char semaphorebuff[lenData];
			memcpy( semaphorebuff, &read[lineLocation], lenData);// copy the information to 
			semaphorebuff[lenData] = '\0';// end of the word
			params.semaphoreInGreenTime=atoi(semaphorebuff);	// it is assign to the parameters structure		
		}

		int ambulancePercentageLine = SearchSubString(read, PercentOfAmbulance);
		if( ambulancePercentageLine > -1) {					
			lineLocation = SearchSubString(read, equal); // save the line Location		
			lenData=strlen(read)-lineLocation;	// reading the line to see the size of the data	
			char ambulancePercentbuff[lenData];
			memcpy( ambulancePercentbuff, &read[lineLocation], lenData);// copy the information to 
			ambulancePercentbuff[lenData] = '\0';// end of the word
			params.PercentOfAmbulance=(float) atoi(ambulancePercentbuff)/100;	// it is assign to the parameters structure		
		}

		int radioactivecarsPercentageLine = SearchSubString(read, PercentOfRadioactive);
		if( radioactivecarsPercentageLine > -1) {			
			lineLocation = SearchSubString(read, equal); // save the line Location		
			lenData=strlen(read)-lineLocation;	// reading the line to see the size of the data	
			char radioactivePercentbuff[lenData];
			memcpy( radioactivePercentbuff, &read[lineLocation], lenData);// copy the information to 
			radioactivePercentbuff[lenData] = '\0';// end of the word
			params.PercentOfRadioactive=(float) atoi(radioactivePercentbuff)/100;	// it is assign to the parameters structure		
		}
		

		int trafficLine = SearchSubString(read, controlMode);
		if( trafficLine > -1) {						
			lineLocation = SearchSubString(read, equal); // save the line Location		
			lenData=strlen(read)-lineLocation;	// reading the line to see the size of the data	
			char trafficbuff[lenData];
			memcpy( trafficbuff, &read[lineLocation], lenData);// copy the information to 
			trafficbuff[lenData] = '\0';		// end of the word	
			if(strncmp(trafficbuff,"SEMAPHORE",9)== 0) //using the semaphore mode to control the traffic
			{
				params.controlMode=SEMAPHORE;
			}
			if(strncmp(trafficbuff,"OFFICER",7)== 0) //using the officer mode to control the traffic
			{
				params.controlMode=OFFICER;
			}
			if(strncmp(trafficbuff,"JUNGLE",6)== 0)  //using the jungle mode to control the traffic (no control)
			{
				params.controlMode=JUNGLE;
			}			
		}	
	}
	fclose(ptr_file);
	return params;
}
//******************************************************************************************************************
void searchInfoConfig()
{
	leftBridge1=getParameterFromFile("ConfigurationFile/ConfigurationFileLeftBridge1.conf",leftBridge1);	
	rightBridge1=getParameterFromFile("ConfigurationFile/ConfigurationFileRightBridge1.conf",rightBridge1);
	leftBridge2=getParameterFromFile("ConfigurationFile/ConfigurationFileLeftBridge2.conf",leftBridge2);	
	rightBridge2=getParameterFromFile("ConfigurationFile/ConfigurationFileRightBridge2.conf",rightBridge2);
	leftBridge3=getParameterFromFile("ConfigurationFile/ConfigurationFileLeftBridge3.conf",leftBridge3);	
	rightBridge3=getParameterFromFile("ConfigurationFile/ConfigurationFileRightBridge3.conf",rightBridge3);
}

