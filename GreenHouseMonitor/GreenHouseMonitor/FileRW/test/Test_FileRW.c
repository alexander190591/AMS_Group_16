/*
 * Test_FileRW.h
 *
 * Created: 07-05-2020 12:12:29
 *  Author: Tonni
 */ 



#include "Test_FileRW.h"




void somename()
	//void main(void)
	{
		file_descriptor_t fd1, fd2;
		char *str = "The quick brown fox jumps over the lazy dog!";
		char str_buf[50];

		byte int_size;
		byte word_size;
		int_size = sizeof(int);
		word_size = sizeof(word);

		
		
		// open file1
		if (!file_open("FILE1.TXT", &fd1, SEEK_START))
		{
			#if DEBUG
			SendString("Failed to create file FILE1.TXT!\r\n");
			#endif
			for(;;);
		}
		
		// write to file1
		if(file_write(&fd1, str, strlen(str)) != strlen(str))
		{
			#if DEBUG
			SendString("problem writing to file FILE1.TXT!\r\n");
			#endif
			for(;;);
		}
		
		// seek back to beginning of file1
		if (!file_seek(&fd1, SEEK_START))
		{
			#if DEBUG
			SendString("Failed to seek to beginning of FILE1.TXT!\r\n");
			#endif
			for(;;);
		}
		
		// read from file1 and save contents to _str_buf_
		if(file_read(&fd1, str_buf, strlen(str)) != strlen(str))
		{
			#if DEBUG
			SendString("problem reading from file FILE1.TXT!\r\n");
			#endif
			for(;;);
		}
		
		// open file2
		if (!file_open("FILE2.TXT", &fd2, SEEK_START))
		{
			#if DEBUG
			SendString("Failed to create file FILE2.TXT!\r\n");
			#endif
			for(;;);
		}
		
		// write to file2 what was read from file1
		if(file_write(&fd2, str_buf, strlen(str)) != strlen(str))
		{
			#if DEBUG
			SendString("problem writing to file!\r\n");
			#endif
			for(;;);
		}
		
		// delete file1
		if (!file_delete(&fd1))
		{
			#if DEBUG
			SendString("problem deleting to file1!\r\n");
			#endif
			for(;;);
		}
		
		// open file3, using file1's descriptor
		if (!file_open("FILE3.TXT", &fd1, SEEK_START))
		{
			#if DEBUG
			SendString("Failed to create file FILE3.TXT!\r\n");
			#endif
			for(;;);
		}
		
		// write to file3
		if(file_write(&fd1, str, strlen(str)) != strlen(str))
		{
			#if DEBUG
			SendString("problem writing to file FILE3.TXT!\r\n");
			#endif
			for(;;);
		}
		
		#if DEBUG
		SendString("File operations successful!\r\n");
		#endif
		
		for(;;);  // make sure not to exit main!
	}

	void initFileRW(void)	
	{
		InitUART(9600,8,'N');
		SPI_Init('B', SD_READER_OUT, SD_READER_IN, SD_READER_CS, SD_READER_CLK );
		if (!InitSD_Reader())
		{
			#if DEBUG
			SendString("Problem initializing SD card!\r\n");
			#endif
			for(;;);
		}
		if (!init_FAT_fs())
		{
			#if DEBUG
			SendString("Problem initializing FAT filesystem!\r\n");
			#endif
			for(;;);
		}
	}
