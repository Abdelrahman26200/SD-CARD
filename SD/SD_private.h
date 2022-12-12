/***********************************************************/
/***********************************************************/
/**************** By  : Abdelrahman Mohamed ****************/
/**************** Date:     24/3/2022       ****************/
/**************** Layer:      HAL           ****************/
/**************** SWC : Secure_Digital(SD)  ****************/
/**************** VER :       1.00          ****************/
/***********************************************************/
/***********************************************************/
#ifndef SD_PRIVATE_H_
#define SD_PRIVATE_H_

#define CMD0       0
#define CMD0_ARG   0x00000000
#define CMD0_CRC   0x94             /*0b10010100*/

#define CMD8       8                /*0b0010000*/
#define CMD8_ARG   0x000001AA
#define CMD8_CRC   0x86             /*(1000011 << 1)*/

#define CMD58       58
#define CMD58_ARG   0x00000000      //Since the arguments and CRC don't matter for CMD58,
#define CMD58_CRC   0x00			//we will set them all to zero

#define CMD55       55
#define CMD55_ARG   0x00000000
#define CMD55_CRC   0x00

#define ACMD41      41
#define ACMD41_ARG  0x40000000
#define ACMD41_CRC  0x00

#define CMD17                   17
#define CMD17_CRC               0x00
/*The host should use 100ms timeout (minimum) for single and multiple read operations
 *  I am using a 8MHz oscillator and have the SPI clock set to divide by 128. Thus,
 *  to get the number of bytes we need to send over SPI to reach 100ms,
 *   we do (0.1s * 8000000 MHz)/(128 * 8 bytes) = 782
 */
#define SD_MAX_READ_ATTEMPTS    782

#define CMD24                   24
#define CMD24_ARG               0x00
#define CMD24_CRC               0x00
/*The host should use 250ms timeout (minimum) for single and multiple read operations
 *  I am using a 8MHz oscillator and have the SPI clock set to divide by 128. Thus,
 *  to get the number of bytes we need to send over SPI to reach 100ms,
 *   we do (0.25s * 8000000 MHz)/(128 * 8 bytes) = 1954
 */
#define SD_MAX_WRITE_ATTEMPTS   1954


/*R1 format*/
#define PARAM_ERROR(X)      X & 0b01000000
#define ADDR_ERROR(X)       X & 0b00100000
#define ERASE_SEQ_ERROR(X)  X & 0b00010000
#define CRC_ERROR(X)        X & 0b00001000
#define ILLEGAL_CMD(X)      X & 0b00000100
#define ERASE_RESET(X)      X & 0b00000010
#define IN_IDLE(X)          X & 0b00000001

/*R7 format*/
#define CMD_VER(X)         ((X >> 4) & 0x0F) //((X & 0xF0) >> 4)
#define VOL_ACC(X)          (X & 0x1F)


#define VOLTAGE_ACC_27_33   0b00000001
#define VOLTAGE_ACC_LOW     0b00000010
#define VOLTAGE_ACC_RES1    0b00000100
#define VOLTAGE_ACC_RES2    0b00001000

/*R3 format*/
#define POWER_UP_STATUS(X)   X & 0x40
#define CCS_VAL(X)           X & 0x40

#define VDD_27_28(X)         X & 0b10000000
#define VDD_28_29(X)         X & 0b00000001
#define VDD_29_30(X)         X & 0b00000010
#define VDD_30_31(X)         X & 0b00000100
#define VDD_31_32(X)         X & 0b00001000
#define VDD_32_33(X)         X & 0b00010000
#define VDD_33_34(X)         X & 0b00100000
#define VDD_34_35(X)         X & 0b01000000
#define VDD_35_36(X)         X & 0b10000000

#define SD_SUCCESS  0
#define SD_ERROR    1
#define SD_READY    0x00
#define SD_START_TOKEN 0xFE
/*Data Error formate*/
#define SD_TOKEN_OOR(X)     X & 0b00001000
#define SD_TOKEN_CECC(X)    X & 0b00000100
#define SD_TOKEN_CC(X)      X & 0b00000010
#define SD_TOKEN_ERROR(X)   X & 0b00000001


#endif
