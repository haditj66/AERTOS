#pragma once

#include "AEPWMPeripheral.h"
 


inline void AEPWM::StartPWM() {  } 
inline void AEPWM::StopPWM() {   } 
inline void AEPWM::ChangeDutyCycle(float dutycycleBetween1To100)
{ 
	DutyCycle = dutycycleBetween1To100;
} 

void ChangePeriodOfSignal(uint32_t period);

 
  

template<templateForPWM>
	inline void PWMPeripheral<templateargsForPWM>::_InitializePinSelectors(CreateTypeSelector_funcPtr(&functPtrsToChangeTypeSelectorss)[1])
	{
		
  
		this->functPtrsToChangeTypeSelectors[0] = []() -> void
		{
			PinSelector::getInstance()->IncludePossiblePin(Portenum::PortE, PinEnum::PIN14); //tim1 ch4
		//pA0 is not working for some reason. Just dont use it if you dont have to
		//PinSelector::getInstance()->IncludePossiblePin(Portenum::PortA, PinEnum::PIN0);	//tim2 ch1
			PinSelector::getInstance()->IncludePossiblePin(Portenum::PortA, PinEnum::PIN1); //tim2 ch2
			PinSelector::getInstance()->IncludePossiblePin(Portenum::PortA, PinEnum::PIN2); //tim2 ch3
			PinSelector::getInstance()->IncludePossiblePin(Portenum::PortA, PinEnum::PIN3); //tim2 ch4
			PinSelector::getInstance()->IncludePossiblePin(Portenum::PortA, PinEnum::PIN6); //tim3 ch1
			PinSelector::getInstance()->IncludePossiblePin(Portenum::PortA, PinEnum::PIN7); //tim3 ch2
			PinSelector::getInstance()->IncludePossiblePin(Portenum::PortB, PinEnum::PIN0); //tim3 ch3
			PinSelector::getInstance()->IncludePossiblePin(Portenum::PortB, PinEnum::PIN1); //tim3 ch4
			PinSelector::getInstance()->IncludePossiblePin(Portenum::PortD, PinEnum::PIN12); //tim4 ch1
			PinSelector::getInstance()->IncludePossiblePin(Portenum::PortD, PinEnum::PIN13); //tim4 ch2
			PinSelector::getInstance()->IncludePossiblePin(Portenum::PortD, PinEnum::PIN14); //tim4 ch3
			PinSelector::getInstance()->IncludePossiblePin(Portenum::PortD, PinEnum::PIN15); //tim4 ch4 	
		}; 
		 
  
	}
 


template<templateForPWM>
	inline void PWMPeripheral<templateargsForPWM>::_Initialize(Port_t port1, Pin_t pin1, Port_t port2, Pin_t pin2, Port_t port3, Pin_t pin3, Port_t port4, Pin_t pin4, Port_t port5, Pin_t pin5)
	{
		 
	}
 