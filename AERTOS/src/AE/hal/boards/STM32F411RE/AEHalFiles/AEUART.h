#pragma once

#include "AEUARTPeripheral.h"







inline void AEUART::_TansmitMsg(char const*  msg, uint32_t size) 
{ 
	while (HAL_UART_GetState(_uartHandle) == HAL_UART_STATE_BUSY_TX)
	{
	} 
	HAL_UART_Transmit_DMA(_uartHandle, (uint8_t*)msg, size);
	//HAL_UART_Transmit_IT(_uartHandle, (uint8_t*)msg, size);
	
} 
 

inline bool AEUART::GetIsStateIsBusy() const 
{ 
	return (HAL_UART_GetState(_uartHandle) == HAL_UART_STATE_BUSY_TX); 
} 
 




template<templateForUART>
	inline void UARTPeripheral<templateargsForUART>::_InitializePinSelectors(CreateTypeSelector_funcPtr(&functPtrsToChangeTypeSelectorss)[2])
	{
		
 
			StartPinSelectorForPin(1)
				M_IncludePossiblePin(Portenum::PortA, PinEnum::PIN2)
				M_IncludePossiblePin(Portenum::PortD, PinEnum::PIN5)
			EndPinSelectorForPin
			
			StartPinSelectorForPin(2)
				M_IncludePossiblePin(Portenum::PortA, PinEnum::PIN3)
				M_IncludePossiblePin(Portenum::PortD, PinEnum::PIN6)
			EndPinSelectorForPin
  
	}
 


