#include "../Inc/System_init.h"

#include "../Inc/LIB/STD_MACROS.h"
#include "../Inc/LIB/STD_TYPES.h"

#include "../Inc/MCAL_Layer/ADC/ADC_interface.h"
#include "../Inc/MCAL_Layer/DIO/DIO_interface.h"
#include "../Inc/MCAL_Layer/GIE/GIE_interface.h"
#include "../Inc/MCAL_Layer/EEPROM/EEPROM_interface.h"
#include "../Inc/MCAL_Layer/EXTI/EXTI_interface.h"
#include "../Inc/MCAL_Layer/USART/USART_interface.h"


void System_vInit(void)
{
  ADC_vInit();
  GIE_vEnable();
  USART_vInit();
  CLCD_vInit();

  EXTI_vEnableInterrupt(EXTI_LINE0);
  EXTI_vSetSignal(EXTI_FALLING_EDGE, EXTI_LINE0);
  EXTI_vSetCallBack(ISR_EXTI_INT, EXTI_LINE0);
  DIO_enumConnectPullUp(DIO_PORTD, DIO_PIN2, DIO_PIN_HIGH);
}

