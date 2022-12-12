/***********************************************************/
/***********************************************************/
/**************** By  : Abdelrahman Mohamed ****************/
/**************** Date:     24/3/2022       ****************/
/**************** Layer:      HAL           ****************/
/**************** SWC : Secure_Digital(SD)  ****************/
/**************** VER :       1.00          ****************/
/***********************************************************/
/***********************************************************/
#include "STD_TYPES.h"

#include "DIO_Interface.h"
#include "SPI_interface.h"
#include "USART_interface.h"

#include "SD_config.h"
#include "SD_private.h"
#include "SD_interface.h"

#include <util/delay.h>

void CS_Enable(void)
{
	DIO_vidSetPinValue(SD_PORT,SD_CS_PIN,LOW);
}
void CS_Disable(void)
{
	DIO_vidSetPinValue(SD_PORT,SD_CS_PIN,HIGH);
}
void SD_VidPowerupSeq(void)
{
	/*Make sure card is deselected*/
	CS_Disable();
	/*Delay until SD card is powerd up (1ms)*/
	_delay_ms(1);
	CS_Enable();

	/*Send 80 clock cycles to synchronise*/
	for(u8 Local_u8Iterator=0; Local_u8Iterator<10 ;Local_u8Iterator++)
		SPI_u8Transceive(0xFF);

	/*Deselect SD card*/
	CS_Disable();
	SPI_u8Transceive(0xFF);
}
void SD_VidSendCommand(u8 Copy_u8CMD,u32 Copy_u32Argument,u8 Copy_u8CRC)
{
	/*Transmit command to SD card ORing with 0b01000000 : 0 for start bit
	 *                                                    1 for transmission bit   */
	SPI_u8Transceive(Copy_u8CMD|0x40);

	/*Transmit argument */
	SPI_u8Transceive((u8)(Copy_u32Argument>>24));
	SPI_u8Transceive((u8)(Copy_u32Argument>>16));
	SPI_u8Transceive((u8)(Copy_u32Argument>>8) );
	SPI_u8Transceive((u8) Copy_u32Argument     );

	/*Transmit CRC*/
	SPI_u8Transceive(Copy_u8CRC |0x01);
}
u8   SD_u8ReadRes1(void)
{
	u8 Local_u8Iterator = 0 ,Local_u8Res1;

	/*Keep polling until actual data received*/
	while( 0xFF == (Local_u8Res1 = SPI_u8Transceive(0xFF)))
	{
		Local_u8Iterator++;

		/*If no data received for 8-byte ,break*/
		if(Local_u8Iterator>8)break;
	}

	return Local_u8Res1 ;
}
u8   SD_u8GoIdleState(void)
{
	/*Assert chip select*/
	SPI_u8Transceive(0xFF);
	CS_Enable();
	SPI_u8Transceive(0xFF);

	/*Send CMD0*/
	SD_VidSendCommand(CMD0,CMD0_ARG,CMD0_CRC);

	/*Read response R1*/
	u8 Local_u8Res1 = SD_u8ReadRes1();

	/*Dassert chip select*/
	SPI_u8Transceive(0xFF);
	DIO_vidSetPinValue(SD_PORT,SD_CS_PIN,HIGH);
	SPI_u8Transceive(0xFF);

	return Local_u8Res1;
}
void SD_VidReadRes3_7(u8* SD_ptrRes7)
{
	/*Read response 1 in R7*/
	SD_ptrRes7[0] = SD_u8ReadRes1();

	/*If error reading R1  (if not equal 0x00 or 0x01) ,return */
	if (SD_ptrRes7[0] > 1 ) return ;

	/*Read remaining bytes*/
	SD_ptrRes7[1] = SPI_u8Transceive(0xFF);
	SD_ptrRes7[2] = SPI_u8Transceive(0xFF);
	SD_ptrRes7[3] = SPI_u8Transceive(0xFF);
	SD_ptrRes7[4] = SPI_u8Transceive(0xFF);
}
void SD_VidSendIfCond(u8* SD_ptrRes7)
{
	/*Assert chip select*/
	SPI_u8Transceive(0xFF);
	DIO_vidSetPinValue(SD_PORT,SD_CS_PIN,LOW);
	SPI_u8Transceive(0xFF);

	/*Send CMD8*/
	SD_VidSendCommand(CMD8,CMD8_ARG,CMD8_CRC);

	/*Read Response7*/
	SD_VidReadRes3_7(SD_ptrRes7);

	/*Deassert chip select*/
	SPI_u8Transceive(0xFF);
	DIO_vidSetPinValue(SD_PORT,SD_CS_PIN,HIGH);
	SPI_u8Transceive(0xFF);
}
void SD_PrintR1(u8 Res1)
{
	    if(Res1 & 0b10000000)
	        { USART_VidSendString("\tError: MSB = 1\r\n"); return; }
	    if(Res1 == 0)
	        { USART_VidSendString("\tCard Ready\r\n"); return; }
	    if(PARAM_ERROR(Res1))
	        USART_VidSendString("\tParameter Error\r\n");
	    if(ADDR_ERROR(Res1))
	        USART_VidSendString("\tAddress Error\r\n");
	    if(ERASE_SEQ_ERROR(Res1))
	        USART_VidSendString("\tErase Sequence Error\r\n");
	    if(CRC_ERROR(Res1))
	        USART_VidSendString("\tCRC Error\r\n");
	    if(ILLEGAL_CMD(Res1))
	        USART_VidSendString("\tIllegal Command\r\n");
	    if(ERASE_RESET(Res1))
	        USART_VidSendString("\tErase Reset Error\r\n");
	    if(IN_IDLE(Res1))
	        USART_VidSendString("\tIn Idle State\r\n");

}
void SD_PrintR7(u8* Res)
{
	SD_PrintR1(Res[0]);

	if(Res[0] > 1) return ;
	USART_VidSendString("\tCommand Version: ");
	USART_VidSendHex8(CMD_VER(Res[1]));
	USART_VidSendData("\r\n");

	USART_VidSendString("\tVoltage Accepted: ");

    if(VOL_ACC(Res[3]) == VOLTAGE_ACC_27_33)
    	USART_VidSendString("2.7-3.6V\r\n");

    else if(VOL_ACC(Res[3]) == VOLTAGE_ACC_LOW)
    	USART_VidSendString("LOW VOLTAGE\r\n");
    else if(VOL_ACC(Res[3]) == VOLTAGE_ACC_RES1)
    	USART_VidSendString("RESERVED\r\n");
    else if(VOL_ACC(Res[3]) == VOLTAGE_ACC_RES2)
    	USART_VidSendString("RESERVED\r\n");
    else
    	USART_VidSendString("NOT DEFINED\r\n");

    USART_VidSendString("\tEcho: ");
    USART_VidSendHex8(Res[4]);
    USART_VidSendString("\r\n");
}
void SD_ReadOCR(u8* Res)
{

	// assert chip select
	SPI_u8Transceive(0xFF);
	CS_Enable();
	SPI_u8Transceive(0xFF);

   // send CMD58
   SD_VidSendCommand(CMD58, CMD58_ARG, CMD58_CRC);

   // read response
   SD_VidReadRes3_7(Res);

   // deassert chip select
   SPI_u8Transceive(0xFF);
   CS_Disable();
   SPI_u8Transceive(0xFF);
}
void SD_PrintR3(u8* Res)
{
	SD_PrintR1(Res[0]);

	    if(Res[0] > 1) return;

	    USART_VidSendString("\tCard Power Up Status: ");
	    if(POWER_UP_STATUS(Res[1]))
	    {
	        USART_VidSendString("READY\r\n");
	        USART_VidSendString("\tCCS Status: ");
	        if(CCS_VAL(Res[1])){ USART_VidSendString("1\r\n"); }
	        else USART_VidSendString("0\r\n");
	    }
	    else
	    {
	        USART_VidSendString("BUSY\r\n");
	    }

	    USART_VidSendString("\tVDD Window: ");
	    if(VDD_27_28(Res[3])) USART_VidSendString("2.7-2.8, ");
	    if(VDD_28_29(Res[2])) USART_VidSendString("2.8-2.9, ");
	    if(VDD_29_30(Res[2])) USART_VidSendString("2.9-3.0, ");
	    if(VDD_30_31(Res[2])) USART_VidSendString("3.0-3.1, ");
	    if(VDD_31_32(Res[2])) USART_VidSendString("3.1-3.2, ");
	    if(VDD_32_33(Res[2])) USART_VidSendString("3.2-3.3, ");
	    if(VDD_33_34(Res[2])) USART_VidSendString("3.3-3.4, ");
	    if(VDD_34_35(Res[2])) USART_VidSendString("3.4-3.5, ");
	    if(VDD_35_36(Res[2])) USART_VidSendString("3.5-3.6");
	    USART_VidSendString("\r\n");
}
u8 SD_u8SendApp(void)
{
	// assert chip select
	SPI_u8Transceive(0xFF);
	CS_Enable();
	SPI_u8Transceive(0xFF);

	// send CMD55
	SD_VidSendCommand(CMD55, CMD55_ARG, CMD55_CRC);

	// read response
	u8 Res1 = SD_u8ReadRes1();

	// deassert chip select
	SPI_u8Transceive(0xFF);
	CS_Disable();
	SPI_u8Transceive(0xFF);

	    return Res1;
}
u8 SD_SendOpCond(void)
{
	// assert chip select
	SPI_u8Transceive(0xFF);
	CS_Enable();
	SPI_u8Transceive(0xFF);

	// send CMD41
	SD_VidSendCommand(ACMD41, ACMD41_ARG, ACMD41_CRC);

	// read response
	u8 Res1 = SD_u8ReadRes1();

	// deassert chip select
	SPI_u8Transceive(0xFF);
	CS_Disable();
	SPI_u8Transceive(0xFF);

	    return Res1;
}
u8 SD_Initialization(void)
{
	u8 res[5] , local_u8cmdAttempts=0 ;

	SD_VidPowerupSeq();
    // command card to idle
	while((res[0] = SD_u8GoIdleState()) != 0x01)
	    {
	        local_u8cmdAttempts++;
	        if(local_u8cmdAttempts > 10) return SD_ERROR;
	    }

	    // send interface conditions
	    SD_VidSendIfCond(res);
	    if(res[0] != 0x01)
	    {
	        return SD_ERROR;
	    }

	    // check echo pattern
	    if(res[4] != 0xAA)
	    {
	        return SD_ERROR;
	    }

	    // attempt to initialize card
	    local_u8cmdAttempts = 0;
	    do
	    {
	        if(local_u8cmdAttempts > 100) return SD_ERROR;

	        // send app cmd
	        res[0] = SD_u8SendApp();

	        // if no error in response
	        if(res[0] < 2)
	        {
	            res[0] = SD_SendOpCond();
	        }

	        // wait
	        _delay_ms(10);

	        local_u8cmdAttempts++;
	    }
	    while(res[0] != SD_READY);

	    // read OCR
	    SD_ReadOCR(res);

	    // check card is ready
	    if(!(res[1] & 0x80)) return SD_ERROR;

	    return SD_SUCCESS;
}
u8 SD_u8ReadSingleBlock(u32 Copy_u32addr , u8* Copy_buffer ,u8* Copy_u8ptoken)
{
	/*******************************************************************************
	 Read single 512 byte block
	 token = 0xFE - Successful read
	 token = 0x0X - Data error
	 token = 0xFF - Timeout
	*******************************************************************************/
	 u8 local_u8Res1, local_u8Read;
	 u16 ReadAttempts=0;

	// set token to none
	*Copy_u8ptoken = 0xFF;

	// assert chip select
	SPI_u8Transceive(0xFF);
	CS_Enable();
	SPI_u8Transceive(0xFF);

	// send CMD17
	SD_VidSendCommand(CMD17, Copy_u32addr, CMD17_CRC);

	// read R1
	local_u8Res1 = SD_u8ReadRes1();

	// if response received from card
	if(local_u8Res1 != 0xFF)
	{
	        // wait for a response token (timeout = 100ms)
	        ReadAttempts = 0;
	        while(++ReadAttempts != SD_MAX_READ_ATTEMPTS)
	            if((local_u8Read = SPI_u8Transceive(0xFF)) != 0xFF) break;

	        // if response token is 0xFE
	        if(local_u8Read == 0xFE)
	        {
	            // read 512 byte block
	            for(u16 i = 0; i < 512; i++) *Copy_buffer++ = SPI_u8Transceive(0xFF);

	            // read 16-bit CRC
	            SPI_u8Transceive(0xFF);
	            SPI_u8Transceive(0xFF);
	        }

	        // set token to card response
	        *Copy_u8ptoken = local_u8Read;
	    }

	    // deassert chip select
	    SPI_u8Transceive(0xFF);
	    CS_Disable();
	    SPI_u8Transceive(0xFF);

	    return local_u8Res1;
}
void SD_VidPrintDataErrToken(u8 Copy_u8token)
{
	if(SD_TOKEN_OOR(Copy_u8token))
        USART_VidSendString("\tData out of range\r\n");
    if(SD_TOKEN_CECC(Copy_u8token))
    	USART_VidSendString("\tCard ECC failed\r\n");
    if(SD_TOKEN_CC(Copy_u8token))
    	USART_VidSendString("\tCC Error\r\n");
    if(SD_TOKEN_ERROR(Copy_u8token))
    	USART_VidSendString("\tError\r\n");
}
u8 SD_u8WriteSingleBlock(u32 Copy_u32addr , u8* Copy_buffer ,u8* Copy_u8ptoken)
{
	/*******************************************************************************
	 Write single 512 byte block
	 token = 0x00 - busy timeout
	 token = 0x05 - data accepted
	 token = 0xFF - response timeout
	*******************************************************************************/
	u8 local_u8ReadAttempts, local_u8Read ,Res[5];

	    // set token to None
	    *Copy_u8ptoken = 0xFF;

	    // assert chip select
	    SPI_u8Transceive(0xFF);
	    CS_Enable();
	    SPI_u8Transceive(0xFF);

	    // send CMD24
	    SD_VidSendCommand(CMD24, Copy_u32addr, CMD24_CRC);

	    // read response
	    Res[0] = SD_u8ReadRes1();

	    // if no error
	    if(Res[0] == SD_READY)
	    {
	        //Send start token
	        SPI_u8Transceive(SD_START_TOKEN);

	        // write buffer to card
	        for(u16 i = 0; i < SD_BLOCK_LEN; i++) SPI_u8Transceive(Copy_buffer[i]);

	        // wait for a response (timeout = 250ms)
	        local_u8ReadAttempts = 0;
	        while(++local_u8ReadAttempts != SD_MAX_WRITE_ATTEMPTS)
	            if((local_u8Read = SPI_u8Transceive(0xFF)) != 0xFF) { *Copy_u8ptoken = 0xFF; break; }

	        // if data accepted
	        if((local_u8Read & 0x1F) == 0x05)
	        {
	            // set token to data accepted
	            *Copy_u8ptoken = 0x05;

	            // wait for write to finish (timeout = 250ms)
	            local_u8ReadAttempts = 0;
	            while(SPI_u8Transceive(0xFF) == 0x00)
	                if(++local_u8ReadAttempts == SD_MAX_WRITE_ATTEMPTS) { *Copy_u8ptoken = 0x00; break; }
	        }
	    }

	    // deassert chip select
	    SPI_u8Transceive(0xFF);
	    CS_Disable();
	    SPI_u8Transceive(0xFF);

	    return Res[0];
}



