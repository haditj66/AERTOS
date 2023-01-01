#include "w25q16dv_NonBlocking.h"

#include <cmath>
#include <cstring>

//#define InterruptWay
#define NonInterruptWay

#ifdef InterruptWay
//the Interrupt api call
#define SPITRANSMIT(SPIHANDLER, dataToSend, sizeOfData, timeout) HAL_SPI_Transmit_IT(SPIHANDLER, (uint8_t *)dataToSend, sizeOfData);//, HAL_MAX_DELAY);  
#define SPIRECEIVE(SPIHANDLER, dataToSend, sizeOfData, timeout) HAL_SPI_Receive_IT(SPIHANDLER, (uint8_t *)dataToSend, sizeOfData);
#endif

#ifdef NonInterruptWay
//normal api call
#define SPITRANSMIT(SPIHANDLER, dataToSend, sizeOfData, timeout) HAL_SPI_Transmit(SPIHANDLER, (uint8_t *)dataToSend, sizeOfData, timeout);//, HAL_MAX_DELAY);  
#define SPIRECEIVE(SPIHANDLER, dataToSend, sizeOfData, timeout) HAL_SPI_Receive(SPIHANDLER, (uint8_t *)dataToSend, sizeOfData, timeout);
#endif


bool w25q16dv_NonBlocking::IsW25busy()
{ 
	//read the busy bit on the register status. 1 is busy 0 is not busy 
	ReadRegisterStatus();
	if ((aRxBuffer[0] & 1) == 1)
	{
		return true;
	}
	return false;
}



void w25q16dv_NonBlocking::EnableWrite()
{ 
	instruction[0] = 0x06; //write enable instruction
	
	this->spiToUse->AE_SPI_Transmit((uint8_t *)instruction, 1);
	
//	HAL_GPIO_WritePin(GpioPort, GpioPin, GPIO_PIN_RESET);
//	//HAL_SPI_TransmitReceive_DMA(&hspi1, (uint8_t *)message, (uint8_t *)aRxBuffer, 1);//, HAL_MAX_DELAY);
//	SPITRANSMIT(hspi1, instruction, 1, HAL_MAX_DELAY); //, HAL_MAX_DELAY);    //	HAL_SPI_Transmit_IT(hspi1, (uint8_t *)instruction, 1);//, HAL_MAX_DELAY);  
//	while (HAL_SPI_GetState(hspi1) != HAL_SPI_STATE_READY)
//	{
//	}
//	HAL_GPIO_WritePin(GpioPort, GpioPin, GPIO_PIN_SET);
}

void w25q16dv_NonBlocking::ReadRegisterStatus()
{
	instruction[0] = 0x05; //read status register 
	
	this->spiToUse->AE_SPI_TransmitReceive((uint8_t *)instruction, 1, (uint8_t *)aRxBuffer, 1); 

//	HAL_GPIO_WritePin(GpioPort, GpioPin, GPIO_PIN_RESET);
//	SPITRANSMIT(hspi1, instruction, 1, HAL_MAX_DELAY); //	HAL_SPI_Transmit_IT(hspi1, (uint8_t *)instruction, 1);
//#ifdef NonInterruptWay
//	while (HAL_SPI_GetState(hspi1) != HAL_SPI_STATE_READY)
//	{
//	}
//#endif
	
	
//	SPIRECEIVE(hspi1, aRxBuffer, 1, HAL_MAX_DELAY); //    	HAL_SPI_Receive_IT(hspi1, (uint8_t *)aRxBuffer, 1);
//	while (HAL_SPI_GetState(hspi1) != HAL_SPI_STATE_READY)
//	{
//	}
//	HAL_GPIO_WritePin(GpioPort, GpioPin, GPIO_PIN_SET);
}

void w25q16dv_NonBlocking::EraseSector(uint8_t sectorToErase, uint8_t block)
{
  
	//first make sure the write is enabled
	EnableWrite();

	instruction[0] = 0x20; //erase instruction
	instruction[1] = block; //address byte 1 // this number is block number (32 blocks)
	instruction[2] = sectorToErase << 4; //address byte 2 //  first number is sector(16 sectors in a block)  second number is page number (16 pages in a sector)  for example: 0xD4  is sector 13 page 4 . for example: 0x38  is sector 3 page 8 
	instruction[3] = 0x00; //address byte 3 //byte number (256 bytes in a page)remember 256 data byte should be zero
	
	this->spiToUse->AE_SPI_Transmit((uint8_t *)instruction, 4);
	
//	HAL_GPIO_WritePin(GpioPort, GpioPin, GPIO_PIN_RESET);
//	SPITRANSMIT(hspi1, instruction, 4, HAL_MAX_DELAY); //	HAL_SPI_Transmit_IT(hspi1, (uint8_t *)instruction, 4);
//	while (HAL_SPI_GetState(hspi1) != HAL_SPI_STATE_READY)
//	{
//	}
//	HAL_GPIO_WritePin(GpioPort, GpioPin, GPIO_PIN_SET);
}

