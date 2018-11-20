
import time
from Tkinter import *
from threading import Thread
from time import sleep
fileQRB3 = '/home/diego/Documentos/TEC/PrincipiosSO/proyecto2/Program/GUI/QRSB3.txt'
fileQRB2 = '/home/diego/Documentos/TEC/PrincipiosSO/proyecto2/Program/GUI/QRSB2.txt'
fileQRB1 = '/home/diego/Documentos/TEC/PrincipiosSO/proyecto2/Program/GUI/QRSB1.txt'
fileQLB3 = '/home/diego/Documentos/TEC/PrincipiosSO/proyecto2/Program/GUI/QLSB3.txt'
fileQLB2 = '/home/diego/Documentos/TEC/PrincipiosSO/proyecto2/Program/GUI/QLSB2.txt'
fileQLB1 = '/home/diego/Documentos/TEC/PrincipiosSO/proyecto2/Program/GUI/QLSB1.txt'
fileCOB1 = '/home/diego/Documentos/TEC/PrincipiosSO/proyecto2/Program/GUI/COB1.txt'
fileCOB2 = '/home/diego/Documentos/TEC/PrincipiosSO/proyecto2/Program/GUI/COB2.txt'
fileCOB3 = '/home/diego/Documentos/TEC/PrincipiosSO/proyecto2/Program/GUI/COB3.txt'
XposBridge1 = 350 ##Esto es deun calculo
XposBridge2 = 850 ## debe salir de un calculo
YposBridge1A = 100;
YposBridge1B = 150;
YposBridge2A = 300;
YposBridge2B = 350;
YposBridge3A = 500;
YposBridge3B = 550;
bridgeSize = 50 ##CAMBIARLO
bridgeSizePix = 500 ## change
tk = Tk()
w = 1200
h = 700
canvas = Canvas(tk, width=w, height=h,background='white')
canvas.pack()

normalCar = PhotoImage(file='normalCar.png')
ambulance = PhotoImage(file='ambulance.png')
radioactiveCar = PhotoImage(file='radioactiveCar.png')
matQueueLB1 = []
matQueueLB2 = []
matQueueLB3 = []
matQueueRB1 = []
matQueueRB2 = []
matQueueRB3 = []

#these blocks of code draw the queues of the bridges
##---------------------------------------------------------------------------------------------------------------------------------
def drawPaintQLB1(matriz):

	offset = XposBridge1 #where the bridge starts
	for i in matriz:
		if(i[1] == "Radioactive"):
			canvasRadioactive = canvas.create_image((offset - int(i[0])*20)-20,YposBridge1A + 15, anchor=NW, image=radioactiveCar)
			offset = offset -5
		if(i[1] == "Ambulance"):
			canvasRadioactive = canvas.create_image((offset - int(i[0])*20)-20,YposBridge1A + 15, anchor=NW, image=ambulance)
			offset = offset -5
		if(i[1] == "Normal"):
			canvasRadioactive = canvas.create_image((offset - int(i[0])*20)-20,YposBridge1A + 15, anchor=NW, image=normalCar)
			offset = offset -5
def drawPaintQLB2(matriz):
	offset = XposBridge1 #where the bridge starts
	for i in matriz:
		if(i[1] == "Radioactive"):
			canvasRadioactive = canvas.create_image((offset - int(i[0])*20)-20,YposBridge2A + 15, anchor=NW, image=radioactiveCar)
			offset = offset -5
		if(i[1] == "Ambulance"):
			canvasRadioactive = canvas.create_image((offset - int(i[0])*20)-20,YposBridge2A + 15, anchor=NW, image=ambulance)
			offset = offset -5
		if(i[1] == "Normal"):
			canvasRadioactive = canvas.create_image((offset - int(i[0])*20)-20,YposBridge2A + 15, anchor=NW, image=normalCar)
			offset = offset -5
def drawPaintQLB3(matriz):
	offset = XposBridge1 #where the bridge starts
	for i in matriz:
		if(i[1] == "Radioactive"):
			canvasRadioactive = canvas.create_image((offset - int(i[0])*20)-20,YposBridge3A + 15, anchor=NW, image=radioactiveCar)
			offset = offset -5
		if(i[1] == "Ambulance"):
			canvasRadioactive = canvas.create_image((offset - int(i[0])*20)-20,YposBridge3A + 15, anchor=NW, image=ambulance)
			offset = offset -5
		if(i[1] == "Normal"):
			canvasRadioactive = canvas.create_image((offset - int(i[0])*20)-20,YposBridge3A + 15, anchor=NW, image=normalCar)
			offset = offset -5
			
