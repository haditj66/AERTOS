#pragma once

#include "AE.h"
 
#include "AEIntegrationTesting.h" 


#if RTOS_USED == FREERTOS
#include "FreeRTOS.h"
#include "task.h"
#include "timers.h"
#include "queue.h"
#include "semphr.h"
#include "event_groups.h"
#endif