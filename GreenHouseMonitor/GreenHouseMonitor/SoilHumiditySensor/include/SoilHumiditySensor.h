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
	int _humidityValue = 0;
	unsigned char _analogPin = 0;
	double _humidityInPercent = 0;
	void (*setUp)(const struct SoilHumiditySensor*, unsigned char analogPin);
	void (*analogRead)(const struct SoilHumiditySensor*);
	void (*getHumidityInPercent)(const struct SoilHumiditySensor*);
	
};

void setUp(const struct SoilHumiditySensor* p, unsigned char analogPin);
void analogRead(const struct SoilHumiditySensor*);
void setHumidityInPercent(const struct SoilHumiditySensor*);
#endif /* SOILHUMIDITYSENSOR_H_ */