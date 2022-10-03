#pragma once

#include "AEI2CPeripheral.h"





 
 

inline bool AEI2C::WriteBytes(uint8_t devAddr, uint8_t regAddr, uint8_t length, uint8_t* datatoWrite)
{
	devAddr = devAddr << 1; // needs to be shifted because of the way stm hal shifts addresses over by one
	this->I2Cbuffer22[0] = regAddr;
	if (length > 0)
	{
		memcpy(this->I2Cbuffer22 + 1, datatoWrite, length);
	} 
	HAL_I2C_Master_Transmit_IT(this->_i2c_Handle, devAddr, this->I2Cbuffer22, length + 1);
	//int16_t attempts = 0;
	//while (HAL_I2C_GetState(this->_i2c_Handle) != HAL_I2C_STATE_READY) {}
	return true;
}

inline int8_t AEI2C::ReadBytes(uint8_t devAddr, uint8_t length, uint8_t *pdata, uint16_t timeout)
{
	devAddr = devAddr << 1; // needs to be shifted because of the way stm hal shifts addresses over by one
	//while (HAL_I2C_GetState(&this->PeripheralHandle_t) != HAL_I2C_STATE_READY)
	//{}
	HAL_I2C_Master_Receive_DMA(this->_i2c_Handle, devAddr, I2Cbuffer22, length);
	//int16_t attempts = 0;
	//while (HAL_I2C_GetState(this->_i2c_Handle) != HAL_I2C_STATE_READY) {}
	//for (uint8_t i = 0; i < length; i++) { pdata[i] = I2Cbuffer22[i]; }


 
	return 1;
}



template<templateForI2C_def>
	inline void I2CPeripheral<templateargsForI2C>::_InitializePinSelectors(CreateTypeSelector_funcPtr(&functPtrsToChangeTypeSelectorss)[2])
	{
		
 
		if (WhichInstanceOfI2C == 1)
		{
			this->functPtrsToChangeTypeSelectors[0] = []() -> void
			{
				PinSelector::getInstance()->IncludePossiblePin(Portenum::PortB, PinEnum::PIN6);
				PinSelector::getInstance()->IncludePossiblePin(Portenum::PortB, PinEnum::PIN8);
			};

			this->functPtrsToChangeTypeSelectors[1] = []() -> void
			{
				PinSelector::getInstance()->IncludePossiblePin(Portenum::PortB, PinEnum::PIN7);
				PinSelector::getInstance()->IncludePossiblePin(Portenum::PortB, PinEnum::PIN9);
			}; 

		}
		if (WhichInstanceOfI2C == 2)
		{
			this->functPtrsToChangeTypeSelectors[0] = []() -> void
			{PinSelector::getInstance()->IncludePossiblePin(Portenum::PortB, PinEnum::PIN10); };

			this->functPtrsToChangeTypeSelectors[1] = []() -> void
			{
				PinSelector::getInstance()->IncludePossiblePin(Portenum::PortB, PinEnum::PIN3);
				PinSelector::getInstance()->IncludePossiblePin(Portenum::PortB, PinEnum::PIN9);
			}; 
		}
		if (WhichInstanceOfI2C == 3)
		{
			this->functPtrsToChangeTypeSelectors[0] = []() -> void
			{PinSelector::getInstance()->IncludePossiblePin(Portenum::PortA, PinEnum::PIN8); };

			this->functPtrsToChangeTypeSelectors[1] = []() -> void
			{
				PinSelector::getInstance()->IncludePossiblePin(Portenum::PortC, PinEnum::PIN9);
				PinSelector::getInstance()->IncludePossiblePin(Portenum::PortB, PinEnum::PIN4);
			};
		}
  
	}
 


