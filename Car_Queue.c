#include "Car_Queue.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "BridgeController.h"

//This method is going to check if the queue is empty
int Car_Queue_is_empty(Car_Queue* q) {
    return (q->first == NULL && q->next == NULL);
}

//This method is going to add a car in a specific location of the queue
void addMiddleCar(Car_Queue *q, Car_Queue_node* new_element, int posInsert )
{
    Car_Queue_node* element_anterior = q->first;
    Car_Queue_node* element_anterior_next;  
    for (int i = 0; i < posInsert; ++i)
    {
        element_anterior = element_anterior->next; 
    }    
    element_anterior_next=element_anterior->next;
    element_anterior->next=new_element;
    new_element->next=element_anterior_next;
    q->count++;
}

//This method is going to add the next of the queue
void addEndCar(Car_Queue *q,Car_Queue_node* new_element)
{
    (q->next)->next = (Car_Queue_node*) malloc(sizeof (Car_Queue_node));
    (q->next)->next = new_element;
    q->next = (q->next)->next;
    q->count++;
}

//This method is going to add the first of the queue
void addStartCar(Car_Queue *q,Car_Queue_node* new_element)
{
    Car_Queue_node* element_anterior = q->first;
    q->first=new_element;
    q->first->next=element_anterior;               
    q->count++;

}

//This method is going to check if there is a normal car on the queue
int verifyNormal(Car_Queue* Car_Queue)
{    
    int pos=-1;
    Car_Queue_node* element = Car_Queue->first;
    for (int i = 0; i < Car_Queue->count; ++i)
    {        
        if(element->data->type==NORMAL)
        {
            pos=i;
            break;
        }
        element = element->next;      
    }
    return pos;
}

//This method is going to check if there is a radioactive car on the queue
int verifyRadioactive(Car_Queue* Car_Queue)
{    
    int pos=-1;
    Car_Queue_node* element = Car_Queue->first;
    for (int i = 0; i < Car_Queue->count; ++i)
    {        
        if(element->data->type==RADIOACTIVE)
        {
            pos=i;
        }
        element = element->next;      
    }
    return pos;
}

//This method is going to check if there is a normal car on the queue
int containsCars(Car_Queue* Car_Queue)
{    
    int result=1;
    Car_Queue_node* element = Car_Queue->first;
    for (int i = 0; i < Car_Queue->count; ++i)
    {   

        if(element->data->type==NORMAL)
        {
           
            result=0;
            break;
        }
        element = element->next;    

         
    }
    
    return result;
}




//This method is going to check if there is an ambulance on the queue
int verifyAmbulance(Car_Queue* Car_Queue)
{    

    int pos=-1;
    Car_Queue_node* element = Car_Queue->first;
    for (int i = 0; i < Car_Queue->count; ++i)
    {   
        //printf("Itera: %d\n",i );    
        if(element!=NULL){ 
            if(element->data->type==AMBULANCE)
            {
                //printf("Entre\n");
                pos=i;
            }
        }
        element = element->next;   
        //printf("Nuevo next\n");   
    }

    //printf("Termine>=: %d\n",pos);
    return pos;
}

//This method is going to add a radioactive car to the queue
void addRadioActiveCar(Car_Queue *q,Car_Queue_node* new_element)
{
    //printf("Radioactive car added\n");      
    int posInsert=verifyRadioactive(q);           
    if(posInsert==-1)
    {
        //printf("Va a agregar radioactivo, y no hay radioactivos\n");
        addStartCar(q,new_element);       
    }
    else
    {   
        if(containsCars(q)==1)
        {
            //printf("Solo contiene radioactivos\n");
            addEndCar(q,new_element);  
        }   
        else
        {          
            //printf("Va a agregar un radioactivo, hay mas radioactivos y hay otros carros\n");
            addMiddleCar(q,new_element,posInsert);                   
        }
     }
}

