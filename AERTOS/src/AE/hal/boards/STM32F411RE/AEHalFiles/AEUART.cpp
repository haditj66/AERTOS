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
	
	
	int8_t command;
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
		 
//		foruart->_RxCpltCallback_t(UARTPERIPHERAL2_Name->_ReadBuffer, UARTPERIPHERAL2_Name->_ReceiveMsgSize);
		foruart->_RxCpltCallback_t(foruart->_ReadBuffer, foruart->_ReceiveMsgSize);
		
		HAL_UART_Receive_IT(foruart->_uartHandle, (uint8_t*)foruart->_ReadBuffer, foruart->_ReceiveMsgSize);

	}
	//UserCode_Section0_end

#ifdef __cplusplus
}
#endif