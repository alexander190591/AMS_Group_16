/*
 * DHT11.h
 *
 * Created: 23-04-2020 10:42:59
 *  Author: Alexander
 */ 
#include <avr/io.h>
#include <avr/interrupt.h>

#ifndef DHT11_H_
#define DHT11_H_

struct AirSensor
{
	double _temperature;											// Variable for storing temperature value when calling getValues()-method.
	double _humidity;												// Variable for storing humidity value when calling getValues()-method.
	int _microseconds;												// Variable for storing microseconds for the timer.
	int _dataBitCounter;											// Variable for counting amount of data collected.
	int _newDataAvailable;											// Set when reading data from DHT11 is done.
	uint8_t _sensorData[5];											// Variable for collecting sensor data. Bytes describe: RH integral, RH decimal, T integral (celcius), T decimal (celcius), Checksum.
	void (*setUpAirSensor)(struct AirSensor*);						// Function pointer for setUpAirSensor 'method'.
	double (*readTemperature)(struct AirSensor*);					// Function pointer for readTemperature 'method'.
	double (*readHumidity)(struct AirSensor*);						// Function pointer for readHumidity 'method'.
	void (*getValues)(struct AirSensor*);							// Function pointer for getValues 'method'.
	void (*stopWatchSetup)(struct AirSensor*);						// Function pointer for stopWatchSetup 'method'.
	void (*stopWatchStart)(struct AirSensor*, uint16_t microseconds);	// Function pointer for stopWatchStart 'method'.
	void (*timerSetup)(struct AirSensor*);							// Function pointer for timerSetup 'method'.
	void (*timerStart)(struct AirSensor*);							// Function pointer for timerStart 'method'.
	uint16_t (*timerStop)(struct AirSensor*);						// Function pointer for timerStop 'method'.
};

void setUpAirSensor(struct AirSensor*);								// Sets up the interrupt for defined pin (defines.h) for communication with the DHT11 module.
double readTemperature(struct AirSensor*);							// Calls getValues() and returns the temperature as a double.
double readHumidity(struct AirSensor*);								// Calls getValues() and returns the humidity as a double.
void getValues(struct AirSensor*);									// Reads values from the DHT11 sensor and stores it in _temperature and _humidity.

// Private methods for one wire communication: Timer and interrupt.
void stopWatchSetup(struct AirSensor*);								// Setup method for creating a timer that creates an interrupt after microseconds parameter.
void stopWatchStart(struct AirSensor*, uint16_t microseconds);			// Starts the stop watch, counting microseconds, then interrupts.
void timerSetup(struct AirSensor*);									// Setup method for the timer used for counting microseconds.
void timerStart(struct AirSensor*);									// Starts the timer. Resets the _microseconds attribute, then starts incrementing _microseconds attribute until stopped.
uint16_t timerStop(struct AirSensor*);								// Stops the timer. Returns the value in _microseconds.

#endif /* DHT11_H_ */