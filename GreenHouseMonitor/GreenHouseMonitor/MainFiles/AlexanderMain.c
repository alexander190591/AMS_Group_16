/*
 * AlexanderMain.c
 *
 * Created: 26-03-2020 08:43:21
 *  Author: Alexander
 */ 

#include "MainFiles.h"
#include "../SoilHumiditySensor/include/SoilHumiditySensor.h"
#include "../DHT11/include/DHT11.h"
#include "../UART/include/uart.h"	// For debugging
#include "../defines.h"
#include <util/delay.h>		// Used for _delay_ms()

void AlexanderMain()
{
	sei();													// Enables all interrupts.
	
	// Uart for testing, copied form Henning's MSYS-class.
	InitUART(9600, 8, 0);
	SendString("UART started."); SendChar('\n');
	
	// // S O I L   S E N S O R   T E S T
	//struct SoilHumiditySensor mySoilHumiditySensor = {0,0,0, setUpSoilHumiditySensor, analogRead, getHumidityInPercent}; // Initializing the "object" of type SoilHumiditySensor called mySoilHumiditySensor.
	//mySoilHumiditySensor.setUpSoilHumiditySensor(&mySoilHumiditySensor, SOILMOISTURE_PIN);	// Setting up soil humidity sensor with ADC pin 0 on the ATMega2560.	
	//
	///* Replace with your application code */
	//while (1)
	//{
		//_delay_ms(1000);
		//mySoilHumiditySensor.analogRead(&mySoilHumiditySensor);	// Reading value, setting it in struct.
		//SendInteger(mySoilHumiditySensor._humidityValue);
		//SendString(" ADC value = ");
		//SendInteger(mySoilHumiditySensor.getHumidityInPercent(&mySoilHumiditySensor));
		//SendString("%\n");
	//}
	
	// A I R   S E N S O R   T E S T
	struct AirSensor myAirSensor = {0, 0, 0, setUpAirSensor, readTemperature, readHumidity, getValues, stopWatchSetup, stopWatchStart, timerSetup, timerStart, timerStop}; // Initializing the "object" of type AirSensor called myAirSensor.
	SendString("myAirSensor initiated."); SendChar('\n');
	
	SendString("setUpAirSensor called..."); SendChar('\n');
	myAirSensor.setUpAirSensor(&myAirSensor);
	SendString("setUpAirSensor DONE."); SendChar('\n');
	
	// CLASS METHOD TEST
		//myAirSensor.setUpAirSensor(&myAirSensor);
		//SendString("setUpAirSensor() done"); SendChar('\n');
		//int tempInt = 0;
		//int tempDec = 0;
		//int humidInt = 0;
		//int humidDec = 0;
		//
		//while(1)
		//{
			//SendString("Entered while(1)...");  SendChar('\n');
			//_delay_ms(2000);
			//myAirSensor.getValues(&myAirSensor);
			//
			//// Temperature test:
			//tempInt = myAirSensor.readTemperature(&myAirSensor);
			//tempDec = ((myAirSensor.readTemperature(&myAirSensor))*100-(tempInt*100));
			//SendString("Temperature value: ");
			//SendInteger(tempInt);
			//SendChar('.');
			//SendInteger(tempDec);
			//SendChar('\n');
			//
			//humidInt = myAirSensor.readHumidity(&myAirSensor);
			//humidDec = ((myAirSensor.readHumidity(&myAirSensor))*100-(humidInt*100));
			//SendString("Humidity value: ");
			//SendInteger(humidInt);
			//SendChar('.');
			//SendInteger(humidDec);
			//SendChar('\n');
		//} // End of while(1)
		
	// TIMER TESTS
		int timeInMicroseconds;
		SendString("Timer initiated."); SendChar('\n');
	
		while(1)
		{
		// Testing if stopWatch to see if it counts 16000 microseconds, then creates interrupt.
			//SendString("stopWatchSetup() called..."); SendChar('\n');
			//myAirSensor.stopWatchSetup(&myAirSensor);
			//SendString("stopWatchStart() called...."); SendChar('\n');
			//myAirSensor.stopWatchStart(&myAirSensor,18000);
			//_delay_ms(1000);	
			
			
		// Testing timer to see if it counts 1000 microseconds in a millisecond:
			//SendString("Starting timer."); SendChar('\n');
			//myAirSensor.timerStart(&myAirSensor);
			//_delay_ms(1);
			//timeInMicroseconds = myAirSensor.timerStop(&myAirSensor);
			//SendString("Timer: Microseconds after a millisecond: "); SendChar('\n');
			//SendInteger(timeInMicroseconds);
			//SendChar('\n');
			//SendChar('\n');
			//SendChar('\n');
		
		// Testing if getValues can use stopWatchStart()......
		myAirSensor.getValues(&myAirSensor);
		
		_delay_ms(1000);
			
		} // End of while(1)
		
		
} // End of AlexanderMain()