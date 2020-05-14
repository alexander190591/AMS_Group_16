/*
 * SoilHumiditySensor.h
 *
 * Created: 26-03-2020 09:05:12
 *  Author: Alexander
 */ 
#include <avr/io.h>

#ifndef SOILHUMIDITYSENSOR_H_
#define SOILHUMIDITYSENSOR_H_

#define _ValueInWater 300
#define _ValueInAir 600

struct SoilHumiditySensor
{
	int _humidityValue;																		// Integer for storing the raw humidity value (between 0 and 1023)
	unsigned char _analogPin;																// Unsigned char for storing the analog pin used for reading the sensor (0-15 for A0-A15 on Mega2560)
	double _humidityInPercent;																// Double for storing the humidity value as a percentage (0-100)
	void (*setUpSoilHumiditySensor)(struct SoilHumiditySensor*, unsigned char analogPin);	// Function pointer for setUp 'method'
	int (*analogRead)(struct SoilHumiditySensor*);											// Function pointer for analogRead 'method'
	double (*getHumidityInPercent)(struct SoilHumiditySensor*);								// Function pointer for getHumidityInPercent 'method'
};

void setUpSoilHumiditySensor(struct SoilHumiditySensor* p, unsigned char analogPin);		//  
int analogRead(struct SoilHumiditySensor*);													// 
double getHumidityInPercent(struct SoilHumiditySensor*);									// 
#endif /* SOILHUMIDITYSENSOR_H_ */