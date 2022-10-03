#ifndef _MBCS



// this library uses uart2 and PA2 and PA3 as TX and RX-------------------------------------
#ifndef UARTConsole_h
#define UARTConsole_h

#include "AEConfig.h"

#ifndef Target_RealUART

#ifdef __cplusplus
 extern "C" {
#endif
#include "stm32f4xx_hal.h"

   
   
typedef struct
{
  uint32_t BaudRate;        
}UARTConsole_InitTypeDef;

__weak void UartRxCommand1Callback(void);
__weak void UartRxCommand2Callback(void); 
__weak void UartRxCommand3Callback(void); 
__weak void UartRxCommand4Callback(void);
__weak void UartRxCommand5Callback(void);


void Init_UARTConsole(UARTConsole_InitTypeDef* UartConsole_init);
void TransmitMsg(char const* s, int num);
char* ReceiveMsg(void);



#ifdef __cplusplus
}
#endif

#endif // __STM32F4xx_HAL_UART_H 


#endif


#endif