 /*! \brief Define file for use throughout the project.
 *			
 *			This file contains definition names for all Arduino MEGA 2560 GPIO pins. 
 *			Free Pins are at the bottom of the file.
 *			Used pins are put in relevant sections.
 *			
 *
 *	
 *	Filename:					defines.h
 *	Path:						./
 *	Created:					02-04-2020 09:12:02
 *	Author:						Alexander
 *	Major change #1:			Tonni Lutze			02-04-2020 12:01:03			Change: Created all definitions. 
 *	Major change #2:			
 */



#ifndef DEFINES_H_
#define DEFINES_H_

/************************************************************************/
/*				!!!!! FIND FREE PINS AT BOTTOM !!!!!                    */
/************************************************************************/

#define F_CPU 16000000


/************************************************************************/
/*				Defines for ITDB02 Arduino MEGA Shield 2.1				*/
/*																		*/
/*			(Shield for TFT display with Touch and SD Card reader)		*/
/************************************************************************/

/*								TFT display								*/

//		Define NAME			Arduino			PCB Pin		Description
//		NAME				Port Pin
#define LCD_DB8				PA0			//	Pin# 22		TFT Data Bus 8
#define LCD_BD9				PA1			//	Pin# 23		TFT Data Bus 9
#define LCD_BD10			PA2			//	Pin# 24		TFT Data Bus 10
#define LCD_BD11			PA3			//	Pin# 25		TFT Data Bus 11
#define LCD_BD12			PA4			//	Pin# 26		TFT Data Bus 12
#define LCD_BD13			PA5			//	Pin# 27		TFT Data Bus 13
#define LCD_BD14			PA6			//	Pin# 28		TFT Data Bus 14
#define LCD_BD15			PA7			//	Pin# 29		TFT Data Bus 15
#define LCD_BD7				PC7			//	Pin# 30		TFT Data Bus 7
#define LDC_DB6				PC6			//	Pin# 31		TFT Data Bus 6
#define LDC_DB5				PC5			//	Pin# 32		TFT Data Bus 5
#define LDC_DB4				PC4			//	Pin# 33		TFT Data Bus 4
#define LDC_DB3				PC3			//	Pin# 34		TFT Data Bus 3
#define LDC_DB2				PC2			//	Pin# 35		TFT Data Bus 2
#define LCD_DB1				PC1			//	Pin# 36		TFT Data Bus 1
#define LCD_DB0				PC0			//	Pin# 37		TFT Data Bus 0
#define LCD_RS				PD7			//	Pin# 38		TFT DC port
#define LCD_WR				PG2			//	Pin# 39		TFT Write
#define LCD_CS				PG1			//	Pin# 40		TFT Cable Select
#define LCD_RESET			PG0			//	Pin# 41		TFT Reset



/*							SD Card reader								*/

//		Define NAME			Arduino			PCB Pin		Description
//		NAME				Port Pin
#define SD_READER_OUT		PB3			//	Pin# 50		SD Card reader Output
#define SD_READER_IN		PB2			//	Pin# 51		SD Card reader Input
#define SD_READER_CLK		PB1			//	Pin# 52		SD Card bus Clock
#define SD_READER_CS		PB0			//	Pin# 53		SD Card Cable Select



/*							Touch interface								*/

//		Define NAME			Arduino			PCB Pin		Description
//		NAME				Port Pin
#define TOUCH_IRQ			PE4			//	PIN# 2		Touch Interrupt Pin
#define TOUCH_OUT			PE5			//	PIN# 3		Touch Output
#define TOUCH_IN			PG5			//	PIN# 4		Touch Input
#define TOUCH_CS			PE3			//	PIN# 5		Touch Cable Select
#define TOUCH_CLK			PH3			//	PIN# 6		Touch bus Clock

/*							Interrupt									*/
#define	TCH_SCRN_INT		INT4			// Interrupt 4 bit for EIMSK (External Interrupt Mask Register)
#define TCH_SCRN_ISC0		ISC40			// Interrupt Sense Control ISCn0 for EICRA (External Interrupt Control Register A)
#define TCH_SCRN_ISC1		ISC41			// Interrupt Sense Control ISCn1 for EICRA (External Interrupt Control Register A)
#define TCH_SCRN_EICR		EICRB			// Interrupt 4 External Interrupt Control Register
#define TCH_SCRN_EIMSK		EIMSK			// Interrupt 4 External Interrupt Mask Register


