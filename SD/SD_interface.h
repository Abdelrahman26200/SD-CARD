/***********************************************************/
/***********************************************************/
/**************** By  : Abdelrahman Mohamed ****************/
/**************** Date:     24/3/2022       ****************/
/**************** Layer:      HAL           ****************/
/**************** SWC : Secure_Digital(SD)  ****************/
/**************** VER :       1.00          ****************/
/***********************************************************/
/***********************************************************/
#ifndef SD_INTERFACE_H_
#define SD_INTERFACE_H_

void SD_VidPowerupSeq(void);

void CS_Enable(void);
void CS_Disable(void);

void SD_VidSendCommand(u8 Copy_u8CMD,u32 Copy_u32Argument,u8 Copy_u8CRC);

u8   SD_u8ReadRes1(void);
u8   SD_u8GoIdleState(void);
void SD_PrintR1(u8 Res1);

void SD_VidReadRes3_7(u8* SD_ptrRes7);
void SD_VidSendIfCond(u8* SD_ptrRes7);
void SD_PrintR7(u8* Res);

void SD_ReadOCR(u8* Res);
void SD_PrintR3(u8* Res);

u8 SD_u8SendApp(void);
u8 SD_SendOpCond(void);

u8 SD_Initialization(void);

u8 SD_u8ReadSingleBlock(u32 Copy_u32addr , u8* Copy_buffer ,u8* Copy_u8ptoken);

void SD_VidPrintDataErrToken(u8 Copy_u8token);

u8 SD_u8WriteSingleBlock(u32 Copy_u32addr , u8* Copy_buffer ,u8* Copy_u8ptoken);
#endif
