/*! \brief Test code for testing ButtonDriver.h/.c
 *	
 *			Description here
 *
 *
 *	
 *	Filename:	Test_ButtonDriver.c
 *	Path:		./GreenHouseMonitor/ButtonDriver/test
 *	Created:	02-04-2020 19:56:48
 *	Author:		Tonni Lutze
 *
 *	Major change #1:
 */

 #include "Test_ButtonDriver.h"
 #include "./../include/ButtonDriver.h"
 


  void TestButtonDriver(){

	//	TEMPORARY STUFF to init LED on pin A7 
	DDRF	|= (1 << PF7);
	#define TEST_LED_ON		(PORTF |=	 (1 << PF7))
	#define TEST_LED_OFF	(PORTF &=	~(1 << PF7))
	//	TEMPORARY STUFF END
	
	//	Init Buttons
	InitButtons();

	while (1){
		
		while (!MntSwitchClosed())
		{
			PORTF |= 0xF0; // 4 output bits high
		}
		PORTF &= ~0xF0; // 4 output bits low

		while (!MntSwitchOpened())
		{
			PORTF |= 0xF0; // 4 output bits high
		}
		PORTF &= ~0xF0; // 4 output bits low
			
		
	}






// while(1) {
//   while (!(STEPPER_READ_BTN_OPENED & (1 << STEPPER_BTN_OPENED)))
//   {
//     PORTF |= 0xF0; // 4 output bits high
//   }
//   PORTF &= ~0xF0; // 4 output bits low
//   
//   while (!(STEPPER_READ_BTN_CLOSED & (1 << STEPPER_BTN_CLOSED)))
//   {
//     PORTF |= 0xF0; // 4 output bits high
//   }
//   PORTF &= ~0xF0; // 4 output bits low
// 
//   
// } 


/*
if (PINK & (1 << 1)) {
  PORTF |= 0xF0; // 4 output bits high
}
else {
  PORTF &= ~0xF0; // 4 output bits low
}
*/



 }