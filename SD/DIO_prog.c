#include "STD_TYPES.h"
#include "BIT_MATH.h"
#include "DIO_register.h"
#include "DIO_interface.h"




void DIO_vidSetPinValue(u8 Copy_u8Port,u8 Copy_u8Pin,u8 Copy_u8Value)
{
	if (Copy_u8Value == HIGH)
		{
		switch(Copy_u8Port){
			case(PORT_A):SET_BIT(PORTA,Copy_u8Pin);break;
			case(PORT_B):SET_BIT(PORTB,Copy_u8Pin);break;
			case(PORT_C):SET_BIT(PORTC,Copy_u8Pin);break;
			case(PORT_D):SET_BIT(PORTD,Copy_u8Pin);break;

		}
		}
		else if (Copy_u8Value == LOW)
		{
			switch(Copy_u8Port){
			case(PORT_A):CLR_BIT(PORTA,Copy_u8Pin);break;
			case(PORT_B):CLR_BIT(PORTB,Copy_u8Pin);break;
			case(PORT_C):CLR_BIT(PORTC,Copy_u8Pin);break;
			case(PORT_D):CLR_BIT(PORTD,Copy_u8Pin);break;
			}
}
}
u8 DIO_u8GetPinValue(u8 Copy_u8Port,u8 Copy_u8Pin)
{
	u8 u8ReVal ;
	switch(Copy_u8Port)
	{
		case(PORT_A):u8ReVal = GET_BIT(PINA,Copy_u8Pin);break;
		case(PORT_B):u8ReVal = GET_BIT(PINB,Copy_u8Pin);break;
		case(PORT_C):u8ReVal = GET_BIT(PINC,Copy_u8Pin);break;
		case(PORT_D):u8ReVal = GET_BIT(PIND,Copy_u8Pin);break;
	 }
    return u8ReVal;

}
void DIO_vidSetPortValue(u8 Copy_u8Port,u8 Copy_u8Value)
{
		switch(Copy_u8Port)
		{
			case(PORT_A):PORTA=Copy_u8Value;break;
			case(PORT_B):PORTB=Copy_u8Value;break;
			case(PORT_C):PORTC=Copy_u8Value;break;
			case(PORT_D):PORTD=Copy_u8Value;break;
		}
}
void DIO_vidGetPortValue(u8 Copy_u8Port,u8 *Copy_u8Value)
{
	switch(Copy_u8Port)
	{
		case(PORT_A):*Copy_u8Value =PINA;break;
		case(PORT_B):*Copy_u8Value =PINB;break;
		case(PORT_C):*Copy_u8Value =PINC;break;
		case(PORT_D):*Copy_u8Value =PIND;break;
     }
}

