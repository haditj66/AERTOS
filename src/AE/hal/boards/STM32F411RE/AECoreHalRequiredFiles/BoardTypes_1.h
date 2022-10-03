#pragma once
  

#define Port_t GPIO_TypeDef* 
#define Pin_t uint16_t 
#define DMAStreamType_t DMA_Stream_TypeDef*
#define DMAHandleType_t DMA_HandleTypeDef
#define DMA_Numbers_Of_DMA 2


//Gpio output
#define GPIO_Handle char

//Gpio input
#define GPIOInput_Handle char
  
 
//ADC 
#define ADC_Handle ADC_HandleTypeDef

//uart
#define UART_Handle UART_HandleTypeDef

//I2C
#define I2C_Handle I2C_HandleTypeDef