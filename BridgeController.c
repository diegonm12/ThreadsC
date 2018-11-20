#include "BridgeController.h"
// This function is the responsable for the creation of the queues, where the cars are going to be 
// waiting to get into the bridge and also the function build the bridges for the usage of the cars
// also create the sides of the bridge according to the information from the configuration file
//********************************************************************************************************************
void setUpBridges(int usingArduino, int numberOfCars){
   if(usingArduino == 1){
     waitTime=1;
   }
   else{
     waitTime=100;
   }
    carsQuantity = numberOfCars; // this is the quantity if cars to be created in the execution time of the program
	// The next 6 lines handle the creation of the queues, where all the cars are going to be waiting for get into the bridge
    leftSideQueueBridge1 = createQueue();
    leftSideQueueBridge2 = createQueue();
    leftSideQueueBridge3 = createQueue();
    rightSideQueueBridge1 = createQueue();
    rightSideQueueBridge2 = createQueue();
    rightSideQueueBridge3 = createQueue();
	// Here the sides of the bridge are going to be set
    BridgeSide* leftSide1 = buildBridgeSide(leftBridge1.lenghtOfBridge, leftBridge1.speedNormalCar,leftBridge1.semaphoreInGreenTime , leftBridge1.K ,leftBridge1.PercentOfAmbulance,leftBridge1.PercentOfRadioactive,leftSideQueueBridge1);
    BridgeSide* leftSide2 = buildBridgeSide(leftBridge2.lenghtOfBridge, leftBridge2.speedNormalCar,leftBridge2.semaphoreInGreenTime , leftBridge2.K ,leftBridge2.PercentOfAmbulance,leftBridge2.PercentOfRadioactive,leftSideQueueBridge2);
    BridgeSide* leftSide3 = buildBridgeSide(leftBridge3.lenghtOfBridge, leftBridge3.speedNormalCar,leftBridge3.semaphoreInGreenTime , leftBridge3.K ,leftBridge3.PercentOfAmbulance,leftBridge3.PercentOfRadioactive,leftSideQueueBridge3);
    BridgeSide* rightSide1 = buildBridgeSide(rightBridge1.lenghtOfBridge, rightBridge1.speedNormalCar,rightBridge1.semaphoreInGreenTime , rightBridge1.K ,rightBridge1.PercentOfAmbulance,rightBridge1.PercentOfRadioactive,rightSideQueueBridge1);
    BridgeSide* rightSide2 = buildBridgeSide(rightBridge2.lenghtOfBridge, rightBridge2.speedNormalCar,rightBridge2.semaphoreInGreenTime , rightBridge2.K ,rightBridge2.PercentOfAmbulance,rightBridge2.PercentOfRadioactive,rightSideQueueBridge2);
    BridgeSide* rightSide3 = buildBridgeSide(rightBridge3.lenghtOfBridge, rightBridge3.speedNormalCar,rightBridge3.semaphoreInGreenTime , rightBridge3.K ,rightBridge3.PercentOfAmbulance,rightBridge3.PercentOfRadioactive,rightSideQueueBridge3);
    // Now that it is ready the sides of the bridge we can build the bridges to be used.
    bridge1 = buildBridge(leftSide1,rightSide1,leftBridge1.controlMode);
    bridge2 = buildBridge(leftSide2,rightSide2,leftBridge2.controlMode);
    bridge3 = buildBridge(leftSide3,rightSide3,leftBridge3.controlMode);
    lock = mymutex_init();
}
//**********************************************************************************************************

