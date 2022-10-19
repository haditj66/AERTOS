
#include "AEGPIOOutputPeripheral.h"

inline void AEGPIOOutput::GPIO_SetHigh() {
	GPIO_Handle_inst->GPIO_SetHigh();
}
inline void AEGPIOOutput::GPIO_SetLow() {
 
	GPIO_Handle_inst->GPIO_SetLow();
}

inline bool AEGPIOOutput::GPIO_ReadPin() {
  
	return GPIO_Handle_inst->GPIO_ReadPin();;
}

inline void AEGPIOOutput::GPIO_TogglePin() { GPIO_Handle_inst->GPIO_TogglePin(); }








template <templateForGPIO>
	inline void GPIOPeripheral<templateargsForGPIO>::_InitializePinSelectors(CreateTypeSelector_funcPtr(&functPtrsToChangeTypeSelectorss)[1])
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
   
	}


