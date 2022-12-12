/***********************************************************/
/***********************************************************/
/**************** By  : Abdelrahman Mohamed ****************/
/**************** Date:     21/3/2022       ****************/
/**************** Layer:      HAL           ****************/
/**************** SWC :       CLCD          ****************/
/**************** VER :       1.05          ****************/
/***********************************************************/
/***********************************************************/
#ifndef CLCD_INTERFACE_H
#define CLCD_INTERFACE_H


void CLCD_VidSendCommand(u8 Copy_u8command);
void CLCD_VidSendData(u8 Copy_u8Data);
void CLCD_VidInit(void);
void CLCD_VidSendString(const s8* Copy_pcString);
void CLCD_VidWriteSpecialChar(u8* Copy_pu8Pattern,u8 Copy_u8PatternNo,u8 Copy_u8XPos,u8 Copy_u8YPos);
void CLCD_VidWriteNum(s32 Copy_s32Number);
#endif
