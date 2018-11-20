

import pygame
from pygame.locals import *
import time

fileQRB3 = '/home/diego/Documentos/TEC/PrincipiosSO/proyecto2/Program/GUI/QRSB3.txt'
fileQRB2 = '/home/diego/Documentos/TEC/PrincipiosSO/proyecto2/Program/GUI/QRSB2.txt'
fileQRB1 = '/home/diego/Documentos/TEC/PrincipiosSO/proyecto2/Program/GUI/QRSB1.txt'
fileQLB3 = '/home/diego/Documentos/TEC/PrincipiosSO/proyecto2/Program/GUI/QLSB3.txt'
fileQLB2 = '/home/diego/Documentos/TEC/PrincipiosSO/proyecto2/Program/GUI/QLSB2.txt'
fileQLB1 = '/home/diego/Documentos/TEC/PrincipiosSO/proyecto2/Program/GUI/QLSB1.txt'
fileCOB1 = '/home/diego/Documentos/TEC/PrincipiosSO/proyecto2/Program/GUI/COB1.txt'
fileCOB2 = '/home/diego/Documentos/TEC/PrincipiosSO/proyecto2/Program/GUI/COB2.txt'
fileCOB3 = '/home/diego/Documentos/TEC/PrincipiosSO/proyecto2/Program/GUI/COB3.txt'
screen = pygame.display.set_mode((1300, 720), HWSURFACE|DOUBLEBUF)
XposBridge1 = 350 ##Esto es deun calculo
XposBridge2 = 850 ## debe salir de un calculo
YposBridge1A = 100;
YposBridge1B = 150;
YposBridge2A = 300;
YposBridge2B = 350;
YposBridge3A = 500;
YposBridge3B = 550;
normalCar = pygame.image.load("normalCar.png")
ambulance = pygame.image.load("ambulance.png")
radioactiveCar = pygame.image.load("radioactiveCar.png")
reloj = pygame.time.Clock()
bridgeSize = 50 ##CAMBIARLO

#these blocks of code draw the queues of the bridges
##---------------------------------------------------------------------------------------------------------------------------------
def drawPaintQLB1(matriz):
	offset = XposBridge1 #where the bridge starts
	for i in matriz:
		if(i[1] == "Radioactive"):
			screen.blit(radioactiveCar, (((offset - int(i[0])*20)-20), YposBridge1A + 15))    # then blit the bird
			offset = offset -5
		if(i[1] == "Ambulance"):
			screen.blit(ambulance, (((offset - int(i[0])*20)-20), YposBridge1A + 15))    # then blit the bird
			offset = offset -5
		if(i[1] == "Normal"):
			screen.blit(normalCar, (((offset - int(i[0])*20)-20), YposBridge1A + 15))    # then blit the bird
			offset = offset -5
def drawPaintQLB2(matriz):
	offset = XposBridge1 #where the bridge starts
	for i in matriz:
		if(i[1] == "Radioactive"):
			screen.blit(radioactiveCar, (((offset - int(i[0])*20)-20), YposBridge2A + 15))    # then blit the bird
			offset = offset -5
		if(i[1] == "Ambulance"):
			screen.blit(ambulance, (((offset - int(i[0])*20)-20), YposBridge2A + 15))    # then blit the bird
			offset = offset -5
		if(i[1] == "Normal"):
			screen.blit(normalCar, (((offset - int(i[0])*20)-20), YposBridge2A + 15))    # then blit the bird
			offset = offset -5
def drawPaintQLB3(matriz):
	offset = XposBridge1 #where the bridge starts
	for i in matriz:
		if(i[1] == "Radioactive"):
			screen.blit(radioactiveCar, (((offset - int(i[0])*20)-20), YposBridge3A + 15))    # then blit the bird
			offset = offset -5
		if(i[1] == "Ambulance"):
			screen.blit(ambulance, (((offset - int(i[0])*20)-20), YposBridge3A + 15))    # then blit the bird
			offset = offset -5
		if(i[1] == "Normal"):
			screen.blit(normalCar, (((offset - int(i[0])*20)-20), YposBridge3A + 15))    # then blit the bird
			offset = offset -5
			
def drawPaintQRB1(matriz):
	offset = XposBridge2 #where the bridge ends 
	for i in matriz:
		if(i[1] == "Radioactive"):
			screen.blit(radioactiveCar, (((offset + int(i[0])*20)+20), YposBridge1A + 15))   
			offset = offset +5
		if(i[1] == "Ambulance"):
			screen.blit(ambulance, (((offset + int(i[0])*20)+20), YposBridge1A + 15))    
			offset = offset +5
		if(i[1] == "Normal"):
			screen.blit(normalCar, (((offset + int(i[0])*20)+20), YposBridge1A + 15))   
			offset = offset +5
