/*
 * GreenHouseMonitor.c
 *
 * Created: 26-03-2020 08:33:42
 * Author : Alexander
 */ 

#define UART_USED	// This will insert all UART-code in main() below if defined.

#include <avr/io.h>
#include "defines.h"
#include "DHT11/include/DHT11.h"
#include "SoilHumiditySensor/include/SoilHumiditySensor.h"
#include <util/delay.h>// Used for _delay_ms()

#ifdef UART_USED
	#include "UART/include/uart.h"
#endif

//#include "MainFiles/MainFiles.h"													// Used for seperate main files for every group member

struct AirSensor* myAirSensorPtr;													// Pointer for the AirSensor "object".

int main(void)
{
////// Group member mains called here. Only one should be called at any time:
//	AlexanderMain();																	
// 	SebastianMain();
//	TonniMain();

	#ifdef UART_USED
		InitUART(115200, 8, 0);															// Uart for testing, copied form Henning's MSYS-class.
	#endif UART_USED
		
	sei();																			// Enables all interrupts.
	
// Air sensor (Relative humidity and temperature)
	#ifdef UART_USED
		SendString("Test: Set up Air sensor... \n");
	#endif UART_USED

	struct AirSensor myAirSensor = {0, 0, 0, 0, 0, 0, 0, 0, {0,0,0,0,0},
									setUpAirSensor, readTemperature, readHumidity,
									getValues, stopWatchSetup, stopWatchStart,
									timerSetup, timerStart, timerStop};				// Initializing the "object" of type AirSensor called myAirSensor.
	myAirSensorPtr = &myAirSensor;													// Stores the address of the AirSensor for use in the ISRs
	myAirSensorPtr->setUpAirSensor(&myAirSensor);									// Setting up AirSensor: Any-edge interrupt setup, timer setup (0,5 us pr. tick).
	

// Soil sensor (Humidity in percent)
	#ifdef UART_USED
		SendString("Test: Set up soil sensor... \n");
	#endif UART_USED

	struct SoilHumiditySensor mySoilHumiditySensor = {0, 0, 0, setUpSoilHumiditySensor, analogRead, getHumidityInPercent};
	mySoilHumiditySensor.setUpSoilHumiditySensor(&mySoilHumiditySensor, 0);
	
	double airHumidity = 0.0;
	double airTemperature = 0.0;
	double soilHumidity = 0.0;
	
	#ifdef UART_USED
		SendString("Test: sensor setup done. \n");
	#endif UART_USED
		
	// Init sensor x2
	// Init sk�rm
	// Init motor
	// Init SD-driver

    while (1) 
    {
		// L�s data
		#ifdef UART_USED
			SendString("L�s air_sensor_data.... \n");
		#endif UART_USED
		
		airHumidity = myAirSensorPtr->readHumidity(myAirSensorPtr);
		airTemperature = myAirSensorPtr->readTemperature(myAirSensorPtr);
		
		#ifdef UART_USED
			SendString("L�s soil sensordata.... \n");
		#endif UART_USED
		
		int analogSoilHumidity = mySoilHumiditySensor.analogRead(&mySoilHumiditySensor);
		
		#ifdef UART_USED
			SendString("Analog soil value: "); SendInteger(analogSoilHumidity); SendChar('\n');
		#endif
		
		soilHumidity = mySoilHumiditySensor.getHumidityInPercent(&mySoilHumiditySensor);
		
		#ifdef UART_USED
			// DEBUGGING:
			int myTempInt = airTemperature;															// Splitting temperature integer from decimal to print with UART-driver.
			int myTempDec = ((double)airTemperature-(double)myTempInt)*100;							// Splitting temperature decimal from integer to print with UART-driver.
			
			SendString("Temperature is: "); SendInteger(myTempInt); SendChar(','); SendInteger(myTempDec); SendString("degrees Celcius.\n");	// Debuggin print.
			
			SendString("Humidity is: ");
			SendInteger(airHumidity); SendString("%\n");	// readHumitidy returns humidity as double, but does not contain any decimal value (,00).
			
			SendString("Soil Humidity is: "); SendInteger(soilHumidity); SendString("%.\n");
		#endif UART_USED
		
		// Gem data p� SD-kort
		
		// S�t data i bestemte dele af sk�rmen
		
		// Vent 10 sekunder
		_delay_ms(2000);
    } // End of while(1)
} // End of Main()

