#pragma once

#include "AESPIPeripheral.h"





 
 

inline void AESPI::AE_SPI_Transmit(uint8_t* data, uint16_t size)
{  
}

inline void AESPI::AE_SPI_Receive(uint8_t* data, uint16_t size)
{ 
}

inline void AESPI::AE_SPI_TransmitReceive(uint8_t* dataToTransmit, uint16_t sizeToTransmit, uint8_t* dataToReceive, uint16_t sizeToReceive)
{ 
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
		 
	  
	}
 