/************************************************************************/
/*			Defines for Big Easy stepper motor driver module			*/
/************************************************************************/

//		Define NAME			Arduino			PCB Pin		Description
//		NAME				Port Pin
#define STEPPER_DIR			PH5			//	Pin# 8		Motor Direction
#define STEPPER_EN			PH6			//	Pin# 9		Enable Stepper Motor
#define STEPPER_MS1			PB4			//	Pin# 10		Register 1	For controlling stepping mode
#define STEPPER_MS2			PB5			//	Pin# 11		Register 2	For controlling stepping mode
#define STEPPER_MS3			PB6			//	Pin# 12		Register 3	For controlling stepping mode
#define STEPPER_STEP		PB7			//	Pin# 13		Step pulse pin


/************************************************************************/
/*			Defines for Senors (Humidity, temperature etc.)				*/
/************************************************************************/

//						A I R   S E N S O R
// Pin & Port for AirSensor
#define AIRSENSOR_PIN			PD3					// Pin# 18		Data-pin for the DHT11
#define AIRSENSOR_PORT			PORTD				// Designating AirSensor pin to PORT D
#define AIRSENSOR_DDR			DDRD				// Designating AirSensor pin to Data Direction Register D
#define ARISENSOR_PINxn			PIND				// All pins on port D.

// Timer for AirSensor
#define	AIRSENSOR_TCNT			TCNT1				// Timer/Counter 1	(16-bit)
#define	AIRSENSOR_TIMSK			TIMSK1				// Timer/Counter 1 Interrupt Mask Register
#define AIRSENSOR_TCCRA			TCCR1A				// Timer/Counter 1 Control Register A
#define AIRSENSOR_TCCRB			TCCR1B				// Timer/Counter 1 Control Register B
#define AIRSENSOR_TIFR			TIFR1				// Timer/Counter 1 Interrupt Flag Register
#define AIRSENSOR_ICIE			ICIE1				// Timer/Counter 1 Input Catpure Interrupt Enable
#define AIRSENSOR_OCIEA			OCIE1A				// Timer/Counter 1 Output Compare A Match Interrupt Enable
#define AIRSENSOR_OCIEB			OCIE1B				// Timer/Counter 1 Output Compare B Match Interrupt Enable
#define AIRSENSOR_OCIEC			OCIE1C				// Timer/Counter 1 Output Compare C Match Interrupt Enable
#define AIRSENSOR_TOIE			TOIE1				// Timer/Counter 1 Overflow Interrupt Enable
#define AIRSENSOR_CS0			CS10				// Timer/Counter 1 Clock Select Bit 0
#define AIRSENSOR_CS1			CS11				// Timer/Counter 1 Clock Select Bit 1
#define AIRSENSOR_CS2			CS12				// Timer/Counter 1 Clock Select Bit 2		
#define AIRSENSOR_WGM0			WGM10				// Timer/Counter 1 Waveform Generation Mode bit 0
#define AIRSENSOR_WGM1			WGM11				// Timer/Counter 1 Waveform Generation Mode bit 1 
#define AIRSENSOR_WGM2			WGM12				// Timer/Counter 1 Waveform Generation Mode bit 2
#define AIRSENSOR_WGM3			WGM13				// Timer/Counter 1 Waveform Generation Mode bit 3
#define AIRSENSOR_OCRA			OCR1A				// Timer/Counter 1 Output Compare Register A
#define AIRSENSOR_OCRB			OCR1B				// Timer/Counter 1 Output Compare Register B
#define AIRSENSOR_OCRC			OCR1C				// Timer/Counter 1 Output Compare Register C
#define AIRSENSOR_TIMEROVFVECT	TIMER1_OVF_vect		// Timer/Counter 1 Interrupt Vector
#define AIRSENSOR_COMPAVECT		TIMER1_COMPA_vect	// Timer/Counter 1 Compare Match A Interrupt Vector

