/*
 * main.c
 *
 *  Created on: May 9, 2025
 *      Author: abdallah-shehawey
 */

#define F_CPU 8000000UL
#include "util/delay.h"

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
#include "../Inc/HAL_Layer/LM35/LM35_interface.h"
#include "../Inc/HAL_Layer/LDR/LDR_interface.h"


LM35_Config LM35 = {ADC_CHANNEL0, 5, ADC_RES_10_BIT};

LDR_Config LDR = {ADC_CHANNEL1, 5, ADC_RES_10_BIT};

u8 LM35_Temp = 0, LDR_Prec = 0;
u8 Error_Time_Out = 0;

void Enter_Sys(void);
void Display_Show(void);

/* ==================== System Configuration Structures ==================== */
// System flags for various states and modes
typedef struct
{
  u8 OneTimeFlag : 1;     // Controls welcome screen display (1: show, 0: hide)
  u8 STOP_Flag : 1;       // System timeout indicator (1: active, 0: inactive)
  u8 Dis_first_time : 1;
} Flags_structConfig;

// Initial system flags configuration
Flags_structConfig Flags = {
    1, // OneTimeFlag: Show welcome screen
    1, // STOP_Flag: Enable timeout
    0,
};

/* ==================== Global Variables ==================== */
// System state variables
volatile u8 Error_State;        // Function return status
volatile u8 KPD_Press;          // Keypad input value
u8 Soil_Pin = 0, Gas_Pin = 0;
// User data
extern u8 UserName[20];    // User's name storage
extern u8 UserName_Length; // Length of username

void main()
{

  System_vInit();
  while (1)
  {
    // if System is close and user want to open system
    if (Flags.OneTimeFlag == 1)
    {
      Error_Time_Out = 0;  // Reset timeout counter for new session
      Flags.STOP_Flag = 1; // Enable system timeout monitoring
      USART_u8SendStringSynch("Press enter to open system");
      do
      {
        // Wait for user input through UART
        Error_State = USART_u8ReceiveData(&KPD_Press);
        if (Error_State == OK)
        {
          if (KPD_Press == 0X0D) // 0x0D is ASCII code for Enter key
          {
            break;
          }
        }
      } while (1); // go into infinite loop until press enter

      // Check username and password
      Sign_In();
      // After Successfully sign in
      CLCD_vClearScreen();
      // print hello message
      CLCD_vSetPosition(2, 7); // Position cursor for welcome message
      CLCD_vSendString("Welcome ");
      CLCD_vSetPosition(3, ((20 - UserName_Length) / 2) + 1); // Center username on LCD
      CLCD_vSendString(UserName);

      USART_u8SendStringSynch("Welcome ");
      USART_u8SendStringSynch(UserName);
      _delay_ms(1000); // Show welcome message for 1 second
      Flags.OneTimeFlag = 0; // to print it one time when system open
      Display_Show();
      Enter_Sys();
    }
    else
    {
      // Reserved for future system state handling
    }
  }
}

void Display_Show()
{
  if (Flags.Dis_first_time == 0)
  {
    Flags.Dis_first_time = 1;
    CLCD_vClearScreen();
    CLCD_vSendString("Sensors :");
    CLCD_vSetPosition(CLCD_ROW_2, CLCD_COL_1);
    CLCD_vSendString("T:");
    LM35_u8GetTemp(&LM35, &LM35_Temp);
    CLCD_vSendIntNumber(LM35_Temp);
    CLCD_vSendString("    ");
    CLCD_vSendString("L:");
    LDR_u8GetLightPres(&LDR, &LDR_Prec);
    CLCD_vSendIntNumber(LDR_Prec);
    CLCD_vSendString("%");

    DIO_enumReadPinVal(DIO_PORTD, DIO_PIN3,&Gas_Pin);
    if (Gas_Pin != 1)
    {
      CLCD_vSetPosition(3, 9);
      CLCD_vSendString("G:");
      CLCD_vSendString("N");
      if (LDR_Prec < 50)
      {
        DIO_enumWritePinVal(DIO_PORTB, DIO_PIN0, DIO_PIN_HIGH);
      }
      else if (LDR_Prec > 50)
      {
        DIO_enumWritePinVal(DIO_PORTB, DIO_PIN0, DIO_PIN_LOW);
      }
    }
    else
    {
      CLCD_vSetPosition(3, 9);
      CLCD_vSendString("G:");
      CLCD_vSendString("Y");
    }
    DIO_enumReadPinVal(DIO_PORTB, DIO_PIN2, &Soil_Pin);
    CLCD_vSetPosition(CLCD_ROW_3, CLCD_COL_1);
    CLCD_vSendString("S:");
    if (Soil_Pin == 0)
    {
      DIO_enumWritePinVal(DIO_PORTB, DIO_PIN1, DIO_PIN_HIGH);
      CLCD_vSendString("N");
    }
    else if (Soil_Pin == 1)
    {
      DIO_enumWritePinVal(DIO_PORTB, DIO_PIN1, DIO_PIN_LOW);
      CLCD_vSendString("Y");
    }
  }
  else if (Flags.Dis_first_time == 1)
  {
    CLCD_vSetPosition(CLCD_ROW_2, CLCD_COL_3);
    LM35_u8GetTemp(&LM35, &LM35_Temp);
    CLCD_vSendIntNumber(LM35_Temp);
    CLCD_vSetPosition(CLCD_ROW_2, CLCD_COL_11);
    LDR_u8GetLightPres(&LDR, &LDR_Prec);
    CLCD_vSendIntNumber(LDR_Prec);
    CLCD_vSendString("%");

    DIO_enumReadPinVal(DIO_PORTD, DIO_PIN3,&Gas_Pin);
    if (Gas_Pin != 1)
    {
      CLCD_vSetPosition(3, 11);
      CLCD_vSendString("N");
      if (LDR_Prec < 50)
      {
        DIO_enumWritePinVal(DIO_PORTB, DIO_PIN0, DIO_PIN_HIGH);
      }
      else if (LDR_Prec > 50)
      {
        DIO_enumWritePinVal(DIO_PORTB, DIO_PIN0, DIO_PIN_LOW);
      }
    }
    else
    {
      CLCD_vSetPosition(3, 11);
      CLCD_vSendString("Y");
    }

    DIO_enumReadPinVal(DIO_PORTB, DIO_PIN2, &Soil_Pin);
    if (Soil_Pin == 0)
    {
      DIO_enumWritePinVal(DIO_PORTB, DIO_PIN1, DIO_PIN_HIGH);
      CLCD_vSetPosition(CLCD_ROW_3, CLCD_COL_3);
      CLCD_vSendString("N");
    }
    else if (Soil_Pin == 1)
    {
      DIO_enumWritePinVal(DIO_PORTB, DIO_PIN1, DIO_PIN_LOW);
      CLCD_vSetPosition(CLCD_ROW_3, CLCD_COL_3);
      CLCD_vSendString("Y");
    }
  }
  else
  {

  }
}