def drawPaintQRB1(matriz):
	offset = XposBridge2 #where the bridge ends 
	for i in matriz:
		if(i[1] == "Radioactive"):
			canvasRadioactive = canvas.create_image((offset + int(i[0])*20)+20,YposBridge1A + 15, anchor=NW, image=radioactiveCar)  
			offset = offset +5
		if(i[1] == "Ambulance"):
			canvasRadioactive = canvas.create_image((offset + int(i[0])*20)+20,YposBridge1A + 15, anchor=NW, image=ambulance)   
			offset = offset +5
		if(i[1] == "Normal"):
			canvasRadioactive = canvas.create_image((offset + int(i[0])*20)+20,YposBridge1A + 15, anchor=NW, image=normalCar) 
			offset = offset +5
def drawPaintQRB2(matriz):
	offset = XposBridge2 #where the bridge ends 
	for i in matriz:
		if(i[1] == "Radioactive"):
			canvasRadioactive = canvas.create_image((offset + int(i[0])*20)+20,YposBridge2A + 15, anchor=NW, image=radioactiveCar)   
			offset = offset +5
		if(i[1] == "Ambulance"):
			canvasRadioactive = canvas.create_image((offset + int(i[0])*20)+20,YposBridge2A + 15, anchor=NW, image=ambulance)  
			offset = offset +5
		if(i[1] == "Normal"):
			canvasRadioactive = canvas.create_image((offset + int(i[0])*20)+20,YposBridge2A + 15, anchor=NW, image=normalCar)    
			offset = offset +5
def drawPaintQRB3(matriz):
	offset = XposBridge2 #where the bridge ends 
	for i in matriz:
		if(i[1] == "Radioactive"):
			canvasRadioactive = canvas.create_image((offset + int(i[0])*20)+20,YposBridge3A + 15, anchor=NW, image=radioactiveCar)    
			offset = offset +5
		if(i[1] == "Ambulance"):
			canvasRadioactive = canvas.create_image((offset + int(i[0])*20)+20,YposBridge3A + 15, anchor=NW, image=ambulance)   
			offset = offset +5
		if(i[1] == "Normal"):
			canvasRadioactive = canvas.create_image((offset + int(i[0])*20)+20,YposBridge3A + 15, anchor=NW, image=normalCar)
			offset = offset +5
#----------------------------------------------------------------------------------------------------------------------------------			
#These methods will draw the cars in the bridges

def drawCarsOnBridge1(matriz):
	offset1 = XposBridge1 #where the bridge ends
	offset2 = XposBridge2
	for i in matriz: 
		if(i[1] == "Radioactive"):
			if(i[2] == "left"):
				canvasRadioactive = canvas.create_image((offset2 - int(i[0])*10),YposBridge1A + 15, anchor=NW, image=radioactiveCar)
				offset2 = offset2 -15
			if(i[2] == "right"):
				canvasRadioactive = canvas.create_image((offset1 + int(i[0])*10),YposBridge1A + 15, anchor=NW, image=radioactiveCar)
				offset1 = offset1 +15
		if(i[1] == "Ambulance"):
			if(i[2] == "left"):
				canvasRadioactive = canvas.create_image((offset2 - int(i[0])*10),YposBridge1A + 15, anchor=NW, image=ambulance)
				offset2 = offset2 -15
			if(i[2] == "right"):
				canvasRadioactive = canvas.create_image((offset1 + int(i[0])*10),YposBridge1A + 15, anchor=NW, image=ambulance) 
				offset1 = offset1 +15
		if(i[1] == "normalCar"):
			if(i[2] == "left"):
				canvasRadioactive = canvas.create_image((offset2 - int(i[0])*10),YposBridge1A + 15, anchor=NW, image=normalCar)
				offset2 = offset2 -15
			if(i[2] == "right"):
				canvasRadioactive = canvas.create_image((offset1 + int(i[0])*10),YposBridge1A + 15, anchor=NW, image=normalCar)
				offset1 = offset1 +15
				