// Interrupt for AirSensor
#define	AIRSENSOR_INT			INT3				// Interrupt 3 bit for EIMSK (External Interrupt Mask Register)
#define AIRSENSOR_ISC0			ISC30				// Interrupt Sense Control ISC30 for EICRA (External Interrupt Control Register A)
#define AIRSENSOR_ISC1			ISC31				// Interrupt Sense Control ISC31 for EICRA (External Interrupt Control Register A)
#define AIRSENSOR_INTVECT		INT3_vect			// Interrupt 3 vector
#define AIRSENSOR_EICR			EICRA				// Interrupt 3 External Interrupt Control Register
#define AIRSENSOR_EIMSK			EIMSK				// Interrupt 3 External Interrupt Mask Register

//			  S O I L   M O I S T U R E   S E N S O R
// Pin & Port for SoilMoistureSensor
#define SOILMOISTURE_PIN	PF0			//	Pin# A0		SoilMoistureSensor (ADC)
#define SOILMOISTURE_PORT   PORTF       //  Designating SoilMoistureSensor pin to PORT F (ADC0-ADC7)
#define SOILMOISTURE_DDR	DDRF		//  Designating SoilMoistureSensor pin to Data Direction Register F


/************************************************************************/
/*			Defines for Misc in/out pins ( Buttons, LEDs. etc. )		*/
/************************************************************************/

//		Define NAME			Arduino			PCB Pin		Description
//		NAME				Port Pin
// #define STEPPER_BTN_CLOSED	PF6			//	Pin# A6		Stepper motor START limit switch
// #define STEPPER_BTN_OPENED	PF7			//	Pin# A7		Stepper motor END limit switch

#define STEPPER_BTN_CLOSED	PK0			//	Pin# A8		Some description
#define STEPPER_BTN_OPENED	PK1			//	Pin# A9		Some description




/************************************************************************/
/*			Interrupt, ADCs, Clocks Alternate Port names etc.			*/
/************************************************************************/
//Stepper PORT and DDR
#define STEPPER_MODE_PORT			PORTB	//	Designating Step Mode Pins to PORT B
#define STEPPER_EN_PORT				PORTH	//	Designating enable Pin to PORT H
#define STEPPER_DIR_PORT			PORTH	//	Designating direction Pin to PORT H
#define STEPPER_STEP_PORT			PORTB	//	Designating step pulse Pin to PORT B
#define STEPPER_MODE_DDR			DDRB	//	Designating Step Mode Pins to DDR B
#define STEPPER_EN_DDR				DDRH	//	Designating enable Pin to DDR H
#define STEPPER_DIR_DDR				DDRH	//	Designating direction Pin to DDR H
#define STEPPER_STEP_DDR			DDRB	//	Designating step pulse Pin to DDR B
//Button PORT and DDR
#define STEPPER_BTN_PORT			PORTK	//	Designating end button Pins to PORT K
#define STEPPER_BTN_DDR				DDRK	//	Designating end button Pins to DDR K

#define STEPPER_READ_BTN_OPENED		PINK
#define STEPPER_READ_BTN_CLOSED		PINK

/************************************************************************/
/*				Misc Defines that could be used in general				*/
/************************************************************************/

#define LOW		0
#define HIGH	1
#define OPEN	1
#define CLOSE	-1