void w25q16dv_NonBlocking::EraseEntireChip()
{
  
        
	//first make sure the write is enabled
	EnableWrite();

	instruction[0] = 0x60; //erase instruction
	
	this->spiToUse->AE_SPI_Transmit((uint8_t *)instruction, 1);
	
//	HAL_GPIO_WritePin(GpioPort, GpioPin, GPIO_PIN_RESET);
//	SPITRANSMIT(hspi1, instruction, 1, HAL_MAX_DELAY); //	HAL_SPI_Transmit_IT(hspi1, (uint8_t *)instruction, 1);
//	while (HAL_SPI_GetState(hspi1) != HAL_SPI_STATE_READY)
//	{
//	}
//	HAL_GPIO_WritePin(GpioPort, GpioPin, GPIO_PIN_SET);
}


/*
void w25q16dv_NonBlocking::SequentialWrite(uint8_t* thingToWrite, uint32_t numOfBytesTowrite)
{
  DoAWriteToMultiPages(Byte, Page, Sector, Block, thingToWrite, numOfBytesTowrite);

}


void w25q16dv_NonBlocking::DoAWriteToMultiPages(uint8_t byte, uint8_t page, uint8_t sector, uint8_t block, uint8_t * thingToWrite, uint32_t numOfBytesTowrite)
{
  placement = 0;
  remainingBytes = 0;
  while(1)
  {
    
    //check if the difference of the placement from the numOfBytesTowrite is less than 255. if it is then this will be the last write.
    if((numOfBytesTowrite + byte) - placement <= 255)
    {
      remainingBytes = (numOfBytesTowrite + byte) - placement; //100+150-0
      
      
      //if remaining bytes is negative, then we have two more pages left to write
      DoAWriteTo(byte, page, sector, block, (thingToWrite + placement), remainingBytes);
      
      //incrememnt all bytes, pages, sectors, blocks
      //since this is last write, update byte to remaning bytes
      byte = remainingBytes;
      //everything will not be updating
      
      //update the current byte, page, sector, and block in global pointer
      //make sure Byte is not 255
      //byte++;
      if(byte >= 255)
      {
        byte = 0;
        
        //page should go up to 16 pages per sector
        page++;
        if(page > 15)
        {
          page = 0; 
          
          //increment sector up to 16 sectors per block
          sector++; 
          if(sector > 15)
          {
            sector = 0;
            
            //increment block up to 32 blocks
            block++;
            if(block > 31)
            {
              //TODO: error handle that the end of the data address was reached.
              return;
            }
          }
        }
      }
      
      Byte = byte;
      Page = page;
      Sector = sector;
      Block = block;   
       
 
      
      break; // break out as it is done
    }
    
    
    
    //first check how many bytes away I am from end of current page
    remainingBytes = 255 - byte;//255-200
    
    DoAWriteTo(byte, page, sector, block, (thingToWrite + placement), remainingBytes);
    
    placement += remainingBytes;
    //((i *256))
    //incrememnt all bytes, pages, sectors, blocks
    //so bytes should always remain zero as we went to the end of page.
    byte = 0;
    //page should go up to 16 pages per sector
    page++;
    if(page > 15)
    {
      page = 0; 
      
      //increment sector up to 16 sectors per block
      sector++; 
      if(sector > 15)
      {
        sector = 0;
        
        //increment block up to 32 blocks
        block++;
        if(block > 31)
        {
          //TODO: error handle that the end of the data address was reached.
          return;
        }
      }
    }
    
    //update the current byte, page, sector, and block in global pointer
    Byte = byte;
    Page = page;
    Sector = sector;
    Block = block;
    
  }
}
*/



void w25q16dv_NonBlocking::DoAReadSequential(uint8_t* buffer, uint32_t numOfBytesToRead)
{
	
	DoAReadFrom(byte_read, page_read, sector_read, block_read, buffer, numOfBytesToRead);

	//increment the byte page sector and block
	byte_read += numOfBytesToRead;

	uint32_t pagesToAdd =  floor(byte_read / 255);
	uint8_t BytesLeftOver = byte_read % 255;
	page_read += pagesToAdd;
	byte_read = BytesLeftOver;
	 
	uint32_t SectorsToAdd = floor(page_read / 16);
	uint8_t PagesLeftOver = page_read % 16;
	sector_read += SectorsToAdd;
	page_read = PagesLeftOver;

	uint32_t BlocksToAdd = floor(sector_read / 31);
	uint8_t SectorsLeftOver = sector_read % 31;
	block_read += BlocksToAdd;
	sector_read = SectorsLeftOver;


}


