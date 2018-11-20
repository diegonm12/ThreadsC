#ifndef BRIDGECONTROLLER_H
#define	BRIDGECONTROLLER_H
#include <stdlib.h>
#include "Bridge.h"
#include "Car_Queue.h"
#include "Car.h"
#include <math.h> 
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "readFile.h" 
#include <time.h>
void setUpBridges(int usingArduino, int numberOfCars); // init the bridges
Direction traficOfficerController(Bridge* bridge); //give a direction this function is use by the officer method
void *functionControlOfficer(void *bridgeId); //to handle the method "OFFICER"
void addCarsToBridge(Bridge* mBridge, Direction direction); // add the cars to the list that represents the bridges
void *jungleLaw(void *carJungle); //to handle the method "Jungle"
void *startingCars(void *arg); // set up the cars
void addCarsToBridgeJungle(Bridge* bridge, Direction direction, Car * actualCar );
void runGUI();
void *functionControlSemaphore(void *bridgeId); //to handle the method "SEMAPHORE"
  Car_Queue* leftSideQueueBridge1;  // queues use to represent the cars waiting to get into the bridge
  Car_Queue* rightSideQueueBridge1;
  Car_Queue* leftSideQueueBridge2; 
  Car_Queue* rightSideQueueBridge2;
  Car_Queue* leftSideQueueBridge3; 
  Car_Queue* rightSideQueueBridge3;
  Bridge* bridge1; // a bridge
  Bridge* bridge2;
  Bridge* bridge3;
  mutext* lock;
  int waitTime;
  int greenLeftSemaphoreBridge1; // time in green for the semaphore depending of the configuration file
  int greenLeftSemaphoreBridge2;
  int greenLeftSemaphoreBridge3;
  int greenRightSemaphoreBridge1;
  int greenRightSemaphoreBridge2;
  int greenRightSemaphoreBridge3;
  int carsQuantity;
#endif	/* BRIDGECONTROLLER_H */
