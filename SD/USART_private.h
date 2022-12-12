/***********************************************************/
/***********************************************************/
/**************** By  : Abdelrahman Mohamed ****************/
/**************** Date:     26/3/2022       ****************/
/**************** Layer:     MCAL           ****************/
/**************** SWC :      USART          ****************/
/**************** VER :      1.00           ****************/
/***********************************************************/
/***********************************************************/
#ifndef USART_PRIVATE_H_
#define USART_PRIVATE_H_

   /* USART Registers definition */

#define UDR       *((volatile u8*)0x2C)

#define UCSRA     *((volatile u8*)0x2B)
           /* UCSRA bits*/
#define UCSRA_RXC       7       /*RXC: USART Receive Complete*/
#define UCSRA_TXC       6       /*TXC: USART Transmit Complete*/
#define UCSRA_UDRE      5       /*UDRE: USART Data Register Empty*/
#define UCSRA_FE        4       /*FE: Frame Error*/
#define UCSRA_DOR       3       /*DOR: Data OverRun*/
#define UCSRA_PE        2       /*PE: Parity Error*/
#define UCSRA_U2X       1       /*U2X: Double the USART Transmission Speed*/
#define UCSRA_MPCM      0       /*MPCM: Multi-processor Communication Mode*/

#define UCSRB     *((volatile u8*)0x2A)
           /* UCSRA bits*/
#define UCSRB_RXCIE     7       /*RXCIE: RX Complete Interrupt Enable*/
#define UCSRB_TXCIE     6       /*TXCIE: TX Complete Interrupt Enable*/
#define UCSRB_UDRIE     5       /*UDRIE: USART Data Register Empty Interrupt Enable*/
#define UCSRB_RXEN      4       /*RXEN: Receiver Enable*/
#define UCSRB_TXEN      3       /*TXEN: Transmitter Enable*/
#define UCSRB_UCSZ2     2       /*UCSZ2: Character Size*/
#define UCSRB_RXB8      1       /*RXB8: Receive Data Bit 8*/
#define UCSRB_TXB8      0       /*TXB8: Transmit Data Bit 8*/

#define UCSRC     *((volatile u8*)0x40)

#define UBRRH     *((volatile u8*)0x40)
#define UBRRL     *((volatile u8*)0x29)



#endif
