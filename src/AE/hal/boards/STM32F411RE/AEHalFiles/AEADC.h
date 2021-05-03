
#pragma once
#include "AEADCPeripheral.h"










template<templateForADC>
	inline void ADCPeripheral<templateargsForADC>::_InitializePinSelectors(CreateTypeSelector_funcPtr(&functPtrsToChangeTypeSelectorss)[NumOFPinsNeeded])
	{
		/*
			this->functPtrsToChangeTypeSelectors[0] = []() -> void
			{PinSelector::getInstance()->IncludePossiblePin(Portenum::PortA, PinEnum::PIN2);
			PinSelector::getInstance()->IncludePossiblePin(Portenum::PortD, PinEnum::PIN5); };

			this->functPtrsToChangeTypeSelectors[1] = []() -> void
			{PinSelector::getInstance()->IncludePossiblePin(Portenum::PortA, PinEnum::PIN3);
			PinSelector::getInstance()->IncludePossiblePin(Portenum::PortD, PinEnum::PIN6); }; 
			*/
		//UserCode_Section4
		this->functPtrsToChangeTypeSelectors[0] = []() -> void
		{ 
			PinSelector::getInstance()->IncludePossiblePin(Portenum::PortB, PinEnum::PIN0); 
		};
		this->functPtrsToChangeTypeSelectors[1] = []() -> void
		{
			PinSelector::getInstance()->IncludePossiblePin(Portenum::PortA, PinEnum::PIN2); 
		};
		this->functPtrsToChangeTypeSelectors[2] = []() -> void
		{
			PinSelector::getInstance()->IncludePossiblePin(Portenum::PortA, PinEnum::PIN3);
		};
		this->functPtrsToChangeTypeSelectors[3] = []() -> void
		{
			PinSelector::getInstance()->IncludePossiblePin(Portenum::PortA, PinEnum::PIN4);
		};
		this->functPtrsToChangeTypeSelectors[4] = []() -> void
		{
			PinSelector::getInstance()->IncludePossiblePin(Portenum::PortA, PinEnum::PIN5);
		};
		//UserCode_Section4_end


	}




