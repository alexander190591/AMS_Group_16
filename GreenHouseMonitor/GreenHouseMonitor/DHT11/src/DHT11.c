/*
 * DHT11.c
 *
 * Created: 23-04-2020 10:43:07
 *  Author: Alexander
 */ 

#include "../include/DHT11.h"
#include "../../defines.h"
#include "../../UART/include/uart.h"

/**
 * \brief Sets up the interrupt for communication with the DHT11 module.
 *		OBS: Remember to modify the interrupt routine (ISR) in DHT11.c for the specific interrupt!
 * 
 * \param ptr is a pointer to the AirSensor struct.
 *
 */

void setUpAirSensor(struct AirSensor* ptr)
{
	//// Any edge of INTn generates asynchronously an interrupt request: ISCn1 == 0, ISCn0 == 1 (Table 15-1, Mega2560 datasheet).
	AIRSENSOR_EICR &= ~(1<<AIRSENSOR_ISC1);
	AIRSENSOR_EICR |= (1<<AIRSENSOR_ISC0);
	AIRSENSOR_EIMSK |= (1<<AIRSENSOR_INT);	// Enables pin interrupt.
	
	// Timer setup:
	timerSetup(ptr);
}

/**
 * \brief Communicates with the DHT11 and returns the temperature as a double.
 * 
 * \param ptr is a pointer to the AirSensor struct.
 *
 * \return double temperature.
 */

double readTemperature(struct AirSensor* ptr)
{
	uint8_t dataReceived = 0;
	do{
		dataReceived = ptr->getValues(ptr);														// Updates the _temperature variable (and _humidity) with data from DHT11.
	} while(!dataReceived);
	
	return ptr->_temperature;
}

/**
 * \brief Communicates with the DHT11 and returns the humidity as a double.
 * 
 * \param ptr is a pointer to the AirSensor struct.
 *
 * \return double humidity.
 */

double readHumidity(struct AirSensor* ptr)
{
	uint8_t dataReceived = 0;
	do{
		dataReceived = ptr->getValues(ptr);														// Updates the _humidity variable (and _temperature) with data from DHT11.
	} while(!dataReceived);
	
	return ptr->_humidity;
}

/**
 * \brief Communicates with the DHT11. Stores values in _humidity and _temperature of the struct.
 *
 * \param ptr is a pointer to the AirSensor struct.
 * 
 * \return 1 if data was read correctly from DHT11 and _humidity and _temperature value was set correctly.
 * \return 0 if data was NOT read correctly (checskum != sum of humidity and temperature).
 */

uint8_t getValues(struct AirSensor* ptr)
{
	// Sending start signal to DHT11 (>=18 ms LOW signal)			 
	AIRSENSOR_DDR |= (1 << AIRSENSOR_PIN);										// Setting pin as output.				
	AIRSENSOR_PORT	&= ~(1 << AIRSENSOR_PIN);									// Pull pin low.
	
	ptr->stopWatchSetup(ptr);													// CTC mode and interrupt set.
	ptr->stopWatchStart(ptr, 18000);											// Creates interrupt when done. Going to ISR(AIRSENSOR_COMPAVECT).
	
	while(!(ptr->_newDataAvailable)){}											// Waiting for all 40 bits to arrive from DHT11.
	
	uint16_t humidInteger = (uint16_t)(ptr->_sensorData[0]);					// Set first byte from DHT11 (Humidity Integer value)
	uint16_t humidDecimal = (uint16_t)(ptr->_sensorData[1]);					// Set second byte from DHT11 (Humidity Decimal value)
	uint16_t tempInteger = (uint16_t)(ptr->_sensorData[2]);						// Set third byte from DHT11 (Temperature Integer value)
	uint16_t tempDecimal = (uint16_t)(ptr->_sensorData[3]);						// Set fourth byte from DHT11 (Temperature Decimal value)
	uint16_t checksum = (uint16_t)(ptr->_sensorData[4]);						// Set fifth byte from DHT11 (Checksum value (sum of the four above)
	
	// Debugging:
	//SendString("tempInteger = "); SendInteger(tempInteger); SendChar('\n');
	//SendString("tempDecimal= "); SendInteger(tempDecimal); SendChar('\n');
	//SendString("humidInteger = "); SendInteger(humidInteger); SendChar('\n');
	//SendString("humidDecimal = "); SendInteger(humidDecimal); SendChar('\n');
	//SendString("Sum = "); SendInteger(humidInteger+humidDecimal+tempInteger+tempDecimal); SendChar('\n');
	//SendString("Checksum = "); SendInteger(checksum); SendChar('\n');
	
	if(checksum == (tempInteger + tempDecimal + humidInteger + humidDecimal))	// If Checksum is correct
	{
		// Debugging:
		//SendChar('\n');
		//SendString("Sum = "); SendInteger(humidInteger+humidDecimal+tempInteger+tempDecimal); 
		// SendString(". Checksum = "); SendInteger(checksum); SendChar('\n');
		
		ptr->_humidity = (double)ptr->_sensorData[0] + 0.01*(double)(ptr->_sensorData[1]);		// Set _humidity variable in Struct to received value.
		ptr->_temperature = (double)ptr->_sensorData[2] + 0.01*(double)(ptr->_sensorData[3]);	// Set _temperature variable in Struct to received value.
		return 1;
	}
	else
		return 0;
	
}


/************************************************************************/
/*                           Private methods                            */
/************************************************************************/

/**
 * \brief Setup method for creating a timer that creates an interrupt after microseconds parameter.
 *
 * \param ptr is a pointer to the AirSensor struct.
 */
