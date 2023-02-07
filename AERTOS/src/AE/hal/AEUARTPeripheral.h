#pragma once 
#include "AEPeripheral.h"
#include "BoardTypes.h"

//#include "AEConfig.h"


#ifndef USING_AEUART 
#error you included this file but you did not provide a AEUART.h file in AEHalFiles directory.
#endif 

#ifdef USING_AEDMA 
#include "AEDMA.h"
#endif 




typedef void(*AE_UART_RxCpltCallback_t)(char* msgReceived, uint32_t sizeOfReceivedMsg); 
typedef void(*AE_UART_TxCpltCallback_t)(void);

class AEUART
{
public:
	AEUART() {
		_RxCpltCallback_t = [](char* msgReceived, uint32_t sizeOfReceivedMsg) -> void {};
		_TxCpltCallback_t = []() -> void {};
		

	}
	;
	
	void TansmitMsg(char const*  msg, uint32_t size)
	{
		rxBlocking = true;
		_TansmitMsg(msg, size);
	}
	void _TansmitMsg(char const*  msg, uint32_t size);
	bool GetIsStateIsBusy() const;
	
	///this shouldnt be called in normal circumstances as this is NOT THREAD SAFE
	const char* ReceiveMsgBlocking()
	{
		
		while (GetIsStateIsBusy() == true || rxBlocking == true)
		{ 
		}
		
		return this->_bufferBeforeTriggeringCallback;
	}
	   
	std::string ReceiveMsgBlocking_String()
	{  
		return AE_convertToString(ReceiveMsgBlocking(), RxSizeOfPreviousReceivedMsg) ;
	}

	
	void SetRxCpltCallback(AE_UART_RxCpltCallback_t rxCpltCallback_t) {_RxCpltCallback_t = rxCpltCallback_t; }
	void SetTxCpltCallback(AE_UART_TxCpltCallback_t txCpltCallback_t) {_TxCpltCallback_t = txCpltCallback_t; }
	 

	void Init(UART_Handle* uartHandle, char* const readBuffer, uint32_t receiveMsgSize, char* bufferBeforeTriggeringCallback) {
		_uartHandle = uartHandle;
		_ReadBuffer = readBuffer;
		_ReceiveMsgSize = receiveMsgSize;
		_ReceiveMsgSizeMax = receiveMsgSize;
		_bufferBeforeTriggeringCallback = bufferBeforeTriggeringCallback;
		
		isDelimiterTriggered = false;
		delimiter = '\n'; 
		counter = 0;
		
		rxBlocking = false;
		
		memset(_bufferBeforeTriggeringCallback, '\0', _ReceiveMsgSizeMax);
		
	}
	;
	
	void RecieveOnDelimiter(char theDelimiter)
	{
		isDelimiterTriggered = true;
		delimiter = theDelimiter;
		counter = 0;
	}
	
	void RecieveOnMsgSize(int32_t theSize)
	{
		//any new sizes needs to be less than the largest size possible
		AEAssertRuntime(theSize < _ReceiveMsgSizeMax, "RecieveOnMsgSize needs to be a size less than _ReceiveMsgSizeMax");
		
		isDelimiterTriggered = false;
		_ReceiveMsgSize = theSize;
		counter = 0;
	}
	
	void RXDataCallback()
	{ 
		
		_bufferBeforeTriggeringCallback[counter] =  _ReadBuffer[0]; counter++;
		if (counter >= _ReceiveMsgSize)
		{
			rxBlocking = false; 
			RxSizeOfPreviousReceivedMsg = counter;
			counter = 0;
			_RxCpltCallback_t(_bufferBeforeTriggeringCallback, RxSizeOfPreviousReceivedMsg); //(foruart->_ReadBuffer, 1);// foruart->_ReceiveMsgSize);
			
			
			//clear the buffer
			memset(_bufferBeforeTriggeringCallback, '\0', counter);
			return;
		 
		}
		 
		if (isDelimiterTriggered == true)
		{	 
			if (_ReadBuffer[0] == delimiter)
			{
				rxBlocking = false;
				RxSizeOfPreviousReceivedMsg = counter;
				counter = 0;
				_RxCpltCallback_t(_bufferBeforeTriggeringCallback, RxSizeOfPreviousReceivedMsg);
				 
				//clear the buffer
				memset(_bufferBeforeTriggeringCallback, '\0', counter); 
				return;
			}
			
		}
 
	}
	
	AE_UART_TxCpltCallback_t _TxCpltCallback_t;
	

	
	char* _ReadBuffer;
	uint32_t _ReceiveMsgSize;
	
	uint32_t GetRxSizeOfPreviousReceivedMsg() const{ return RxSizeOfPreviousReceivedMsg;}
	uint32_t GetMaxReceivedMsgSize() const{ return _ReceiveMsgSizeMax;}
	
	UART_Handle* _uartHandle;
private: 
	
	AE_UART_RxCpltCallback_t _RxCpltCallback_t;
	 
	uint32_t _ReceiveMsgSizeMax;
	
	bool rxBlocking;
	bool isDelimiterTriggered;
	char delimiter;
	
	char* _bufferBeforeTriggeringCallback;
	
	uint32_t counter;
	uint32_t RxSizeOfPreviousReceivedMsg;
}
;
 
  
 
  
#define NumOFPinsNeeded 2  
  
#define templateForUART  uint32_t BaudRate, uint32_t ReceiveMsgSize, Portenum UART_TX_Port, PinEnum UART_TX_Pin, Portenum UART_RX_Port, PinEnum UART_RX_Pin
#define templateargsForUART  BaudRate, ReceiveMsgSize, UART_TX_Port, UART_TX_Pin, UART_RX_Port, UART_RX_Pin
#define templateargsForHardware UART_TX_Port, UART_TX_Pin, UART_RX_Port, UART_RX_Pin
 