template<templateForADC>
	inline void ADCPeripheral<templateargsForADC>::_Initialize(Port_t port1, Pin_t pin1, Port_t port2, Pin_t pin2, Port_t port3, Pin_t pin3, Port_t port4, Pin_t pin4, Port_t port5, Pin_t pin5)
	{
		
		//TODO this should be moved to a preinitialization like the msp_init()
//		ch1_Port = port1;
//		ch1_Pin =  pin1;
//		ch2_Port = port2;
//		ch2_Pin =  pin2;
//		ch3_Port = port3;
//		ch3_Pin =  pin3;
//		ch4_Port = port4;
//		ch4_Pin =  pin4;
//		ch5_Port = port5;
//		ch5_Pin =  pin5;
  
		ADC_HandleTypeDef* adc_periph = &this->PeripheralHandle_t;
		
		
		
		
		dmaForADC.Init(adc_periph,2, DMA_StreamEnum::DMAStream_0, DMACHEnum::DMACH0, DMA_CIRCULAR);
		__HAL_LINKDMA(adc_periph, DMA_Handle, *dmaForADC.GetDMAHandle());  
		
//		DMA_HandleTypeDef* hdma_adc = dmaForADC.GetDMAHandle();// &hdma_adcc;  //this->PeripheralHandle_t.hdma_adc;
 
//					__HAL_RCC_DMA2_CLK_ENABLE();
//				hdma_adc->Instance = DMA2_Stream0;
//				hdma_adc->Init.Channel = DMA_CHANNEL_0;
//				hdma_adc->Init.Direction = DMA_PERIPH_TO_MEMORY;
//				hdma_adc->Init.PeriphBurst = DMA_PINC_DISABLE;
//				hdma_adc->Init.MemInc = DMA_MINC_ENABLE;
//				hdma_adc->Init.PeriphDataAlignment = DMA_PDATAALIGN_HALFWORD;
//				hdma_adc->Init.MemDataAlignment = DMA_MDATAALIGN_HALFWORD;
//				hdma_adc->Init.Mode = DMA_CIRCULAR;
//				hdma_adc->Init.Priority = DMA_PRIORITY_LOW;
//				hdma_adc->Init.FIFOMode = DMA_FIFOMODE_DISABLE;
//				HAL_DMA_Init(hdma_adc);
//		
//				__HAL_LINKDMA(adc_periph, DMA_Handle, *hdma_adc);
//		
//				HAL_NVIC_SetPriority(DMA2_Stream0_IRQn, 5, 0);
//				HAL_NVIC_EnableIRQ(DMA2_Stream0_IRQn);


		
		


				/* ADC1 interrupt Init */
				HAL_NVIC_SetPriority(ADC_IRQn, 5, 0);
		HAL_NVIC_EnableIRQ(ADC_IRQn);


		ADC_ChannelConfTypeDef sConfig;
		__HAL_RCC_ADC1_CLK_ENABLE();
        
		uint8_t numOfChannelsUsed = 0;
		if (ADC_ch1_Port != PortsMaxNum)
		{ 
			//set up the gpios that I will use for the ADC channels in analog mode 
			GPIO_InitTypeDef GPIO_InitStruct;
			GPIO_InitStruct.Pin = pin1;
			GPIO_InitStruct.Mode = GPIO_MODE_ANALOG;
			GPIO_InitStruct.Pull = GPIO_PULLDOWN;
			HAL_GPIO_Init(port1, &GPIO_InitStruct);
          
          
			numOfChannelsUsed++;
		}
		if (ADC_ch2_Port != PortsMaxNum)
		{ 
			GPIO_InitTypeDef GPIO_InitStruct;
			GPIO_InitStruct.Pin = pin2;
			GPIO_InitStruct.Mode = GPIO_MODE_ANALOG;
			GPIO_InitStruct.Pull = GPIO_PULLDOWN;
			HAL_GPIO_Init(port2, &GPIO_InitStruct);
          
			numOfChannelsUsed++;
		} 
		if (ADC_ch3_Port != PortsMaxNum)
		{ 
          
			GPIO_InitTypeDef GPIO_InitStruct;
			GPIO_InitStruct.Pin = pin3;
			GPIO_InitStruct.Mode = GPIO_MODE_ANALOG;
			GPIO_InitStruct.Pull = GPIO_PULLDOWN;
			HAL_GPIO_Init(port3, &GPIO_InitStruct);
          
			numOfChannelsUsed++;
		}
		if (ADC_ch4_Port != PortsMaxNum)
		{ 
          
			GPIO_InitTypeDef GPIO_InitStruct;
			GPIO_InitStruct.Pin = pin4;
			GPIO_InitStruct.Mode = GPIO_MODE_ANALOG;
			GPIO_InitStruct.Pull = GPIO_PULLDOWN;
			HAL_GPIO_Init(port4, &GPIO_InitStruct);
        
			numOfChannelsUsed++;
		} 
		if (ADC_ch5_Port != PortsMaxNum)
		{ 
          
			GPIO_InitTypeDef GPIO_InitStruct;
			GPIO_InitStruct.Pin = pin5;
			GPIO_InitStruct.Mode = GPIO_MODE_ANALOG;
			GPIO_InitStruct.Pull = GPIO_PULLDOWN;
			HAL_GPIO_Init(port5, &GPIO_InitStruct);
        
			numOfChannelsUsed++;
		}

		adc_periph->Instance = ADC1;
		adc_periph->Init.ClockPrescaler = ADC_CLOCK_SYNC_PCLK_DIV8;
		adc_periph->Init.Resolution = ADC_RESOLUTION_12B;
		adc_periph->Init.ScanConvMode = ENABLE;
		adc_periph->Init.ContinuousConvMode = ENABLE;
		adc_periph->Init.DiscontinuousConvMode = DISABLE;
		adc_periph->Init.DataAlign = ADC_DATAALIGN_RIGHT;
		adc_periph->Init.NbrOfConversion = numOfChannelsUsed;
		adc_periph->Init.DMAContinuousRequests = ENABLE;
		adc_periph->Init.EOCSelection = ADC_EOC_SEQ_CONV;
        
        
		HAL_ADC_Init(adc_periph);

		//now to configure the channels.
		if(ADC_ch1_Port != PortsMaxNum)
		{
			sConfig.Channel = ADC_CHANNEL_8;
			sConfig.Rank = 1;
			sConfig.SamplingTime = ADC_SAMPLETIME_28CYCLES;
			HAL_ADC_ConfigChannel(adc_periph, &sConfig);
		}
		if (ADC_ch2_Port != PortsMaxNum)
		{
			sConfig.Channel = ADC_CHANNEL_2;
			sConfig.Rank = 2;
			sConfig.SamplingTime = ADC_SAMPLETIME_28CYCLES;
			HAL_ADC_ConfigChannel(adc_periph, &sConfig); 
		}

		if (ADC_ch3_Port != PortsMaxNum)
		{
			sConfig.Channel = ADC_CHANNEL_3;
			sConfig.Rank = 3;
			sConfig.SamplingTime = ADC_SAMPLETIME_28CYCLES;
			HAL_ADC_ConfigChannel(adc_periph, &sConfig);
		}
		if (ADC_ch4_Port != PortsMaxNum)
		{ 
			sConfig.Channel = ADC_CHANNEL_4;
			sConfig.Rank = 4;
			sConfig.SamplingTime = ADC_SAMPLETIME_28CYCLES;
			HAL_ADC_ConfigChannel(adc_periph, &sConfig);
		} 
		if (ADC_ch5_Port != PortsMaxNum)
		{
			sConfig.Channel = ADC_CHANNEL_5;
			sConfig.Rank = 5;
			sConfig.SamplingTime = ADC_SAMPLETIME_28CYCLES;
			HAL_ADC_ConfigChannel(adc_periph, &sConfig);
		}


		HAL_ADC_Start_DMA(adc_periph, (uint32_t*)(&ADCdata[0]), numOfChannelsUsed);   //3
		 
 
	}
 