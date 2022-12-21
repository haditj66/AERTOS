#pragma once

#include "AESPIPeripheral.h"





 
 

inline void AESPI::AE_SPI_Transmit(uint8_t* data, uint16_t size)
{ 
	HAL_GPIO_WritePin(this->NssPort, this->NssPin, GPIO_PIN_RESET);
	HAL_SPI_Transmit(this->_spi_Handle, (uint8_t *)data, size, HAL_MAX_DELAY);  
	while (HAL_SPI_GetState(this->_spi_Handle) != HAL_SPI_STATE_READY)
	{
	}
	HAL_GPIO_WritePin(this->NssPort, this->NssPin, GPIO_PIN_SET);
	
	
	//HAL_SPI_Transmit_IT(this->_spi_Handle, data, size);
}

inline void AESPI::AE_SPI_Receive(uint8_t* data, uint16_t size)
{
	HAL_GPIO_WritePin(this->NssPort, this->NssPin, GPIO_PIN_RESET);  
	HAL_SPI_Receive(this->_spi_Handle, data, size, HAL_MAX_DELAY);  
	while (HAL_SPI_GetState(this->_spi_Handle) != HAL_SPI_STATE_READY)
	{
	}
	HAL_GPIO_WritePin(this->NssPort, this->NssPin, GPIO_PIN_SET);
	
	//HAL_SPI_Receive(this->_spi_Handle, data, size, 0xFFFFFF);
}

inline void AESPI::AE_SPI_TransmitReceive(uint8_t* dataToTransmit, uint16_t sizeToTransmit, uint8_t* dataToReceive, uint16_t sizeToReceive)
{
	HAL_GPIO_WritePin(this->NssPort, this->NssPin, GPIO_PIN_RESET);
	HAL_SPI_Transmit(this->_spi_Handle, (uint8_t *)dataToTransmit, sizeToTransmit, HAL_MAX_DELAY);  
	while (HAL_SPI_GetState(this->_spi_Handle) != HAL_SPI_STATE_READY)
	{
	} 
	
	
	HAL_SPI_Receive(this->_spi_Handle, dataToReceive, sizeToReceive, HAL_MAX_DELAY);  
	while (HAL_SPI_GetState(this->_spi_Handle) != HAL_SPI_STATE_READY)
	{
	}
	HAL_GPIO_WritePin(this->NssPort, this->NssPin, GPIO_PIN_SET);
}

