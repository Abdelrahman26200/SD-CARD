/***********************************************************/
/***********************************************************/
/**************** By  : Abdelrahman Mohamed ****************/
/**************** Date:     23/3/2022       ****************/
/**************** Layer:      MCAL          ****************/
/**************** SWC :       SPI           ****************/
/**************** VER :       1.00          ****************/
/***********************************************************/
/***********************************************************/
#include "STD_TYPES.h"
#include "BIT_MATH.h"

#include "SPI_interface.h"
#include "SPI_private.h"
#include "SPI_config.h"
#include "SPI_register.h"

void SPI_VidMasterInt(void)
{
	/*Master initialization*/
	SET_BIT(SPCR,SPCR_MSTR);

	/*Prescaler :dividing by 16*/
	SET_BIT(SPCR,SPCR_SPR0);
	SET_BIT(SPCR,SPCR_SPR1);
	CLR_BIT(SPSR,SPSR_SPI2X);

	/*SPI Enable*/
	SET_BIT(SPCR,SPCR_SPE);
}
void SPI_VidSlaveInt(void)
{
	/*Slave initialization*/
	CLR_BIT(SPCR,SPCR_MSTR);

	/*SPI Enable*/
	SET_BIT(SPCR,SPCR_SPE);
}

u8   SPI_u8Transceive(u8 Copy_u8Date)
{
	/*Send the data*/
	SPDR = Copy_u8Date;
	/*wait (busy waiting) until transfer complete*/
	while(0 == GET_BIT(SPSR,SPSR_SPIF));
	/*Get the exchanged data*/

	return SPDR;
}

