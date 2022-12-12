/***********************************************************/
/***********************************************************/
/**************** By  : Abdelrahman Mohamed ****************/
/**************** Date:     21/3/2022       ****************/
/**************** Layer:      HAL           ****************/
/**************** SWC :       CLCD          ****************/
/**************** VER :       1.05          ****************/
/***********************************************************/
/***********************************************************/
#include "STD_TYPES.h"
#include "BIT_MATH.h"

#include "DIO_interface.h"

#include "CLCD_private.h"
#include "CLCD_config.h"
#include "CLCD_interface.h"

#include <util/delay.h>


void CLCD_VidSendCommand(u8 Copy_u8command)
{
#if CLCD_MODE == CLCD_8BIT
	/*set RS as LOW to send commend*/
	DIO_vidSetPinValue(CLCD_CONTROL_PORT,CLCD_RS_PIN,LOW);
	/*Set RW as LOW to write*/
	DIO_vidSetPinValue(CLCD_CONTROL_PORT,CLCD_RW_PIN,LOW);
	/*Send your commend*/
	DIO_vidSetPortValue(CLCD_DATA_PORT,Copy_u8command);
	/*Set enable as HIGH*/
	DIO_vidSetPinValue(CLCD_CONTROL_PORT,CLCD_E_PIN,HIGH);
	/**Delay 2ms*/
	_delay_ms(2);
	/*Set Enable as LOW*/
	DIO_vidSetPinValue(CLCD_CONTROL_PORT,CLCD_E_PIN,LOW);
#elif CLCD_MODE == CLCD_4BIT
	/*set RS as LOW to send commend*/
	DIO_vidSetPinValue(CLCD_CONTROL_PORT,CLCD_RS_PIN,LOW);
	/*Set RW as LOW to write*/
	DIO_vidSetPinValue(CLCD_CONTROL_PORT,CLCD_RW_PIN,LOW);
	/*Send your commend*/
	for(u8 Local_u8Iterator=0;Local_u8Iterator<2;Local_u8Iterator++)
	{
		switch (Local_u8Iterator)
		{
		case 0 :
			DIO_vidSetPinValue(CLCD_DATA_PORT,CLCD_DB7_PIN,((Copy_u8command &0b10000000)>>7));
			DIO_vidSetPinValue(CLCD_DATA_PORT,CLCD_DB6_PIN,((Copy_u8command &0b01000000)>>6));
			DIO_vidSetPinValue(CLCD_DATA_PORT,CLCD_DB5_PIN,((Copy_u8command &0b00100000)>>5));
			DIO_vidSetPinValue(CLCD_DATA_PORT,CLCD_DB4_PIN,((Copy_u8command &0b00010000)>>4));
			break;
		case 1 :
			DIO_vidSetPinValue(CLCD_DATA_PORT,CLCD_DB7_PIN,((Copy_u8command &0b00001000)>>3));
			DIO_vidSetPinValue(CLCD_DATA_PORT,CLCD_DB6_PIN,((Copy_u8command &0b00000100)>>2));
			DIO_vidSetPinValue(CLCD_DATA_PORT,CLCD_DB5_PIN,((Copy_u8command &0b00000010)>>1));
			DIO_vidSetPinValue(CLCD_DATA_PORT,CLCD_DB4_PIN,(Copy_u8command &0b00000001));
			break;
		}
		/*Set Enable as HIGH*/
		DIO_vidSetPinValue(CLCD_CONTROL_PORT,CLCD_E_PIN,HIGH);
		/**Delay 2ms*/
		_delay_ms(2);
		/*Set Enable as LOW*/
		DIO_vidSetPinValue(CLCD_CONTROL_PORT,CLCD_E_PIN,LOW);
	}

#endif
}
void CLCD_VidSendData(u8 Copy_u8Data)
{
#if CLCD_MODE == CLCD_8BIT
	/*set RS as HIGH to send Data*/
	DIO_vidSetPinValue(CLCD_CONTROL_PORT,CLCD_RS_PIN,HIGH);
	/*Set RW as LOW to write*/
	DIO_vidSetPinValue(CLCD_CONTROL_PORT,CLCD_RW_PIN,LOW);
	/*Send your Data*/
	DIO_vidSetPortValue(CLCD_DATA_PORT,Copy_u8Data);
	/*Set Enable as HIGH*/
	DIO_vidSetPinValue(CLCD_CONTROL_PORT,CLCD_E_PIN,HIGH);
	/**Delay 2ms*/
	_delay_ms(2);
	/*Set Enable as LOW*/
	DIO_vidSetPinValue(CLCD_CONTROL_PORT,CLCD_E_PIN,LOW);
#elif CLCD_MODE == CLCD_4BIT
	/*set RS as HIGH to send Data*/
	DIO_vidSetPinValue(CLCD_CONTROL_PORT,CLCD_RS_PIN,HIGH);
	/*Set RW as LOW to write*/
	DIO_vidSetPinValue(CLCD_CONTROL_PORT,CLCD_RW_PIN,LOW);
	/*Send your Data*/
	for(u8 Local_u8Iterator=0;Local_u8Iterator<2;Local_u8Iterator++)
		{
			switch (Local_u8Iterator)
			{
			case 0 :
				DIO_vidSetPinValue(CLCD_DATA_PORT,CLCD_DB7_PIN,((Copy_u8Data &0b10000000)>>7));
				DIO_vidSetPinValue(CLCD_DATA_PORT,CLCD_DB6_PIN,((Copy_u8Data &0b01000000)>>6));
				DIO_vidSetPinValue(CLCD_DATA_PORT,CLCD_DB5_PIN,((Copy_u8Data &0b00100000)>>5));
				DIO_vidSetPinValue(CLCD_DATA_PORT,CLCD_DB4_PIN,((Copy_u8Data &0b00010000)>>4));
				break;
			case 1 :
				DIO_vidSetPinValue(CLCD_DATA_PORT,CLCD_DB7_PIN,((Copy_u8Data &0b00001000)>>3));
				DIO_vidSetPinValue(CLCD_DATA_PORT,CLCD_DB6_PIN,((Copy_u8Data &0b00000100)>>2));
				DIO_vidSetPinValue(CLCD_DATA_PORT,CLCD_DB5_PIN,((Copy_u8Data &0b00000010)>>1));
				DIO_vidSetPinValue(CLCD_DATA_PORT,CLCD_DB4_PIN,(Copy_u8Data &0b00000001));
				break;
			}
			/*Set Enable as HIGH*/
			DIO_vidSetPinValue(CLCD_CONTROL_PORT,CLCD_E_PIN,HIGH);
			/**Delay 2ms*/
			_delay_ms(2);
			/*Set Enable as LOW*/
			DIO_vidSetPinValue(CLCD_CONTROL_PORT,CLCD_E_PIN,LOW);
		}
#endif
}
void CLCD_VidInit(void)
{
#if CLCD_MODE == CLCD_8BIT
	/*Wait for more than 30 ms*/
	_delay_ms(40);
	/*Function set command : 2 lines ,5*8 Font size */
	CLCD_VidSendCommand(0b00111000);
	_delay_ms(1);
	/*Display on / off control : display enable ,disable cursor ,no blink cursor */
	CLCD_VidSendCommand(0b00001100);
	_delay_ms(1);
	/*Clear display*/
	CLCD_VidSendCommand(0b00000001);
	_delay_ms(1);

#elif CLCD_MODE ==CLCD_4BIT
	/*Wait for more than 30 ms*/
	_delay_ms(40);
	/*Function set command : 2 lines ,5*8 Font size */
	DIO_vidSetPinValue(CLCD_DATA_PORT,CLCD_DB7_PIN,0);
	DIO_vidSetPinValue(CLCD_DATA_PORT,CLCD_DB6_PIN,0);
	DIO_vidSetPinValue(CLCD_DATA_PORT,CLCD_DB5_PIN,1);
	DIO_vidSetPinValue(CLCD_DATA_PORT,CLCD_DB4_PIN,0);
	/*Set Enable as HIGH*/
	DIO_vidSetPinValue(CLCD_CONTROL_PORT,CLCD_E_PIN,HIGH);
	/**Delay 2ms*/
	_delay_ms(2);
	/*Set Enable as LOW*/
	DIO_vidSetPinValue(CLCD_CONTROL_PORT,CLCD_E_PIN,LOW);
	CLCD_VidSendCommand(0b00101000);
	_delay_ms(1);
	/*Display on / off control : display enable ,disable cursor ,no blink cursor */
	CLCD_VidSendCommand(0b00001100);
	_delay_ms(1);
	/*Clear display*/
	CLCD_VidSendCommand(0b00000001);
	_delay_ms(2);
#endif
}
void CLCD_VidSendString(const s8* Copy_pcString)
{
	u8 Local_u8Counter=0;
	while(Copy_pcString[Local_u8Counter] != '\0')
	{
		CLCD_VidSendData(Copy_pcString[Local_u8Counter]);
		Local_u8Counter++;
	}
}
void CLCD_VidGoToXY(u8 Copy_u8XPos,u8 Copy_u8YPos)
{
	u8 Local_u8Adrress;
	if(Copy_u8XPos == 0)
	{
		/*Location is at first line*/
		Local_u8Adrress =Copy_u8YPos ;
	}
	else if(Copy_u8XPos ==1)
	{
		/*Location is at seconed line*/
		Local_u8Adrress =Copy_u8YPos+0x40;
	}
	CLCD_VidSendCommand(Local_u8Adrress+128);
}
void CLCD_VidWriteSpecialChar(u8* Copy_pu8Pattern,u8 Copy_u8PatternNo,u8 Copy_u8XPos,u8 Copy_u8YPos)
{
	u8 Local_u8CGRAMAddress=0,Local_u8Iterator;
	/*Calculate CGRAM Adress whose each block is 8 bytes*/
	Local_u8CGRAMAddress =Copy_u8PatternNo*8;
	/*Send CGRAM Address command to LCD ,With setting bit 6 ,And clearing bit 7 */
	CLCD_VidSendCommand(Local_u8CGRAMAddress+64);
	/*Write the Pattern into CGRAM*/
	for(Local_u8Iterator =0 ; Local_u8Iterator<8 ; Local_u8Iterator++)
	{
		CLCD_VidSendData(Copy_pu8Pattern[Local_u8Iterator]);
	}
	/*Go back to the DDRAM to display the pattern*/
	CLCD_VidGoToXY(Copy_u8XPos,Copy_u8YPos);
	/*Display the pattern written in the CGRAM*/
	CLCD_VidSendData(Copy_u8PatternNo);
}
void CLCD_VidWriteNum(s32 Copy_s32Number)
{
	s32 Local_s32Variable;
	u32 Local_u32Divider=10;
	u8 Local_u8Iterator=0,Local_u8Sign=0;
	if(Copy_s32Number<0)
		{
		Local_u8Sign=1;
		Copy_s32Number*=(-1);
		}
	if(Local_u8Sign==1)CLCD_VidSendData('-');
	Local_s32Variable =Copy_s32Number;
	while(Local_s32Variable != 0)
	{
		Local_s32Variable/=Local_u32Divider;
		Local_u8Iterator++;
	}
	for(u8 i=Local_u8Iterator ; i>0 ; i--)
	{
		Local_s32Variable =Copy_s32Number;
		Local_u32Divider=1;
		for(u8 k=(i-1) ; k>0 ; k--)
		{
			Local_u32Divider*=10;
		}
		Local_s32Variable/=Local_u32Divider;
		Copy_s32Number-=(Local_s32Variable*Local_u32Divider);
		switch (Local_s32Variable)
		{
		case 1 :CLCD_VidSendData('1');break;
		case 2 :CLCD_VidSendData('2');break;
		case 3 :CLCD_VidSendData('3');break;
		case 4 :CLCD_VidSendData('4');break;
		case 5 :CLCD_VidSendData('5');break;
		case 6 :CLCD_VidSendData('6');break;
		case 7 :CLCD_VidSendData('7');break;
		case 8 :CLCD_VidSendData('8');break;
		case 9 :CLCD_VidSendData('9');break;
		case 0 :CLCD_VidSendData('0');break;
		}

	}
}