template<templateForSPI>
	inline void SPIPeripheral<templateargsForSPI>::_InitializePinSelectors(CreateTypeSelector_funcPtr(&functPtrsToChangeTypeSelectorss)[4])
	{
		
 
		if (WhichInstanceOfSPI == 1)
		{
			this->functPtrsToChangeTypeSelectors[0] = []() -> void
			{
				PinSelector::getInstance()->IncludePossiblePin(Portenum::PortA, PinEnum::PIN5);
				PinSelector::getInstance()->IncludePossiblePin(Portenum::PortB, PinEnum::PIN3);
			};

			this->functPtrsToChangeTypeSelectors[1] = []() -> void
			{
				PinSelector::getInstance()->IncludePossiblePin(Portenum::PortA, PinEnum::PIN6);
				PinSelector::getInstance()->IncludePossiblePin(Portenum::PortB, PinEnum::PIN4);
			};

			this->functPtrsToChangeTypeSelectors[2] = []() -> void
			{
				PinSelector::getInstance()->IncludePossiblePin(Portenum::PortA, PinEnum::PIN7);
				PinSelector::getInstance()->IncludePossiblePin(Portenum::PortB, PinEnum::PIN5);
			};

			if (SLAVEMODE == false)
			{
				this->functPtrsToChangeTypeSelectors[3] = []() -> void {
					PinSelector::getInstance()->AnyPinIsPossible();
				};
			}
			else
			{
				this->functPtrsToChangeTypeSelectors[3] = []() -> void
				{
					PinSelector::getInstance()->IncludePossiblePin(Portenum::PortA, PinEnum::PIN4);
					PinSelector::getInstance()->IncludePossiblePin(Portenum::PortA, PinEnum::PIN15);
				};
			}
		}

		else if (WhichInstanceOfSPI == 2)
		{
			this->functPtrsToChangeTypeSelectors[0] = []() -> void
			{
				PinSelector::getInstance()->IncludePossiblePin(Portenum::PortB, PinEnum::PIN10);
				PinSelector::getInstance()->IncludePossiblePin(Portenum::PortB, PinEnum::PIN13);
			};

			this->functPtrsToChangeTypeSelectors[1] = []() -> void
			{
				PinSelector::getInstance()->IncludePossiblePin(Portenum::PortC, PinEnum::PIN2);
				PinSelector::getInstance()->IncludePossiblePin(Portenum::PortB, PinEnum::PIN14);
			};

			this->functPtrsToChangeTypeSelectors[2] = []() -> void
			{
				PinSelector::getInstance()->IncludePossiblePin(Portenum::PortC, PinEnum::PIN3);
				PinSelector::getInstance()->IncludePossiblePin(Portenum::PortB, PinEnum::PIN15);
			};

			if (SLAVEMODE == false)
			{
				this->functPtrsToChangeTypeSelectors[3] = []() -> void {
					PinSelector::getInstance()->AnyPinIsPossible();
				};
			}
			else
			{
				this->functPtrsToChangeTypeSelectors[3] = []() -> void
				{
					PinSelector::getInstance()->IncludePossiblePin(Portenum::PortB, PinEnum::PIN12);
					PinSelector::getInstance()->IncludePossiblePin(Portenum::PortB, PinEnum::PIN9);
				};
			}
		}
  
	}
 