/************************************************************************/
/*                                TIMERS                                */
/************************************************************************/
//		Define NAME			Register		Description
/*
#define	SOME_NAME			TCNT0				// Timer/Counter 0	(8-bit)
#define	SOME_NAME			TIMSK0				// Timer/Counter 0 Interrupt Mask Register
#define SOME_NAME			TCCR0A				// Timer/Counter 0 Control Register A
#define SOME_NAME			TCCR0B				// Timer/Counter 0 Control Register B
#define SOME_NAME			TIFR0				// Timer/Counter 0 Interrupt Flag Register
#define SOME_NAME			ICIE0				// Timer/Counter 0 Input Catpure Interrupt Enable
#define SOME_NAME			OCIE0A				// Timer/Counter 0 Output Compare A Match Interrupt Enable
#define SOME_NAME			OCIE0B				// Timer/Counter 0 Output Compare B Match Interrupt Enable
#define SOME_NAME			OCIE0C				// Timer/Counter 0 Output Compare C Match Interrupt Enable
#define SOME_NAME			TOIE0				// Timer/Counter 0 Overflow Interrupt Enable
#define SOME_NAME			CS00				// Timer/Counter 0 Clock Select Bit 0
#define SOME_NAME			CS01				// Timer/Counter 0 Clock Select Bit 1
#define SOME_NAME			CS02				// Timer/Counter 0 Clock Select Bit 2
#define SOME_NAME			WGM00				// Timer/Counter 0 Waveform Generation Mode bit 0
#define SOME_NAME			WGM01				// Timer/Counter 0 Waveform Generation Mode bit 1
#define SOME_NAME			WGM02				// Timer/Counter 0 Waveform Generation Mode bit 2
#define SOME_NAME			WGM03				// Timer/Counter 0 Waveform Generation Mode bit 3
#define SOME_NAME			OCR0A				// Timer/Counter 0 Output Compare Register A
#define SOME_NAME			OCR0B				// Timer/Counter 0 Output Compare Register B
#define SOME_NAME			OCR0C				// Timer/Counter 0 Output Compare Register C
#define SOME_NAME			INT0_vect			// Timer/Counter 0 Interrupt Vector
#define SOME_NAME			TIMER0_COMPA_vect	// Timer/Counter 0 Compare Match A Interrupt Vector

#define	SOME_NAME			TCNT2				// Timer/Counter 2	(8-bit)
#define	SOME_NAME			TIMSK2				// Timer/Counter 2 Interrupt Mask Register
#define SOME_NAME			TCCR2A				// Timer/Counter 2 Control Register A
#define SOME_NAME			TCCR2B				// Timer/Counter 2 Control Register B
#define SOME_NAME			TIFR2				// Timer/Counter 2 Interrupt Flag Register
#define SOME_NAME			ICIE2				// Timer/Counter 2 Input Catpure Interrupt Enable
#define SOME_NAME			OCIE2A				// Timer/Counter 2 Output Compare A Match Interrupt Enable
#define SOME_NAME			OCIE2B				// Timer/Counter 2 Output Compare B Match Interrupt Enable
#define SOME_NAME			OCIE2C				// Timer/Counter 2 Output Compare C Match Interrupt Enable
#define SOME_NAME			TOIE2				// Timer/Counter 2 Overflow Interrupt Enable
#define SOME_NAME			CS20				// Timer/Counter 2 Clock Select Bit 0
#define SOME_NAME			CS21				// Timer/Counter 2 Clock Select Bit 1
#define SOME_NAME			CS22				// Timer/Counter 2 Clock Select Bit 2
#define SOME_NAME			WGM20				// Timer/Counter 2 Waveform Generation Mode bit 0
#define SOME_NAME			WGM21				// Timer/Counter 2 Waveform Generation Mode bit 1
#define SOME_NAME			WGM22				// Timer/Counter 2 Waveform Generation Mode bit 2
#define SOME_NAME			WGM23				// Timer/Counter 2 Waveform Generation Mode bit 3
#define SOME_NAME			OCR2A				// Timer/Counter 2 Output Compare Register A
#define SOME_NAME			OCR2B				// Timer/Counter 2 Output Compare Register B
#define SOME_NAME			OCR2C				// Timer/Counter 2 Output Compare Register C
#define SOME_NAME			INT2_vect			// Timer/Counter 2 Interrupt Vector
#define SOME_NAME			TIMER2_COMPB_vect	// Timer/Counter 2 Compare Match B Interrupt Vector

#define	SOME_NAME			TCNT3				// Timer/Counter 3	(16-bit)
#define	SOME_NAME			TIMSK3				// Timer/Counter 3 Interrupt Mask Register
#define SOME_NAME			TCCR3A				// Timer/Counter 3 Control Register A
#define SOME_NAME			TCCR3B				// Timer/Counter 3 Control Register B
#define SOME_NAME			TIFR3				// Timer/Counter 3 Interrupt Flag Register
#define SOME_NAME			ICIE3				// Timer/Counter 3 Input Catpure Interrupt Enable
#define SOME_NAME			OCIE3A				// Timer/Counter 3 Output Compare A Match Interrupt Enable
#define SOME_NAME			OCIE3B				// Timer/Counter 3 Output Compare B Match Interrupt Enable
#define SOME_NAME			OCIE3C				// Timer/Counter 3 Output Compare C Match Interrupt Enable
#define SOME_NAME			TOIE3				// Timer/Counter 3 Overflow Interrupt Enable
#define SOME_NAME			CS30				// Timer/Counter 3 Clock Select Bit 0
#define SOME_NAME			CS31				// Timer/Counter 3 Clock Select Bit 1
#define SOME_NAME			CS32				// Timer/Counter 3 Clock Select Bit 2
#define SOME_NAME			WGM30				// Timer/Counter 3 Waveform Generation Mode bit 0
#define SOME_NAME			WGM31				// Timer/Counter 3 Waveform Generation Mode bit 1
#define SOME_NAME			WGM32				// Timer/Counter 3 Waveform Generation Mode bit 2
#define SOME_NAME			WGM33				// Timer/Counter 3 Waveform Generation Mode bit 3
#define SOME_NAME			OCR3A				// Timer/Counter 3 Output Compare Register A
#define SOME_NAME			OCR3B				// Timer/Counter 3 Output Compare Register B
#define SOME_NAME			OCR3C				// Timer/Counter 3 Output Compare Register C
#define SOME_NAME			INT3_vect			// Timer/Counter 3 Interrupt Vector
#define SOME_NAME			TIMER3_COMPA_vect	// Timer/Counter 3 Compare Match A Interrupt Vector

#define	SOME_NAME			TCNT4				// Timer/Counter 4	(16-bit)
#define	SOME_NAME			TIMSK4				// Timer/Counter 4 Interrupt Mask Register
#define SOME_NAME			TCCR4A				// Timer/Counter 4 Control Register A
#define SOME_NAME			TCCR4B				// Timer/Counter 4 Control Register B
#define SOME_NAME			TIFR4				// Timer/Counter 4 Interrupt Flag Register
#define SOME_NAME			ICIE4				// Timer/Counter 4 Input Catpure Interrupt Enable
#define SOME_NAME			OCIE4A				// Timer/Counter 4 Output Compare A Match Interrupt Enable
#define SOME_NAME			OCIE4B				// Timer/Counter 4 Output Compare B Match Interrupt Enable
#define SOME_NAME			OCIE4C				// Timer/Counter 4 Output Compare C Match Interrupt Enable
#define SOME_NAME			TOIE4				// Timer/Counter 4 Overflow Interrupt Enable
#define SOME_NAME			CS40				// Timer/Counter 4 Clock Select Bit 0
#define SOME_NAME			CS41				// Timer/Counter 4 Clock Select Bit 1
#define SOME_NAME			CS42				// Timer/Counter 4 Clock Select Bit 2
#define SOME_NAME			WGM40				// Timer/Counter 4 Waveform Generation Mode bit 0
#define SOME_NAME			WGM41				// Timer/Counter 4 Waveform Generation Mode bit 1
#define SOME_NAME			WGM42				// Timer/Counter 4 Waveform Generation Mode bit 2
#define SOME_NAME			WGM43				// Timer/Counter 4 Waveform Generation Mode bit 3
#define SOME_NAME			OCR4A				// Timer/Counter 4 Output Compare Register A
#define SOME_NAME			OCR4B				// Timer/Counter 4 Output Compare Register B
#define SOME_NAME			OCR4C				// Timer/Counter 4 Output Compare Register C
#define SOME_NAME			INT4_vect			// Timer/Counter 4 Interrupt Vector
#define SOME_NAME			TIMER4_COMPA_vect	// Timer/Counter 4 Compare Match A Interrupt Vector

#define	SOME_NAME			TCNT5				// Timer/Counter 5	(16-bit)
#define	SOME_NAME			TIMSK5				// Timer/Counter 5 Interrupt Mask Register
#define SOME_NAME			TCCR5A				// Timer/Counter 5 Control Register A
#define SOME_NAME			TCCR5B				// Timer/Counter 5 Control Register B
#define SOME_NAME			TIFR5				// Timer/Counter 5 Interrupt Flag Register
#define SOME_NAME			ICIE5				// Timer/Counter 5 Input Catpure Interrupt Enable
#define SOME_NAME			OCIE5A				// Timer/Counter 5 Output Compare A Match Interrupt Enable
#define SOME_NAME			OCIE5B				// Timer/Counter 5 Output Compare B Match Interrupt Enable
#define SOME_NAME			OCIE5C				// Timer/Counter 5 Output Compare C Match Interrupt Enable
#define SOME_NAME			TOIE5				// Timer/Counter 5 Overflow Interrupt Enable
#define SOME_NAME			CS50				// Timer/Counter 5 Clock Select Bit 0
#define SOME_NAME			CS51				// Timer/Counter 5 Clock Select Bit 1
#define SOME_NAME			CS52				// Timer/Counter 5 Clock Select Bit 2
#define SOME_NAME			WGM50				// Timer/Counter 5 Waveform Generation Mode bit 0
#define SOME_NAME			WGM51				// Timer/Counter 5 Waveform Generation Mode bit 1
#define SOME_NAME			WGM52				// Timer/Counter 5 Waveform Generation Mode bit 2
#define SOME_NAME			WGM53				// Timer/Counter 5 Waveform Generation Mode bit 3
#define SOME_NAME			OCR5A				// Timer/Counter 5 Output Compare Register A
#define SOME_NAME			OCR5B				// Timer/Counter 5 Output Compare Register B
#define SOME_NAME			OCR5C				// Timer/Counter 5 Output Compare Register C
#define SOME_NAME			INT5_vect			// Timer/Counter 5 Interrupt Vector
#define SOME_NAME			TIMER5_COMPA_vect	// Timer/Counter 5 Compare Match A Interrupt Vector
*/


