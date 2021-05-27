#pragma once

#include "AE.h"

#include "AEObjects.h"

  
  

#if RTOS_USED == FREERTOS
#include "FreeRTOS.h"
#include "task.h"
#include "timers.h"
#include "queue.h"
#include "semphr.h"
#include "event_groups.h"
#endif


#ifdef Using_AEHAL 
#include "AllPeripheralObjects.h"
#endif


#ifdef IARBuild
#ifdef Target_stm32f4 
#include "UARTConsole.h"
#endif
#endif


#include "AESetUpBase.h"


#ifdef BoardModelType2
#include "ModelType2Setup.h"
static ModelType2Setup setup;

#elif BoardModelType1
#include "ModelType1Setup.h"
static ModelType1Setup setup;

#elif BoardSeries
#include "SeriesSetup.h"
static SeriesSetup setup;

#elif BoardVendor
#include "BoardVendorSetup.h"
static BoardVendorSetup setup;

#elif IsPC
#include "BoardVendorSetup.h"
static BoardVendorSetup setup;
#endif




//###################
//PORTABILITY FUNCTIONS
//these are all the functions needed to be implemented by RTOS, BSP, and RTOS-specific changes for a BSP
//###################

//intialization for the RTOS in use.  
//static void RTOSInit();
////HAL specific intialization code
//static void BSPInit();
////any things needed to be changed in the BSP to satisfy the RTOS being used
//static void RTOS_ToBSP_SpecificCode();


void AE_Init(void);


