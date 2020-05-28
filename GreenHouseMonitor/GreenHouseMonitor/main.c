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
#include "MainFiles/MainFiles.h"
#include "TouchDisplay/include/TouchDriver.h"
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <avr/interrupt.h>

#include "ButtonDriver/include/ButtonDriver.h"
#include "StepperDriver/include/StepperDriver.h"

#ifdef UART_USED
	#include "UART/include/uart.h"
#endif

#include "MainFiles/MainFiles.h"													// Used for seperate main files for every group member

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
		//
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
//
	struct SoilHumiditySensor mySoilHumiditySensor = {0, 0, 0, setUpSoilHumiditySensor, analogRead, getHumidityInPercent};
	mySoilHumiditySensor.setUpSoilHumiditySensor(&mySoilHumiditySensor, 0);
	
	sei();
	SetupTouch();
	
	updateEarthHumidDisplay(0.0);
	updateTemperaturDisplay(0.0);
	updateAirHumidDisplay(0.0);
	
	double airHumidity = 0.0;
	double airTemperature = 0.0;
	double soilHumidity = 0.0;
	
	#ifdef UART_USED
		SendString("Test: sensor setup done. \n");
	#endif UART_USED
		//
		
	StepperInit();
	
	cli();
	//CalibrateWindowOpening();
	#ifdef UART_USED
		SendString("Haj med Dej \n");
		SendInteger(maxNbrRevolutions);
		SendString("Haj med Dej \n");
		SendInteger(120);
	#endif UART_USED
	sei();
	
    while (1) 
    {
		//_delay_ms(10000);
		// Læs data
		#ifdef UART_USED
			SendString("Læs air_sensor_data.... \n");
		#endif UART_USED
		
		airHumidity = myAirSensorPtr->readHumidity(myAirSensorPtr);
		airTemperature = myAirSensorPtr->readTemperature(myAirSensorPtr);
		//
		#ifdef UART_USED
			SendString("Læs soil sensordata.... \n");
		#endif UART_USED
		//
		int analogSoilHumidity = mySoilHumiditySensor.analogRead(&mySoilHumiditySensor);
		//
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
		
		// Gem data på SD-kort
		
		// Sæt data i bestemte dele af skærmen
		// Creating string with air temperature
		
		
		// Create string with humidity value
		//strcpy(humidityArray, humidityChar);
		//strcat(humidityArray, "rh");
		
		updateEarthHumidDisplay(soilHumidity);
		updateTemperaturDisplay(airTemperature);
		updateAirHumidDisplay(airHumidity);
		
		// Vent 10 sekunder
		_delay_ms(2000);
    } // End of while(1)
} // End of Main()


ISR(AIRSENSOR_INTVECT) // Interrupt on any edge
{
	uint8_t pinState = (PIND & (1 << AIRSENSOR_PIN));
	
	switch(pinState)
	{
		case 0:	// If signal just went low, compute time of high signal.
		myAirSensorPtr->timerStop(myAirSensorPtr);									// Stops timer.
		
		if(myAirSensorPtr->_responseSignalReceived)									// Checks if the response signal has been received. If it has, the falling edge is from a bit.
		{
			// Calculating the next bit to set:
			myAirSensorPtr->_byteNumber = (myAirSensorPtr->_dataBitCounter) / 8;	// Finds the byte number currently worked on.
			myAirSensorPtr->_bitNumber = (myAirSensorPtr->_dataBitCounter) % 8;		// Finds the bit number to be set in this interrupt.
			
			if(myAirSensorPtr->_microseconds > 40)									// If length of signal is more than 40 us, bit == 1.
			{
				myAirSensorPtr->_sensorData[myAirSensorPtr->_byteNumber] = (myAirSensorPtr->_sensorData[myAirSensorPtr->_byteNumber] << 1) | 1;	// Shift the entire byte once and set the new bit 0 to 1.
				myAirSensorPtr->_dataBitCounter++;									// Increment the bit counter.
			}
			else if(myAirSensorPtr->_microseconds <= 40)							// If length of signal is less than 35, bit == 0.
			{
				myAirSensorPtr->_sensorData[myAirSensorPtr->_byteNumber] = (myAirSensorPtr->_sensorData[myAirSensorPtr->_byteNumber] << 1);	// Shift the entire byte once. The new bit is a 0.
				myAirSensorPtr->_dataBitCounter++;									// Increment the bit counter.
			}
			
			if(myAirSensorPtr->_dataBitCounter >= 40)								// If all 40 bits have been received,
			{
				myAirSensorPtr->_newDataAvailable = 1;								// Notify getValues() that all data is received.
				myAirSensorPtr->_dataBitCounter = 0;								// Reset the _dataBitCounter for next set of data.
				myAirSensorPtr->_responseSignalReceived = 0;						// Reset the _responseSignalReceived for the next set of data.
			}
		} // End if(responseSignalReceived
		
		// Checking if the signal received is the response signal:
		if(75 <= myAirSensorPtr->_microseconds && myAirSensorPtr->_microseconds <= 100)	// Response signal should be 80 microseconds.
		{
			myAirSensorPtr->_responseSignalReceived = 1;							// Set the flag to notify that the response signal has been received.
		}
		break; // End of Case: LOW
		default:																	// If signal is anything other than low after 'any edge', it must be HIGH:
		myAirSensorPtr->timerStart(myAirSensorPtr);									// Clears _microseconds and stars the timer.
		break; // End of Case: HIGH (Any other than low)
	} // End of switch()
} // End of ISR(AIRSENSOR_INTVECT)

ISR(AIRSENSOR_COMPAVECT)															// Interrupt for when 18 ms start signal from MCU has been sent to DHT11.
{
// Make Digital line input with pull-up resistor:
AIRSENSOR_DDR &= ~(1 << AIRSENSOR_PIN);											// Set pin as input.
AIRSENSOR_PORT |= (1 << AIRSENSOR_PIN);											// Pull-up resistor (make the signal go HIGH while listening).

AIRSENSOR_TCNT = 0;																// Clearing the counter.
AIRSENSOR_TCCRB &= ~(1 << AIRSENSOR_WGM2);										// Clearing the mode.

myAirSensorPtr->timerStart(myAirSensorPtr);										// Starts timer as data request is done. Used to look for response signal (80us).

} // End of ISR(AIRSENSOR_COMPAVECT)