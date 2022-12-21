

//#include "stm32f4xx_hal.h"

#include <string>
#include "AECore.h" 
#include "AE_Init.h" 

//#include <cmath>
#ifndef W25Q16DVNonBlock_H
#define W25Q16DVNonBlock_H 

class w25q16dv_NonBlocking
{
public: 
  
	uint32_t GetBytesWrittenSoFar(){return bytesWrittensofar;}
	;
  
	//char message[5] = 0x00;
	//char message2[4050] = { 0x1A };
	//static char message3[10000];
	//SPI_HandleTypeDef* hspi1;
	AESPI* spiToUse;

	w25q16dv_NonBlocking(AESPI* spi)//(SPI_HandleTypeDef* spi1, GPIO_TypeDef* gpioPort, uint16_t gpioPin)
	{
		//hspi1 = spi1->_spi_Handle;
		spiToUse = spi1;
//		GpioPort = GPIOA;//gpioPort;
//		GpioPin = GPIO_PIN_4;//gpioPin;
		bytesWrittensofar = 0;
          
		byte_read = 0; page_read = 0; sector_read = 0; block_read = 0;

	}
	;
	 
	bool IsW25busy();
	void EnableWrite();
	void ReadRegisterStatus();
	void EraseSector(uint8_t sectorToErase, uint8_t block);
	void EraseEntireChip();
	//void SequentialWrite(uint8_t* thingToWrite, uint32_t numOfBytesTowrite);
//void DoAWriteToMultiPages(uint8_t byte, uint8_t page, uint8_t sector, uint8_t block, uint8_t* thingToWrite, uint32_t numOfBytesTowrite);
	void DoAReadFrom(uint8_t byte, uint8_t page, uint8_t sector, uint8_t block, uint8_t* buffer, uint32_t numOfBytesToRead);
	void DoAReadSequential(uint8_t* buffer, uint32_t numOfBytesToRead);
	void DoAWriteTo(uint8_t byte, uint8_t page, uint8_t sector, uint8_t block, uint8_t* thingToWrite, uint8_t numOfBytesTowrite);


 
private:
	uint32_t bytesWrittensofar;
  
	char lastZeroByte[1] = { 0 };
	char instruction[4];
	uint8_t aRxBuffer[2];

//	GPIO_TypeDef* GpioPort;
//	uint16_t GpioPin;
	uint32_t byte_read; uint16_t page_read; uint16_t sector_read; uint16_t block_read;
};

#endif