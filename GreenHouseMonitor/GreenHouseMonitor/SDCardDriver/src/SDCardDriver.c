/*
 * SDCardDriver.c
 *
 * Created: 16-04-2020 13:56:55
 *  Author: Tonni
 */ 


#include <avr/io.h>
#include "../include/SDCardDriver.h"
#include "../../defines.h"



unsigned char Command(unsigned char cmd, long arg){
	unsigned char _byte;

	SPI_SlaveSelect(SD_READER_CS, true);

	_byte = SPI_CycleByte(0xFF);		//	transmitting dummy byte
	_byte = SPI_CycleByte(0x40|cmd);	//	sending command token
	
	//	because of endian-ness we want to send MSB first (little endian)
	_byte = SPI_CycleByte((unsigned char)arg >> 24);
	_byte = SPI_CycleByte((unsigned char)arg >> 16);
	_byte = SPI_CycleByte((unsigned char)arg >> 8);
	_byte = SPI_CycleByte((unsigned char)arg);

	_byte = SPI_CycleByte(0x95);	//	hardcoded CRC as it is only needed this once
	_byte = SPI_CycleByte(0xFF);	//	sending a dummy byte to allow the card time to react

	return SPI_CycleByte(0xFF);		//	return response value from SD
}

int InitSD_Reader(){
	
	int l;
	unsigned char _byte;

	//	according to the SD Specifications (Part1_Physical_Layer_Simplified_Specification_Ver6.00.pdf page 230)
	//	It may take up to 74 cycles for it to be ready, doing it lazy we just give it 80 
	SPI_SlaveSelect(SD_READER_CS, false);
	for (l=0; l<10; l++){
		_byte = SPI_CycleByte(0xFF); 
	}

	SPI_SlaveSelect(SD_READER_CS, false);
	//	sending reset command: Part1_Physical_Layer_Simplified_Specification_Ver6.00.pdf page 230
	_byte = SPI_CycleByte(0x00 | 0x40);
	_byte = SPI_CycleByte(0x00);
	_byte = SPI_CycleByte(0x00);
	_byte = SPI_CycleByte(0x00);
	_byte = SPI_CycleByte(0x00);
	_byte = SPI_CycleByte(0x95);

	//	waiting for SD to enter idle state (returns 0x01)
	for (l=0; l<500; l++){
		_byte = SPI_CycleByte(0xFF);
		if (_byte == 0x01)
		break;
	}

	//	returning error if CMD0 fails
	if (!(_byte == 0x01))	{ return 0; } 

	for (l=0; l<1000; l++)	{
		_byte = Command(APP_CMD, 0);
		_byte = Command(SD_SEND_OP_COND,0);
		//	break loop if cmd 55 and 41 are OK.
		if (!_byte)	{ break; }
	}
	//	should not happen, but if the data received is 0 at this point, there is something wrong, returning error. 
	if ( _byte != 0 )	{ return 0; }

	//	Setting block size
	_byte = Command(SET_BLOCK_LEN,BLOCKSIZE);

	SPI_SlaveSelect(SD_READER_CS, false);
	for (l=0; l<3; l++)	{ _byte = SPI_CycleByte(0xFF); }
	SPI_SlaveSelect(SD_READER_CS, true);

	//	returning 1 if all is ok. 
	return 1;
}


unsigned char ReadBlock(unsigned char * buffer, unsigned long startAddress){
	
	int i;
	unsigned char c, r1;

	// checking if the start address is not at the beginning of a block. 
	if (startAddress % BLOCKSIZE != 0)	{ return 0; }

	r1 = Command(READ_SINGLE_BLOCK, startAddress);
	//	wait for SD to locate data
	for (int i = 0; i<50; i++)	{
		//	If return is empty we break out of the loop.
		if (r1 == 0x00) break;
		r1 = SPI_CycleByte(0xFF);
	}
	// return error if return data is 0 
	if (r1 != 0x00) return 0;


	c = SPI_CycleByte(0xFF);
	//	waiting for 
	while (c != 0xFE)	{ c = SPI_CycleByte(0xFF); }
	for (i=0;i<512;i++)	{
		*(buffer++)=SPI_CycleByte(0xFF);
	}
	//	clearing queues with a few dummy bytes
	SPI_CycleByte(0xFF);
	SPI_CycleByte(0xFF);
	SPI_CycleByte(0xFF);

	return 1;
}


