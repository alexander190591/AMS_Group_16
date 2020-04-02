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
#define SOILMOISTURE_PIN	PF0			//	Pin# A0		SoilMoistureSensor (ADC)


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
#define SOME_NAME			PD3			//	Pin# 18		Some description
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