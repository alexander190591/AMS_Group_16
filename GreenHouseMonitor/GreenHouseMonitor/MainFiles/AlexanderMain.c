/*
 * AlexanderMain.c
 *
 * Created: 26-03-2020 08:43:21
 *  Author: Alexander
 */ 

#include "MainFiles.h"
#include "../SoilHumiditySensor/include/SoilHumiditySensor.h"
#include "../UART/include/uart.h"

void AlexanderMain()
{
	// Uart for testing, copied form Henning's MSYS-class.
	InitUART(9600, 1, 0);
	
	struct SoilHumiditySensor mySoilHumiditySensor = {0,0,0,setUp, analogRead, setHumidityInPercent}; // Initializing the "object" of type SoilHumiditySensor called mySoilHumiditySensor.
	mySoilHumiditySensor->setUp(&mySoilHumiditySensor, 0);	// Setting up soil humidity sensor with ADC pin 0 on the ATMega2560.	
	
	/* Replace with your application code */
	while (1)
	{
		mySoilHumiditySensor->analogRead(&mySoilHumiditySensor);	// Reading value, setting it in struct.
		
		SendInteger(mySoilHumiditySensor->_humidityValue);
	}
}