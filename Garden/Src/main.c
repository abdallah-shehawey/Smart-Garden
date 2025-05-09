/*
 * main.c
 *
 *  Created on: May 9, 2025
 *      Author: abdallah-shehawey
 */

#include "util/delay.h"

#include "../Inc/LIB/STD_MACROS.h"
#include "../Inc/LIB/STD_TYPES.h"
#include "../Inc/System_init.h"

#include "../Inc/MCAL_Layer/ADC/ADC_interface.h"
#include "../Inc/MCAL_Layer/DIO/DIO_interface.h"
#include "../Inc/MCAL_Layer/GIE/GIE_interface.h"
#include "../Inc/MCAL_Layer/EEPROM/EEPROM_interface.h"
#include "../Inc/MCAL_Layer/EXTI/EXTI_interface.h"
#include "../Inc/MCAL_Layer/USART/USART_interface.h"

#include "../Inc/HAL_Layer/CLCD/CLCD_interface.h"



void main()
{
  System_vInit();
  while(1)
  {
    
  }

}


void ISR_EXTI_INT(void)
{
  CLCD_vSendData('A');
}
