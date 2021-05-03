#pragma once


#define GPIOPERIPHERAL1_INITIALIZE
#define GPIOPERIPHERAL2_INITIALIZE
#define GPIOPERIPHERAL3_INITIALIZE
#define GPIOPERIPHERAL4_INITIALIZE
#define GPIOPERIPHERAL5_INITIALIZE
#define GPIOPERIPHERAL6_INITIALIZE


#define GPIOInputPERIPHERAL1_INITIALIZE
#define GPIOInputPERIPHERAL2_INITIALIZE
#define GPIOInputPERIPHERAL3_INITIALIZE
#define GPIOInputPERIPHERAL4_INITIALIZE
#define GPIOInputPERIPHERAL5_INITIALIZE
#define GPIOInputPERIPHERAL6_INITIALIZE


#define ADCPERIPHERAL1_INITIALIZE
#define ADCPERIPHERAL2_INITIALIZE
#define ADCPERIPHERAL3_INITIALIZE
#define ADCPERIPHERAL4_INITIALIZE
#define ADCPERIPHERAL5_INITIALIZE
#define ADCPERIPHERAL6_INITIALIZE

#define UARTPERIPHERAL1_INITIALIZE
#define UARTPERIPHERAL2_INITIALIZE
#define UARTPERIPHERAL3_INITIALIZE
#define UARTPERIPHERAL4_INITIALIZE
#define UARTPERIPHERAL5_INITIALIZE
#define UARTPERIPHERAL6_INITIALIZE


#ifdef USING_AEGPIOOutput 
#include "AEGPIOOutput.h"
#endif
#ifdef USING_AEGPIOInput
#include "AEGPIOInput.h"
#endif  
#ifdef USING_AEADC 
#include "AEADC.h"
#endif 
#ifdef USING_AEUART 
#include "AEUART.h"
#endif 


#define InitializeAllPeripheral                                                \
  GPIOPERIPHERAL1_INITIALIZE                                                   \
  GPIOPERIPHERAL2_INITIALIZE                                                   \
  GPIOPERIPHERAL3_INITIALIZE                                                   \
  GPIOPERIPHERAL4_INITIALIZE                                                   \
  GPIOPERIPHERAL5_INITIALIZE                                                   \
  GPIOPERIPHERAL6_INITIALIZE												    \
  GPIOInputPERIPHERAL1_INITIALIZE                                                   \
  GPIOInputPERIPHERAL2_INITIALIZE                                                   \
  GPIOInputPERIPHERAL3_INITIALIZE                                                   \
  GPIOInputPERIPHERAL4_INITIALIZE                                                   \
  GPIOInputPERIPHERAL5_INITIALIZE                                                   \
  GPIOInputPERIPHERAL6_INITIALIZE													\
	ADCPERIPHERAL1_INITIALIZE \
ADCPERIPHERAL2_INITIALIZE \
ADCPERIPHERAL3_INITIALIZE \
ADCPERIPHERAL4_INITIALIZE \
ADCPERIPHERAL5_INITIALIZE \
ADCPERIPHERAL6_INITIALIZE \
	UARTPERIPHERAL1_INITIALIZE \
	UARTPERIPHERAL2_INITIALIZE \
	UARTPERIPHERAL3_INITIALIZE \
	UARTPERIPHERAL4_INITIALIZE \
	UARTPERIPHERAL5_INITIALIZE \
	UARTPERIPHERAL6_INITIALIZE
	
		//