template<templateForI2C_def>
	inline void I2CPeripheral<templateargsForI2C>::_Initialize(Port_t port1, Pin_t pin1, Port_t port2, Pin_t pin2, Port_t port3, Pin_t pin3, Port_t port4, Pin_t pin4, Port_t port5, Pin_t pin5)
	{
		 
		//initialize the real peripheral here 
		if (WhichInstanceOfI2C == 1)
		{
			this->PeripheralHandle_t.Instance = I2C1;
			__HAL_RCC_I2C1_CLK_ENABLE();
         
			this->dmaForI2C.GetDMAHandle()->Instance = DMA1_Stream0;
			this->dmaForI2C.GetDMAHandle()->Init.Channel = DMA_CHANNEL_1;
//			this->dmaForI2C.Instance = DMA1_Stream0;
//			this->dmaForI2C.Init.Channel = DMA_CHANNEL_1;
		}
		else if (WhichInstanceOfI2C == 2)
		{ 
			this->PeripheralHandle_t.Instance = I2C2;
			__HAL_RCC_I2C2_CLK_ENABLE();
         
         
			this->dmaForI2C.GetDMAHandle()->Instance = DMA1_Stream2;
			this->dmaForI2C.GetDMAHandle()->Init.Channel = DMA_CHANNEL_7;
		}
		else if (WhichInstanceOfI2C == 3)
		{ 
			this->PeripheralHandle_t.Instance = I2C3;
			__HAL_RCC_I2C3_CLK_ENABLE();
         
			this->dmaForI2C.GetDMAHandle()->Instance = DMA1_Stream1;
			this->dmaForI2C.GetDMAHandle()->Init.Channel = DMA_CHANNEL_1;
		}
	
		this->PeripheralHandle_t.Init.ClockSpeed = Clockspeed; //10000;
		this->PeripheralHandle_t.Init.DutyCycle = I2C_DUTYCYCLE_2;
		this->PeripheralHandle_t.Init.OwnAddress1 = 0;
		this->PeripheralHandle_t.Init.AddressingMode = I2C_ADDRESSINGMODE_7BIT;
		this->PeripheralHandle_t.Init.DualAddressMode = I2C_DUALADDRESS_DISABLE;
		this->PeripheralHandle_t.Init.OwnAddress2 = 0;
		this->PeripheralHandle_t.Init.GeneralCallMode = I2C_GENERALCALL_DISABLE;
		this->PeripheralHandle_t.Init.NoStretchMode = I2C_NOSTRETCH_DISABLE;
		if (HAL_I2C_Init(&this->PeripheralHandle_t) != HAL_OK)
		{
			AEAssertRuntime(false, "i2c not initialized correctly");
			//_Error_Handler(__FILE__, __LINE__);
		}
		GPIO_InitTypeDef GPIO_InitStruct;
		GPIO_InitTypeDef GPIO_InitStruct2;
		/*
			  PB6     ------> I2C1_SCL
			  PB7     ------> I2C1_SDA
			  */
		GPIO_InitStruct.Pin = pin1;
		GPIO_InitStruct.Mode = GPIO_MODE_AF_OD;
		GPIO_InitStruct.Pull = GPIO_PULLUP;
		GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
		GPIO_InitStruct.Alternate = GPIO_AF4_I2C1;
		HAL_GPIO_Init(port1, &GPIO_InitStruct);

		GPIO_InitStruct2.Pin = pin2;
		GPIO_InitStruct2.Mode = GPIO_MODE_AF_OD;
		GPIO_InitStruct2.Pull = GPIO_PULLUP;
		GPIO_InitStruct2.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
		GPIO_InitStruct2.Alternate = GPIO_AF4_I2C1;
		HAL_GPIO_Init(port2, &GPIO_InitStruct2);




		/* I2C1 DMA Init */
		/* I2C1_RX Init */
		__HAL_RCC_DMA1_CLK_ENABLE();
		

//
		this->dmaForI2C.GetDMAHandle()->Init.Direction = DMA_PERIPH_TO_MEMORY;
		this->dmaForI2C.GetDMAHandle()->Init.PeriphInc = DMA_PINC_DISABLE;
		this->dmaForI2C.GetDMAHandle()->Init.MemInc = DMA_MINC_ENABLE;
		this->dmaForI2C.GetDMAHandle()->Init.PeriphDataAlignment = DMA_PDATAALIGN_BYTE;
		this->dmaForI2C.GetDMAHandle()->Init.MemDataAlignment = DMA_MDATAALIGN_BYTE;
		this->dmaForI2C.GetDMAHandle()->Init.Mode = DMA_CIRCULAR;
		this->dmaForI2C.GetDMAHandle()->Init.Priority = DMA_PRIORITY_LOW;
		this->dmaForI2C.GetDMAHandle()->Init.FIFOMode = DMA_FIFOMODE_DISABLE;
		if (HAL_DMA_Init((this->dmaForI2C.GetDMAHandle()) ) != HAL_OK)
		{
			AEAssertRuntime(false, "i2c not initialized correctly");
			//_Error_Handler(__FILE__, __LINE__);
		}

		__HAL_LINKDMA(&this->PeripheralHandle_t, hdmarx, *this->dmaForI2C.GetDMAHandle());
		
		
		
//		this->dmaForI2C.Init.Direction = DMA_PERIPH_TO_MEMORY;
//		this->dmaForI2C.Init.PeriphInc = DMA_PINC_DISABLE;
//		this->dmaForI2C.Init.MemInc = DMA_MINC_ENABLE;
//		this->dmaForI2C.Init.PeriphDataAlignment = DMA_PDATAALIGN_BYTE;
//		this->dmaForI2C.Init.MemDataAlignment = DMA_MDATAALIGN_BYTE;
//		this->dmaForI2C.Init.Mode = DMA_CIRCULAR;
//		this->dmaForI2C.Init.Priority = DMA_PRIORITY_LOW;
//		this->dmaForI2C.Init.FIFOMode = DMA_FIFOMODE_DISABLE;
//		if (HAL_DMA_Init((&this->dmaForI2C)) != HAL_OK)
//		{
//			AEAssertRuntime(false, "i2c not initialized correctly");
//			//_Error_Handler(__FILE__, __LINE__);
//		}
//
//		__HAL_LINKDMA(&this->PeripheralHandle_t, hdmarx, this->dmaForI2C);
		
		
		

		/* I2C1 interrupt Init */
		//Hadi Here : interrup priorit used to be 6, now it works when it is 4 or lower. I hecked all nvic stuff. looks fine. ask this question on freertos
		static const int priorityOFInter = 0;
		if (WhichInstanceOfI2C == 1)
		{ 
			HAL_NVIC_SetPriority(I2C1_EV_IRQn, priorityOFInter, 0);
			HAL_NVIC_EnableIRQ(I2C1_EV_IRQn);
			HAL_NVIC_SetPriority(I2C1_ER_IRQn, priorityOFInter, 0);
			HAL_NVIC_EnableIRQ(I2C1_ER_IRQn);
            
			HAL_NVIC_SetPriority(DMA1_Stream0_IRQn, priorityOFInter, 0);
			HAL_NVIC_EnableIRQ(DMA1_Stream0_IRQn);
		}
		else if (WhichInstanceOfI2C == 2)
		{ 
			HAL_NVIC_SetPriority(I2C2_EV_IRQn, priorityOFInter, 0);
			HAL_NVIC_EnableIRQ(I2C2_EV_IRQn);
			HAL_NVIC_SetPriority(I2C2_ER_IRQn, priorityOFInter, 0);
			HAL_NVIC_EnableIRQ(I2C2_ER_IRQn);
        
			HAL_NVIC_SetPriority(DMA1_Stream1_IRQn, priorityOFInter, 0);
			HAL_NVIC_EnableIRQ(DMA1_Stream1_IRQn);
		}
		else if (WhichInstanceOfI2C == 3)
		{ 
			HAL_NVIC_SetPriority(I2C3_EV_IRQn, priorityOFInter, 0);
			HAL_NVIC_EnableIRQ(I2C3_EV_IRQn);
			HAL_NVIC_SetPriority(I2C3_ER_IRQn, priorityOFInter, 0);
			HAL_NVIC_EnableIRQ(I2C3_ER_IRQn);
            
			HAL_NVIC_SetPriority(DMA1_Stream2_IRQn, priorityOFInter, 0);
			HAL_NVIC_EnableIRQ(DMA1_Stream2_IRQn);
		} 
 
	}
 