template<templateForUART>
	class UARTPeripheral :
		public AEPeripheral <UARTPeripheral<templateargsForUART>,
		NumOFPinsNeeded,
		UART_Handle,
		templateargsForHardware>
	{
		
		friend void AE_Init(void);
		
		friend class AEUART;
	public:
		
		
		
#ifdef USING_AEDMA 
		AEDMA dmaForUART;
#endif  
	
		char readBuffer[1]; //[ReceiveMsgSize];
		char bufferBeforeTriggeringCallback[ReceiveMsgSize]; //[ReceiveMsgSize];
	

 
	protected:
		Port_t UART_Port;
		Pin_t  UART_Pin;
		Port_t TX_Port;
		Pin_t  TX_Pin;
		Port_t RX_Port;
		Pin_t  RX_Pin;
		
		AEUART InstanceOfUart;





		// Inherited via HardwarePeripheral 
		void _InitializePinSelectors(CreateTypeSelector_funcPtr(&functPtrsToChangeTypeSelectorss)[2]) override;

 

		// Inherited via HardwarePeripheral
		void _Initialize(Port_t port1, Pin_t pin1, Port_t port2, Pin_t pin2, Port_t port3, Pin_t pin3, Port_t port4, Pin_t pin4, Port_t port5, Pin_t pin5)override;
		
		AEUART* GetPeripheralInstance(){ this->InstanceOfUart.Init((&this->PeripheralHandle_t), readBuffer, ReceiveMsgSize, bufferBeforeTriggeringCallback); return &InstanceOfUart;}
		 

	}
	;
	











//global pheripherals declaration
#ifdef UARTPERIPHERAL1
extern UARTPERIPHERAL1* UARTPERIPHERAL1_Instance;  
#define UARTPERIPHERAL1_INITIALIZE UARTPERIPHERAL1_Instance->ForWhichPeripheralNumber = 1; UARTPERIPHERAL1_Instance->initializePeripheral(); UARTPERIPHERAL1_Name = UARTPERIPHERAL1_Instance->GetPeripheralInstance();
#ifndef UARTPERIPHERAL1_Name
#error You need to define UARTPERIPHERAL1_Name
#else
extern  AEUART* UARTPERIPHERAL1_Name;
#endif
#endif 

#ifdef UARTPERIPHERAL2
extern UARTPERIPHERAL2* UARTPERIPHERAL2_Instance;  
#define UARTPERIPHERAL2_INITIALIZE UARTPERIPHERAL2_Instance->ForWhichPeripheralNumber = 2; UARTPERIPHERAL2_Instance->initializePeripheral(); UARTPERIPHERAL2_Name = UARTPERIPHERAL2_Instance->GetPeripheralInstance();
#ifndef UARTPERIPHERAL2_Name
#error You need to define UARTPERIPHERAL2_Name
#else
extern  AEUART* UARTPERIPHERAL2_Name;
#endif
#endif 


#ifdef UARTPERIPHERAL3
extern UARTPERIPHERAL3* UARTPERIPHERAL3_Instance;  
#define UARTPERIPHERAL3_INITIALIZE UARTPERIPHERAL3_Instance->ForWhichPeripheralNumber = 3; UARTPERIPHERAL3_Instance->initializePeripheral(); UARTPERIPHERAL3_Name = UARTPERIPHERAL3_Instance->GetPeripheralInstance();
#ifndef UARTPERIPHERAL3_Name
#error You need to define UARTPERIPHERAL3_Name
#else
extern  AEUART* UARTPERIPHERAL3_Name;
#endif
#endif 

#ifdef UARTPERIPHERAL4
extern UARTPERIPHERAL4* UARTPERIPHERAL4_Instance;  
#define UARTPERIPHERAL4_INITIALIZE UARTPERIPHERAL4_Instance->ForWhichPeripheralNumber = 4; UARTPERIPHERAL4_Instance->initializePeripheral(); UARTPERIPHERAL4_Name = UARTPERIPHERAL4_Instance->GetPeripheralInstance();
#ifndef UARTPERIPHERAL4_Name
#error You need to define UARTPERIPHERAL4_Name
#else
extern  AEUART* UARTPERIPHERAL4_Name;
#endif
#endif 

#ifdef UARTPERIPHERAL5
extern UARTPERIPHERAL5* UARTPERIPHERAL5_Instance;  
#define UARTPERIPHERAL5_INITIALIZE UARTPERIPHERAL5_Instance->ForWhichPeripheralNumber = 5; UARTPERIPHERAL5_Instance->initializePeripheral(); UARTPERIPHERAL5_Name = UARTPERIPHERAL5_Instance->GetPeripheralInstance();
#ifndef UARTPERIPHERAL5_Name
#error You need to define UARTPERIPHERAL5_Name
#else
extern  AEUART* UARTPERIPHERAL5_Name;
#endif
#endif 

#ifdef UARTPERIPHERAL6
extern UARTPERIPHERAL6* UARTPERIPHERAL6_Instance;  
#define UARTPERIPHERAL6_INITIALIZE UARTPERIPHERAL6_Instance->ForWhichPeripheralNumber = 6; UARTPERIPHERAL6_Instance->initializePeripheral(); UARTPERIPHERAL6_Name = UARTPERIPHERAL6_Instance->GetPeripheralInstance();
#ifndef UARTPERIPHERAL6_Name
#error You need to define UARTPERIPHERAL6_Name
#else
extern  AEUART* UARTPERIPHERAL6_Name;
#endif
#endif 


 
 








