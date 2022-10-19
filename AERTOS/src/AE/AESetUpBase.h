#pragma once
#include "AE.h"


#if RTOS_USED == FREERTOS
#include "FreeRTOS.h"
#include "task.h"
#include "timers.h"
#include "queue.h"
#include "semphr.h"
#include "event_groups.h"
#endif



class AESetUpBase
{
public:
	AESetUpBase() {}
	;

	virtual void RTOSInit() {};
    //HAL specific intialization code
    virtual void BSPInit(){};
    //any things needed to be changed in the BSP to satisfy the RTOS being used
    virtual void RTOS_ToBSP_SpecificCode(){};

private:
};