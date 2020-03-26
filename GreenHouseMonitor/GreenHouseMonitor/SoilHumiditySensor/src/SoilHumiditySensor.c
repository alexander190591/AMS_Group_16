/*
 * SoilHumiditySensor.c
 *
 * Created: 26-03-2020 09:05:25
 *  Author: Alexander
 */ 

#include "../include/SoilHumiditySensor.h"

/**
 * \brief Sets up the ADC for reading the humidity sensor on the analogPin.
 * 
 * \param analogPin is the pin number used for the soil humidity sensor.
 * 
 * \return void
 */
void SoilHumiditySensor_SetUp(unsigned char analogPin) // 
{
	ADCSRA |= 0b10000000; // Enables ADC.
	
	// ADCW will contain the ADC result. Split up into ADCH and ADCL (READ ONLY).
	// Can be read by unsigned int val = ADCW;
	
	ADCSRA &= 0b11111000; // ADC prescaler bits cleared. 
	ADCSRA |= 0b00000111; // Sets division factor to 128 to ensure 125 kHz (16MHz / 128)
	
	// Choosing reference voltage, ADMUX REFS1, REFS0 (ADMUX bit 7 and 6).
	
	// Choosing of ADC input.
	
	
}


/**
 * \brief Reads the value on the ADC set with the SoilHumiditySensor.
 * 
 * 
 * \return unsigned int Returns the value of the analog read.
 */
unsigned int SoilHumiditySensor_AnalogRead()
{
	return ADCW;
}

/**
 * \brief Returns the relative soil humidity in percentage.
 * 
 * \return double Percentage of soil humidity.
 */
double SoilHumiditySensor_GetHumidityInPercent()
{
	
}