//This method is going to add an ambulance to the queue
void addAmbulanceCar(Car_Queue *q,Car_Queue_node* new_element)
{
    //printf("Ambulance car added\n");
    int posInsert=verifyAmbulance(q);
    //no hay ambulancias
    if(posInsert==-1)
    {        
        int posNormal=verifyNormal(q);
        int posRadioactive=verifyRadioactive(q);
        //printf("No encontre ambulancias, posNormal: %d\n",posNormal);
        if(posNormal!=-1)
        {  
            if(posRadioactive==-1)
            {
                //printf("No hay ambulancias, hay carros normales, pero no hay radioactivos\n");  
                addStartCar(q,new_element);
            }
            else
            {
                //printf("Va a agregar una ambulancia y hay carros normales y radioactivos\n");                  
                addMiddleCar(q,new_element,posNormal-1); 
            }
        }                   
        else
        {
            //printf("Va a agregar una ambulancia y no hay carros normales\n");
            addEndCar(q,new_element);           
        }
    }
    else
    {                
        //printf("Va a agregar una ambulancia, ya hay ambulancias y ya hay carros\n");
        if(containsCars(q)==1)
        {
            //printf("Hay carros normales\n");
            addEndCar(q,new_element);  
        }
        else
        {                   
           addMiddleCar(q,new_element,posInsert);
        }
     }
}

//This method is going to add a car to the queue
int EnqueueCar(Car_Queue *q, Car *t) {
    Car_Queue_node* new_element = (Car_Queue_node*) malloc(sizeof (Car_Queue_node));
    if (new_element == NULL) {
        return ERROR;
    } else {
        new_element->data = t;
        new_element->next = NULL;
        //Empty queue
        if(t->type==RADIOACTIVE)
        {
            q->radioActiveCount++;            
        } 
        if (Car_Queue_is_empty(q)) {          
            q->first = new_element;
            q->next = new_element;            
            q->count++;
        }
        //If car is radioactive type
        else if(t->type==RADIOACTIVE)
        {
            addRadioActiveCar(q, new_element);
            
        }
        else if(t->type==AMBULANCE)
        {
            addAmbulanceCar(q, new_element);                       
        }
        else
        {
            //printf("Normal car added\n");
            addEndCar(q,new_element);
        }

        return NO_ERROR;
    }
}

//This method is going to extract a car from the queue
Car* DequeueCar(Car_Queue* Car_Queue) {
    if (Car_Queue_is_empty(Car_Queue)) {
        return NULL;
    } 
    else if ((Car_Queue->first) == (Car_Queue->next)) // queue has only one element
    {
        Car_Queue_node* element = Car_Queue->first;

        if(element->data->type==RADIOACTIVE)
        {
            Car_Queue->radioActiveCount--;         
               
        }

        Car_Queue->first = NULL;
        Car_Queue->next = NULL;
        Car_Queue->count--;
        return element->data;
    } 
    else
    {
        Car_Queue_node* element = Car_Queue->first;

        if(element->data->type==RADIOACTIVE)
        {
            Car_Queue->radioActiveCount--;
            
               
        }

        Car_Queue->first = (Car_Queue->first)->next;
        Car_Queue->count--;
        
        return element->data;
    }
}


