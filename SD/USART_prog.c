#include "STD_TYPES.h"
#include "BIT_MATH.h"

#include "DIO_Interface.h"
#include "USART_interface.h"
#include "USART_private.h"

void USART_u16Int(u16 Copy_u16Baud)
{
	switch (Copy_u16Baud)
	{
	case 2400 :
		Copy_u16Baud = 207 ;
		break ;
	case 4800 :
		Copy_u16Baud = 103 ;
		break ;
	case 9600 :
		Copy_u16Baud = 51 ;
		break ;
	case 14400 :
		Copy_u16Baud = 34 ;
		break ;
	case 19200 :
		Copy_u16Baud = 25 ;
		break ;
	case 28800 :
		Copy_u16Baud = 16 ;
		break ;
	case 38400 :
		Copy_u16Baud = 12 ;
		break ;
	case 57600 :
		Copy_u16Baud = 8 ;
		break ;
	}
	/* Initializing UART */
	/*Bit 7 : 1  (To select UCSRC register)                                             *
	 *Bit 6 – UMSEL : 1  (Asynchronous operation) ,Bit 5:4 – UPM1:0 : 00 Disable Parity *
	 *Bit 3 – USBS  : 0  (1-Stop bit)  ,Bit 2:1 – UCSZ1:0 : 1 1  (8-bit data)           */
	UCSRC = 0b10000110 ;

	UBRRH = (u8) (Copy_u16Baud>>8);
	UBRRL = (u8) (Copy_u16Baud & 0xFF) ;

	/* Enable RX & TX */
	SET_BIT(UCSRB,UCSRB_RXEN);
	SET_BIT(UCSRB,UCSRB_TXEN);
}

void USART_VidSendData(u8 Copy_u8Data)
{
	/*Polling untill UDRE flag is set(Data register is empty)*/
	while (GET_BIT(UCSRA,UCSRA_UDRE)==0);

	/*Send Data*/
	UDR =Copy_u8Data ;
}

u8   USART_u8ReciveData(void)
{
	/*Polling untill RXC flag is set(Receive complete)*/
	while (GET_BIT(UCSRA,UCSRA_RXC)== 0);

	return UDR ;
}
void USART_VidSendString(u8* Copy_pString)
{

// transmit character until NULL is reached
   while(*Copy_pString != '\0' ) USART_VidSendData(*Copy_pString++);
}
void USART_VidSendHex8(u8 Copy_Val)
{
    // extract upper and lower nibbles from input value
	u8 upperNibble = (Copy_Val & 0xF0) >> 4; //the upper 4 bits (upper nibble) of a byte
	u8 lowerNibble =  Copy_Val & 0x0F;       // the lower 4 bits (lower nibble) of a byte

	    // convert nibble to its ASCII hex equivalent
	    upperNibble += upperNibble > 9 ? 'A' - 10 : '0';
	    lowerNibble += lowerNibble > 9 ? 'A' - 10 : '0';

	    // print the characters
	    USART_VidSendData(upperNibble);
	    USART_VidSendData(lowerNibble);
}
void USART_VidSendHex16(u16 Copy_Val)
{
	 // transmit upper 8 bits
	  USART_VidSendHex8((u8)(Copy_Val >> 8));

	 // transmit lower 8 bits
	  USART_VidSendHex8((u8)(Copy_Val & 0x00FF));
}
