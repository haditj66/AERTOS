#ifndef _MBCS


#include "UARTConsole.h"
#include "string.h"  
#include "stm32f4xx_hal.h" 



#ifndef Target_RealUART

  DMA_HandleTypeDef hdma_uart2_TX;
  static char buffer[100];
  static char readBuffer[100]; 
  UART_HandleTypeDef huart2;
 
void Init_UARTConsole(UARTConsole_InitTypeDef* UartConsole_init) 
{
      __GPIOA_CLK_ENABLE();
    __HAL_RCC_USART2_CLK_ENABLE();
   
    //PA2     ------> USART2_TX
    //PA3     ------> USART2_RX 
     
    GPIO_InitTypeDef GPIO_InitStruct;
    GPIO_InitStruct.Pin = GPIO_PIN_2|GPIO_PIN_3;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Pull = GPIO_PULLUP;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
    GPIO_InitStruct.Alternate = GPIO_AF7_USART2;
    HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

    
    
  huart2.Instance = USART2;
  huart2.Init.BaudRate = UartConsole_init->BaudRate;//115200;
  huart2.Init.WordLength = UART_WORDLENGTH_8B;
  huart2.Init.StopBits = UART_STOPBITS_1;
  huart2.Init.Parity = UART_PARITY_NONE;
  huart2.Init.Mode = UART_MODE_TX_RX;
  huart2.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  huart2.Init.OverSampling = UART_OVERSAMPLING_16;
  int isUartWorking = HAL_UART_Init(&huart2);
  if ( isUartWorking != HAL_OK) 
  {
    //_Error_Handler(__FILE__, __LINE__);
  }
    
    HAL_NVIC_SetPriority(USART2_IRQn, 5, 0);
  HAL_NVIC_EnableIRQ(USART2_IRQn); 
  
  
  //---------------------------------------------set up DMA 
  //this will be for DMA request USART2_TX . which is bounded to at DMA1 channel 4 stream 6
  __HAL_RCC_DMA1_CLK_ENABLE();
  hdma_uart2_TX.Instance = DMA1_Stream6;
  hdma_uart2_TX.Init.Channel = DMA_CHANNEL_4;
  hdma_uart2_TX.Init.Direction = DMA_MEMORY_TO_PERIPH;
  hdma_uart2_TX.Init.PeriphInc = DMA_PINC_DISABLE;
  hdma_uart2_TX.Init.MemInc  =DMA_MINC_ENABLE;
  hdma_uart2_TX.Init.PeriphDataAlignment = DMA_PDATAALIGN_BYTE;
  hdma_uart2_TX.Init.MemDataAlignment = DMA_MDATAALIGN_BYTE;
  hdma_uart2_TX.Init.Mode = DMA_NORMAL;
  hdma_uart2_TX.Init.Priority = DMA_PRIORITY_MEDIUM;
  hdma_uart2_TX.Init.FIFOMode            = DMA_FIFOMODE_DISABLE;
  hdma_uart2_TX.Init.FIFOThreshold       = DMA_FIFO_THRESHOLD_FULL;
  hdma_uart2_TX.Init.MemBurst            = DMA_MBURST_INC4;
  hdma_uart2_TX.Init.PeriphBurst         = DMA_PBURST_INC4;
  //hdma_uart2_TX.XferCpltCallback = &DMATransferComplete;
  HAL_DMA_Init(&hdma_uart2_TX);
  
  __HAL_LINKDMA(&huart2, hdmatx, hdma_uart2_TX); 
  
     
  HAL_NVIC_SetPriority(DMA1_Stream6_IRQn,5,0);
  HAL_NVIC_EnableIRQ(DMA1_Stream6_IRQn);
  
  //start recieving
  HAL_UART_Receive_IT(&huart2,(uint8_t*)readBuffer, 1);
}



void TransmitMsg(char const* s, int num)
{
  snprintf(buffer,100,s, num);
  HAL_UART_Transmit_DMA(&huart2, (uint8_t*)buffer, sizeof(buffer));
 
}

char* ReceiveMsg(void){
  
  //HAL_UART_Receive_IT(&huart2,(uint8_t*)readBuffer, 1);
  return readBuffer;

}


void DMA1_Stream6_IRQHandler(void)
{
   HAL_DMA_IRQHandler(&hdma_uart2_TX);
  
}

void USART2_IRQHandler(void)
{ 
  HAL_UART_IRQHandler(&huart2);
}


 
int8_t command;
void HAL_UART_RxCpltCallback(UART_HandleTypeDef *UartHandle)
{
  
   HAL_UART_Receive_IT(&huart2,(uint8_t*)readBuffer, 1); 
   
   
   
   //now go through the console and call correct function
   //convert readBuffer to num
   command= atoi(readBuffer);
   
   if(command == 1)
   {
     UartRxCommand1Callback();
   }
   else if(command == 2)
   {
     UartRxCommand2Callback();
   }
   else if(command == 3)
   {
     UartRxCommand3Callback();
   }
   else if(command == 4)
   {
     UartRxCommand4Callback();
   }
   else if(command == 5)
   {
     UartRxCommand5Callback();
   } 
   
}


__weak void Command1Callback( ) 
{ }
__weak void Command2Callback( ) 
{ }
__weak void Command3Callback( ) 
{ }
__weak void Command4Callback( ) 
{ }
__weak void Command5Callback( ) 
{ }
   

#endif


#endif