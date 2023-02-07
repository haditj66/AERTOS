#include "AEUART.h"


#ifdef __cplusplus
extern "C" {
#endif 


	
	 


	
	//put all your interupt calls in here
	
#ifdef UARTPERIPHERAL1
	void USART1_IRQHandler(void)
	{
		HAL_UART_IRQHandler(&UARTPERIPHERAL1_Instance->PeripheralHandle_t);
	} 
#endif
#ifdef UARTPERIPHERAL2
	void USART2_IRQHandler(void)
	{
		HAL_UART_IRQHandler(&UARTPERIPHERAL2_Instance->PeripheralHandle_t);
	} 
#endif
	
	
	
	
	
	
	
	
	
	void HAL_UART_TxCpltCallback(UART_HandleTypeDef* UartHandle)
	{
		
		AEUART* foruart;
		
#ifdef UARTPERIPHERAL1
		if (UartHandle->Instance = USART1)
		{
			//			 forUartHandle = &UARTPERIPHERAL1_Instance->PeripheralHandle_t;
			foruart = UARTPERIPHERAL1_Name; 
		}
#endif
#ifdef UARTPERIPHERAL2
		if (UartHandle->Instance = USART2)
		{
			//			forUartHandle = &UARTPERIPHERAL2_Instance->PeripheralHandle_t;
			foruart = UARTPERIPHERAL2_Name; 
		}
#endif
		
#ifdef UARTPERIPHERAL6
		if (UartHandle->Instance = USART6)
		{ 
			foruart = UARTPERIPHERAL6_Name; 
		}
#endif
		
		foruart->_TxCpltCallback_t( );
	}
	
	
	
	
	
	
	
	
	
	
	
	
	int8_t command;
	int8_t counter2 = 0;
	char  buf2[30];
	void HAL_UART_RxCpltCallback(UART_HandleTypeDef* UartHandle)
	{
		
//		UART_HandleTypeDef* forUartHandle;
		AEUART* foruart;
#ifdef UARTPERIPHERAL1
		if (UartHandle->Instance = USART1)
		{
//			 forUartHandle = &UARTPERIPHERAL1_Instance->PeripheralHandle_t;
			 foruart = UARTPERIPHERAL1_Name; 
		}
#endif

#ifdef UARTPERIPHERAL2
		if (UartHandle->Instance = USART2)
		{
//			forUartHandle = &UARTPERIPHERAL2_Instance->PeripheralHandle_t;
			foruart = UARTPERIPHERAL2_Name; 
		}
#endif
		
#ifdef UARTPERIPHERAL6
		if (UartHandle->Instance = USART6)
		{ 
			foruart = UARTPERIPHERAL6_Name; 
		}
#endif
		
//		int sizeOfmsg = 0;
//		for (size_t i = 0; i < foruart->_ReceiveMsgSize; i++)
//		{
//			foruart->_ReadBuffer
//		}
		 
//		foruart->_RxCpltCallback_t(UARTPERIPHERAL2_Name->_ReadBuffer, UARTPERIPHERAL2_Name->_ReceiveMsgSize);
		
		foruart->RXDataCallback();
//		buf2[counter2] = foruart->_ReadBuffer[0];counter2++;
//		if (counter2 >20)
//		{
//		foruart->_RxCpltCallback_t(buf2,1); //(foruart->_ReadBuffer, 1);// foruart->_ReceiveMsgSize);
//			counter2 = 0;
//		 
//		}
		
		HAL_UART_Receive_IT(foruart->_uartHandle, (uint8_t*)foruart->_ReadBuffer, 1);//foruart->_ReceiveMsgSize);

	}
	//UserCode_Section0_end

#ifdef __cplusplus
}
#endif