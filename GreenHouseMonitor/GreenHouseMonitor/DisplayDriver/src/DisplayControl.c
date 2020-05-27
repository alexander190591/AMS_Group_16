/*
 * DisplayData.c
 *
 * Created: 16-04-2020 08:51:39
 *  Author: Sebastian Folsach
 */ 




#include "../include/DisplayControl.h"
#include "../include/Characters.h"
#include <string.h>


//////////////////////////////
//							//
//	   Private variables	//
//							//
//////////////////////////////

// Window boarder coordinates:
unsigned int windowLeftx = 0;
unsigned int windowRightx = 160;
unsigned int windowHighy = 0;
unsigned int windowLowy = 80;

// Earth Humidity borders:
unsigned int earthLeftx = 0;
unsigned int earthRightx = 160;
unsigned int earthHighy = 80;
unsigned int earthLowy = 160;

// Temperature borders:
unsigned int tempLeftx = 0;
unsigned int tempRightx = 160;
unsigned int tempHighy = 160;
unsigned int tempLowy = 240;

// Window adjust variables:
unsigned int adjustDownX0 = 0;
unsigned int adjustDownX1 = 80;
unsigned int adjustDownY0 = 0;
unsigned int adjustDownY1 = 80;

unsigned int adjustUpX0 = 80;
unsigned int adjustUpX1 = 160;
unsigned int adjustUpY0 = 0;
unsigned int adjustUpY1 = 80;

unsigned int windowInc = 0;
 

// Window flag:
unsigned int windowFlag = 0;

// Earth Humidity flag:
unsigned int earthFlag = 0;


//////////////////////////////////
//								//
//		Private functions		//
//								//
//////////////////////////////////

unsigned int writeBigeA(unsigned int Xstart,unsigned int Ystart){
	FillRectangle(Xstart+3,Ystart+1,8,3,0,0,0);
	
	FillRectangle(Xstart+2,Ystart+5,3,3,0,0,0);
	FillRectangle(Xstart+9,Ystart+5,3,3,0,0,0);
	
	FillRectangle(Xstart,Ystart+9,3,3,0,0,0);
	FillRectangle(Xstart+11,Ystart+9,3,3,0,0,0);
	
	FillRectangle(Xstart,Ystart+13,3,3,0,0,0);
	FillRectangle(Xstart+11,Ystart+13,3,3,0,0,0);
	
	//FillRectangle(Xstart,Ystart+16,3,3,0,0,0);
	//FillRectangle(Xstart+11,Ystart+16,3,3,0,0,0);
	
	FillRectangle(Xstart,Ystart+16,17,3,0,0,0);
	
	FillRectangle(Xstart,Ystart+19,3,3,0,0,0);
	FillRectangle(Xstart+11,Ystart+19,3,3,0,0,0);
	
	FillRectangle(Xstart,Ystart+22,3,3,0,0,0);
	FillRectangle(Xstart+11,Ystart+22,3,3,0,0,0);
	
	return Xstart+8;
}

unsigned int writeLittleA(unsigned int Xstart,unsigned int Ystart){
	FillRectangle(Xstart+3,Ystart+6,9,3,0,0,0);
	
	FillRectangle(Xstart+1,Ystart+10,3,3,0,0,0);
	FillRectangle(Xstart+11,Ystart+10,3,3,0,0,0);
	
	FillRectangle(Xstart+6,Ystart+14,9,3,0,0,0);
	
	FillRectangle(Xstart+3,Ystart+17,3,3,0,0,0);
	FillRectangle(Xstart+11,Ystart+17,3,3,0,0,0);
	
	FillRectangle(Xstart+1,Ystart+20,3,3,0,0,0);
	FillRectangle(Xstart+11,Ystart+20,3,3,0,0,0);
	
	FillRectangle(Xstart+4,Ystart+23,9,3,0,0,0);
	FillRectangle(Xstart+12,Ystart+23,3,3,0,0,0);
	
	return Xstart+10;
}

unsigned int writeLittleI(unsigned int Xstart,unsigned int Ystart){
	FillRectangle(Xstart+3,Ystart+2,4,4,0,0,0);
	FillRectangle(Xstart+3,Ystart+8,3,18,0,0,0);
	
	return Xstart+2;
	
}

unsigned int writeLittleN(unsigned int Xstart,unsigned int Ystart){
	FillRectangle(Xstart+3,Ystart+6,12,3,0,0,0);
	
	FillRectangle(Xstart+3,Ystart+10,3,16,0,0,0);
	
	FillRectangle(Xstart+12,Ystart+10,4,4,3,0,0);
	
	FillRectangle(Xstart+13,Ystart+14,3,12,3,0,0);
	
	return Xstart+11;
	
}

unsigned int writeBigW(unsigned int Xstart,unsigned int Ystart){
	FillRectangle(Xstart,Ystart+1,3,20,0,0,0);
	FillRectangle(Xstart+15,Ystart+1,3,19,0,0,0);
	FillRectangle(Xstart+8,Ystart+13,2,8,0,0,0);
	
	FillRectangle(Xstart+3,Ystart+20,4,3,0,0,0);
	FillRectangle(Xstart+12,Ystart+20,4,3,0,0,0);
	
	FillRectangle(Xstart+8,Ystart+20,3,3,0,0,0);
	
	FillRectangle(Xstart+4,Ystart+24,4,3,0,0,0);
	FillRectangle(Xstart+11,Ystart+24,4,3,0,0,0);
	
	return Xstart+10;
}


/*
void windowChange(){
	FillRectangle(windowLeftx,windowHighy,windowRightx,windowLowy,0,60,0);
}
*/

unsigned int writeLetter(char letter, unsigned int startX, unsigned int startY){
	switch (letter)
	{
		case 65:
			//FillRectangle(startX, startY, )
		return writeBigeA(startX, startY);
		break;
		case 87:
		return writeBigW(startX,startY);
		break;
		case 97:
		return writeLittleA(startX,startY);
		break;
		case 105:
		return writeLittleI(startX,startY);
		break;
		case 110:
		return writeLittleN(startX,startY);
		break;
		
	}
}

void writeLine(char* sentence, unsigned int startX, unsigned int startY){
	
	/*unsigned int spacing = 0;
	for(int i = 0; i<strlen(sentence); i++){
		spacing = writeLetter(sentence[i],(startX+16*i),startY);
	}*/
		
	unsigned int spacing = 0;
	
	SetColumnAddress(startY, startY+15);
	SetPageAddress(startX, startX+(strlen(sentence)*16));
	MemoryWrite();
	

	
	for(int i = 0; i<strlen(sentence); i++){
		
		//Skal fetche Character
		char* wrtChar = getWriteChar(*(sentence+i));

		for(int j = 0; j<32; j++){
			for (int k = 0; k<8; k++)
			{
				if(!(((*(wrtChar+j))<<k)&0x80))
					WritePixel(31,63,31);
				else
					WritePixel(0,0,0);	
			}	
		}	
	}
}



//////////////////////////////
//							//
//		Public functions	//
//							//
//////////////////////////////

void updateWindowDisplay(char* arr){
	writeLine("soil:", 20, 20);
	FillRectangle(180, 20, 200, 16, 31, 63, 31);
	writeLine(arr, 180, 20);
}

void updateEarthHumidDisplay(char* arr){
	writeLine("soil:", 20, 20);
	writeLine(arr, 180, 20);
}

void updateTemperaturDisplay(char* arr){
	writeLine("temp:", 20, 50);
	writeLine(arr, 180, 50);
}

void updateAirHumidDisplay(char* arr){
	writeLine("humid:", 20, 80);
	writeLine(arr, 180, 80);
}












