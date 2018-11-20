#include "Thread.h"
#include "Car_Queue.h"
#include "Car.h"
#include <stdio.h>                                                              
#include <unistd.h>
#include "readFile.h" 
#include <math.h> 
#include "BridgeController.h"


void init(int usingGUI, int usingArduino,int numberOfCarsToCreateExpTime){
  searchInfoConfig(); 
  setUpBridges(usingArduino,numberOfCarsToCreateExpTime);
  mythread_init();  
  //initCarsOnBridge();
  int fillCars_thread=mythread_create(startingCars, REALTIME, 0,0, 50);
  //if(usingArduino == 1){
    // int arduino=mythread_create(updateBridgesArduino, REALTIME, 0,0, 49);
  //}
  /*if(usingGUI == 1){
    threadGUI=mythread_create(runGUI, REALTIME, 0,0, 1);

  }*/
  mythread_join(fillCars_thread);
  /*if(usingGUI == 1){
     mythread_join(threadGUI);
  }*/
 
}
//***********************************************************************************************************************************************
int main(int argc, char *argv[]) 
{
  int usingArduino = 0; // option to use (Arduino)
  int usingGUI = 0;     // the other option to use (GUI)
  int optionToRun = 0;
  int numberOfCarsToCreateExpTime = 0; // number of car to be created in exponential time
  if(argc == 3){
	  numberOfCarsToCreateExpTime = atoi(argv[1]); // number of cars to create in exponential time
	  optionToRun = atoi(argv[2]);	// Depending of this number the program will be use the GUI or the Arduinoto show whats happening 
	  if(optionToRun == 0){
		   usingArduino = 0; // the arduino is not going to be use
           usingGUI = 1;	 // the GUI is going to be use
		   init(usingGUI,usingArduino,numberOfCarsToCreateExpTime);
	  }
	  else if(optionToRun == 1){
		  usingArduino = 1;// the arduino is going to be use
          usingGUI = 0;	 // the GUI is not going to be use
		  init(usingGUI,usingArduino,numberOfCarsToCreateExpTime);
	  
	  }
	  else{
	  	printf("To select the option just input:\n");
		printf("0 --> To use the GUI\n");
		printf("1 --> To use the Arduino Board\n");  
	  }
  }
  else{
    printf("The information inputed is wrong!!\n");
	printf("Insert the number of cars to be create in exponential time in the execution of the program\n");  
	printf("And also insert:\n");
	printf("0 --> To use the GUI\n");
	printf("1 --> To use the Arduino Board\n");
    return 0;
  }
}
//***********************************************************************************************************************************************