def drawPaintQRB2(matriz):
	offset = XposBridge2 #where the bridge ends 
	for i in matriz:
		if(i[1] == "Radioactive"):
			screen.blit(radioactiveCar, (((offset + int(i[0])*20)+20), YposBridge2A + 15))    
			offset = offset +5
		if(i[1] == "Ambulance"):
			screen.blit(ambulance, (((offset + int(i[0])*20)+20), YposBridge2A + 15))   
			offset = offset +5
		if(i[1] == "Normal"):
			screen.blit(normalCar, (((offset + int(i[0])*20)+20), YposBridge2A + 15))    
			offset = offset +5
def drawPaintQRB3(matriz):
	offset = XposBridge2 #where the bridge ends 
	for i in matriz:
		if(i[1] == "Radioactive"):
			screen.blit(radioactiveCar, (((offset + int(i[0])*20)+20), YposBridge3A + 15))    
			offset = offset +5
		if(i[1] == "Ambulance"):
			screen.blit(ambulance, (((offset + int(i[0])*20)+20), YposBridge3A + 15))   
			offset = offset +5
		if(i[1] == "Normal"):
			screen.blit(normalCar, (((offset + int(i[0])*20)+20), YposBridge3A + 15))    
			offset = offset +5
#----------------------------------------------------------------------------------------------------------------------------------			
#These methods will draw the cars in the bridges

def drawCarsOnBridge1(matriz):
	offset1 = XposBridge1 #where the bridge ends
	offset2 = XposBridge2
	for i in matriz: 
		if(i[1] == "Radioactive"):
			if(i[2] == "left"):
				screen.blit(radioactiveCar, (((offset2 - int(i[0])*10), YposBridge1A + 15)))  
				offset2 = offset2 -15
			if(i[2] == "right"):
				screen.blit(radioactiveCar, (((offset1 + int(i[0])*10) , YposBridge1A + 15)))
				offset1 = offset1 +15
		if(i[1] == "Ambulance"):
			if(i[2] == "left"):
				screen.blit(ambulance, (((offset2 - int(i[0])*10), YposBridge1A + 15)))
				offset2 = offset2 -15
			if(i[2] == "right"):
				screen.blit(ambulance, (((offset1 + int(i[0])*10), YposBridge1A + 15)))
				offset1 = offset1 +15
		if(i[1] == "normalCar"):
			if(i[2] == "left"):
				screen.blit(normalCar, (((offset2 - int(i[0])*10), YposBridge1A + 15)))
				offset2 = offset2 -15
			if(i[2] == "right"):
				screen.blit(normalCar, (((offset1 + int(i[0])*10), YposBridge1A + 15)))
				offset1 = offset1 +15
				
def drawCarsOnBridge2(matriz):
	offset1 = XposBridge1 #where the bridge ends
	offset2 = XposBridge2
	for i in matriz: 
		if(i[1] == "Radioactive"):
			if(i[2] == "left"):
				screen.blit(radioactiveCar, (((offset2 - int(i[0])*10), YposBridge2A + 15)))  
				offset2 = offset2 -15
			if(i[2] == "right"):
				screen.blit(radioactiveCar, (((offset1 + int(i[0])*10) , YposBridge2A + 15)))
				offset1 = offset1 +15
		if(i[1] == "Ambulance"):
			if(i[2] == "left"):
				screen.blit(ambulance, (((offset2 - int(i[0])*10), YposBridge2A + 15)))
				offset2 = offset2 -15
			if(i[2] == "right"):
				screen.blit(ambulance, (((offset1 + int(i[0])*10), YposBridge2A + 15)))
				offset1 = offset1 +15
		if(i[1] == "normalCar"):
			if(i[2] == "left"):
				screen.blit(normalCar, (((offset2 - int(i[0])*10), YposBridge2A + 15)))
				offset2 = offset2 -15
			if(i[2] == "right"):
				screen.blit(normalCar, (((offset1 + int(i[0])*10), YposBridge2A + 15)))
				offset1 = offset1 +15

def drawCarsOnBridge3(matriz):
	offset1 = XposBridge1 #where the bridge ends
	offset2 = XposBridge2
	for i in matriz: 
		if(i[1] == "Radioactive"):
			print("HOLa")
			if(i[2] == "left"):
				screen.blit(radioactiveCar, (((offset2 - int(i[0])*10), YposBridge3A + 15)))  
				offset2 = offset2 -15
			if(i[2] == "right"):
				screen.blit(radioactiveCar, (((offset1 + int(i[0])*10) , YposBridge3A + 15)))
				offset1 = offset1 +15
		if(i[1] == "Ambulance"):
			if(i[2] == "left"):
				screen.blit(ambulance, (((offset2 - int(i[0])*10), YposBridge3A + 15)))
				offset2 = offset2 -15
			if(i[2] == "right"):
				screen.blit(ambulance, (((offset1 + int(i[0])*10), YposBridge3A + 15)))
				offset1 = offset1 +15
		if(i[1] == "normalCar"):
			if(i[2] == "left"):
				screen.blit(normalCar, (((offset2 - int(i[0])*10), YposBridge3A + 15)))
				offset2 = offset2 -15
			if(i[2] == "right"):
				screen.blit(normalCar, (((offset1 + int(i[0])*10), YposBridge3A + 15)))
				offset1 = offset1 +15