def drawCarsOnBridge2(matriz):
	offset1 = XposBridge1 #where the bridge ends
	offset2 = XposBridge2
	for i in matriz: 
		if(i[1] == "Radioactive"):
			if(i[2] == "left"):
				canvasRadioactive = canvas.create_image((offset2 - int(i[0])*10),YposBridge2A + 15, anchor=NW, image=radioactiveCar)
				offset2 = offset2 -15
			if(i[2] == "right"):
				canvasRadioactive = canvas.create_image((offset1 + int(i[0])*10),YposBridge2A + 15, anchor=NW, image=radioactiveCar)
				offset1 = offset1 +15
		if(i[1] == "Ambulance"):
			if(i[2] == "left"):
				canvasRadioactive = canvas.create_image((offset2 - int(i[0])*10),YposBridge2A + 15, anchor=NW, image=ambulance)
				offset2 = offset2 -15
			if(i[2] == "right"):
				canvasRadioactive = canvas.create_image((offset1 + int(i[0])*10),YposBridge2A + 15, anchor=NW, image=ambulance) 
				offset1 = offset1 +15
		if(i[1] == "normalCar"):
			if(i[2] == "left"):
				canvasRadioactive = canvas.create_image((offset2 - int(i[0])*10),YposBridge2A + 15, anchor=NW, image=normalCar)
				offset2 = offset2 -15
			if(i[2] == "right"):
				canvasRadioactive = canvas.create_image((offset1 + int(i[0])*10),YposBridge2A + 15, anchor=NW, image=normalCar)
				offset1 = offset1 +15

def drawCarsOnBridge3(matriz):
	offset1 = XposBridge1 #where the bridge ends
	offset2 = XposBridge2
	for i in matriz: 
		if(i[1] == "Radioactive"):
			if(i[2] == "left"):
				canvasRadioactive = canvas.create_image((offset2 - int(i[0])*10),YposBridge3A + 15, anchor=NW, image=radioactiveCar)
				offset2 = offset2 -15
			if(i[2] == "right"):
				canvasRadioactive = canvas.create_image((offset1 + int(i[0])*10),YposBridge3A + 15, anchor=NW, image=radioactiveCar)
				offset1 = offset1 +15
		if(i[1] == "Ambulance"):
			if(i[2] == "left"):
				canvasRadioactive = canvas.create_image((offset2 - int(i[0])*10),YposBridge3A + 15, anchor=NW, image=ambulance)
				offset2 = offset2 -15
			if(i[2] == "right"):
				canvasRadioactive = canvas.create_image((offset1 + int(i[0])*10),YposBridge3A + 15, anchor=NW, image=ambulance) 
				offset1 = offset1 +15
		if(i[1] == "normalCar"):
			if(i[2] == "left"):
				canvasRadioactive = canvas.create_image((offset2 - int(i[0])*10),YposBridge3A + 15, anchor=NW, image=normalCar)
				offset2 = offset2 -15
			if(i[2] == "right"):
				canvasRadioactive = canvas.create_image((offset1 + int(i[0])*10),YposBridge3A + 15, anchor=NW, image=normalCar)
				offset1 = offset1 +15

#Thread manager functions
#----------------------------------------------------------------------------------------------------------------------------------
def threadWork(listFeatureThread,lista):
	lista.append(listFeatureThread)
	print(matQueueLB1)
	
def threadsUpdate(newPos, ID,lista):
	for element in lista:
		if (element[2] ==ID):
			element[0] = newPos
			print (ID)

def isID(element,matrix,indexID):
	for i in matrix:
		if (element == i[indexID]):
			return True
	return False
	
#----------------------------------------------------------------------------------------------------------------------------------			
def initDraw():
	canvas.create_line(350, YposBridge1A, 850, YposBridge1A, width=4, fill='blue')
	canvas.create_line(350, YposBridge1B, 850, YposBridge1B, width=4, fill='blue')
	canvas.create_line(350, YposBridge2A, 850, YposBridge2A, width=4, fill='orange')
	canvas.create_line(350, YposBridge2B, 850, YposBridge2B, width=4, fill='orange')
	canvas.create_line(350, YposBridge3A, 850, YposBridge3A, width=4, fill='purple')
	canvas.create_line(350, YposBridge3B, 850, YposBridge3B, width=4, fill='purple')