//This method is going to print the queue
void printQueue(Car_Queue* Car_Queue, int queueID)
{    
	char file [100];
	char command[100];
	if(queueID == 1){
		strcpy(file, "/home/diego/Documentos/TEC/PrincipiosSO/proyecto2/Program/GUI/QLSB1.txt");
		strcpy(command,"> ");
		strcat(command,file);
		system(command);
	}
	if(queueID == 2){
		strcpy(file, "/home/diego/Documentos/TEC/PrincipiosSO/proyecto2/Program/GUI/QRSB1.txt");
		strcpy(command,"> ");
		strcat(command,file);
		system(command);
	}
	if(queueID == 3){
		strcpy(file, "/home/diego/Documentos/TEC/PrincipiosSO/proyecto2/Program/GUI/QLSB2.txt");
		strcpy(command,"> ");
		strcat(command,file);
		system(command);
	}
	if(queueID == 4){
		strcpy(file, "/home/diego/Documentos/TEC/PrincipiosSO/proyecto2/Program/GUI/QRSB2.txt");
		strcpy(command,"> ");
		strcat(command,file);
		system(command);
	}
	if(queueID == 5){
		strcpy(file, "/home/diego/Documentos/TEC/PrincipiosSO/proyecto2/Program/GUI/QLSB3.txt");
		strcpy(command,"> ");
		strcat(command,file);
		system(command);
	}
	if(queueID == 6){
		strcpy(file, "/home/diego/Documentos/TEC/PrincipiosSO/proyecto2/Program/GUI/QRSB3.txt");
		strcpy(command,"> ");
		strcat(command,file);
		system(command);
	}
	
    Car_Queue_node* element = Car_Queue->first;
    for (int i = 0; i < Car_Queue->count; ++i)
    {        
        if(element->data->type==AMBULANCE)
        {
            printf("%d -> Ambulance car, Speed: %d, Position on Bridge: %d, Can car move: %d, Bridge: %d, carID: %d\n",i,element->data->SpeedOfCar,element->data->bridgePos,element->data->askContinue,element->data->bridgeID,element->data->carID);
        	char completeCharArray [255];
			char writingCommand [255];
			char str[10];
			sprintf(str, "%d", i);
			strcpy(completeCharArray,str);
			strcat(completeCharArray,",");
			strcat(completeCharArray,"Ambulance");
			strcat(completeCharArray,",");
			sprintf(str, "%d", element->data->carID);
			strcat(completeCharArray,str);
			strcat(completeCharArray,",");
  			sprintf(str, "%d", element->data->SpeedOfCar);
			strcat(completeCharArray,str);
			strcat(completeCharArray,",");
			sprintf(str, "%d", element->data->bridgeID);
			strcat(completeCharArray,str);
			strcpy(writingCommand,"echo ");
			strcat(writingCommand,completeCharArray);
			strcat(writingCommand,">> ");
			strcat(writingCommand,file);
			system(writingCommand);

		}
        else if(element->data->type==RADIOACTIVE)
        {
            printf("%d -> Radioactive car, Speed: %d, Position on Bridge: %d, Can car move: %d, Bridge: %d, carID: %d\n",i,element->data->SpeedOfCar,element->data->bridgePos,element->data->askContinue,element->data->bridgeID,element->data->carID);
			char completeCharArray [255];
			char writingCommand [255];
			char str[10];
			sprintf(str, "%d", i);
			strcpy(completeCharArray,str);
			strcat(completeCharArray,",");
			strcat(completeCharArray,"Radioactive");
			strcat(completeCharArray,",");
			sprintf(str, "%d", element->data->carID);
			strcat(completeCharArray,str);
			strcat(completeCharArray,",");
  			sprintf(str, "%d", element->data->SpeedOfCar);
			strcat(completeCharArray,str);
			strcat(completeCharArray,",");
			sprintf(str, "%d", element->data->bridgeID);
			strcat(completeCharArray,str);
			strcpy(writingCommand,"echo ");
			strcat(writingCommand,completeCharArray);
			strcat(writingCommand,">> ");
			strcat(writingCommand,file);
			system(writingCommand); 
        }
        else
        {
            printf("%d -> Normal car, Speed: %d, Position on Bridge: %d, Can car move: %d, Bridge: %d, carID: %d\n",i,element->data->SpeedOfCar,element->data->bridgePos,element->data->askContinue,element->data->bridgeID,element->data->carID);
        	char completeCharArray [255];
			char writingCommand [255];
			char str[10];
			sprintf(str, "%d", i);
			strcpy(completeCharArray,str);
			strcat(completeCharArray,",");
			strcat(completeCharArray,"Normal");
			strcat(completeCharArray,",");
			sprintf(str, "%d", element->data->carID);
			strcat(completeCharArray,str);
			strcat(completeCharArray,",");
  			sprintf(str, "%d", element->data->SpeedOfCar);
			strcat(completeCharArray,str);
			strcat(completeCharArray,",");
			sprintf(str, "%d", element->data->bridgeID);
			strcat(completeCharArray,str);
			strcpy(writingCommand,"echo ");
			strcat(writingCommand,completeCharArray);
			strcat(writingCommand,">> ");
			strcat(writingCommand,file);
			system(writingCommand);
		}
        element = element->next;       
    }
    if (Car_Queue->count==0)
    {
        printf("Empty queue\n");
    }

}

//This method is going to remove the cars of the queue of the jungle law
Car* carJungleRemove(Car_Queue* car_Queue, int carID) {
    //printf("Remove from list %d \n", Car->thread_id);
   
   Car_Queue_node* pointer = car_Queue->first;
   Car_Queue_node* pastPointer = NULL; 
   Car_Queue_node* frontCar = car_Queue->first;
   Car_Queue_node* rearCar = car_Queue->next;
   

    while (pointer != NULL) {
      
        //Car_Queue_node* to_be_removed = pointer;

        if ((car_Queue->first)->next == NULL && ((car_Queue->first)->data)->carID == carID ) // list has only one element
        {
            car_Queue->first = NULL;
            car_Queue->next = NULL;
            car_Queue->count--;
        } 
        else if ((pointer->data)->carID == (frontCar->data)->carID && (pointer->data)->carID == carID) // list has more than one element and first element is to be removed
        {
            car_Queue->first = (car_Queue->first)->next;
            car_Queue->count--;
        }  
        else if ((pointer->next)!=NULL && ((pointer->next)->data)->carID == (rearCar->data)->carID && ((pointer->next)->data)->carID == carID) // list has more than one element and last element is to be removed
        {
            car_Queue->next = pointer;
            pointer->next = NULL;
            car_Queue->count--;
        } 
        else if((pointer->data)->carID == carID)// default
        {
            pastPointer->next = pointer->next;
            car_Queue->count--;
        }
        //free(to_be_removed);
        
        pastPointer = pointer;
        pointer = pointer->next;
    }

    return NULL;
}