/************************************************************************/
/*                              INTERRUPTS                              */
/************************************************************************/
//		Define NAME			Register		Description
/*
#define	SOME_NAME			INT0			// Interrupt 0 bit for EIMSK (External Interrupt Mask Register)
#define SOME_NAME			ISC00			// Interrupt Sense Control ISC00 for EICRA (External Interrupt Control Register A)
#define SOME_NAME			ISC01			// Interrupt Sense Control ISC01 for EICRA (External Interrupt Control Register A)
#define SOME_NAME			INT0_vect		// Interrupt 0 vector
#define SOME_NAME			EICRA			// Interrupt 0 External Interrupt Control Register
#define SOME_NAME			EIMSK			// Interrupt 0 External Interrupt Mask Register

#define	SOME_NAME			INT1			// Interrupt 1 bit for EIMSK (External Interrupt Mask Register)
#define SOME_NAME			ISC10			// Interrupt Sense Control ISC10 for EICRA (External Interrupt Control Register A)
#define SOME_NAME			ISC11			// Interrupt Sense Control ISC11 for EICRA (External Interrupt Control Register A)
#define SOME_NAME			INT1_vect		// Interrupt 1 vector
#define SOME_NAME			EICRA			// Interrupt 1 External Interrupt Control Register
#define SOME_NAME			EIMSK			// Interrupt 1 External Interrupt Mask Register

#define	SOME_NAME			INT2			// Interrupt 2 bit for EIMSK (External Interrupt Mask Register)
#define SOME_NAME			ISC20			// Interrupt Sense Control ISC20 for EICRA (External Interrupt Control Register A)
#define SOME_NAME			ISC21			// Interrupt Sense Control ISC21 for EICRA (External Interrupt Control Register A)
#define SOME_NAME			INT2_vect		// Interrupt 2 vector
#define SOME_NAME			EICRA			// Interrupt 2 External Interrupt Control Register
#define SOME_NAME			EIMSK			// Interrupt 2 External Interrupt Mask Register

#define	SOME_NAME			INT5			// Interrupt 5 bit for EIMSK (External Interrupt Mask Register)
#define SOME_NAME			ISC50			// Interrupt Sense Control ISC50 for EICRB (External Interrupt Control Register B)
#define SOME_NAME			ISC51			// Interrupt Sense Control ISC51 for EICRB (External Interrupt Control Register B)
#define SOME_NAME			INT5_vect		// Interrupt 5 vector
#define SOME_NAME			EICRB			// Interrupt 5 External Interrupt Control Register
#define SOME_NAME			EIMSK			// Interrupt 5 External Interrupt Mask Register

#define	SOME_NAME			INT6			// Interrupt 6 bit for EIMSK (External Interrupt Mask Register)
#define SOME_NAME			ISC60			// Interrupt Sense Control ISC60 for EICRB (External Interrupt Control Register B)
#define SOME_NAME			ISC61			// Interrupt Sense Control ISC61 for EICRB (External Interrupt Control Register B)
#define SOME_NAME			INT6_vect		// Interrupt 6 vector
#define SOME_NAME			EICRB			// Interrupt 6 External Interrupt Control Register
#define SOME_NAME			EIMSK			// Interrupt 6 External Interrupt Mask Register

#define	SOME_NAME			INT7			// Interrupt 7 bit for EIMSK (External Interrupt Mask Register)
#define SOME_NAME			ISC70			// Interrupt Sense Control ISC70 for EICRB (External Interrupt Control Register B)
#define SOME_NAME			ISC71			// Interrupt Sense Control ISC71 for EICRB (External Interrupt Control Register B)
#define SOME_NAME			INT7_vect		// Interrupt 7 vector
#define SOME_NAME			EICRB			// Interrupt 6 External Interrupt Control Register
#define SOME_NAME			EIMSK			// Interrupt 6 External Interrupt Mask Register
*/


