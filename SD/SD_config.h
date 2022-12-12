/***********************************************************/
/***********************************************************/
/**************** By  : Abdelrahman Mohamed ****************/
/**************** Date:     24/3/2022       ****************/
/**************** Layer:      HAL           ****************/
/**************** SWC : Secure_Digital(SD)  ****************/
/**************** VER :       1.00          ****************/
/***********************************************************/
/***********************************************************/
#ifndef SD_CONFIG_H_
#define SD_CONFIG_H_

#define SD_PORT           PORT_B
#define SD_CS_PIN         4       /*CHIP SELECT PIN*/
#define SD_MOSI_PIN       5       /*PB5 : MOSI  MASTR OUTPUT SLAVE INPUT*/
#define SD_MISO_PIN       6       /*PB6 : MISO  MASTR INPUT SLAVE OUTPUT*/
#define SD_SCK_PIN        7       /*PB7 : SCK   clock*/

#define SD_BLOCK_LEN    512

#endif