template<templateForSPI>
	inline void SPIPeripheral<templateargsForSPI>::_Initialize(Port_t port1, Pin_t pin1, Port_t port2, Pin_t pin2, Port_t port3, Pin_t pin3, Port_t port4, Pin_t pin4, Port_t port5, Pin_t pin5)
	{
		 
		SPI_TypeDef* spiTypedef;
		IRQn_Type IRQForSPI;
		if (WhichInstanceOfSPI == 1)
		{
			IRQForSPI = SPI1_IRQn;
			spiTypedef = SPI1;
			__HAL_RCC_SPI1_CLK_ENABLE();

		}
		else if (WhichInstanceOfSPI == 2)
		{
			IRQForSPI = SPI2_IRQn;
			spiTypedef = SPI2;
			__HAL_RCC_SPI2_CLK_ENABLE();

		}
	

		uint32_t Slave_Setting;
		uint32_t NSS_Setting;
		if (SLAVEMODE == true)
		{
			Slave_Setting = SPI_MODE_SLAVE;
			NSS_Setting = SPI_NSS_SOFT; //SPI_NSS_HARD_INPUT;
		}
		else
		{
			Slave_Setting = SPI_MODE_MASTER;
			NSS_Setting = SPI_NSS_SOFT;
		}


		//SPI1 GPIO Configuration    
		//PA5     ------> SPI1_SCK
		//PA6     ------> SPI1_MISO
		//PA7     ------> SPI1_MOSI 

		GPIO_InitTypeDef GPIO_InitStruct;

		GPIO_InitStruct.Pin = pin1;
		GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
		GPIO_InitStruct.Pull = GPIO_NOPULL;
		GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
		GPIO_InitStruct.Alternate = GPIO_AF5_SPI1;
		HAL_GPIO_Init(port1, &GPIO_InitStruct);

		GPIO_InitTypeDef GPIO_InitStruct2;

		GPIO_InitStruct2.Pin = pin2;
		GPIO_InitStruct2.Mode = GPIO_MODE_AF_PP;
		GPIO_InitStruct2.Pull = GPIO_NOPULL;
		GPIO_InitStruct2.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
		GPIO_InitStruct2.Alternate = GPIO_AF5_SPI1;
		HAL_GPIO_Init(port2, &GPIO_InitStruct2);

		GPIO_InitTypeDef GPIO_InitStruct3;

		GPIO_InitStruct3.Pin = pin3;
		GPIO_InitStruct3.Mode = GPIO_MODE_AF_PP;
		GPIO_InitStruct3.Pull = GPIO_NOPULL;
		GPIO_InitStruct3.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
		GPIO_InitStruct3.Alternate = GPIO_AF5_SPI1;
		HAL_GPIO_Init(port3, &GPIO_InitStruct3);


		if (SLAVEMODE == true)
		{
			GPIO_InitTypeDef GPIO_InitStruct4;

			//Configure GPIO pin : PA4  
			GPIO_InitStruct4.Pin = pin4;
			GPIO_InitStruct4.Mode = GPIO_MODE_OUTPUT_PP;
			GPIO_InitStruct4.Pull = GPIO_NOPULL;
			GPIO_InitStruct4.Speed = GPIO_SPEED_FREQ_LOW;
			HAL_GPIO_Init(port4, &GPIO_InitStruct4);

			HAL_GPIO_WritePin(port4, pin4, GPIO_PIN_RESET);
		}
		else
		{
			GPIO_InitTypeDef GPIO_InitStruct4;

			//Configure GPIO pin : PA4  
			GPIO_InitStruct4.Pin = pin4;
			GPIO_InitStruct4.Mode = GPIO_MODE_OUTPUT_PP;
			GPIO_InitStruct4.Pull = GPIO_NOPULL;
			GPIO_InitStruct4.Speed = GPIO_SPEED_FREQ_LOW;
			HAL_GPIO_Init(port4, &GPIO_InitStruct4);

			HAL_GPIO_WritePin(port4, pin4, GPIO_PIN_RESET);
		}
		/* GPIO_InitTypeDef GPIO_InitStruct4;

		 //Configure GPIO pin : PA4
		 GPIO_InitStruct4.Pin = pin4;
		 GPIO_InitStruct4.Mode = GPIO_MODE_OUTPUT_PP;
		 GPIO_InitStruct4.Pull = GPIO_NOPULL;
		 GPIO_InitStruct4.Speed = GPIO_SPEED_FREQ_LOW;
		 HAL_GPIO_Init(port4, &GPIO_InitStruct4);

		 HAL_GPIO_WritePin(port4, pin4, GPIO_PIN_RESET);*/



		 // SPI1 interrupt Init 
		HAL_NVIC_SetPriority(IRQForSPI, 6, 0);
		HAL_NVIC_EnableIRQ(IRQForSPI);

		
		

		this->PeripheralHandle_t.Instance = spiTypedef;
		this->PeripheralHandle_t.Init.Mode = Slave_Setting; //slavemaster
		this->PeripheralHandle_t.Init.Direction = SPI_DIRECTION_2LINES;
		this->PeripheralHandle_t.Init.DataSize = SPI_DATASIZE_8BIT;
		this->PeripheralHandle_t.Init.CLKPolarity = SPI_POLARITY_LOW;
		this->PeripheralHandle_t.Init.CLKPhase = SPI_PHASE_1EDGE;
		this->PeripheralHandle_t.Init.NSS = NSS_Setting; //slavemaster
		this->PeripheralHandle_t.Init.FirstBit = SPI_FIRSTBIT_MSB;
		this->PeripheralHandle_t.Init.TIMode = SPI_TIMODE_DISABLE;
		this->PeripheralHandle_t.Init.CRCCalculation = SPI_CRCCALCULATION_DISABLE;
		this->PeripheralHandle_t.Init.BaudRatePrescaler = SPI_BAUDRATEPRESCALER_256;
		this->PeripheralHandle_t.Init.CRCPolynomial = 10;
		if (HAL_SPI_Init(&this->PeripheralHandle_t) != HAL_OK)
		{
			//_Error_Handler(__FILE__, __LINE__);
		}


		if (SLAVEMODE == true)
		{
			HAL_SPI_Receive_IT(&this->PeripheralHandle_t, (uint8_t*)this->InstanceOfSPI.GetSPIBuffer(), this->InstanceOfSPI.GetSPIBufferSize());
		}
 
	}
 