//Place the cars in the queue of the bridges
Car_Queue* creatingQueueOfCarsJungle(Car_Queue* Queue,float PercentOfAmbulance, float PercentOfRadioactive, int speedNormalCar, int speedAmbulance, int speedRadioactive,int carsQuantity, int bridgeID, QueueOfSides queueSide, int bridgePos){    
   
    int ambulance= carsQuantity*PercentOfAmbulance; // the percent of ambulances to be created
    int radioactive= carsQuantity*PercentOfRadioactive; // the percent of radioactive cars to be created
    int counter= carsQuantity-ambulance-radioactive;   // contador de carros 
   
    for (int i = 0; i < counter; ++i)
    {       
        Car* actualCar = createCar(NORMAL,speedNormalCar, bridgeID, queueSide,bridgePos); // a car is created
        int x = mythread_create(jungleLaw,ROUNDROBIN,0,actualCar,50); //cars will use round robin    
        actualCar->carID =  x; // assign the car id
        EnqueueCar(Queue,actualCar);  //queue the car in the corresponding queue.

        if(queueSide==LEFTQUEUE)    // the side of the queue is left 
        {
            printf("Normal car added to left queue, bridge %d, carID:%d \n",bridgeID,x); // print the car is added
        }
        else    // the side of the queue is right
        {
            printf("Normal car added to right queue, bridge %d, carID:%d \n",bridgeID,x); // print the car is added
        }
        
    }

    
    for (int i = 0; i < ambulance; ++i) // the ambulance is going to be added
    {        
        Car* actualCar = createCar(AMBULANCE,speedAmbulance, bridgeID, queueSide,bridgePos); // the ambulance is created
        int x = mythread_create(jungleLaw,RAFFLE,10,actualCar,50);  // the ambulance is going to use other scheduler   
        actualCar->carID =  x;      // the id is assign    
        EnqueueCar(Queue,actualCar);    // queue the ambulance in the corresponding queue

        if(queueSide==LEFTQUEUE)    // left side accordin to the queueSide
        {
            printf("Ambulance car added to left queue, bridge %d, carID:%d \n",bridgeID,x);
        }
        else    // right side accordin to the queueSide
        {
            printf("Ambulance car added to right queue, bridge %d, carID:%d \n",bridgeID,x);
        }
    }


    for (int i = 0; i < radioactive; ++i)   // the radioactive is going to be added in the queue
    {        
        Car* actualCar = createCar(RADIOACTIVE,speedRadioactive, bridgeID, queueSide,bridgePos); //the car is created in this case is radioactive
        int x = mythread_create(jungleLaw,REALTIME,0,actualCar,50);   // use realtime   
        actualCar->carID =  x;      // the id is assign
        EnqueueCar(Queue,actualCar);    // the car is enqueue
        if(queueSide==LEFTQUEUE)    //depending to the queue side is located in the left side
        {
            printf("Radioactive car added to left queue, bridge %d, carID:%d \n",bridgeID,x);
        }
        else    // is located in the right side
        {
            printf("Radioactive car added to right queue, bridge %d, carID:%d \n",bridgeID,x);
        }  
    }
    return Queue;   // Then the queue created with the added information is returned   
}


//This method is going to get a car from the queue
Car* Car_Queue_get(Car_Queue* Car_Queue, int carID){
    Car_Queue_node* pointer = Car_Queue->first;
    while (pointer != NULL) {
        if ((pointer->data)->carID == carID) {
            return (pointer->data);
        }
        pointer = pointer->next;
    }
    return NULL;
}

Car_Queue* createQueue() { // This method is going to create the queue for the cars with default values
    Car_Queue* carsQueue = (Car_Queue*) malloc(sizeof (Car_Queue));
    if (carsQueue == NULL) {
        return NULL;
    } else {
        carsQueue->first = NULL; // default value
        carsQueue->next = NULL; // default value
        carsQueue->count = 0;   //default value
        carsQueue->radioActiveCount = 0;    //default value
        return carsQueue;
    }
}





