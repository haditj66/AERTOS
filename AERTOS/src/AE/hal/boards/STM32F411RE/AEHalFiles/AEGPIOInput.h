#pragma once
#include "AEGPIOInputPeripheral.h"

 
inline bool AEGPIOInput::GPIO_ReadPin() {
 
	return HAL_GPIO_ReadPin(buttongpio_Port, buttongpio_Pin); 
 
}
 













template <templateForButton>
	inline void GPIOInputPeripheral<templateargsForButton>::_InitializePinSelectors(CreateTypeSelector_funcPtr(&functPtrsToChangeTypeSelectorss)[1])
	{
		StartPinSelectorForPin(1)
		M_AnyPinIsPossible 
		EndPinSelectorForPin
	}

template <templateForButton>
	inline void GPIOInputPeripheral<templateargsForButton>::_Initialize(Port_t port1, Pin_t pin1, Port_t port2, Pin_t pin2, Port_t port3, Pin_t pin3, Port_t port4, Pin_t pin4, Port_t port5, Pin_t pin5)
	{
		buttongpio_Port = port1;
		buttongpio_Pin = pin1; 
  
		GPIO_InitTypeDef GPIO_InitStruct;

		GPIO_InitStruct.Pin = pin1;
		GPIO_InitStruct.Mode = GPIO_MODE_IT_RISING_FALLING;
		GPIO_InitStruct.Pull = GPIO_PULLDOWN;
		GPIO_InitStruct.Alternate = GPIO_AF5_SPI1;
		HAL_GPIO_Init(port1, &GPIO_InitStruct);
		
		
		
		if (pin1 == GPIO_PIN_0)
		{
			HAL_NVIC_SetPriority(EXTI0_IRQn, 6, 0);
			HAL_NVIC_EnableIRQ(EXTI0_IRQn);
		}
		else if (pin1 == GPIO_PIN_1)
		{
			HAL_NVIC_SetPriority(EXTI1_IRQn, 6, 0);
			HAL_NVIC_EnableIRQ(EXTI1_IRQn);
		}
		else if (pin1 == GPIO_PIN_2)
		{
			HAL_NVIC_SetPriority(EXTI2_IRQn, 6, 0);
			HAL_NVIC_EnableIRQ(EXTI2_IRQn);
		}
		else if (pin1 == GPIO_PIN_3)
		{
			HAL_NVIC_SetPriority(EXTI3_IRQn, 6, 0);
			HAL_NVIC_EnableIRQ(EXTI3_IRQn);
		} 
		else if (pin1 == GPIO_PIN_4)
		{
			HAL_NVIC_SetPriority(EXTI4_IRQn, 6, 0);
			HAL_NVIC_EnableIRQ(EXTI4_IRQn);
		}
		else 
		{
			AEAssertRuntime(false, "Im not supporting external lines greather then 4 at the moment. pick a pin that is less than 4");
		}
	}
 
