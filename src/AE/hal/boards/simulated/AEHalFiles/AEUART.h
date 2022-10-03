#pragma once

#include "AEUARTPeripheral.h"







inline void AEUART::TansmitMsg(char const*  msg, uint32_t size) 
{ 
	AEPrint("%s\n", msg);
	
	//fire the fake interrupt?
	_TxCpltCallback_t();
} 
 





template<templateForUART>
	inline void UARTPeripheral<templateargsForUART>::_InitializePinSelectors(CreateTypeSelector_funcPtr(&functPtrsToChangeTypeSelectorss)[2])
	{
		
 
			StartPinSelectorForPin(1)
				M_AnyPinIsPossible
			EndPinSelectorForPin
			
			StartPinSelectorForPin(2)
				M_AnyPinIsPossible
			EndPinSelectorForPin
  
	}
 


template<templateForUART>
	inline void UARTPeripheral<templateargsForUART>::_Initialize(Port_t port1, Pin_t pin1, Port_t port2, Pin_t pin2, Port_t port3, Pin_t pin3, Port_t port4, Pin_t pin4, Port_t port5, Pin_t pin5)
	{
		
		//make sure baude rate is valid
		bool validBaud = (BaudRate == 1200) ||
			(BaudRate == 2400) ||
			(BaudRate == 4800) ||
			(BaudRate == 19200) ||
			(BaudRate == 38400) ||
			(BaudRate == 57600) ||
			(BaudRate == 115200) ||
			(BaudRate == 460800) ||
			(BaudRate == 921600);
		
		AEAssertRuntime(validBaud, "you picked an invalid baud rate");
		 
 
	}
 