#----------------------------------------------------------------------------------------------------------------------------------			
def initDraw():
	screen.fill((255,255,255))
	#Bridge 1 lines here the position in x will change***
	pygame.draw.line(screen, (255,0,0), (350, YposBridge1A), (850, YposBridge1A), 4)
	pygame.draw.line(screen, (255,0,0), (350, YposBridge1B), (850, YposBridge1B), 4)
	#Bridge 2 lines
	pygame.draw.line(screen, (0,255,0), (350, YposBridge2A), (850, YposBridge2A), 4)
	pygame.draw.line(screen, (0,255,0), (350, YposBridge2B), (850, YposBridge2B), 4)
	#Bridge 3 lines
	pygame.draw.line(screen, (0,0,250), (350, YposBridge3A), (850, YposBridge3A), 4)
	pygame.draw.line(screen, (0,0,250), (350, YposBridge3B), (850, YposBridge3B), 4)
	pygame.display.update()
	
def main():
	pygame.init()
	initDraw()
	while 1:
		with open(fileCOB1) as f:
			data = f.readlines()
			f = open(fileCOB1)
			data = f.readlines()
			f.close()
			matrizCarsOnBridge1 =[]
			for n, line in enumerate(data, 1):
				stringCarsOnBridge = line.rstrip()
				listCars = stringCarsOnBridge.split(",")
				matrizCarsOnBridge1.append(listCars)

		with open(fileCOB2) as f:
			data = f.readlines()
			f = open(fileCOB2)
			data = f.readlines()
			f.close()
			matrizCarsOnBridge2 =[]
			for n, line in enumerate(data, 1):
				stringCarsOnBridge = line.rstrip()
				listCars = stringCarsOnBridge.split(",")
				matrizCarsOnBridge2.append(listCars)
		with open(fileCOB3) as f:
			data = f.readlines()
			f = open(fileCOB3)
			data = f.readlines()
			f.close()
			matrizCarsOnBridge3 =[]
			for n, line in enumerate(data, 1):
				stringCarsOnBridge = line.rstrip()
				listCars = stringCarsOnBridge.split(",")
				matrizCarsOnBridge3.append(listCars)
		with open(fileQLB1) as f:
			data = f.readlines()
			f = open(fileQLB1)
			data = f.readlines()
			f.close()
			matrizQueueLB1 =[]
			for n, line in enumerate(data, 1):
				stringParams = line.rstrip()
				listParams = stringParams.split(",")
				matrizQueueLB1.append(listParams)
		with open(fileQRB1) as f:
			data = f.readlines()
			f = open(fileQRB1)
			data = f.readlines()
			f.close()
			matrizQueueRB1 =[]
			for n, line in enumerate(data, 1):
				stringParams = line.rstrip()
				listParams = stringParams.split(",")
				matrizQueueRB1.append(listParams)
		with open(fileQLB2) as f:
			data = f.readlines()
			f = open(fileQLB2)
			data = f.readlines()
			f.close()
			matrizQueueLB2 =[]
			for n, line in enumerate(data, 1):
				stringParams = line.rstrip()
				listParams = stringParams.split(",")			
				matrizQueueLB2.append(listParams)
		with open(fileQRB2) as f:
			data = f.readlines()
			f = open(fileQRB2)
			data = f.readlines()
			f.close()
			matrizQueueRB2 =[]
			for n, line in enumerate(data, 1):
				stringParams = line.rstrip()
				listParams = stringParams.split(",")			
				matrizQueueRB2.append(listParams)
		with open(fileQLB3) as f:
			data = f.readlines()
			f = open(fileQLB3)
			data = f.readlines()
			f.close()
			matrizQueueLB3 =[]
			for n, line in enumerate(data, 1):
				stringParams = line.rstrip()
				listParams = stringParams.split(",")
				matrizQueueLB3.append(listParams)
		with open(fileQRB3) as f:
			data = f.readlines()
			f = open(fileQRB3)
			data = f.readlines()
			f.close()
			matrizQueueRB3 =[]
			for n, line in enumerate(data, 1):
				stringParams = line.rstrip()
				listParams = stringParams.split(",")
				matrizQueueRB3.append(listParams)
		time.sleep(0.5)
		
		initDraw()
		drawPaintQLB1(matrizQueueLB1)
		drawPaintQRB3(matrizQueueRB3)
		drawPaintQRB2(matrizQueueRB2)
		drawPaintQLB2(matrizQueueLB2)
		drawPaintQRB1(matrizQueueRB1)
		drawPaintQLB3(matrizQueueLB3)
		drawCarsOnBridge1(matrizCarsOnBridge1)
		drawCarsOnBridge2(matrizCarsOnBridge2)
		drawCarsOnBridge3(matrizCarsOnBridge3)
		pygame.display.update()

		
		
		
		
if __name__ == '__main__': main()
