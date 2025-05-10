/*
 * main.c
 *
 *  Created on: May 9, 2025
 *      Author: abdallah-shehawey
 */

#include "../Inc/LIB/STD_MACROS.h"
#include "../Inc/LIB/STD_TYPES.h"
#include "../Inc/System_init.h"
#include "../Inc/LIB/SECURITY_interface.h"

#include "../Inc/MCAL_Layer/ADC/ADC_interface.h"
#include "../Inc/MCAL_Layer/DIO/DIO_interface.h"
#include "../Inc/MCAL_Layer/GIE/GIE_interface.h"
#include "../Inc/MCAL_Layer/EEPROM/EEPROM_interface.h"
#include "../Inc/MCAL_Layer/EXTI/EXTI_interface.h"
#include "../Inc/MCAL_Layer/USART/USART_interface.h"
#include "../Inc/MCAL_Layer/TIMER/TIMER_interface.h"

#include "../Inc/HAL_Layer/CLCD/CLCD_interface.h"
#include "../Inc/HAL_Layer/SM/Servo_Motor_interface.h"


void System_vInit(void)
{
  ADC_vInit();
  GIE_vEnable();
  USART_vInit();
  CLCD_vInit();
  EEPROM_vInit();
  TIMER1_vInit();
  SM_vInit();

  DIO_enumSetPinDir(DIO_PORTB, DIO_PIN0, DIO_PIN_OUTPUT);
  DIO_enumWritePinVal(DIO_PORTB, DIO_PIN0, DIO_PIN_LOW);

  DIO_enumSetPinDir(DIO_PORTB, DIO_PIN1, DIO_PIN_OUTPUT);
  DIO_enumWritePinVal(DIO_PORTB, DIO_PIN1, DIO_PIN_LOW);

  DIO_enumSetPinDir(DIO_PORTB, DIO_PIN2, DIO_PIN_INPUT);

  EXTI_vEnableInterrupt(EXTI_LINE0);
  EXTI_vSetSignal(EXTI_FALLING_EDGE, EXTI_LINE0);
  EXTI_vSetCallBack(ISR_EXTI0_INT, EXTI_LINE0);
  DIO_enumConnectPullUp(DIO_PORTD, DIO_PIN2, DIO_PIN_HIGH);

  EXTI_vEnableInterrupt(EXTI_LINE1);
  EXTI_vSetSignal(EXTI_RISING_EDGE, EXTI_LINE1);
  EXTI_vSetCallBack(ISR_EXTI1_INT, EXTI_LINE1);
  DIO_enumSetPinDir(DIO_PORTD, DIO_PIN3, DIO_PIN_INPUT);
}

