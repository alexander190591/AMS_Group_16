/*
 * AlexanderMain.c
 *
 * Created: 26-03-2020 08:43:21
 *  Author: Alexander
 */ 

#include "MainFiles.h"
#include "../SoilHumiditySensor/include/SoilHumiditySensor.h"
#include "../UART/include/uart.h"	// For debugging
#include "../defines.h"
#include <util/delay.h>		// Used for _delay_ms()

void AlexanderMain()
{
	// Uart for testing, copied form Henning's MSYS-class.
	InitUART(9600, 8, 0);
	
	struct SoilHumiditySensor mySoilHumiditySensor = {0,0,0,setUp, analogRead, getHumidityInPercent}; // Initializing the "object" of type SoilHumiditySensor called mySoilHumiditySensor.
	mySoilHumiditySensor.setUp(&mySoilHumiditySensor, SOILMOISTURE_PIN);	// Setting up soil humidity sensor with ADC pin 0 on the ATMega2560.	
	
	/* Replace with your application code */
	while (1)
	{
		_delay_ms(1000);
		mySoilHumiditySensor.analogRead(&mySoilHumiditySensor);	// Reading value, setting it in struct.
		SendInteger(mySoilHumiditySensor._humidityValue);
		SendString(" ADC value = ");
		SendInteger(mySoilHumiditySensor.getHumidityInPercent(&mySoilHumiditySensor));
		SendString("%\n");
	}
}