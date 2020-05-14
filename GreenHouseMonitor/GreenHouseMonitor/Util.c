/*
 * Util.c
 *
 * Created: 07-05-2020 13:58:02
 *  Author: Tonni
 */ 

 #include "Util.h"
 #include "UART/include/uart.h"
 #include "defines.h"

void SendDebugMessage(char * message){
	
	#if DEBUG
	
	SendString(message);
	SendString("\r\n");

	#endif
	


}