/************************************************************************/
/*								FREE PINS                               */
/************************************************************************/

//		Define NAME			Arduino			PCB Pin		Description
//		NAME				Port Pin
/*
#define SOME_NAME			PE0			//	Pin# 0		Some description
#define SOME_NAME			PE1			//	Pin# 1		Some description
#define SOME_NAME			PH4			//	Pin# 7		Some description
#define SOME_NAME			PJ1			//	Pin# 14		Some description
#define SOME_NAME			PJ0			//	Pin# 15		Some description
#define SOME_NAME			PH1			//	Pin# 16		Some description
#define SOME_NAME			PH0			//	Pin# 17		Some description
#define SOME_NAME			PD2			//	Pin# 19		Some description
#define SOME_NAME			PD1			//	Pin# 20		Some description
#define SOME_NAME			PD0			//	Pin# 21		Some description
#define SOME_NAME			PL7			//	Pin# 42		Some description
#define SOME_NAME			PL6			//	Pin# 43		Some description
#define SOME_NAME			PL5			//	Pin# 44		Some description
#define SOME_NAME			PL4			//	Pin# 45		Some description
#define SOME_NAME			PL3			//	Pin# 46		Some description
#define SOME_NAME			PL2			//	Pin# 47		Some description
#define SOME_NAME			PL1			//	Pin# 48		Some description
#define SOME_NAME			PL0			//	Pin# 49		Some description
												
#define SOME_NAME			PF1			//	Pin# A1		Some description
#define SOME_NAME			PF2			//	Pin# A2		Some description
#define SOME_NAME			PF3			//	Pin# A3		Some description
#define SOME_NAME			PF4			//	Pin# A4		Some description
#define SOME_NAME			PF5			//	Pin# A5		Some description

#define SOME_NAME			PK2			//	Pin# A10	Some description
#define SOME_NAME			PK3			//	Pin# A11	Some description
#define SOME_NAME			PK4			//	Pin# A12	Some description
#define SOME_NAME			PK5			//	Pin# A13	Some description
#define SOME_NAME			PK6			//	Pin# A14	Some description
#define SOME_NAME			PK7			//	Pin# A15	Some description
*/
#endif /* DEFINES_H_ */