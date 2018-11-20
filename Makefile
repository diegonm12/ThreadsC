CC = gcc
ouput = ThreadBridge

main:
		$(CC) -std=gnu99 -o $(ouput) main.c Thread.c Scheduler.c TCB.c ContextManage.c Dispatcher.c Mutex.c TCB_list.c TCB_Queue.c BridgeController.c Brigde.c Car.c Car_List.c Car_Queue.c readFile.c  `sdl-config --cflags --libs` -Wall -lm -lm -L/usr/lib/python2.3/config





clean:
		rm $(ouput)




