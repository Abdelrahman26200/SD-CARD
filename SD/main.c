#include "STD_TYPES.h"
#include "BIT_MATH.h"

#include "PORT_interface.h"

#include "CLCD_interface.h"
#include "CLCD_config.h"

#include "SPI_interface.h"
#include "USART_interface.h"

#include "SD_interface.h"
#include "SD_private.h"

#include <util/delay.h>

 void main()
 {
	PORT_VidInit();

    // initialize UART and SPI
	USART_u16Int(57600);
	SPI_VidMasterInt();

	// array to hold responses
	u8 res[5], sdBuf[512], token;

	// initialize sd card
	if(SD_Initialization() != SD_SUCCESS)
	{
	        USART_VidSendString("Error initializaing SD CARD\r\n"); while(1);
	    }
	    else
	    {
	        USART_VidSendString("SD Card initialized\r\n");
	    }
	/*u8 buf[512];
	for(u16 i = 0; i < 512; i++) buf[i] = 0x55;

	    // write 0x55 to address 0x100 (256)
	    res[0] = SD_u8WriteSingleBlock(0x00000100,buf, &token);
	    SD_PrintR1(res[0]);
	    if(token == 0x05)
	    {
	    	USART_VidSendString("Data ACCEPTED");
	    }
	    else if(token == 0x00)
	    {
	    	USART_VidSendString("busy time out");
	    }
	    else if(token == 0xFF)
	    {
	    	USART_VidSendString("response timeout");
	    }*/
	    // read sector 8448
	    res[0] = SD_u8ReadSingleBlock(0x00002100, sdBuf, &token);

	    // print response
	    if((res[0]==SD_READY) && (token == 0xFE))
	    {
	        for(u16 i = 0; i < 512; i++) USART_VidSendHex8(sdBuf[i]);
	        USART_VidSendString("\r\n");
	    }
	    else
	    {
	        USART_VidSendString("Error reading sector\r\n");
	    }


	 while(1);
 }
