#include "Car.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
//This method is going to create the structures of all the cars to be used
Car* createCar(TypeCar type, int SpeedOfCar, int bridgeID, QueueOfSides queueSide, int bridgePos){
	Car* carCreated = (Car*) malloc(sizeof (Car));
	if(carCreated == NULL){
		return NULL;
	}
	else{
		carCreated->type = type; // the type of the movementCar created
		carCreated->SpeedOfCar = SpeedOfCar; // the speed
		carCreated->bridgePos = bridgePos; // the position of the movementCar in the bridge
		carCreated->askContinue = 0; //if the movementCar can be moved the ask continue value is going to be 0, if is 1 the movementCar can be moved
		carCreated->bridgeID = bridgeID; // id of the bridge the movementCar is passing
		carCreated->queueSide = queueSide; // a reference to its queue
    	carCreated->continueOnRoad = 1;	// is in one queue or in a bridge
		return carCreated;
	}
}
//This method is going to handle everything about the movements of the cars
void *moveCarThread(void *moveCar){
 Car* movementCar = ((Car*)(moveCar));
 while(1){ 	
  if(movementCar->askContinue == 1){ //the car can move
  	if(movementCar->bridgePos<0) // is getting out of the bridge
  	{
  		movementCar->bridgePos=0;
  	}
  	else
  	{
  		movementCar->bridgePos--;    // the movement in the bridge to update the position
  	}
  } 
  mythread_sleep(100);
 }
}
