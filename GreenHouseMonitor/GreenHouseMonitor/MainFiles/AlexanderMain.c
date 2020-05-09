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
	
struct AirSensor* myAirSensorPtr;													// Pointer for the AirSensor "object".

ISR(AIRSENSOR_COMPAVECT)															// Interrupt for when 18 ms start signal from MCU has been sent to DHT11.
{
	// Make Digital line input with pull-up resistor:
	AIRSENSOR_DDR &= ~(1 << AIRSENSOR_PIN);											// Set pin as input.
	AIRSENSOR_PORT |= (1 << AIRSENSOR_PIN);											// Pull-up resistor (make the signal go HIGH while listening).
	
	AIRSENSOR_TCNT = 0;																// Clearing the counter.
	AIRSENSOR_TCCRB &= ~(1 << AIRSENSOR_WGM2);										// Clearing the mode.
	
	myAirSensorPtr->timerStart(myAirSensorPtr);										// Starts timer as data request is done. Used to look for response signal (80us).
	
} // End of ISR(AIRSENSOR_COMPAVECT)

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
} // End of ISR

void AlexanderMain()
{
	sei();																			// Enables all interrupts.
	struct AirSensor myAirSensor = {0, 0, 0, 0, 0, 0, 0, 0, {0,0,0,0,0}, 
									setUpAirSensor, readTemperature, readHumidity, 
									getValues, stopWatchSetup, stopWatchStart, 
									timerSetup, timerStart, timerStop};				// Initializing the "object" of type AirSensor called myAirSensor.
	myAirSensorPtr = &myAirSensor;
	InitUART(115200, 8, 0);															// Uart for testing, copied form Henning's MSYS-class.
	
	myAirSensorPtr->setUpAirSensor(&myAirSensor);									// Setting up AirSensor: Any-edge interrupt setup, timer setup (0,5 us pr. tick).
	
	while(1)
	{
	SendString("Humidity is: ");
	SendInteger(myAirSensorPtr->readHumidity(myAirSensorPtr)); SendString("%\n");	// readHumitidy returns humidity as double, but does not contain any decimal value (,00).
	
	double myTemp = myAirSensorPtr->readTemperature(myAirSensorPtr);				// readTemperature returns temperature as double with decimal value.
	int myTempInt = myTemp;															// Splitting temperature integer from decimal to print with UART-driver.
	int myTempDec = ((double)myTemp-(double)myTempInt)*100;							// Splitting temperature decimal from integer to print with UART-driver.
	SendString("Temperature is: "); SendInteger(myTempInt); SendChar(','); SendInteger(myTempDec); SendString("degrees Celcius.\n");	// Debuggin print.
		
	_delay_ms(2000);																// DHT11 cannot send data faster than once every other second. Faster returns in no data sent.
		
	} // End of while(1)

} // End of AlexanderMain()