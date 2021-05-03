#pragma once

#include "AE.h"

#include "AEObjects.h"
  

#ifdef Using_AEHAL 
#include "AllPeripheralObjects.h"
#endif


#ifdef IARBuild
#ifdef Target_stm32f4 
#include "UARTConsole.h"
#endif
#endif




//###################
//PORTABILITY FUNCTIONS
//these are all the functions needed to be implemented by RTOS, BSP, and RTOS-specific changes for a BSP
//###################

//intialization for the RTOS in use.  
static void RTOSInit();
//HAL specific intialization code
static void BSPInit();
//any things needed to be changed in the BSP to satisfy the RTOS being used
static void RTOS_ToBSP_SpecificCode();


void AE_Init(void);


