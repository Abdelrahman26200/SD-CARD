/***********************************************************/
/***********************************************************/
/**************** By  : Abdelrahman Mohamed ****************/
/**************** Date:     23/2/2022       ****************/
/**************** Layer:      MCAL          ****************/
/**************** SWC :       DIO           ****************/
/**************** VER :       1.00          ****************/
/***********************************************************/
/***********************************************************/
#ifndef DIO_INTERFACE_H
#define DIO_INTERFACE_H

#define PORT_A  0
#define PORT_B  1
#define PORT_C  2
#define PORT_D  3

#define Pin_0   0
#define Pin_1   1
#define Pin_2   2
#define Pin_3   3
#define Pin_4   4
#define Pin_5   5
#define Pin_6   6
#define Pin_7   7

#define HIGH    1
#define LOW     0

void DIO_vidSetPinValue(u8 Copy_u8Port,u8 Copy_u8Pin,u8 Copy_u8Value);
u8 DIO_u8GetPinValue(u8 Copy_u8Port,u8 Copy_u8Pin);
void DIO_vidSetPortValue(u8 Copy_u8Port,u8 Copy_u8Value);
void DIO_vidGetPortValue(u8 Copy_u8Port,u8 *Copy_u8Value);

#endif
