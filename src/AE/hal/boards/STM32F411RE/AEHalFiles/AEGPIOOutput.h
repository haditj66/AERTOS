#pragma once
#include "AEGPIOOutputPeripheral.h"

inline void AEGPIOOutput::GPIO_SetHigh() {

  Port->BSRR = Pin; 
//  HAL_GPIO_WritePin(Port, Pin, GPIO_PIN_SET);
}
inline void AEGPIOOutput::GPIO_SetLow() {

  Port->BSRR = (uint32_t)Pin << 16U;
//  HAL_GPIO_WritePin(Port, Pin, GPIO_PIN_RESET);
 
}

inline bool AEGPIOOutput::GPIO_ReadPin() {
 
  return HAL_GPIO_ReadPin(Port, Pin); 
 
}

inline void AEGPIOOutput::GPIO_TogglePin() { return HAL_GPIO_TogglePin(Port, Pin); }













template <templateForGPIO>
inline void GPIOPeripheral<templateargsForGPIO>::_InitializePinSelectors(CreateTypeSelector_funcPtr (&functPtrsToChangeTypeSelectorss)[1])
{
	StartPinSelectorForPin(1)
	M_AnyPinIsPossible 
	EndPinSelectorForPin
}

template <templateForGPIO>
inline void GPIOPeripheral<templateargsForGPIO>::_Initialize(Port_t port1, Pin_t pin1, Port_t port2, Pin_t pin2, Port_t port3, Pin_t pin3, Port_t port4, Pin_t pin4, Port_t port5, Pin_t pin5)
{
	Port = port1;
	Pin = pin1;
	IsAlreadyInUse = true;
  
	GPIO_InitTypeDef gpio_init_structure;

	gpio_init_structure.Pin = pin1;
	gpio_init_structure.Mode = GPIO_MODE_OUTPUT_PP;
	gpio_init_structure.Speed = GPIO_SPEED_HIGH;
	gpio_init_structure.Pull = GPIO_NOPULL;
	HAL_GPIO_Init(port1, &gpio_init_structure); 
}
 
