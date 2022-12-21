//generated file: SPI_TEST.cpp
//**********************************************************************
//this is an auto-generated file using the template file located in the directory of C:\CodeGenerator\CodeGenerator\bin\Debug\..\..\FileTemplates\Files
//ONLY WRITE CODE IN THE UserCode_Section BLOCKS
//If you write code anywhere else,  it will be overwritten. modify the actual template file if needing to modify code outside usersection blocks.


#if INTEGRATION_TESTS_FOR_exeHalTest__SPI_TEST
 
#include "IntegTestPipeline.h"

//UserCode_Sectiona
#include "AECore.h" 
#include "AE_Init.h"
#include "AELoopObject.h"
#include "AEObjects.h"

#include "w25q16dv_NonBlocking.h"

DECLARE_ALL_AO_PTR
	
	char message2[6000] = { 0x1A };
static char message3[10000];
//UserCode_Sectiona_end

void RunSelectedIntegrationTest_SPI_TEST()
{

//UserCode_Sectionb
AE_Init();
	
	
	w25q16dv_NonBlocking w25(spi1);//(&hspi1, GPIOA, GPIO_PIN_4);
	
	//do many sequential writes
	memset(message2, 0x1A, 4050);
	message2[0] = 0x8; //thing to write in there  
	message2[4] = 0x0; //thing to write in there 
	message2[255] = 0x56; //thing to write in there 
	message2[300] = 0x57; //thing to write in there 
	message2[301] = 0x58; //thing to write in there 
	message2[810] = 0x59; //thing to write in there 
	
	w25.EraseEntireChip();
	w25.ReadRegisterStatus();
	
	uint32_t numOfBytestoWriteAndRead1 = 300;
	uint32_t numOfBytestoWriteAndRead2 = 256;
	uint32_t numOfBytestoWriteAndRead3 = 256;
	
//	w25.SequentialWrite((uint8_t*)message2, numOfBytestoWriteAndRead1);
//	w25.SequentialWrite((uint8_t*)message2 + numOfBytestoWriteAndRead1, numOfBytestoWriteAndRead2);
//	w25.SequentialWrite((uint8_t*)message2 + numOfBytestoWriteAndRead2 + numOfBytestoWriteAndRead1, numOfBytestoWriteAndRead3);
  
	w25.EnableWrite();
	w25.DoAWriteTo(0, 0, 0, 0,(uint8_t*) message2, 4);

	//do a read  
	uint32_t numOfBytestoRead =  numOfBytestoWriteAndRead1 + numOfBytestoWriteAndRead2 + numOfBytestoWriteAndRead3;
	w25.DoAReadFrom(0, 0, 0, 0, (uint8_t*)message3, 4); //4200);
  
	  //check that message3 and message2 are the same
	for (int i = 0; i < 4; i++)
	{
		if (message2[i] != message3[i])
		{
			AEPrint("Not the same");
			break;
		} 
	}
	
	
//spi1->
//UserCode_Sectionb_end

}


//UserCode_Sectionc
//UserCode_Sectionc_end

#endif
