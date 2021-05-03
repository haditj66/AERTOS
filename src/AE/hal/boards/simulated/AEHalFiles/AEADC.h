
#pragma once
#include "AEADCPeripheral.h"










template<templateForADC>
	inline void ADCPeripheral<templateargsForADC>::_InitializePinSelectors(CreateTypeSelector_funcPtr(&functPtrsToChangeTypeSelectorss)[NumOFPinsNeeded])
	{
		/*
			this->functPtrsToChangeTypeSelectors[0] = []() -> void
			{PinSelector::getInstance()->IncludePossiblePin(Portenum::PortA, PinEnum::PIN2);
			PinSelector::getInstance()->IncludePossiblePin(Portenum::PortD, PinEnum::PIN5); };

			this->functPtrsToChangeTypeSelectors[1] = []() -> void
			{PinSelector::getInstance()->IncludePossiblePin(Portenum::PortA, PinEnum::PIN3);
			PinSelector::getInstance()->IncludePossiblePin(Portenum::PortD, PinEnum::PIN6); }; 
			*/
		//UserCode_Section4
		this->functPtrsToChangeTypeSelectors[0] = []() -> void
		{ 
			PinSelector::getInstance()->AnyPinIsPossible(); 
		};
		this->functPtrsToChangeTypeSelectors[1] = []() -> void
		{
			PinSelector::getInstance()->AnyPinIsPossible();
		};
		this->functPtrsToChangeTypeSelectors[2] = []() -> void
		{
			PinSelector::getInstance()->AnyPinIsPossible();
		};
		this->functPtrsToChangeTypeSelectors[3] = []() -> void
		{
			PinSelector::getInstance()->AnyPinIsPossible();
		};
		this->functPtrsToChangeTypeSelectors[4] = []() -> void
		{
			PinSelector::getInstance()->AnyPinIsPossible();
		};
		//UserCode_Section4_end


	}




template<templateForADC>
	inline void ADCPeripheral<templateargsForADC>::_Initialize(Port_t port1, Pin_t pin1, Port_t port2, Pin_t pin2, Port_t port3, Pin_t pin3, Port_t port4, Pin_t pin4, Port_t port5, Pin_t pin5)
	{
		
		
		 
 
	}
 