template<templateForUART>
	inline void UARTPeripheral<templateargsForUART>::_Initialize(Port_t port1, Pin_t pin1, Port_t port2, Pin_t pin2, Port_t port3, Pin_t pin3, Port_t port4, Pin_t pin4, Port_t port5, Pin_t pin5)
	{
		
		if (true)
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
		
			UART_Port = port1;
			UART_Pin =  pin1;
			TX_Port = port2;
			TX_Pin =  pin2;
			RX_Port = port3;
			RX_Pin =  pin3;
 
			//initialize the real peripheral here
		
			USART_TypeDef* uartInstance;
			
			if (this->ForWhichPeripheralNumber == 1)
			{
				uartInstance = USART1;
				__HAL_RCC_USART1_CLK_ENABLE(); 
			
				HAL_NVIC_SetPriority(USART1_IRQn, 6, 0);
				HAL_NVIC_EnableIRQ(USART1_IRQn);
			} 
			else if (this->ForWhichPeripheralNumber == 2)
			{
				uartInstance = USART2;
				__HAL_RCC_USART2_CLK_ENABLE();
			
				HAL_NVIC_SetPriority(USART2_IRQn, 6, 0);
				HAL_NVIC_EnableIRQ(USART2_IRQn);
			
			} 
			else if (this->ForWhichPeripheralNumber  == 6)
			{
				uartInstance = USART6;
				__HAL_RCC_USART6_CLK_ENABLE();
			
				HAL_NVIC_SetPriority(USART6_IRQn, 6, 0);
				HAL_NVIC_EnableIRQ(USART6_IRQn);
			} 
			else
			{
				AEAssertRuntime(false, "you picked a uart instance that is not supported");
			}

			//PA2     ------> USART2_TX
			//PA3     ------> USART2_RX 

			GPIO_InitTypeDef GPIO_InitStruct;
			GPIO_InitStruct.Pin = pin1;
			GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
			GPIO_InitStruct.Pull = GPIO_PULLUP;
			GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
			GPIO_InitStruct.Alternate = GPIO_AF7_USART2;
			HAL_GPIO_Init(port1, &GPIO_InitStruct);

			GPIO_InitStruct.Pin = pin2;
			GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
			GPIO_InitStruct.Pull = GPIO_PULLUP;
			GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
			GPIO_InitStruct.Alternate = GPIO_AF7_USART2;
			HAL_GPIO_Init(port2, &GPIO_InitStruct);



			this->PeripheralHandle_t.Instance = uartInstance;
			this->PeripheralHandle_t.Init.BaudRate = BaudRate; //460800 * 2;    //460800;//UartConsole_init->BaudRate;//115200;
			this->PeripheralHandle_t.Init.WordLength = UART_WORDLENGTH_8B;
			this->PeripheralHandle_t.Init.StopBits = UART_STOPBITS_1;
			this->PeripheralHandle_t.Init.Parity = UART_PARITY_NONE;
			this->PeripheralHandle_t.Init.Mode = UART_MODE_TX_RX;
			this->PeripheralHandle_t.Init.HwFlowCtl = UART_HWCONTROL_NONE;
			this->PeripheralHandle_t.Init.OverSampling = UART_OVERSAMPLING_16;
			int isUartWorking = HAL_UART_Init(&this->PeripheralHandle_t);
			if (isUartWorking != HAL_OK)
			{
				//_Error_Handler(__FILE__, __LINE__);
			}

	


			UART_HandleTypeDef* uardhandle =  &this->PeripheralHandle_t;
		


			dmaForUART.SetCustomInitialization([](DMAHandleType_t* DMAHandle, DMAStreamType_t* DMAStream, uint32_t dmaChannel)-> void {
			
				__HAL_RCC_DMA1_CLK_ENABLE();
				DMAHandle->Instance = *DMAStream;
				DMAHandle->Init.Channel = dmaChannel;
				DMAHandle->Init.Direction = DMA_MEMORY_TO_PERIPH;
				DMAHandle->Init.PeriphInc = DMA_PINC_DISABLE;
				DMAHandle->Init.MemInc = DMA_MINC_ENABLE;
				DMAHandle->Init.PeriphDataAlignment = DMA_PDATAALIGN_BYTE;
				DMAHandle->Init.MemDataAlignment = DMA_MDATAALIGN_BYTE;
				DMAHandle->Init.Mode = DMA_NORMAL;
				DMAHandle->Init.Priority = DMA_PRIORITY_MEDIUM;
				DMAHandle->Init.FIFOMode = DMA_FIFOMODE_DISABLE;
				DMAHandle->Init.FIFOThreshold = DMA_FIFO_THRESHOLD_FULL;
				DMAHandle->Init.MemBurst = DMA_MBURST_INC4;
				DMAHandle->Init.PeriphBurst = DMA_PBURST_INC4;
				//hdma_uart2_TX.XferCpltCallback = &DMATransferComplete;
				HAL_DMA_Init(DMAHandle); 
			});
		
			dmaForUART.Init(&this->PeripheralHandle_t, 1, DMA_StreamEnum::DMAStream_6, DMACHEnum::DMACH4, DMA_NORMAL);
			__HAL_LINKDMA(uardhandle, hdmatx, *dmaForUART.GetDMAHandle());  
			
			//start recieving
			HAL_UART_Receive_IT(&this->PeripheralHandle_t, (uint8_t*)readBuffer, 2); //ReceiveMsgSize);
		}
	
		else
		{
			__HAL_RCC_USART2_CLK_ENABLE();

			__HAL_RCC_GPIOA_CLK_ENABLE();
			/**USART2 GPIO Configuration
			PA2     ------> USART2_TX
			PA3     ------> USART2_RX
			*/
			GPIO_InitTypeDef GPIO_InitStruct;
			GPIO_InitStruct.Pin = GPIO_PIN_2 | GPIO_PIN_3;
			GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
			GPIO_InitStruct.Pull = GPIO_NOPULL;
			GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
			GPIO_InitStruct.Alternate = GPIO_AF7_USART2;
			HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

			/* USART2 interrupt Init */
			HAL_NVIC_SetPriority(USART2_IRQn, 6, 0);
			HAL_NVIC_EnableIRQ(USART2_IRQn);
			/* USER CODE BEGIN USART2_MspInit 1 */
		
			this->PeripheralHandle_t.Instance = USART2;
			this->PeripheralHandle_t.Init.BaudRate = 115200;
			this->PeripheralHandle_t.Init.WordLength = UART_WORDLENGTH_8B;
			this->PeripheralHandle_t.Init.StopBits = UART_STOPBITS_1;
			this->PeripheralHandle_t.Init.Parity = UART_PARITY_NONE;
			this->PeripheralHandle_t.Init.Mode = UART_MODE_TX_RX;
			this->PeripheralHandle_t.Init.HwFlowCtl = UART_HWCONTROL_NONE;
			this->PeripheralHandle_t.Init.OverSampling = UART_OVERSAMPLING_16;
			if (HAL_UART_Init(&this->PeripheralHandle_t) != HAL_OK)
			{
				AEPrint("sdf");
			}
			
			//start recieving
			HAL_UART_Receive_IT(&this->PeripheralHandle_t, (uint8_t*)readBuffer, 1); //ReceiveMsgSize);
		}
		
		

		
		
 
	}
 