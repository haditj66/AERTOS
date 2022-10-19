#pragma once
#include "AEUtilityAsService.h" 

#include "AEPublishSubscribeManager.h"

#include "ActionRequestForUARTTransmit.h"
 
#include "AE_TDUAsService.h"

#include  "ActionRequestForUARTTransmitTDU.h"
 
class UUartDriver : public AEUtilityAsService<10,ActionRequestForUARTTransmit>
{
public:
	 
	UUartDriver()
	{ 
		//UARTPERIPHERAL2_Instance->AE_UART_RxCpltCallback = UartdriverRXCallback;
		 
	}; 

};



class UUartDriverTDU : public AETDUAsService<10, ActionRequestForUARTTransmitTDU>
{
public: 

	//this tdu needs the Uuartdriver utility.  
	UUartDriverTDU()
	{ 
		//UARTPERIPHERAL2_Instance->AE_UART_RxCpltCallback = UartdriverRXCallback;
		 
	}
	; 
	  

};