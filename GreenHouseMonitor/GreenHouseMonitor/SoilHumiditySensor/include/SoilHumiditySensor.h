/*
 * SoilHumiditySensor.h
 *
 * Created: 26-03-2020 09:05:12
 *  Author: Alexander
 */ 


#ifndef SOILHUMIDITYSENSOR_H_
#define SOILHUMIDITYSENSOR_H_

struct SoilHumiditySensor
{
	int humidityValue = 0;
	unsigned char analogPin = 0;
	double humidityInPercent = 0;
};

void SoilHumiditySensor_SetUp(unsigned char analogPin);
unsigned int SoilHumiditySensor_AnalogRead();
double SoilHumiditySensor_GetHumidityInPercent();

#endif /* SOILHUMIDITYSENSOR_H_ */