void runGUI(){
	int a = system("python3 -m GUI");
}
void *startingCars(void *arg) {   //this method puts the cars in the queues of the bridges
      
    int B1 = 1;	// represents the first bridge
    int B2 = 2; // represents the second bridge
    int B3 = 3; // represents the third bridge
	// The next if are going to look for the control mode of the sides of the bridges
	//According to the information in the file of configuration for the bridges
    if(leftBridge1.controlMode==OFFICER) 
    {
      int controller_thread1 = mythread_create(functionControlOfficer,REALTIME,0,B1,50); //*******************************************
    }
    if(leftBridge2.controlMode==OFFICER)
    {
      int controller_thread2 = mythread_create(functionControlOfficer,REALTIME,0,B2,50);
    }
    if(leftBridge3.controlMode==OFFICER)
    {
      int controller_thread3 = mythread_create(functionControlOfficer,REALTIME,0,B3,50);
    }
//**********************************************************************************************************   
    if(leftBridge1.controlMode==SEMAPHORE)
    {
      int controller_thread1 = mythread_create(functionControlSemaphore,REALTIME,0,B1,50);
    }
    if(leftBridge2.controlMode==SEMAPHORE)
    {
      int controller_thread2 = mythread_create(functionControlSemaphore,REALTIME,0,B2,50);
    }
    if(leftBridge3.controlMode==SEMAPHORE)
    {
      int controller_thread3 = mythread_create(functionControlSemaphore,REALTIME,0,B3,50);
    }  
	int i = 0; 
    while(++i){  // this part of the code creates the queues of the bridges depending on the media
      int media = 3 * exp(i); // media handles the creation of the queues
      printf("****QUEUE ADDED (CAR WAITING)****\n");  
      leftSideQueueBridge1 = creatingQueueOfCarsJungle(leftSideQueueBridge1,leftBridge1.PercentOfAmbulance,leftBridge1.PercentOfRadioactive,leftBridge1.speedNormalCar,leftBridge1.speedAmbulance,leftBridge1.speedRadioactive, carsQuantity,1, LEFTQUEUE,leftBridge1.lenghtOfBridge);
	  rightSideQueueBridge3 = creatingQueueOfCarsJungle(rightSideQueueBridge3,rightBridge3.PercentOfAmbulance,rightBridge3.PercentOfRadioactive,rightBridge3.speedNormalCar,rightBridge3.speedAmbulance,rightBridge3.speedRadioactive,carsQuantity, 3, RIGHTQUEUE,rightBridge3.lenghtOfBridge);
	  //rightSideQueueBridge2 = creatingQueueOfCarsJungle(rightSideQueueBridge2,rightBridge2.PercentOfAmbulance,rightBridge2.PercentOfRadioactive,rightBridge2.speedNormalCar,rightBridge2.speedAmbulance,rightBridge2.speedRadioactive,carsQuantity, 2, RIGHTQUEUE,rightBridge2.lenghtOfBridge);
	  
		//************************METER MASS!!!!!*************************************************************
      printf("****The next round of queues to add is in %d seconds****\n",media );  
      
      mythread_sleep(media*1000); // wait media seconds to create new queue that want to get in into the bridge         
    }                                                   
} 