oldMatrix1 = []
oldMatrix2 = []
oldMatrix3 = []
oldMatrix4 = []
oldMatrix5 = []
oldMatrix6 = []
oldMatrix7 = []
oldMatrix8 = []
oldMatrix9 = []
threadsQLB1 = []
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
		newMatrix1 = matrizCarsOnBridge1
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
		newMatrix2 = matrizCarsOnBridge2
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
		newMatrix3 = matrizCarsOnBridge3
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
		newMatrix4 = matrizQueueLB1
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
		newMatrix5 = matrizQueueRB1
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
		newMatrix6 = matrizQueueLB2
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
		newMatrix7 = matrizQueueRB2
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
		newMatrix8 = matrizQueueLB3
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
		newMatrix9 = matrizQueueRB3
		
	if(newMatrix1 != oldMatrix1):
		rectangle7 = canvas.create_rectangle(XposBridge1,YposBridge1A+10,XposBridge2,YposBridge1A+40,fill="white",width=0)
		oldMatrix1 = newMatrix1
	if(newMatrix2 != oldMatrix2):
		rectangle8 = canvas.create_rectangle(XposBridge1,YposBridge2A+10,XposBridge2,YposBridge2A+40,fill="white",width=0)
		oldMatrix2 = newMatrix2
	if(newMatrix3 != oldMatrix3):
		rectangle9 = canvas.create_rectangle(XposBridge1,YposBridge3A+10,XposBridge2,YposBridge3A+40,fill="white",width=0)
		oldMatrix3 = newMatrix3
		
	if(newMatrix4 != oldMatrix4): 
		if(len(newMatrix4) < len(oldMatrix4)):
			if(newMatrix4 == []):
				oldMatrix4 = newMatrix4
				matQueueLB1 = []
				oldMatrix4 = newMatrix4
			else:
				for element in oldMatrix4:
					if(not(isID(element[2], newMatrix4,2))):
						for ele in matQueueLB1:
							if (ele[2] == element[2]):
								matQueueLB1.remove(ele)
				oldMatrix4 = newMatrix4
		else:
			for element in newMatrix4: 
				if(not(isID(element[2], oldMatrix4,2))):  ## here is going to be added a thread
					ThreadFeatures = [element[0], element[1],element[2]]
					thread = Thread(target=threadWork,args = (ThreadFeatures,matQueueLB1 ))
					thread.start()
					thread.join()
				else:
					threadsUpdate(element[0],element[2],matQueueLB1) ##just need to update the position
			print(matQueueLB1)
			oldMatrix4 = newMatrix4
	if(newMatrix5 != oldMatrix5):
		
		if(len(newMatrix5) < len(oldMatrix5)):
			if(newMatrix5 == []):
				oldMatrix5 = newMatrix5
				matQueueRB1 = []
				oldMatrix5 = newMatrix5
			else:
				for element in oldMatrix5:
					if(not(isID(element[2], newMatrix5,2))):
						for ele in matQueueRB1:
							if (ele[2] == element[2]):
								matQueueRB1.remove(ele)
				oldMatrix5 = newMatrix5
		else:
			for element in newMatrix5: 
				if(not(isID(element[2], oldMatrix5,2))):  ## here is going to be added a thread
					ThreadFeatures = [element[0], element[1],element[2]]
					thread = Thread(target=threadWork,args = (ThreadFeatures,matQueueRB1))
					thread.start()
					thread.join()
				else:
					threadsUpdate(element[0],element[2],matQueueRB1) ##just need to update the position
			oldMatrix5 = newMatrix5
	if(newMatrix6 != oldMatrix6):
		if(len(newMatrix6) < len(oldMatrix6)):
			if(newMatrix6 == []):
				oldMatrix6 = newMatrix6
				matQueueLB2 = []
				oldMatrix6 = newMatrix6
			else:
				for element in oldMatrix6:
					if(not(isID(element[2], newMatrix6,2))):
						for ele in matQueueLB2:
							if (ele[2] == element[2]):
								matQueueLB2.remove(ele)
				oldMatrix6 = newMatrix6
		else:
			for element in newMatrix6: 
				if(not(isID(element[2], oldMatrix6,2))):  ## here is going to be added a thread
					ThreadFeatures = [element[0], element[1],element[2]]
					thread = Thread(target=threadWork,args = (ThreadFeatures,matQueueLB2 ))
					thread.start()
					thread.join()
				else:
					threadsUpdate(element[0],element[2],matQueueLB2) ##just need to update the position
			oldMatrix6 = newMatrix6
	if(newMatrix7 != oldMatrix7):
		if(len(newMatrix7) < len(oldMatrix7)):
			if(newMatrix7 == []):
				oldMatrix7 = newMatrix7
				matQueueRB2 = []
				oldMatrix7 = newMatrix7
			else:
				for element in oldMatrix7:
					if(not(isID(element[2], newMatrix7,2))):
						for ele in matQueueRB2:
							if (ele[2] == element[2]):
								matQueueRB2.remove(ele)
				oldMatrix7 = newMatrix7
		else:
			for element in newMatrix7: 
				if(not(isID(element[2], oldMatrix7,2))):  ## here is going to be added a thread
					ThreadFeatures = [element[0], element[1],element[2]]
					thread = Thread(target=threadWork,args = (ThreadFeatures,matQueueRB2 ))
					thread.start()
					thread.join()
				else:
					threadsUpdate(element[0],element[2],matQueueRB2) ##just need to update the position
			oldMatrix7 = newMatrix7
	if(newMatrix8 != oldMatrix8):
		
		if(len(newMatrix8) < len(oldMatrix8)):
			if(newMatrix8 == []):
				oldMatrix8 = newMatrix8
				matQueueLB3 = []
				oldMatrix8 = newMatrix8
			else:
				for element in oldMatrix8:
					if(not(isID(element[2], newMatrix8,2))):
						for ele in matQueueLB3:
							if (ele[2] == element[2]):
								matQueueLB3.remove(ele)
				oldMatrix8 = newMatrix8
		else:
			for element in newMatrix8: 
				if(not(isID(element[2], oldMatrix8,2))):  ## here is going to be added a thread
					ThreadFeatures = [element[0], element[1],element[2]]
					thread = Thread(target=threadWork,args = (ThreadFeatures,matQueueLB3 ))
					thread.start()
					thread.join()
				else:
					threadsUpdate(element[0],element[2],matQueueLB3) ##just need to update the position
			oldMatrix8 = newMatrix8
	if(newMatrix9 != oldMatrix9):
		if(len(newMatrix9) < len(oldMatrix9)):
			if(newMatrix9 == []):
				oldMatrix9 = newMatrix9
				matQueueRB3 = []
				oldMatrix9 = newMatrix9
			else:
				for element in oldMatrix9:
					if(not(isID(element[2], newMatrix9,2))):
						for ele in matQueueRB3:
							if (ele[2] == element[2]):
								matQueueRB3.remove(ele)
				oldMatrix9 = newMatrix9
		else:
			for element in newMatrix9: 
				if(not(isID(element[2], oldMatrix9,2))):  ## here is going to be added a thread
					ThreadFeatures = [element[0], element[1],element[2]]
					thread = Thread(target=threadWork,args = (ThreadFeatures,matQueueRB3 ))
					thread.start()
					thread.join()
				else:
					threadsUpdate(element[0],element[2],matQueueRB3) ##just need to update the position
			print(matQueueLB1)
			oldMatrix9 = newMatrix9
		
	rectangle4 = canvas.create_rectangle(XposBridge2,YposBridge2A,1450,YposBridge2A+50,fill="white",width=0)
	rectangle6 = canvas.create_rectangle(XposBridge2,YposBridge3A,1450,YposBridge3A+50,fill="white",width=0)
	rectangle1 = canvas.create_rectangle(-1450,YposBridge1A,XposBridge1,YposBridge1A+50,fill="white",width=0)	
	rectangle5 = canvas.create_rectangle(-1450,YposBridge3A,XposBridge1,YposBridge3A+50,fill="white",width=0)	
	rectangle3 = canvas.create_rectangle(-1450,YposBridge2A,XposBridge1,YposBridge2A+50,fill="white",width=0)
	rectangle2 = canvas.create_rectangle(XposBridge2,YposBridge1A,1450,YposBridge1A+50,fill="white",width=0)
	###QUede aqui hay qye ver como se hace con los hilos
	drawPaintQLB1(matQueueLB1)
	drawPaintQLB2(matQueueLB2)
	drawPaintQLB3(matQueueLB3)
	drawPaintQRB1(matQueueRB1)
	drawPaintQRB2(matQueueRB2)
	drawPaintQRB3(matQueueRB3)
	drawCarsOnBridge1(matrizCarsOnBridge1)
	drawCarsOnBridge2(matrizCarsOnBridge2)
	drawCarsOnBridge3(matrizCarsOnBridge3)
	time.sleep(0.01)
	tk.update()
	

