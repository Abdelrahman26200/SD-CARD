/***********************************************************/
/***********************************************************/
/**************** By  : Abdelrahman Mohamed ****************/
/**************** Date:     22/3/2022       ****************/
/**************** Layer:      MCAL          ****************/
/**************** SWC :       PORT          ****************/
/**************** VER :       1.00          ****************/
/***********************************************************/
/***********************************************************/
#ifndef PORT_CONFIG_H
#define PORT_CONFIG_H

/* DETERMINE : OUTPUT
        OR     INPUT
		               */
#define PORTA_PIN0_DIR      INPUT
#define PORTA_PIN1_DIR      INPUT
#define PORTA_PIN2_DIR      INPUT
#define PORTA_PIN3_DIR      INPUT
#define PORTA_PIN4_DIR      INPUT
#define PORTA_PIN5_DIR      INPUT
#define PORTA_PIN6_DIR      INPUT
#define PORTA_PIN7_DIR      INPUT
                            
#define PORTB_PIN0_DIR      INPUT
#define PORTB_PIN1_DIR      INPUT
#define PORTB_PIN2_DIR      INPUT
#define PORTB_PIN3_DIR      INPUT
#define PORTB_PIN4_DIR      OUTPUT   //ss
#define PORTB_PIN5_DIR      OUTPUT   //MOSI
#define PORTB_PIN6_DIR      INPUT    //MISO
#define PORTB_PIN7_DIR      OUTPUT   //SCK
                            
#define PORTC_PIN0_DIR      INPUT
#define PORTC_PIN1_DIR      INPUT
#define PORTC_PIN2_DIR      INPUT
#define PORTC_PIN3_DIR      INPUT
#define PORTC_PIN4_DIR      INPUT
#define PORTC_PIN5_DIR      INPUT
#define PORTC_PIN6_DIR      INPUT
#define PORTC_PIN7_DIR      INPUT
                            
#define PORTD_PIN0_DIR      INPUT    //RX
#define PORTD_PIN1_DIR      OUTPUT   //TX
#define PORTD_PIN2_DIR      OUTPUT
#define PORTD_PIN3_DIR      OUTPUT
#define PORTD_PIN4_DIR      OUTPUT
#define PORTD_PIN5_DIR      OUTPUT
#define PORTD_PIN6_DIR      OUTPUT
#define PORTD_PIN7_DIR      OUTPUT
/* LOW : for floating if INPUT , LOW  if OUTPUT
   HIGH: for PULLUP if INPUT   , HIGH if OUTPUT */
#define PORTA_PIN0_INTIAL_VALUE    LOW
#define PORTA_PIN1_INTIAL_VALUE    LOW
#define PORTA_PIN2_INTIAL_VALUE    LOW
#define PORTA_PIN3_INTIAL_VALUE    LOW
#define PORTA_PIN4_INTIAL_VALUE    LOW
#define PORTA_PIN5_INTIAL_VALUE    LOW
#define PORTA_PIN6_INTIAL_VALUE    LOW
#define PORTA_PIN7_INTIAL_VALUE    LOW

#define PORTB_PIN0_INTIAL_VALUE    LOW
#define PORTB_PIN1_INTIAL_VALUE    LOW
#define PORTB_PIN2_INTIAL_VALUE    LOW
#define PORTB_PIN3_INTIAL_VALUE    LOW
#define PORTB_PIN4_INTIAL_VALUE    LOW
#define PORTB_PIN5_INTIAL_VALUE    LOW
#define PORTB_PIN6_INTIAL_VALUE    LOW
#define PORTB_PIN7_INTIAL_VALUE    LOW

#define PORTC_PIN0_INTIAL_VALUE    LOW
#define PORTC_PIN1_INTIAL_VALUE    LOW
#define PORTC_PIN2_INTIAL_VALUE    LOW
#define PORTC_PIN3_INTIAL_VALUE    LOW
#define PORTC_PIN4_INTIAL_VALUE    LOW
#define PORTC_PIN5_INTIAL_VALUE    LOW
#define PORTC_PIN6_INTIAL_VALUE    LOW
#define PORTC_PIN7_INTIAL_VALUE    LOW

#define PORTD_PIN0_INTIAL_VALUE    LOW
#define PORTD_PIN1_INTIAL_VALUE    LOW
#define PORTD_PIN2_INTIAL_VALUE    LOW
#define PORTD_PIN3_INTIAL_VALUE    LOW
#define PORTD_PIN4_INTIAL_VALUE    LOW
#define PORTD_PIN5_INTIAL_VALUE    LOW
#define PORTD_PIN6_INTIAL_VALUE    LOW
#define PORTD_PIN7_INTIAL_VALUE    LOW

#endif