// The method is use when the user want to control the bridge with the officer
void *functionControlOfficer(void *bridgeId)
{	
  int IDbridge = ((int)(bridgeId)); // gets the information  of the ID bridge 
  int actualK = 0;	//initialize the number of cars
  int currentRadioactiveCars = 0; // initialize the number
  Bridge *bridge;
  if(IDbridge == 1)
  {       
      bridge = bridge1; // chance the references according to the bridge to use this method in this case the bridge 1
  }
  else if(IDbridge == 2)
  {       
      bridge = bridge2; // bridge 2 is going to use this method
  }
  else if(IDbridge == 3)
  {
      bridge = bridge3; // bridge 3 is going to use this method
  }   
   Car_list* carsOnBridgeList = bridge->carsOnBridge;    
   int actualKCars = -1;
   printList(carsOnBridgeList,IDbridge);
   int it = 0;
   while(1)
   {
        int carsOnBridge =  carsOnBridgeList->count;
        int allowCars=0; //initialization of the allow cars to pass
        if(bridge->direction == RIGHT){
          actualKCars = (bridge->leftSide)->KCars; // if the dir is right the cars that can pass throught the bridge is update
        }
        else if(bridge->direction == LEFT){
          actualKCars = (bridge->rightSide)->KCars; // if the dir is left the cars that can pass throught the bridge is update
        }
        if((bridge->rightSide)!= NULL && (bridge->leftSide)!= NULL) // the bridge has cars waiting for get into it
        {
            Car_Queue* carsWaitingLeft = (bridge->leftSide)->queueCarsSide; // the cars waiting are assign to a queue to pass the bridge
            Car_Queue* carsWaitingRight =  (bridge->rightSide)->queueCarsSide;        
            int radioactiveLeftCount = carsWaitingLeft->radioActiveCount; // how many radioactive cars a side has
            int radioactiveRightCount = carsWaitingRight->radioActiveCount; // how many radioactive cars a side has
			printf("\n");
			printf("\n");
            printf("****************************************************************************************************************************************\n");	
            printf("*********Iteration #: %d, Control Method is Officer, Bridge ID: %d*********\n",it,IDbridge);
            if(bridge->direction==LEFT)
            {
              allowCars=(bridge->rightSide->lengthBridgeSide)/2; // how many cars can the bridge handle according to the lenght
              printf("Officer moves the traffic to the LEFT\n");
            }
            else if(bridge->direction==RIGHT)
            {
              allowCars=(bridge->leftSide->lengthBridgeSide)/2;	// how many cars can the bridge handle according to the lenght
              printf("Officer moves the traffic to the RIGHT\n");
            }
            else
            {
              if((bridge->rightSide->lengthBridgeSide)>(bridge->leftSide->lengthBridgeSide))
              {
                allowCars=(bridge->rightSide->lengthBridgeSide)/2; // how many cars can the bridge handle according to the lenght
              }
              else
              {
                allowCars=(bridge->leftSide->lengthBridgeSide)/2; // how many cars can the bridge handle according to the lenght
              }              
              printf("Direction: No direction\n");
            }

           
            if(carsOnBridge < allowCars) // while the amount of cars in the bridge is OK
            {
                if(currentRadioactiveCars != 0){
                  addCarsToBridge(bridge,bridge->direction); // if the is a radioactive car the access to the bridge is immediately
                  currentRadioactiveCars--; // less radioactive cars
                }
                else if(radioactiveLeftCount > 0 || radioactiveRightCount > 0){ // we have radioactive cars
                    if(radioactiveLeftCount > 0){ // in this case the radioactive car is in the left
                        if(carsOnBridgeList->count == 0){ // if the bridge is empty
                           currentRadioactiveCars = radioactiveLeftCount; // the amount of current radioactive cars is equal to the amount of the
                           bridge->direction = RIGHT;						//radioactive cars in the left and change the direction of the bridge
                        }
                        else
                        {
                          if(verifyRadioActiveonList(carsOnBridgeList,LEFTQUEUE)) //This method is going verify if there is a radioactive car on the list
                          {
                            currentRadioactiveCars = radioactiveLeftCount; // assign the number of radioactive cars
                            bridge->direction = RIGHT;	// the direction
                          }

                        }                        
                    }
                    else if(radioactiveRightCount > 0){ // in this case the radioactive is gping to be in the right
                        if(carsOnBridgeList->count == 0){	// of there is no car in the bridge
                           currentRadioactiveCars = radioactiveRightCount; // assign the number of radioactive cars
                           bridge->direction = LEFT;
                        }
                        else
                        {
                          if(verifyRadioActiveonList(carsOnBridgeList,RIGHTQUEUE))//This method is going verify if there is a radioactive car on the list
                          {
                            currentRadioactiveCars = radioactiveRightCount;// assign the number of radioactive cars
                            bridge->direction = LEFT;
                          }
                        } 
                    }
                } // end of the block that handle when there is a radioactive car
                else 
                {
                  if(actualK == actualKCars) // if the actualK == actualKCars, parameter to control the flow of cars 
                  {
                      if(carsOnBridgeList->count==0) // if all the cars have passed
                      {
                        actualK=0; // the new K is going to be 0
                      }
                  }
                  else if(bridge->direction == NODIRECTION || carsOnBridge == 0){ // in the case there are no cars in the bridge
                        Direction changeDirection = traficOfficerController(bridge); // the dir is going to be changed
                        addCarsToBridge(bridge,changeDirection);
                        actualK++; // the number of cars that can pass increase
                    }
                  else{
                        addCarsToBridge(bridge,bridge->direction); // the cars passing the bridge
                        actualK++;
                    }
                }
          }
        }
        StatePrinter(); 
        if(carsOnBridgeList)
        {
          moveCarsOnBridge(carsOnBridgeList); // the cars in the bridge continue moving
          int posBridge = queueUpdating(carsOnBridgeList,IDbridge,bridge->direction); // update the position of the car in the bridge
          Car_list_remove(carsOnBridgeList,posBridge); //remove a car from the list
        }

        it++;
        
        mythread_sleep(waitTime);

    }
} 
// method use to change the direction
Direction traficOfficerController(Bridge* bridge){
    Direction dir = bridge->direction; // get the dir
    if(dir == NODIRECTION){ // no direction
      bridge->direction = LEFT; //change it
      return LEFT;
    }
    else if(dir == LEFT){ // left dir
      bridge->direction = RIGHT; // change it
      return RIGHT;
    }
    else if(dir == RIGHT){ // right dir
       bridge->direction = LEFT; // change it
       return LEFT;
    }
   
}
//Function takes care of adding cars to the list of cars that are crossing the bridge at that time
void addCarsToBridge(Bridge* bridge, Direction direction ){
    Car_list* carsOnBridge = (Car_list*) malloc(sizeof (Car_list)); // reserves the memory to push elements in the list 
    Car_Queue* carsWaiting = (Car_Queue*) malloc(sizeof (Car_Queue)); // reserves memory to the list of cars waiting
    if(direction == RIGHT){
      carsOnBridge = bridge->carsOnBridge; // get the current elements in the list
      carsWaiting = (bridge->leftSide)->queueCarsSide;// get the current elements in the list, these are the cars waiting because the direction is the other
    }
    else if(direction == LEFT){
      carsOnBridge = bridge->carsOnBridge; // get the current elements in the list
      carsWaiting = (bridge->rightSide)->queueCarsSide;// get the current elements in the list, these are the cars waiting because the direction is the other       
    }
    else if(direction == NODIRECTION){ // no car can get into the bridge
      return;
    }      
    if(carsWaiting->count >0){ // there are cars waiting to get into the bridge
      Car* actualCar = DequeueCar(carsWaiting);  // gets out of the list of waiting   
      actualCar->askContinue = 1; // now the car can move in the bridge
      Car_list_add(carsOnBridge,actualCar);	// the car is push in the list of the cars on the bridge
    }
}
//This method add cars to the bridge when the bridge execute the jungle law
void addCarsToBridgeJungle(Bridge* bridge, Direction direction, Car * actualCar ){
  Car_list* carsOnBridge = (Car_list*) malloc(sizeof (Car_list)); // reserves the memory to push elements in the list 
    Car_Queue* carsWaiting = (Car_Queue*) malloc(sizeof (Car_Queue)); // reserves memory to the list of cars waiting
    if(direction == RIGHT){
      carsOnBridge = bridge->carsOnBridge; // get the current elements in the list
      carsWaiting = (bridge->leftSide)->queueCarsSide;// get the current elements in the list, these are the cars waiting because the direction is the other
    }
    else if(direction == LEFT){
      carsOnBridge = bridge->carsOnBridge; // get the current elements in the list
      carsWaiting = (bridge->rightSide)->queueCarsSide;// get the current elements in the list, these are the cars waiting because the direction is the other       
    }
    else if(direction == NODIRECTION){
      return;
    } 
 if(carsWaiting->count > 0){  
    actualCar->askContinue = 1;    
   Car_list_add(carsOnBridge,actualCar);
   carJungleRemove(carsWaiting, actualCar->carID);

  }
}
//this manage the movements between the bridges if a car is in the 1st dridge and it has the right direction the car is going to be moved
//to second bridge