void stopWatchSetup(struct AirSensor* ptr)
{
	AIRSENSOR_TCCRB = 0;														// Clearing TCCRB to make sure no other mode is set.
	
	// Sets up to interrupt for when compare value is reached.
	// WGMn3:0 == 0100 for CTC mode.
	AIRSENSOR_TCCRB |= (1 << AIRSENSOR_WGM2);
	
	AIRSENSOR_TIMSK |= (1 << AIRSENSOR_OCIEA);									// Enable Output Compare A Match Interupt (OCIEnA).
}

/**
 * \brief Starts the stop watch, counting microseconds, then interrupts.
 *
 * \param ptr is a pointer to the AirSensor struct.
 */
void stopWatchStart(struct AirSensor* ptr, uint16_t microseconds)
{
	AIRSENSOR_TCNT = 0;															// Clear counter.
	
	// Set compare value for Output Compare Register A:
	AIRSENSOR_OCRA = (microseconds*2);											// every tick is half a microsecond with prescaler to 18 at 16MHz.
	
	// Timer activated when clock source is selected (Mega2560 datasheet p. 135).
	// Prescaler set to 8 to make one tick equal to half a microsecond.
	// TCCR1B Bit2:0 (CS12:0, Clock Select) == 0b010.
	AIRSENSOR_TCCRB &= ~(1 << AIRSENSOR_CS0);
	AIRSENSOR_TCCRB |= (1 << AIRSENSOR_CS1);
	AIRSENSOR_TCCRB &= ~(1 << AIRSENSOR_CS2);
}

/**
 * \brief Setup method for the timer used for counting microseconds.
 *		When this is called, the timer defined in defines.h will increment the counter every half microsecond.
 *		Call void timerStart() to begin the timer. 
 *		Call uint16_t timerStop() to end the timer and catch the time in microseconds.
 *
 * \param ptr is a pointer to the AirSensor struct.
 */
void timerSetup(struct AirSensor* ptr)
{
	// Timer 1 is chosen. 16-bit timer. Mega2560 datasheet page 133 ->.
	// Timer/Counter Interrupt Mask Register (Figure 17.11.33, Mega2560 datasheet) set to enable overflow interrupt. Nothing else:
	// Bit5 (ICIEn5, Timer/Countern, Input Capture Interrupt Enable) == 0.
	AIRSENSOR_TIMSK &= ~(1 << AIRSENSOR_ICIE);
	
	// Bit3:1 (OCIE1C:OCIE1A, Output Compare C:A Match Interrupt Enable) == 0.
	// Is set correctly in stopWatchSetup(), when called.
	AIRSENSOR_TIMSK &= ~(1 << AIRSENSOR_OCIEA);
	AIRSENSOR_TIMSK &= ~(1 << AIRSENSOR_OCIEB);
	AIRSENSOR_TIMSK &= ~(1 << AIRSENSOR_OCIEC);
	
	// Bit0 (TOIE1, Overflow Interrupt Enable) == 1.
	//AIRSENSOR_TIMSK |= (1 << AIRSENSOR_TOIE);
		
	// Timer inactive, when no clock source is selected.
	// Prescaler set to "No clock source" == Timer/Counter stopped (Table 17-6, page 157, Mega2560 datasheet).
	// Makes sure that nothing is set in the TCCR registers before setting bits.
	AIRSENSOR_TCCRA = 0;
	AIRSENSOR_TCCRB = 0;

	// TCCR1B Bit2:0 (CS12:0, Clock Select) == 0b000. "No clock source"
	AIRSENSOR_TCCRB &= ~(1 << AIRSENSOR_CS0);
	AIRSENSOR_TCCRB &= ~(1 << AIRSENSOR_CS1);
	AIRSENSOR_TCCRB &= ~(1 << AIRSENSOR_CS2);
}

/**
 * \brief Resets the _microseconds attribute, then starts incrementing _microseconds attribute until stopped with the timerStop() method.
 *
 * \param ptr is a pointer to the AirSensor struct.
 */
void timerStart(struct AirSensor* ptr)
{
	AIRSENSOR_TCCRA = 0b00000000;									
		
	AIRSENSOR_TCNT = 0;															// Clears the counter.
	
	// Timer activated when clock source is selected (Mega2560 datasheet p. 135).
	// Prescaler set to 8 to make one tick equal to half a microsecond.
	// TCCR1B Bit2:0 (CS12:0, Clock Select) == 0b010.
	AIRSENSOR_TCCRB &= ~(1 << AIRSENSOR_CS0);
	AIRSENSOR_TCCRB |= (1 << AIRSENSOR_CS1);
	AIRSENSOR_TCCRB &= ~(1 << AIRSENSOR_CS2);
}

/**
 * \brief Stops the timer. Returns the value in _microseconds.
 *
 * \param ptr is a pointer to the AirSensor struct.
 */
uint16_t timerStop(struct AirSensor* ptr)
{
	// Stops timer:
	// Timer inactive, when no clock source is selected.
	// Prescaler set to "No clock source" == Timer/Counter stopped (Table 17-6, page 157, Mega2560 datasheet).
	// TCCR1B Bit2:0 (CS12:0, Clock Select) == 0b000.
	AIRSENSOR_TCCRB &= ~(1 << AIRSENSOR_CS0);
	AIRSENSOR_TCCRB &= ~(1 << AIRSENSOR_CS1);
	AIRSENSOR_TCCRB &= ~(1 << AIRSENSOR_CS2);
	
	if(ptr != 0)																// If the method is called within the struct:
	{
		// Reads timer value to _microseconds.
		ptr->_microseconds = AIRSENSOR_TCNT/2;									// Every count in timer with prescaler 8 on 16MHz is 0,5 microseconds.
	}
	
	return AIRSENSOR_TCNT/2;
}