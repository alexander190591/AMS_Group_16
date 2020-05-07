/*
 * DHT11.c
 *
 * Created: 23-04-2020 10:43:07
 *  Author: Alexander
 */ 

#include "../include/DHT11.h"
#include "../../defines.h"

/**
 * \brief Sets up the interrupt for communication with the DHT11 module.
 *		OBS: Remember to modify the interrupt routine (ISR) in DHT11.c for the specific interrupt!
 * 
 * \param ptr is a pointer to the AirSensor struct.
 *
 */

void setUpAirSensor(struct AirSensor* ptr)
{
	// TODO SOMETHING WRONG HERE  *********************************************************************************************************************
	
	//// Any edge of INTn generates asynchronously an interrupt request: ISCn1 == 0, ISCn0 == 1 (Table 15-1, Mega2560 datasheet).
	
	EICRA &= ~(1<<AIRSENSOR_ISC1);
	EICRA|= (1<<AIRSENSOR_ISC0);
	
	EIMSK |= (1<<AIRSENSOR_INT);	// Enables pin interrupt.
	// TODO SOMETHING WRONG HERE  *********************************************************************************************************************
	
	// Enables pin interrupt (EIMSK |= (1<<AIRSENSOR_INT);)
	//// Any edge of INTn generates asynchronously an interrupt request: ISCn1 == 0, ISCn0 == 1 (Table 15-1, Mega2560 datasheet).
	
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
	ptr->getValues(ptr);
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
	ptr->getValues(ptr);
	return ptr->_humidity;
}

/**
 * \brief Communicates with the DHT11. Stores values in _humidity and _temperature of the struct.
 *
 * \param ptr is a pointer to the AirSensor struct.
 */

void getValues(struct AirSensor* ptr)
{
	// Setting pin as output:
	AIRSENSOR_DDR |= (1 << AIRSENSOR_PIN);
	// Pull pin low
	AIRSENSOR_PORT	&= ~(1 << AIRSENSOR_PIN);
	ptr->stopWatchSetup(ptr);
	ptr->stopWatchStart(ptr, 18000);
	
	ptr->_humidity = 123.45;
	ptr->_temperature = 654.32;
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
	// Clearing TCCRB to make sure no other mode is set:
	AIRSENSOR_TCCRB = 0;
	
	// Sets up to interrupt for when compare value is reached.
	// WGMn3:0 == 0100 for CTC mode.
	AIRSENSOR_TCCRB |= (1 << AIRSENSOR_WGM2);
	
	// Enable Output Compare A Match Interupt (OCIEnA)
	AIRSENSOR_TIMSK |= (1 << AIRSENSOR_OCIEA);
}

/**
 * \brief Starts the stop watch, counting microseconds, then interrupts.
 *
 * \param ptr is a pointer to the AirSensor struct.
 */
void stopWatchStart(struct AirSensor* ptr, uint16_t microseconds)
{
	// Set compare value to microseconds.
	// Starts stopwatch timer.
	// Interrupt when microseconds are up.
	
	// Clear counter
	AIRSENSOR_TCNT = 0;
	
	// Set compare value for Output Compare Register A
	AIRSENSOR_OCRA = (microseconds*2);
	
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
	AIRSENSOR_TIMSK |= (1 << AIRSENSOR_TOIE);
		
	// Timer inactive, when no clock source is selected.
	// Prescaler set to "No clock source" == Timer/Counter stopped (Table 17-6, page 157, Mega2560 datasheet).
	// Makes sure that nothing is set in the TCCR registers before setting bits.
	AIRSENSOR_TCCRA = 0;
	AIRSENSOR_TCCRB = 0;

	//// TCCR1B Bit2:0 (CS12:0, Clock Select) == 0b000. "No clock source"
	//AIRSENSOR_TCCRB &= ~(1 << AIRSENSOR_CS0);
	//AIRSENSOR_TCCRB &= ~(1 << AIRSENSOR_CS1);
	//AIRSENSOR_TCCRB &= ~(1 << AIRSENSOR_CS2);
}

/**
 * \brief Resets the _microseconds attribute, then starts incrementing _microseconds attribute until stopped with the timerStop() method.
 *
 * \param ptr is a pointer to the AirSensor struct.
 */
void timerStart(struct AirSensor* ptr)
{
	// Normal mode chosen (Important, because CTC is used for timer):
	AIRSENSOR_TCCRA = 0b00000000;
		
	AIRSENSOR_TCNT = 0;	// Clears the counter.
	
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
	
	if(ptr != 0)									// If the method is called within the struct:
	{
		// Reads timer value to _microseconds.
		ptr->_microseconds = AIRSENSOR_TCNT/2;		// Every count in timer with prescaler 8 on 16MHz is 0,5 microseconds.
	}
	
	return AIRSENSOR_TCNT/2;
}



ISR(AIRSENSOR_TIMEROVFVECT)
{
// This is what happens when compare value is reached...
	SendString("TIMER OVERFLOW!!!!"); SendChar('\n');  SendChar('\n');  SendChar('\n');
	
} // End of ISR(AIRSENSOR_TIMERINT)

ISR(AIRSENSOR_COMPAVECT)
{
	// OUTPUT TOGGLE TEST TO CHECK TIMER......
	//// Setting pin as output:
	//AIRSENSOR_DDR |= (1 << AIRSENSOR_PIN);
	//// Toggle pin:
	//AIRSENSOR_PORT ^= (1 << AIRSENSOR_PIN);

	
	// TODO::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
	//// Make Digital line input with pull-up resistor.
	AIRSENSOR_DDR &= ~(1 << AIRSENSOR_PIN);		// Set pin as input.
	AIRSENSOR_PORT |= (1 << AIRSENSOR_PIN);		// Pull-up resistor (make the signal go HIGH while listening).
	
	// Clearing the counter:
	AIRSENSOR_TCNT = 0;
		
	// Clearing the mode:
	AIRSENSOR_TCCRB &= ~(1 << AIRSENSOR_WGM2);
		
	//// Start interrupt on change.
	//
} // End of ISR(AIRSENSOR_COMPAVECT)