// This method implement the function to handle the control with the jungle law method.
void *jungleLaw(void *carJungle){
  Car* newCar = ((Car*)(carJungle)); // new car is created
  int it=0; // iterator
  while(newCar->continueOnRoad) // the new car is in some queue or in some bridge
  {      
    int IDbridge = newCar->bridgeID; // assign the bridge id
    Bridge *bridge; // new bridge object
    if(IDbridge == 1){    // dependinf of the bridge  
      bridge = bridge1;
    }
    else if(IDbridge == 2){       
        bridge = bridge2;
    }
    else if(IDbridge == 3){
        bridge = bridge3;        
    }
    if(bridge->controller==JUNGLE) // verify if it is a bridge with a jungle law control method
    {
      mymutex_lock(lock);
	   printf("\n");
	   printf("\n");
       printf("****************************************************************************************************************************************\n");	
      printf("*********Iteration #: %d, Control Method is Jungle Law, Bridge ID: %d*********\n",it,IDbridge);          
      printf("asking to continue: %d, Car ID: %d\n",newCar->askContinue,newCar->carID);
      Car_list* carsOnBridgeList = bridge->carsOnBridge;  // update the cars in the bridge
      if(newCar->askContinue == 1) // moving the car checking if the car can keep moving
      {
        if(newCar->bridgePos<=0) // the car pass the bridge
        {
          newCar->bridgePos=0; // change the pos
        }
        else
        {
          newCar->bridgePos--; // passing the bridge
        }
        if(carsOnBridgeList) // is in the bridge
        {          
          int posBridge = queueUpdating(carsOnBridgeList,IDbridge,bridge->direction);
          Car_list_remove(carsOnBridgeList,posBridge);
        } 
      }
      else
      {
          int allowCars=0;   // cars allow to pass       
          int carsOnBridge =  carsOnBridgeList->count;   // how many cars in the bridge          
          if((bridge->rightSide)!= NULL && (bridge->leftSide)!= NULL ) // there are cars waiting to pass
          {
            Car_Queue* carsWaitingLeft = (bridge->leftSide)->queueCarsSide; // cars waiting in the left
            Car_Queue* carsWaitingRight = (bridge->rightSide)->queueCarsSide;   // cars waiting in the right          
            if(bridge->direction==LEFT)
            {
              allowCars=(bridge->rightSide->lengthBridgeSide)/2; // calculate the quantity of cars to pass
              printf("Officer moves the traffic to the LEFT\n");
            }
            else if(bridge->direction==RIGHT)
              {
                allowCars=(bridge->leftSide->lengthBridgeSide)/2; // calculate the quantity of cars to pass
                printf("Officer moves the traffic to the RIGHT\n");
              }
            else
                {
                  if((bridge->rightSide->lengthBridgeSide)>(bridge->leftSide->lengthBridgeSide)) // in the case there more car in one side
                  {
                    allowCars=(bridge->rightSide->lengthBridgeSide)/2; // pass the cars with  the more lenght
                  }
                  else
                  {
                    allowCars=(bridge->leftSide->lengthBridgeSide)/2; // the other hand
                  }              
                  printf("Direction: No direction\n");
                }
             if(carsOnBridge < allowCars) // when the cars in the brigde are less than the cars allow
                {
                      if(carsOnBridge == 0){ // this happens if there is no cars in the bridge 
						  if(newCar->queueSide == LEFTQUEUE){ // no cars in the left so
                        	bridge->direction = RIGHT; // the cars in the right can pass
                        	addCarsToBridgeJungle(bridge, bridge->direction, newCar); // push to the cars to the bridge
						  }
                          else{
                        	bridge->direction = LEFT; 	// in the other hand
                        	addCarsToBridgeJungle(bridge, bridge->direction, newCar);
						  }
                      }
                      else if(bridge->direction == LEFT){ // the other case
                      	if(newCar->queueSide == RIGHTQUEUE){
                      		addCarsToBridgeJungle(bridge, bridge->direction, newCar); // the same thing above
                      	}
                      }
                      else if(bridge->direction = RIGHT){// the same thing above
                      	if(newCar->queueSide == LEFTQUEUE){
                      		addCarsToBridgeJungle(bridge, bridge->direction, newCar);                  		
                      	}
                      }
                }
            }
          }
          StatePrinter();       // prints everything 
          it++;
          mymutex_unlock(lock);  
          mythread_sleep(waitTime); // sleep the thread
      }
    }
}

