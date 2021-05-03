#pragma once 
#include "AEPeripheral.h"
#include "BoardTypes.h"

#include "AEConfig.h"


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
	AEUART() {}
	;
	
	
	void TansmitMsg(char const*  msg, uint32_t size);
 

	
	void SetRxCpltCallback(AE_UART_RxCpltCallback_t rxCpltCallback_t) {_RxCpltCallback_t = rxCpltCallback_t; }
	void SetTxCpltCallback(AE_UART_TxCpltCallback_t txCpltCallback_t) {_TxCpltCallback_t = txCpltCallback_t; }
	 

	void Init(UART_Handle* uartHandle, char* const readBuffer, uint32_t receiveMsgSize) {
		_uartHandle = uartHandle;
		_ReadBuffer = readBuffer;
		_ReceiveMsgSize = receiveMsgSize;
	}
	;
	
	AE_UART_RxCpltCallback_t _RxCpltCallback_t;
	AE_UART_TxCpltCallback_t _TxCpltCallback_t;
	
	char* _ReadBuffer;
	uint32_t _ReceiveMsgSize;
	
	UART_Handle* _uartHandle;
private: 
	
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
	
	char readBuffer[ReceiveMsgSize];
	

 
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
		
	AEUART* GetPeripheralInstance(){ this->InstanceOfUart.Init((&this->PeripheralHandle_t), readBuffer, ReceiveMsgSize); return &InstanceOfUart;}
		 

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


 
 








