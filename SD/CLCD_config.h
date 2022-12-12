/***********************************************************/
/***********************************************************/
/**************** By  : Abdelrahman Mohamed ****************/
/**************** Date:     21/3/2022       ****************/
/**************** Layer:      HAL           ****************/
/**************** SWC :       CLCD          ****************/
/**************** VER :       1.05          ****************/
/***********************************************************/
/***********************************************************/
#ifndef CLCD_CONFIG_H
#define CLCD_CONFIG_H

/*Define LCD MODE : 4_bit MODE  CLCD_4BIT
                    8_bit MODE  CLCD_8BIT
                                         */

#define CLCD_MODE          CLCD_4BIT

/*Define LCD PORTS */
#define CLCD_DATA_PORT     PORT_D
#define CLCD_CONTROL_PORT  PORT_D

/*Define if LCD in 4bit MODE connection */

#if CLCD_MODE == CLCD_4BIT
#define CLCD_DB4_PIN      Pin_3
#define CLCD_DB5_PIN      Pin_2
#define CLCD_DB6_PIN      Pin_1
#define CLCD_DB7_PIN      Pin_0
#endif

#define CLCD_RS_PIN        Pin_6
#define CLCD_RW_PIN        Pin_5
#define CLCD_E_PIN         Pin_4

#endif