void Enter_Sys(void)
{
  USART_SendDataFuncName(0X0D);
  USART_u8SendStringSynch("1- Door");
  USART_SendDataFuncName(0X0D);
  do
  {
    Display_Show();
    Error_State = USART_u8ReceiveData(&KPD_Press);
    if (Error_State == OK)
    {
      switch (KPD_Press)
      {
      case '1':
        Garden_vDoor();
        break;

      default:
        break;
      }
    }
    else if (Error_State == TIMEOUT_STATE)
    {
      // Handle system timeout
      if (Error_Time_Out == Time_Out) // Check if maximum timeout reached
      {
        if (Flags.STOP_Flag == 1)
        {
          Flags.Dis_first_time = 0;
          CLCD_vClearScreen();
          CLCD_vSendString("Session Time Out");
          USART_u8SendStringSynch("Session Time Out");
          USART_SendDataFuncName(0X0D);
          _delay_ms(1000);
          Flags.STOP_Flag = 0;
          CLCD_vClearScreen();
        }
        else
        {
          // Reserved for additional timeout handling
        }
        Flags.OneTimeFlag = 1;
        break;
      }
      else
      {
        // Reserved for additional timeout states
      }
      Error_Time_Out++; // Increment timeout counter
    }
  }while(KPD_Press != 0X08);
}

void Garden_vDoor()
{
  // Display door control options
  USART_SendDataFuncName(0X0D);
  USART_u8SendStringSynch("Garden Door : ");
  USART_SendDataFuncName(0X0D);
  USART_u8SendStringSynch("1- Open      ");
  USART_u8SendStringSynch("2- Lock");
  USART_SendDataFuncName(0X0D);

  do
  {
    Display_Show();
    // Wait for user input
    Error_State = USART_u8ReceiveData(&KPD_Press);
    if (Error_State == OK)
    {
      switch (KPD_Press)
      {
      case '1': // Open door (0 degrees)
        SM_vTimer1Degree(0);
        Error_Time_Out = 0;
        break;

      case '2': // Lock door (90 degrees)
        SM_vTimer1Degree(90);
        Error_Time_Out = 0;
        break;

      case 0x08: // Back button pressed
        // Return to main menu
        USART_SendDataFuncName(0X0D);
        USART_u8SendStringSynch("1- Door");
        USART_SendDataFuncName(0X0D);
        break;

      default:
        break;
      }
    }
    else if (Error_State == TIMEOUT_STATE) // Handle timeout condition
    {
      if (Error_Time_Out == Time_Out) // Maximum timeout reached
      {
        if (Flags.STOP_Flag == 1)
        {
          Flags.Dis_first_time = 0;
          CLCD_vClearScreen();
          CLCD_vSendString("Session Time Out");
          USART_u8SendStringSynch("Session Time Out");
          USART_SendDataFuncName(0X0D);
          _delay_ms(1000);
          Flags.STOP_Flag = 0;
          CLCD_vClearScreen();
        }
        Flags.OneTimeFlag = 1; // Set flag to show welcome screen
        break;
      }
      Error_Time_Out++; // Increment timeout counter
    }
  } while (KPD_Press != 0X08); // Continue until back button pressed
}



void ISR_EXTI0_INT(void)
{
  USART_u8SendStringSynch("someone on the door");
  USART_SendDataFuncName(0X0D);
  Garden_vDoor();

}

void ISR_EXTI1_INT()
{
  DIO_enumWritePinVal(DIO_PORTB, DIO_PIN0, DIO_PIN_LOW);
}


