void w25q16dv_NonBlocking::DoAReadFrom(uint8_t byte, uint8_t page, uint8_t sector, uint8_t block, uint8_t * buffer, uint32_t numOfBytesToRead)
{
  
	numOfBytesToRead = (numOfBytesToRead * 1.05) + 1;
  
        
	uint8_t sectorAndPage = page;
	sectorAndPage |= sector << 4;

	instruction[0] = 0x03; //instruction for a read
	instruction[1] = block; //address byte 1
	instruction[2] = sectorAndPage; //address byte 2
	instruction[3] = byte; //address byte 3 
	
	this->spiToUse->AE_SPI_TransmitReceive((uint8_t *)instruction, 4, (uint8_t *)buffer, numOfBytesToRead); 
	

//	HAL_GPIO_WritePin(GpioPort, GpioPin, GPIO_PIN_RESET);
//	SPITRANSMIT(hspi1, instruction, 4, HAL_MAX_DELAY); //, HAL_MAX_DELAY);    //	HAL_SPI_Transmit_IT(hspi1, (uint8_t *)instruction, 4);
//	while (HAL_SPI_GetState(hspi1) != HAL_SPI_STATE_READY)
//	{
//	}
//	SPIRECEIVE(hspi1, buffer, numOfBytesToRead, HAL_MAX_DELAY); //255 for one page   //	HAL_SPI_Receive_IT(hspi1, (uint8_t *)buffer, numOfBytesToRead);//255 for one page
//	while (HAL_SPI_GetState(hspi1) != HAL_SPI_STATE_READY)
//	{
//	}
//	HAL_GPIO_WritePin(GpioPort, GpioPin, GPIO_PIN_SET);


	//remove every trailing byte at the end of the each page 
	uint32_t bytesToBeRemoved = (numOfBytesToRead - byte) / 256;
	bytesToBeRemoved = bytesToBeRemoved == 0 ? 1 : bytesToBeRemoved; 
 
	//memcpy(message3 + ((255)), (message3 + ((256))), 255);
	if (numOfBytesToRead > 255)
	{
		for (int i = 1; i <= (1 + bytesToBeRemoved); i++)
		{ 
			memcpy(buffer + (((i) * 255)) - byte, buffer + (((i) * 256) - byte), 255); 
		}
	}
	else if ((numOfBytesToRead + byte) > 256)//check if it transitions to another page   
	{
		//there will only be one to remove
		memcpy(buffer + ((255 - byte)), (buffer + 255 - byte + 1), numOfBytesToRead);
          
	}
	
}






void w25q16dv_NonBlocking::DoAWriteTo(uint8_t byte, uint8_t page, uint8_t sector, uint8_t block, uint8_t * thingToWrite, uint8_t numOfBytesTowrite)
{
  
  

	//first make sure the write is enabled
	EnableWrite();

	uint8_t sectorAndPage = page;
	sectorAndPage |= sector << 4;


	instruction[0] = 0x02; //write to page instruction
	instruction[1] = block; //address byte 1 // this number is block number (32 blocks)
	instruction[2] = sectorAndPage; //address byte 2 //  first number is sector(16 sectors in a block)  second number is page number (16 pages in a sector)  for example: 0xD4  is sector 13 page 4 . for example: 0x38  is sector 3 page 8 
	instruction[3] = byte; //address byte 3 //byte number (255 bytes in a page)remember 255 data byte should be zero

	
	
	
	this->spiToUse->AE_SPI_Transmit((uint8_t *)instruction, 4);
	
	this->spiToUse->AE_SPI_Transmit((uint8_t *)thingToWrite, numOfBytesTowrite);
	
	
//	HAL_GPIO_WritePin(GpioPort, GpioPin, GPIO_PIN_RESET);
//	//throw in the write instruction   
//	SPITRANSMIT(hspi1, instruction, 4, HAL_MAX_DELAY); //4+255+1     //             HAL_SPI_Transmit_IT(hspi1, (uint8_t *)instruction, 4); //4+255+1
//	while (HAL_SPI_GetState(hspi1) != HAL_SPI_STATE_READY)
//	{
//	}
//	//put in the thing to write
//	SPITRANSMIT(hspi1, thingToWrite, numOfBytesTowrite, HAL_MAX_DELAY); //4+255+1   //HAL_SPI_Transmit_IT(hspi1, (uint8_t *)thingToWrite, numOfBytesTowrite); //4+255+1
//	while (HAL_SPI_GetState(hspi1) != HAL_SPI_STATE_READY)
//	{
//	}
//
//	HAL_GPIO_WritePin(GpioPort, GpioPin, GPIO_PIN_SET);
                
}





