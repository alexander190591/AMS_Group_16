/*! \brief Temp Main file for testing
 *	
 *			Description here
 *
 *
 *	
 *	Filename:	TonniMain.c
 *	Path:		./GreenHouseMonitor/MainFiles
 *	Created:	26-03-2020 08:44:17
 *	Author:		Tonni Lutze
 *	Major change #1:			
 */

#include <avr/io.h>
//#define F_CPU 16000000
//#include <util/delay.h>


#include "MainFiles.h"

#include "../UART/include/uart.h"
// #include "../StepperDriver/test/Test_StepperDriver.h"
// #include "../ButtonDriver/test/Test_ButtonDriver.h"
// #include "../SPIDriver/test/Test_SPIDriver.h"
// #include "../SDCardDriver/test/Test_SDCardDriver.h"
// #include "../FileRW/test/Test_FileRW.h"
// #include "../FileRW/include/FileRW.h"
// #include "../FATDriver/src/newfat.h"
#include "../SDCardDriver/include/fileDefs.h"
#include "../SDCardDriver/include/SDCardDriver.h"
#include <stdio.h>
#include <stdlib.h>



void TonniMain(){
// 	
//  	TestStepperDriver();
//	TestButtonDriver();

// TestSDCardDriver();
// 
// RunTest();	
// 		


// initialize system
// initFileRW();
// #if DEBUG
// SendString("All initializations successful!\r\n");
// #endif
// somename();

InitUART(9600,8,'N');


SendString("\nUART is initialized\n\r ");



SensorDataObj dataObj;
dataObj.blockSize = 24;

//InitSD_Reader();

CollectData(& dataObj, 33.3, 44.4, 55.5);

char s[50]; 


double testobj = 44.4; 
char * test2 = "tester";
char * test3 = "dd";

sprintf(test3, "%f", 55.5);

sprintf(s, "%f", testobj);


dtostrf(dataObj.humidityAir, 10, 2, s);

SendString("\r\nprinting tests\r\n");

SendString("\r\n Airtemp: ");
SendString(dtostrf(dataObj.tempAir, 4, 2, s));

SendString("\r\n Air Humidity: ");

SendString(dtostrf(dataObj.humidityAir, 4, 2, s));

SendString("\r\n Soil Humidity: ");

SendString(dtostrf(dataObj.humiditySoil, 4, 2, s));




SendString("\r\n size of dataobj: ");

SendString(dtostrf(sizeof(dataObj), 10, 2, s));

}