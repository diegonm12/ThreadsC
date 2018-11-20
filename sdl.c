/*******************************************
 2:  *   Introduccion a SDL - 1                *
 3:  *   Curso de C, Nacho Cabanes             *
 4:  *******************************************/
  
 #include <stdlib.h>
 #include "Thread.h"
 #include <SDL/SDL.h>
#include "Car_Queue.h"
#include "Car.h"
#include <stdio.h>                                                              
#include <unistd.h>
#include "readFile.h" 
#include <math.h> 
#include "BridgeController.h"
#include "Interfaz.h" 
 

void* muestraInterfaz(void * x_void_ptr){
  if (SDL_Init(SDL_INIT_VIDEO) < 0) {
     printf("No se pudo inicializar SDL: %s\n", SDL_GetError());
     exit(1);
   }
   
   /* Si todo ha ido bien, hacemos algo: 
       entrar a modo grafico y cambiar el título de la ventana */
   if( SDL_SetVideoMode( 640, 480, 16, SDL_HWSURFACE ) == NULL ) {
      printf( "Error al entrar a modo grafico: %s\n", SDL_GetError() );
      SDL_Quit();
      return -1;
   }
   
   SDL_WM_SetCaption( "Hola mundo!", "Hola Mundo!" );

  while(1){
/* Tratamos de inicializar la biblioteca SDL */
   
 
  // SDL_Delay( 500 );
   
    mythread_sleep(100);
   /* Finalmente, preparamos para salir */
 //  SDL_Quit();
 }
}

void* imprime(void * x_void){
	int z = 0;
/* Tratamos de inicializar la biblioteca SDL */
   while(1){
   	printf("hoa\n");
 //  	z = z +1;
    mythread_sleep(100);
   }
   
   
//   printf("hoa\n");
//   printf("hoa\n");
   /* Finalmente, preparamos para salir */
 //  SDL_Quit();
}

int main()
 {
  initConfigFile(); 
  
  
  //Initialize all the structs of the BridgeController
  initBridgeController();

 	mythread_init();  

  initCarsOnBridge();

  int fillCars_thread=mythread_create(fillCarsJungle, REALTIME, 0,0, 1);

  
 	int fillCars_thread2=mythread_create(animatedThreadBridge, REALTIME, 0,0, 1);
 //	int fillCars_thread2=mythread_create(imprime, REALTIME, 0,0, 34);
  
  mythread_join(fillCars_thread);
  mythread_join(fillCars_thread2);

   return 0;
 }