unsigned char WriteBlock(unsigned char * data, unsigned long startAddress){
	
	unsigned char c; 
	short i; 
	// checking if the start address is not at the beginning of a block. 
	if (startAddress % BLOCKSIZE != 0)	{ return 0; }

	// if write cmd dont return 0 theres an write error. 
	if (Command(WRITE_SINGLE_BLOCK,startAddress) != 0)	{ return 0; }

	//	clearing any data before sending actual data.
	c = SPI_CycleByte(0xFF);
	c = SPI_CycleByte(0xFF);
	c = SPI_CycleByte(0xFF);

	//	
	for (i = 0; i < BLOCKSIZE; i++)	{ 
		c = SPI_CycleByte(data[i]); 
	}
	//	Dummies before getting response
	c = SPI_CycleByte(0xFF);
	c = SPI_CycleByte(0xFF);

	c = SPI_CycleByte(0xFF);
	c &= 0x1F;	//	Mask for Write error - see documentation for SD
	
	//	React to write failure: 
	if (c != 0x05)
	{
		//TODO: dunno what to do here atm... 
	}
	


}



// 
// 
// //#include "SPI_Driver.h"
// 
// //******************************************************************
// //Function	: To initialize the SD/SDHC card in SPI mode
// //Arguments	: None
// //return	: unsigned char; will be 0 if no error,
// // 			  otherwise the response byte will be sent
// //******************************************************************
// unsigned char InitSDCard()
// {
// 	unsigned char i, response, SD_version;
// 	unsigned int retry = 0;	
// 	
// 	//SPI_init();
// 	SPI_Init('B', SD_READER_OUT, SD_READER_IN, SD_READER_CS, SD_READER_CLK );
// 		
// 	for(i = 0; i < 10; i++)
// 	{
// 		SPI_Tx(0xFF);
// 		//SPI_transmit(0xff); //80 clock pulses before sending the first command (Only needs 76, but we just do 80 to be sure)
// 	}
// 	
// 	//SPI_Chip_Select();
// 	SPI_SlaveSelect(SD_READER_CS, true);
// 	do
// 	{
// 		response = SD_sendCommand(GO_IDLE_STATE, 0); //send 'reset & go idle' command (= CMD0)
// 		retry++;
// 		if(retry > 0x20)
// 			return 1; //time out, card not detected
// 	} while(response != 0x01); //repeat until SD is in IDLE state
// 
// 	//SPI_Chip_Deselect();
// 	SPI_SlaveSelect(SD_READER_CS, false);
// 	//SPI_transmit (0xff);
// 	//SPI_transmit (0xff);
// 	SPI_Tx(0xFF);
// 	SPI_Tx(0xFF);
// 
// 	retry = 0;
// 	
// 	SD_version = 2; //default set to SD compliance with ver2.x;
// 					//this may change after checking the next command
// 	do
// 	{
// 		response = SD_sendCommand(SEND_IF_COND, 0x000001AA); //Check power supply status, mandatory for SDHC card (= CMD8)
// 		retry++;
// 		if(retry > 0xfe)
// 		{
// 			SD_version = 1;
// 			cardType = 1;
// 			break;
// 		} //time out
// 	} while(response != 0x01);
// 	
// 	retry = 0;
// 	do
// 	{
// 		response = SD_sendCommand(APP_CMD, 0); //CMD55, must be sent before sending any ACMD command
// 		response = SD_sendCommand(SD_SEND_OP_COND, 0x40000000); //ACMD41
// 
// 		retry++;
// 		if(retry > 0xfe)
// 			return 2;  //time out, card initialization failed
// 	} while(response != 0x00);
// 	
// 	retry = 0;
// 	SDHC_flag = 0;
// 	
// 	if (SD_version == 2)
// 	{
// 		do
// 		{
// 			response = SD_sendCommand(READ_OCR, 0); // (=CMD58)
// 			retry++;
// 			if(retry > 0xfe)
// 			{
// 				cardType = 0;
// 				break;
// 			} //time out
// 		} while(response != 0x00);
// 		
// 		if(SDHC_flag == 1)
// 			cardType = 2;
// 		else
// 			cardType = 3;
// 	}
// 
// 	SD_sendCommand(CRC_ON_OFF, OFF); //disable CRC; default - CRC disabled in SPI mode
// 	SD_sendCommand(SET_BLOCK_LEN, 512); //set block size to 512; default size is 512
// 	
// 	return 0; //successful return
// }
// 
// //******************************************************************
// //Function	: To send a command to SD card
// //Arguments	: unsigned char (8-bit command value)
// // 			  & unsigned long (32-bit command argument)
// //return	: unsigned char; response byte
// //******************************************************************
// unsigned char SD_sendCommand(unsigned char cmd, unsigned long arg)
// {
// 	unsigned char response, retry = 0, status;
// 
// 	//SD card accepts byte address while SDHC accepts block address in multiples of 512
// 	//so, if it's SD card we need to convert block address into corresponding byte address by 
// 	//multiplying it with 512. which is equivalent to shifting it left 9 times.
// 	//The following 'if' statement does that
// 	if(SDHC_flag == 0)
// 	{
// 		if(cmd == READ_SINGLE_BLOCK      ||
// 		   cmd == READ_MULTIPLE_BLOCKS   ||
// 		   cmd == WRITE_SINGLE_BLOCK     ||
// 		   cmd == WRITE_MULTIPLE_BLOCKS  ||
// 		   cmd == ERASE_BLOCK_START_ADDR ||
// 		   cmd == ERASE_BLOCK_END_ADDR)
// 		   {
// 			   arg = arg << 9;
// 		   }
//     }
//  
// // 	SPI_Chip_Select();
// 	SPI_SlaveSelect(SD_READER_CS, true);
// 
// // 	SPI_transmit(cmd | 0b01000000); //send command, the first two bits are always '01'
// // 	SPI_transmit(arg >> 24);
// // 	SPI_transmit(arg >> 16);
// // 	SPI_transmit(arg >> 8);
// // 	SPI_transmit(arg);
// 
// 	SPI_Tx(cmd | 0b01000000);
// 	SPI_Tx(arg >> 24);
// 	SPI_Tx(arg >> 16);
// 	SPI_Tx(arg >> 8);
// 	SPI_Tx(arg);
// 
// 	if(cmd == SEND_IF_COND)	//it is compulsory to send correct CRC for CMD8 (CRC=0x87) & CMD0 (CRC=0x95)
// // 		SPI_transmit(0x87); //for remaining commands, CRC is ignored in SPI mode
// 		SPI_Tx(0x87);
// 	else 
// // 		SPI_transmit(0x95); 
// 		SPI_Tx(0x95);
// 
// //	while((response = SPI_receive()) == 0xff) //wait for response
// 	while((response = SPI_Rx()) == 0xff) //wait for response
// 
// 	{
// 		if(retry++ > 254)
// 			break; //time out error
// 	}
// 
// 	if(response == 0x00 && cmd == READ_OCR) //checking response of CMD58
// 	{
// // 		status = SPI_receive() & 0x40; //first byte of the OCR register (bit 31:24)
// 		status = SPI_Rx() & 0x40; //first byte of the OCR register (bit 31:24)
// 		if(status == 0x40)
// 			SDHC_flag = 1; //we need it to verify SDHC card
// 		else
// 			SDHC_flag = 0;
// 
// // 		SPI_receive(); //remaining 3 bytes of the OCR register are ignored here
// // 		SPI_receive(); //one can use these bytes to check power supply limits of SD
// // 		SPI_receive(); 
// 
// 		SPI_Rx(); //remaining 3 bytes of the OCR register are ignored here
// 		SPI_Rx(); //one can use these bytes to check power supply limits of SD
// 		SPI_Rx();
// 	}
// 
//     // This is added by Henning Hargaard 6/3 2020 (Response = 1b => busy while reading 0)
// 	if (cmd == ERASE_SELECTED_BLOCKS)
// 	{
// // 		while (SPI_receive() == 0)
// 		while (SPI_Rx() == 0)
// 		{}
// 	}
//     
// // 	SPI_receive(); //extra 8 CLK
// // 	SPI_Chip_Deselect();
// 	SPI_Rx(); //extra 8 CLK
// 	SPI_SlaveSelect(SD_READER_CS, false);
// 	return response; //return state
// }
// 
// //*****************************************************************
// //Function	: To erase specified no. of blocks of SD card
// //Arguments	: None
// //return	: unsigned char; will be 0 if no error,
// // 			  otherwise the response byte will be sent
// //*****************************************************************
// unsigned char SD_erase (unsigned long startBlock, unsigned long totalBlocks)
// {
// 	unsigned char response;
// 
// 	response = SD_sendCommand(ERASE_BLOCK_START_ADDR, startBlock); //send starting block address
// 	if(response != 0x00) //check for SD status: 0x00 - OK (No flags set)
// 		return response;
// 
// 	response = SD_sendCommand(ERASE_BLOCK_END_ADDR, (startBlock + totalBlocks - 1)); //send end block address
// 	if(response != 0x00) //check for SD status: 0x00 - OK (No flags set)
// 		return response;
// 
// 	response = SD_sendCommand(ERASE_SELECTED_BLOCKS, 0); //erase all selected blocks
// 	if(response != 0x00) //check for SD status: 0x00 - OK (No flags set)
// 		return response;
// 
// 	return 0; //normal return
// }
// 
// //******************************************************************
// //Function	: To read a single block from SD card
// //Arguments	: None
// //return	: unsigned char; will be 0 if no error,
// // 			  otherwise the response byte will be sent
// //******************************************************************
// unsigned char SD_readSingleBlock(unsigned long startBlock)
// {
// 	unsigned char response;
// 	unsigned int i, retry = 0;
// 
// 	response = SD_sendCommand(READ_SINGLE_BLOCK, startBlock); //CMD17 = read a Block command
//  
// 	if(response != 0x00)
// 		return response; //check for SD status: 0x00 - OK (No flags set)
// 
// // 	SPI_Chip_Select();
// 	SPI_SlaveSelect(SD_READER_CS, true);
// 
// 	retry = 0;
// 	
// // 	while(SPI_receive() != 0b11111110) //wait for start single block token (0b11111110)
// 	while(SPI_Rx() != 0b11111110) //wait for start single block token (0b11111110)
// 	{
// 		if(retry++ > 65000)
// 		{
// // 			SPI_Chip_Deselect();
// 			SPI_SlaveSelect(SD_READER_CS, false);
// 
// 			return 1;
// 		} //return if time-out
// 	}
// 			
// 	for(i = 0; i < 512; i++) //read 512 bytes
// 	{
// // 		buffer[i] = SPI_receive();
//  		buffer[i] = SPI_Rx();
// 	}		
// 
// // 	SPI_receive(); //receive incoming CRC (16-bit), CRC is ignored here
// // 	SPI_receive();
// //
// // 	SPI_receive(); //extra 8 clock pulses
// 	SPI_Rx(); //receive incoming CRC (16-bit), CRC is ignored here
// 	SPI_Rx();
// 
// 	SPI_Rx(); //extra 8 clock pulses
// // 	SPI_Chip_Deselect();
// 	SPI_SlaveSelect(SD_READER_CS, false);
// 	return 0;
// }
// 
// //******************************************************************
// //Function	: To write to a single block of SD card
// //Arguments	: None
// //return	: unsigned char; will be 0 if no error,
// // 			  otherwise the response byte will be sent
// //******************************************************************
// unsigned char SD_writeSingleBlock(unsigned long startBlock)
// {
// 	unsigned char response;
// 	unsigned int i, retry = 0;
// 
// 	response = SD_sendCommand(WRITE_SINGLE_BLOCK, startBlock); //write a Block command
//   
// 	if(response != 0x00)
// 		return response; //check for SD status: 0x00 - OK (No flags set)
// 
// //	SPI_Chip_Select();
// 	SPI_SlaveSelect(SD_READER_CS, true);
// 
// 
// // 	SPI_transmit(0b11111110); //Send start single block token (0b11111110)
// // 	for(i = 0; i < 512; i++) //send 512 bytes data
// // 	{
// // 		SPI_transmit(buffer[i]);
// // 	}
// // 	SPI_transmit(0xff); //transmit dummy CRC (16-bit), CRC is ignored here
// // 	SPI_transmit(0xff);
// // 
// // 	response = SPI_receive();
// 
// 	SPI_Tx(0b11111110); //Send start single block token (0b11111110)
// 	for(i = 0; i < 512; i++) //send 512 bytes data
// 	{
// 		SPI_Tx(buffer[i]);
// 	}
// 	SPI_Tx(0xff); //transmit dummy CRC (16-bit), CRC is ignored here
// 	SPI_Tx(0xff);
// 
// 	response = SPI_Rx();
// 
// 	if( (response & 0b00011111) != 0b00000101) //response= 0bXXX0AAA1 ; AAA='010' - data accepted
// 	{                              //AAA='101'-data rejected due to CRC error
// //		SPI_Chip_Deselect();       //AAA='110'-data rejected due to write error
// 		SPI_SlaveSelect(SD_READER_CS, false);
// 		return response;
// 	}
// 
// //	while(SPI_receive() == 0) //wait for SD card to complete writing and get idle
// 	while(SPI_Rx() == 0) //wait for SD card to complete writing and get idle
// 	{
// 		if(retry++ > 65000)
// 		{
// //			SPI_Chip_Deselect();
// 			SPI_SlaveSelect(SD_READER_CS, false);
// 			return 1;
// 		}
// 	}
// 
// //	SPI_Chip_Deselect();
// 	SPI_SlaveSelect(SD_READER_CS, false);
// //	SPI_transmit(0xff);   //just spend 8 clock cycle delay before reasserting the CS line
// 	SPI_Tx(0xff);   //just spend 8 clock cycle delay before reasserting the CS line
// //	SPI_Chip_Select();    //re-asserting the CS line to verify if card is still busy
// 	SPI_SlaveSelect(SD_READER_CS, true);
// 
// //	while(SPI_receive() == 0) //wait for SD card to complete writing and get idle
// 	while(SPI_Rx() == 0) //wait for SD card to complete writing and get idle
// 	{
// 		if(retry++ > 65000)
// 		{
// //			SPI_Chip_Deselect();
// 			SPI_SlaveSelect(SD_READER_CS, false);
// 			return 1;
// 		}
// 	}			
// 	   
// //	SPI_Chip_Deselect();
// 	SPI_SlaveSelect(SD_READER_CS, false);
// 	return 0;
// }