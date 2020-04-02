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

void setUp(const struct SoilHumiditySensor* p, unsigned char analogPin)
{
	p->_analogPin = analogPin;	// Setting structs variable (like attribute in class)
	// ADC, Mega2560 Datasheet p. 268 ->
	
	// ADCSRA, Mega2560 Datasheet p. 285
	ADCSRA	= 0b00000000; // Clearing all bits.
	ADCSRA |= (1<<ADEN); // Enables ADC: ADEN bit.
	ADCSRA |= 0b00000111; // Sets division factor to 128 to ensure 125 kHz (16MHz / 128) (ADC Prescaler Select Bits ADPS2:ADPS1).
	
	// ADMUX, Mega2560 Datasheet p. 281-282.
	// Choosing internal 5V reference voltage ADMUX REFS1, REFS0 (ADMUX bit 7 and 6) == 0b10.
	// Right adjusted == ADLAR (ADMUX but 5) == 0;
	// Analog input pin (ADC 0 through 15 can be used).
	// No gain (MUX:3 == 0).
	// No differential inputs (MUX:4 == 0).
	ADMUX = (1<<REFS1);
	
	// Choosing of ADC input: analog input channel selected by writing to MUX bits in ADMUX and ADCSRB.
	if(analogPin < 8)
	{
		ADMUX |= analogPin;	
	}
	else if(analogPin < 16 && analogPin > 7)
	{
		ADMUX |= (0b11000 + analogPin);		// See table 26-4. Done to make analogPin fit to table... (0b11000 + 8 == 0b100000, 0b11000 + 9 == 0b100001 etc).
	else // WRONG ADC PIN NUMBER!!! DISABLE ADC!
	{
		// ADEN == 0;
		ADCSRA &= ~(1<<ADEN);
	}
}


/**
 * \brief Reads the value on the ADC set with the SoilHumiditySensor.
 * 
 * \return unsigned int Returns the value of the analog read.
 */
void analogRead(const struct SoilHumiditySensor* p)
{
	// Begin conversion from Analog to Digital: Setting ADSC bit (ADC Start Conversion) in ADCSRA high. (Mega2560 Datasheet p. 285)
	ADCSRA |= (1<<ADSC);
	
	// When conversion is done, ADSC returns to zero. Wait for it to return to zero.
	while((ADCSRA & (1<<ADSC)))
	{}
	
	// ADCW will contain the ADC result. Split up into ADCH and ADCL (READ ONLY).
	// Can be read by unsigned int val = ADCW;
	
	p->_humidityValue = ADCW;
}

/**
 * \brief Returns the relative soil humidity in percentage.
 * 
 * \return double Percentage of soil humidity.
 */
double SoilHumiditySensor_GetHumidityInPercent()
{
	
}

