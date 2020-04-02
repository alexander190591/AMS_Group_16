/*
 * SoilHumiditySensor.h
 *
 * Created: 26-03-2020 09:05:12
 *  Author: Alexander
 */ 
#include <avr/io.h>

#ifndef SOILHUMIDITYSENSOR_H_
#define SOILHUMIDITYSENSOR_H_

struct SoilHumiditySensor
{
	int _humidityValue;
	unsigned char _analogPin;
	double _humidityInPercent;
	void (*setUp)(struct SoilHumiditySensor*, unsigned char analogPin);
	int (*analogRead)(struct SoilHumiditySensor*);
	double (*getHumidityInPercent)(struct SoilHumiditySensor*);
	
};

void setUp(struct SoilHumiditySensor* p, unsigned char analogPin);
int analogRead(struct SoilHumiditySensor*);
double getHumidityInPercent(struct SoilHumiditySensor*);
#endif /* SOILHUMIDITYSENSOR_H_ */