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
	
	//trigger fake itnerrupt?
	this->AE_I2C_MasterTxCpltCallback();
	
	return true;
}

inline int8_t AEI2C::ReadBytes(uint8_t devAddr, uint8_t length, uint8_t *pdata, uint16_t timeout)
{
	devAddr = devAddr << 1; // needs to be shifted because of the way stm hal shifts addresses over by one
	//while (HAL_I2C_GetState(&this->PeripheralHandle_t) != HAL_I2C_STATE_READY)
	//{}
	
	//HAL_I2C_Master_Receive_DMA(this->_i2c_Handle, devAddr, I2Cbuffer22, length);
	
	//int16_t attempts = 0;
	//while (HAL_I2C_GetState(this->_i2c_Handle) != HAL_I2C_STATE_READY) {}
	//for (uint8_t i = 0; i < length; i++) { pdata[i] = I2Cbuffer22[i]; }

	//trigger fake itnerrupt?
	this->AE_I2C_MasterRxCpltCallback();
 
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
		 
		 
 
	}
 