int queueUpdating(Car_list* Car_list, int IDbridge,Direction direction ) {
   carNode* firstCarInList = Car_list->firstCar; // get the first car in the list
   int valueToReturn; // the value to be returned
    while (firstCarInList != NULL) { // so there is a car in the list
        if ((firstCarInList->data)->bridgePos <= 0) {  
          if(IDbridge==1)
          {            
            if(direction==RIGHT) // if the dir is to right
            {
              firstCarInList->data->bridgeID=2; // goes to the next bridge the second one
              EnqueueCar(leftSideQueueBridge2,firstCarInList->data); // queue
              valueToReturn= leftBridge2.lenghtOfBridge; // change the lenght of the side
            }           
            if(direction==LEFT)
            {
              printf("Killing the car with the ID:",firstCarInList->data->carID); // if it is moving to the left at the end of the 1st bridge is           
              valueToReturn=0;																// going to die
            }
          }
          else if(IDbridge==2)
          {            
            if(direction==RIGHT) // a car moving to the right in the second bridge
            {        
              firstCarInList->data->bridgeID=3;  // if was the dir to the right so the car get into the 3th bridge    
              EnqueueCar(leftSideQueueBridge3,firstCarInList->data); // queue
              valueToReturn= leftBridge3.lenghtOfBridge; // chang
            }
            else if(direction==LEFT) // a car moving to the left in the second bridge
            {      
              firstCarInList->data->bridgeID=1;        // so the car pass to the 1st 
              EnqueueCar(rightSideQueueBridge1,firstCarInList->data);  // queue
              valueToReturn= rightBridge1.lenghtOfBridge; // update change
            }
          }
          else if(IDbridge==3)
          {
            if(direction==LEFT) // a car moving to the left in the 3th bridge
            {   
              firstCarInList->data->bridgeID=2;          	// change to the second bridge 
              EnqueueCar(rightSideQueueBridge2,firstCarInList->data); // queue
              valueToReturn= rightBridge2.lenghtOfBridge; // update
            }
            if(direction==RIGHT)
            {              
			  printf("Killing the car with the ID:%d \n",firstCarInList->data->carID); // the car is gone
              firstCarInList->data->continueOnRoad=0;
              valueToReturn=0;         
            }
          }
        }
        firstCarInList = firstCarInList->next;
    }
    return valueToReturn;   
}
// this function prints the state of the execution
void StatePrinter()
{
  printf("\n");	
  printf("\n");
  printf("\n");	
  printf("************************************************\n");	
  printf("****BRIDGE 1****\n");
  printf("QUEUE IN THE LEFT SIDE OF THE BRIDGE 1:\n");
  printQueue(leftSideQueueBridge1,1); 
  printf("\n"); 
  printf("QUEUE IN THE RIGHT SIDE OF THE BRIDGE 1:\n");   
  printQueue(rightSideQueueBridge1,2);
  printf("\n");
  printf("CAR DRIVING IN THE BRIDGE 1:\n");
  printList(bridge1->carsOnBridge,1);
  printf("\n");
  printf("\n");
  printf("\n");	
  printf("************************************************\n");
  printf("****BRIGDE 2****\n");
  printf("QUEUE IN THE LEFT SIDE OF THE BRIDGE 2:\n");
  printQueue(leftSideQueueBridge2,3);
  printf("\n");
  printf("QUEUE IN THE RIGHT SIDE OF THE BRIDGE 2:\n");   
  printQueue(rightSideQueueBridge2,4); 
  printf("\n");
  printf("CARS DRIVING IN THE BRIDGE 2:\n");
  printList(bridge2->carsOnBridge,2);
  printf("\n");
  printf("\n");	
  printf("\n");	
  printf("*************************************************\n");
  printf("****BRIDGE 3****\n");
  printf("QUEUE IN THE LEFT SIDE OF THE BRIDGE 3:\n");
  printQueue(leftSideQueueBridge3,5);
  printf("\n");
  printf("QUEUE IN THE RIGHT SIDE OF THE BRIDGE 3:\n");   
  printQueue(rightSideQueueBridge3,6); 
  printf("\n");
  printf("CARS DRIVING IN THE BRIDGE 3:\n");
  printList(bridge3->carsOnBridge,3);

}
//Function that handles the semaphoreInGreenTime control 
void *functionControlSemaphore(void *bridgeId)
{ 
    int IDbridge = ((int)(bridgeId)); // assign the id of the bridge
    Bridge *bridge; // new bridge to use
    if(IDbridge == 1){ // cases depending of the bridge
        bridge = bridge1;
    }
    else if(IDbridge == 2){
        bridge = bridge2;
    }
    else if(IDbridge == 3){
        bridge = bridge3;
    }
    Car_list* carsOnBridgeList = bridge->carsOnBridge; // create a list and update with the current information
    int time_spent = 0; // time of the semaphore
    int currentTimeLimit = 0; // current time limit
    int currentRadioactiveCars = 0; // number of radioactive cars
    int it=0; // iterator
    while(1){
        int carsOnBridge =  carsOnBridgeList->count; // how many cars in the bridge at some moment
         int allowCars=0; // initialize variable
        if((bridge->rightSide)!= NULL && (bridge->leftSide)!= NULL ) // both side with cars 
        {
            Car_Queue* carsWaitingLeft = (bridge->leftSide)->queueCarsSide; // update queue
            Car_Queue* carsWaitingRight =  (bridge->rightSide)->queueCarsSide;  // update queue           
            int radioactiveLeftCount = carsWaitingLeft->radioActiveCount; // update how many radioactive cars we have in the left
            int radioactiveRightCount = carsWaitingRight->radioActiveCount;// update how many radioactive cars we have in the right
			printf("\n");
			printf("\n");
            printf("****************************************************************************************************************************************\n");	
			
            printf("*********Iteration #: %d, Control Method is Semaphore, Bridge ID: %d*********\n",it,IDbridge);              
            if(bridge->direction==LEFT) // moving to the eft
            {
              allowCars=(bridge->rightSide->lengthBridgeSide)/2; // how many cars can pass depending of the lenght
              printf("Semaphore moves the traffic to the LEFT\n");
            }
            else if(bridge->direction==RIGHT)
            {
              allowCars=(bridge->leftSide->lengthBridgeSide)/2;  // how many cars can pass depending of the lenght
              printf("Semaphore moves the traffic to the RIGHT\n");
            }
            else
            {
              if((bridge->rightSide->lengthBridgeSide)>(bridge->leftSide->lengthBridgeSide)) // more cars in the right side
              {
                allowCars=(bridge->rightSide->lengthBridgeSide)/2;  // how many cars can pass depending of the lenght
              }
              else // the other case
              {
                allowCars=(bridge->leftSide->lengthBridgeSide)/2;  // how many cars can pass depending of the lenght
              }              
              printf("Direction: No direction\n");
            }
            if(carsOnBridge < allowCars) // cars in the bridge are less than the allow quantity
            {                         
              if(currentRadioactiveCars != 0){ // radioactive car existence
                  addCarsToBridge(bridge,bridge->direction); // add this car to the bridge
                  currentRadioactiveCars--; // less cars
                }
              else if(radioactiveLeftCount > 0 || radioactiveRightCount >0){ // radioactive
                    if(radioactiveLeftCount > 0){ // in the left
                        if(carsOnBridgeList->count == 0){
                           currentRadioactiveCars = radioactiveLeftCount;
                           bridge->direction = RIGHT; // change the direction to move the radioactive car
                        }
                        else
                        {
                          if(verifyRadioActiveonList(carsOnBridgeList,LEFTQUEUE)) // verify radioactive
                          {
                            currentRadioactiveCars = radioactiveLeftCount;
                            bridge->direction = RIGHT; // change dir
                          }
                        }                        
                    }
                    else if(radioactiveRightCount > 0){ // radioactive
                        if(carsOnBridgeList->count == 0){ // in the right
                           currentRadioactiveCars = radioactiveRightCount; // count of radio active
                           bridge->direction = LEFT; //change dir
                        }
                        else
                        {
                          if(verifyRadioActiveonList(carsOnBridgeList,RIGHTQUEUE)) // verify radioactive cars
                          {
                            currentRadioactiveCars = radioactiveRightCount;
                            bridge->direction = LEFT;
                          }
                        } 
                    }
                }
              else{
                if(bridge->direction == RIGHT){  // depending to the semaphore the dir of the bridge change
                  currentTimeLimit = (bridge->leftSide)->semaphoreGreenSide; // semaphore time in green
                  if(IDbridge == 1){		// depending of the bridge
                      greenLeftSemaphoreBridge1 = 1;
                      greenRightSemaphoreBridge1 = 0;
					  
                  }
                  else if (IDbridge == 2){
                      greenLeftSemaphoreBridge2 = 1;
                      greenRightSemaphoreBridge2 = 0;
                  }
                  else if(IDbridge == 3){
                      greenLeftSemaphoreBridge3 = 1;
                      greenRightSemaphoreBridge3 = 0;
                  }
                }
                else if(bridge->direction == LEFT){ //the same as above but in this case according the left side direction
                  currentTimeLimit = (bridge->rightSide)->semaphoreGreenSide;
                  if(IDbridge == 1){
                      greenLeftSemaphoreBridge1 = 0;
                      greenRightSemaphoreBridge1 = 1;
                  }
                  else if (IDbridge == 2){
                      greenLeftSemaphoreBridge2 = 0;
                      greenRightSemaphoreBridge2 = 1;
                  }
                  else if(IDbridge == 3){
                      greenLeftSemaphoreBridge3 = 0;
                      greenRightSemaphoreBridge3 = 1;
                  }
                }
                if(time_spent < currentTimeLimit){ // they can pass, they have time
                   addCarsToBridge(bridge,bridge->direction);
                }
                else if(time_spent >= currentTimeLimit &  carsOnBridge == 0){ // no more cars in the bridge passing
                  Direction changeDirection = traficOfficerController(bridge);
                  addCarsToBridge(bridge,changeDirection);
                  time_spent= 0.0; //change the time 
                }
              }
        }
        StatePrinter();  // print the data
        if(carsOnBridgeList)
        {     
          moveCarsOnBridge(carsOnBridgeList);  // the movement of the cars
          int posBridge = queueUpdating(carsOnBridgeList,IDbridge,bridge->direction); // getting pos
          Car_list_remove(carsOnBridgeList,posBridge); // remove the car depending of the posbridge     
        }
        time_spent+= 1.0; // count the seconds			
        it++;
        printf("\n");
        mythread_sleep(waitTime);
        }
    }
}
