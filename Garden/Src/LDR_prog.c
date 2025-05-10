/*
 *<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<    KPD_program.c    >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
 *
 *  Author : Abdallah Abdelmoemen Shehawey
 *  Layer  : HAL
 *  SWC    : LDR
 *
 */

#include "../Inc/LIB/STD_TYPES.h"
#include "../Inc/LIB/STD_MACROS.h"

#include "../Inc/MCAL_Layer/DIO/DIO_interface.h"
#include "../Inc/MCAL_Layer/ADC/ADC_interface.h"

#include "../Inc/HAL_Layer/LDR/LDR_interface.h"
#include "../Inc/HAL_Layer/LDR/LDR_private.h"
#include "../Inc/HAL_Layer/LDR/LDR_config.h"

/*___________________________________________________________________________________________________________________*/
/*
* Breif : This Function initialize the pin which connected to led as output pin
* Parameters :
            => struct has the LDR Channel, ADC VoltageReference , ADCResolution
      => Pointer to LightPrecentage Variable which will return in it
* return : Error State
*/
u8 LDR_u8GetLightPres(LDR_Config * LDR, u8 *Copy_u8LightPrec)
{
  u8 Local_u8ErrorState = OK;

  u16 Local_u16ADCResult;
  u16 Local_u16AnalogSignal;

  /* ADC Digital Reading */
  ADC_u8GetResultSync(LDR->Copy_u8LDRChannel, &Local_u16ADCResult);

  /* Check for ADC Resolution */
  if (LDR->Copy_u8ADCRes == ADC_RES_10_BIT)
  {
    *Copy_u8LightPrec =  (Local_u16ADCResult / 1024.0) * 100 ;
  }
  else if (LDR->Copy_u8ADCRes == ADC_RES_8_BIT)
  {
    *Copy_u8LightPrec =  (Local_u16ADCResult / 256.0) * 100 ;
  }

  return Local_u8ErrorState;
}