/*
 *<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<    GIE_program.c    >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
 *
 *  Author : Abdallah Abdelmoemen Shehawey
 *  Layer  : HAL
 *  SWC    : GIE
 *
 */

#include "../Inc/LIB/STD_MACROS.h"
#include "../Inc/LIB/STD_TYPES.h"

#include "../Inc/MCAL_Layer/GIE/GIE_interface.h"
#include "../Inc/MCAL_Layer/GIE/GIE_register.h"

/*___________________________________________________________________________________________________________________*/

/*
 * Breif : This Function used to enable General Interrupt Enable (GIE)
 * Parameters : Nothing
 * return : Nothing
 */
void GIE_vEnable(void)
{
  SET_BIT(SREG, SREG_I_BIT);
}

/*___________________________________________________________________________________________________________________*/

/*
 * Breif : This Function used to disable General Interrupt Enable (GIE)
 * Parameters : Nothing
 * return : Nothing
 */
void GIE_vDisable(void)
{
  CLR_BIT(SREG, SREG_I_BIT);
}

//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<    END    >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>