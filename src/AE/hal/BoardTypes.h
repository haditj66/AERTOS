#pragma once

#include "BoardTypes_1.h"

#ifndef Port_t
#error you need to define the Port_t type for this board in BoardTypes_1.h . this is the port type of a gpio pin.
#endif // !1

#ifndef Pin_t
#error you need to define the Pin_t type for this board in BoardTypes_1.h . this is the pin type of a gpio pin.
#endif // !1

#ifndef DMAStreamType_t
#error you need to define DMAStreamType_t type for this board in BoardTypes_1.h . this is the DMAStream type
#endif // !1

#ifndef DMAHandleType_t
#error you need to define DMAHandleType_t type for this board in BoardTypes_1.h . this is the DMAStream type
#endif // !1

#ifndef DMA_Numbers_Of_DMA
DMA_Numbers_Of_DMA 2
#endif // !1
 
 

#ifdef USING_AEGPIOOutput 
#ifndef GPIO_Handle
#error you need to define GPIO_Handle type for this board in BoardTypes_1.h since you are using AEGPIOOutput 
#endif  
#endif

#ifdef USING_AEGPIOInput
#ifndef GPIOInput_Handle
#error you need to define GPIOInput_Handle type for this board in BoardTypes_1.h since you are using GPIOInput_Handle 
#endif   
#endif 

#ifdef USING_AEADC
#ifndef ADC_Handle
#error you need to define ADC_Handle type for this board in BoardTypes_1.h since you are using adc 
#endif   
#endif 
	
#ifdef USING_AEUART
#ifndef UART_Handle
#error you need to define UART_Handle type for this board in BoardTypes_1.h since you are using UART
#endif   
#endif 
	
	
	
	
	
	
	
	
	
	
	
	
	
//########################
//define types
//########################
	
//adc

//uart
