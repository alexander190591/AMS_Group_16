/*
 * DisplayData.c
 *
 * Created: 16-04-2020 08:51:39
 *  Author: Sebastian Folsach
 */ 




#include "../include/DisplayControl.h"
#include "../include/Characters.h"
#include <string.h>
#include <stdint.h>


void DisplayControlConstruct(){
	
	DisplayInit();
	FillRectangle(0,0,320,240,31,63,31);
	
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

void writeWindowBoxes(){
	//Første box
	writeLine("dwn", 10, 130+30);	
	writeLine("full", 10, 150+30);
	
	//Anden box
	writeLine("dwn", 90, 130+20);
	writeLine("10", 90, 150+20);
	writeLine("pct", 90, 170+20);	
	
	//Tredje box
	writeLine("up", 170, 130+20);	
	writeLine("10", 170, 150+20);
	writeLine("pct", 170, 170+20);	
	
	//Fjerde box
	writeLine("up", 250, 130+30);	
	writeLine("full",250, 150+30);
}

void updateEarthHumidDisplay(double earthHumid){
	uint8_t mySoilHumInt = earthHumid;
	
	char humidityArray[50];
	char humidityIntChar[5];
	
	itoa(mySoilHumInt, humidityIntChar, 10);
	strcpy(humidityArray, humidityIntChar);
	strcat(humidityArray, " rh");
	
	writeLine("soil:", 20, 20);
	FillRectangle(180, 20, 200, 16, 31, 63, 31);
	writeLine(humidityArray, 180, 20);
}

void updateTemperaturDisplay(double temp){
	uint8_t myTempInt = temp;															// Splitting temperature integer from decimal to print with UART-driver.
	uint8_t myTempDec = ((double)temp-(double)(myTempInt))*100;						// Splitting temperature decimal from integer to print with UART-driver.
	//
	char temperatureArray[50];
	char temperatureIntChar[5];
	char temperatureDecChar[5];
	
	itoa(myTempInt, temperatureIntChar, 10);
	itoa(myTempDec, temperatureDecChar, 10);
	
	// Create string with temperature value
	strcpy(temperatureArray, temperatureIntChar);
	strcat(temperatureArray, ":");
	strcat(temperatureArray, temperatureDecChar);
	strcat(temperatureArray, " deg");
	
	
	
	writeLine("temp:", 20, 50);
	FillRectangle(180, 50, 200, 16, 31, 63, 31);
	writeLine(temperatureArray, 180, 50);
}

void updateAirHumidDisplay(double humidity){
	char humidityArray[50];
	char humidityChar[5];
	
	uint8_t myAirHumidInt = humidity;
	
	itoa(myAirHumidInt, humidityChar, 10);
	strcpy(humidityArray, humidityChar);
	strcat(humidityArray, " rh");

	writeLine("humid:", 20, 80);
	FillRectangle(180, 80, 200, 16, 31, 63, 31);
	writeLine(humidityArray, 180, 80);
}












