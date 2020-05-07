/*
 * Test_SDCardDriver.c
 *
 * Created: 16-04-2020 13:57:22
 *  Author: Tonni
 */ 

 #include <avr/io.h>
 #include <util/delay.h>

 #include "../include/SDCardDriver.h"
 #include "../../defines.h"
 #include "../../UART/include/uart.h"

 #define Block_1 718
 #define Block_2 1234567



 void RunTest(){
	while(1) {
		SD_readSingleBlock(Block_1);
		SendString("\r\nBlock1 ");
		SendLong(Block_1);
		SendString(" =\n");
		for (int i = 0; i<512; i++) {
			SendInteger(buffer[i]);
			SendChar(' ');
		}

		SD_readSingleBlock(Block_2);
		SendString("\r\nBlock2 ");
		SendLong(Block_2);
		SendString(" =\n");
		for (int i = 0; i<512; i++) {
			SendInteger(buffer[i]);
			SendChar(' ');
		}

		char x = ReadChar();
	
		if (x == 'e') {
			SD_erase (Block_1, Block_2-Block_1+1);
			SendString("\nSD Blocks from ");
			SendLong(Block_1);
			SendString(" to ");
			SendLong(Block_2);
			SendString("erased\n");
		}
	
		if (x == '1')	 {
			for (int i = 0; i<512; i++)		 {
				buffer[i] = i;
			}
			SD_writeSingleBlock(Block_1);
			SendString("\nBlock ");
			SendLong(Block_1);
			SendString(" programmed with 0,1,2,3,...\n");
		}
	
		if (x == '2')	 {
			for (int i = 0; i<512; i++)		 {
				buffer[i] = i;
			}
			SD_writeSingleBlock(Block_2);
			SendString("\nBlock ");
			SendLong(Block_2);
			SendString(" programmed with 0,1,2,3,...\n");
		}
	}
}


 void TestSDCardDriver(){

	InitSDCard();
	InitUART(9600,8,'N');

	SendString("\nUART is initialized\n\r ");
	SendString("\nSD_Card is initialized\n\r ");
	_delay_ms(10000);

	



 }

