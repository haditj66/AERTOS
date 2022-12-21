//generated file: I2C_TEST.cpp
//**********************************************************************
//this is an auto-generated file using the template file located in the directory of C:\CodeGenerator\CodeGenerator\bin\Debug\..\..\FileTemplates\Files
//ONLY WRITE CODE IN THE UserCode_Section BLOCKS
//If you write code anywhere else,  it will be overwritten. modify the actual template file if needing to modify code outside usersection blocks.


#if INTEGRATION_TESTS_FOR_exeHalTest__I2C_TEST
 
#include "IntegTestPipeline.h"

//UserCode_Sectiona
#include "AECore.h" 
#include "AE_Init.h"
#include "AELoopObject.h"
#include "AEObjects.h"
 

  uint32_t adcCountToPrint1 = 0;
uint32_t adcCountToPrint2 = 0;
uint32_t adcCountToPrint3 = 0;

bool txcmplt;
bool rxcmplt;

void loopfunc1(void* ptr);



uint8_t I2Cbuffer2[2];


#ifdef  SWIL_HWIL_DRIVEN__HWIL
#define WAIT_UNTIL_I2C_READY while (HAL_I2C_GetState(i2c1->_i2c_Handle) != HAL_I2C_STATE_READY) {}
#else 
#define WAIT_UNTIL_I2C_READY 
#endif 



#ifndef aehal

#include "stm32f4xx_hal.h"
#include "stm32f4xx_hal_cortex.h"

I2C_HandleTypeDef hi2c1;
DMA_HandleTypeDef hdma_i2c1_rx;


uint8_t* I2Cbuffer;
int16_t  accelXValue;
uint8_t  firstHalf; 
uint8_t  secondHalf;

uint8_t firstinit = 1;
 
#define I2CADDRESSOFMPU6050 0xD0 
#define ACCELX8_15 0x3B 
#define ACCELX0_7 0x3C
#define ACCELY8_15 0x3D 
#define ACCELY0_7 0x3E
#define ACCELZ8_15 0x3F
#define ACCELZ0_7 0x40
#define WHO_AM_I 0x75
#define POWER_CONFIG1 0x6B

void Using_I2C_in_DMA_without_Sequential()
{
	if (firstinit == 1)
	{
		firstinit = 0; 
		I2Cbuffer2[0] = POWER_CONFIG1;
		I2Cbuffer2[1] = 0;
		HAL_I2C_Master_Transmit_IT(&hi2c1, I2CADDRESSOFMPU6050, I2Cbuffer2, 2); 
		while (HAL_I2C_GetState(&hi2c1) != HAL_I2C_STATE_READY) ;
	}
	//in DMA mode sequential does NOT work, unless you go directly into the 
	//registers to do it. 
	//Also, I cant get DMA to wotk in transmit but then why would I really want to right?
	I2Cbuffer2[0] = ACCELX8_15;
	HAL_I2C_Master_Transmit_IT(&hi2c1, I2CADDRESSOFMPU6050, I2Cbuffer2, 1); 
	while (HAL_I2C_GetState(&hi2c1) != HAL_I2C_STATE_READY) ;
   
	//over her I dont transsmit the ACCELX8_15 to ACCELX0_7 as the I2C device does it for me 
	//(burst mode)
	HAL_I2C_Master_Receive_DMA(&hi2c1, I2CADDRESSOFMPU6050, I2Cbuffer2, 1);
	while (HAL_I2C_GetState(&hi2c1) != HAL_I2C_STATE_READY) ;
	firstHalf = I2Cbuffer2[0];  
	HAL_I2C_Master_Receive_DMA(&hi2c1, I2CADDRESSOFMPU6050, I2Cbuffer2, 1);
	while (HAL_I2C_GetState(&hi2c1) != HAL_I2C_STATE_READY) ;
	secondHalf = I2Cbuffer2[0];
  
	accelXValue =  firstHalf << 8 | secondHalf;
}

void initI2C()
{
	__HAL_RCC_GPIOB_CLK_ENABLE();
	
	
	/* DMA controller clock enable */
	__HAL_RCC_DMA1_CLK_ENABLE();

	/* DMA interrupt init */
	/* DMA1_Stream0_IRQn interrupt configuration */
	HAL_NVIC_SetPriority(DMA1_Stream0_IRQn, 0, 0);
	HAL_NVIC_EnableIRQ(DMA1_Stream0_IRQn);
	
	
	hi2c1.Instance = I2C1;
	hi2c1.Init.ClockSpeed = 10000; //100000
	hi2c1.Init.DutyCycle = I2C_DUTYCYCLE_2;
	hi2c1.Init.OwnAddress1 = 0;
	hi2c1.Init.AddressingMode = I2C_ADDRESSINGMODE_7BIT;
	hi2c1.Init.DualAddressMode = I2C_DUALADDRESS_DISABLE;
	hi2c1.Init.OwnAddress2 = 0;
	hi2c1.Init.GeneralCallMode = I2C_GENERALCALL_DISABLE;
	hi2c1.Init.NoStretchMode = I2C_NOSTRETCH_DISABLE;
	if (HAL_I2C_Init(&hi2c1) != HAL_OK)
	{
		
	}
	

}



void HAL_I2C_MspInit(I2C_HandleTypeDef* hi2c)
{

	GPIO_InitTypeDef GPIO_InitStruct;
	if (hi2c->Instance == I2C1)
	{
		/* USER CODE BEGIN I2C1_MspInit 0 */

		/* USER CODE END I2C1_MspInit 0 */
  
		  /**I2C1 GPIO Configuration    
		  PB6     ------> I2C1_SCL
		  PB7     ------> I2C1_SDA 
		  */
		GPIO_InitStruct.Pin = GPIO_PIN_6 | GPIO_PIN_7;
		GPIO_InitStruct.Mode = GPIO_MODE_AF_OD;
		GPIO_InitStruct.Pull = GPIO_PULLUP;
		GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
		GPIO_InitStruct.Alternate = GPIO_AF4_I2C1;
		HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

		/* Peripheral clock enable */
		__HAL_RCC_I2C1_CLK_ENABLE();
  
		/* I2C1 DMA Init */
		/* I2C1_RX Init */
		hdma_i2c1_rx.Instance = DMA1_Stream0;
		hdma_i2c1_rx.Init.Channel = DMA_CHANNEL_1;
		hdma_i2c1_rx.Init.Direction = DMA_PERIPH_TO_MEMORY;
		hdma_i2c1_rx.Init.PeriphInc = DMA_PINC_DISABLE;
		hdma_i2c1_rx.Init.MemInc = DMA_MINC_ENABLE;
		hdma_i2c1_rx.Init.PeriphDataAlignment = DMA_PDATAALIGN_BYTE;
		hdma_i2c1_rx.Init.MemDataAlignment = DMA_MDATAALIGN_BYTE;
		hdma_i2c1_rx.Init.Mode = DMA_CIRCULAR;
		hdma_i2c1_rx.Init.Priority = DMA_PRIORITY_LOW;
		hdma_i2c1_rx.Init.FIFOMode = DMA_FIFOMODE_DISABLE;
		if (HAL_DMA_Init(&hdma_i2c1_rx) != HAL_OK)
		{ 
		}

		__HAL_LINKDMA(hi2c, hdmarx, hdma_i2c1_rx);

		/* I2C1 interrupt Init */
		HAL_NVIC_SetPriority(I2C1_EV_IRQn, 0, 0);
		HAL_NVIC_EnableIRQ(I2C1_EV_IRQn);
		HAL_NVIC_SetPriority(I2C1_ER_IRQn, 0, 0);
		HAL_NVIC_EnableIRQ(I2C1_ER_IRQn);
		/* USER CODE BEGIN I2C1_MspInit 1 */

		/* USER CODE END I2C1_MspInit 1 */
	}

}

void HAL_MspInit(void)
{
	/* USER CODE BEGIN MspInit 0 */

	/* USER CODE END MspInit 0 */

	HAL_NVIC_SetPriorityGrouping(NVIC_PRIORITYGROUP_0);

	/* System interrupt init*/
	/* MemoryManagement_IRQn interrupt configuration */
	HAL_NVIC_SetPriority(MemoryManagement_IRQn, 0, 0);
	/* BusFault_IRQn interrupt configuration */
	HAL_NVIC_SetPriority(BusFault_IRQn, 0, 0);
	/* UsageFault_IRQn interrupt configuration */
	HAL_NVIC_SetPriority(UsageFault_IRQn, 0, 0);
	/* SVCall_IRQn interrupt configuration */
	HAL_NVIC_SetPriority(SVCall_IRQn, 0, 0);
	/* DebugMonitor_IRQn interrupt configuration */
	HAL_NVIC_SetPriority(DebugMonitor_IRQn, 0, 0);
	/* PendSV_IRQn interrupt configuration */
	HAL_NVIC_SetPriority(PendSV_IRQn, 0, 0);
	/* SysTick_IRQn interrupt configuration */
	HAL_NVIC_SetPriority(SysTick_IRQn, 0, 0);

	/* USER CODE BEGIN MspInit 1 */

	/* USER CODE END MspInit 1 */
}


void msp_init()
{
	
	auto hi2c = &hi2c1;
		
	HAL_NVIC_SetPriorityGrouping(NVIC_PRIORITYGROUP_0);

	/* System interrupt init*/
	/* MemoryManagement_IRQn interrupt configuration */
	HAL_NVIC_SetPriority(MemoryManagement_IRQn, 0, 0);
	/* BusFault_IRQn interrupt configuration */
	HAL_NVIC_SetPriority(BusFault_IRQn, 0, 0);
	/* UsageFault_IRQn interrupt configuration */
	HAL_NVIC_SetPriority(UsageFault_IRQn, 0, 0);
	/* SVCall_IRQn interrupt configuration */
	HAL_NVIC_SetPriority(SVCall_IRQn, 0, 0);
	/* DebugMonitor_IRQn interrupt configuration */
	HAL_NVIC_SetPriority(DebugMonitor_IRQn, 0, 0);
	/* PendSV_IRQn interrupt configuration */
	HAL_NVIC_SetPriority(PendSV_IRQn, 0, 0);
	/* SysTick_IRQn interrupt configuration */
	HAL_NVIC_SetPriority(SysTick_IRQn, 0, 0);
	
	
	GPIO_InitTypeDef GPIO_InitStruct;
	if (hi2c->Instance == I2C1)
	{
		/* USER CODE BEGIN I2C1_MspInit 0 */

		/* USER CODE END I2C1_MspInit 0 */
  
		  /**I2C1 GPIO Configuration    
		  PB6     ------> I2C1_SCL
		  PB7     ------> I2C1_SDA 
		  */
		GPIO_InitStruct.Pin = GPIO_PIN_6 | GPIO_PIN_7;
		GPIO_InitStruct.Mode = GPIO_MODE_AF_OD;
		GPIO_InitStruct.Pull = GPIO_PULLUP;
		GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
		GPIO_InitStruct.Alternate = GPIO_AF4_I2C1;
		HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

		/* Peripheral clock enable */
		__HAL_RCC_I2C1_CLK_ENABLE();
  
		/* I2C1 DMA Init */
		/* I2C1_RX Init */
		hdma_i2c1_rx.Instance = DMA1_Stream0;
		hdma_i2c1_rx.Init.Channel = DMA_CHANNEL_1;
		hdma_i2c1_rx.Init.Direction = DMA_PERIPH_TO_MEMORY;
		hdma_i2c1_rx.Init.PeriphInc = DMA_PINC_DISABLE;
		hdma_i2c1_rx.Init.MemInc = DMA_MINC_ENABLE;
		hdma_i2c1_rx.Init.PeriphDataAlignment = DMA_PDATAALIGN_BYTE;
		hdma_i2c1_rx.Init.MemDataAlignment = DMA_MDATAALIGN_BYTE;
		hdma_i2c1_rx.Init.Mode = DMA_CIRCULAR;
		hdma_i2c1_rx.Init.Priority = DMA_PRIORITY_LOW;
		hdma_i2c1_rx.Init.FIFOMode = DMA_FIFOMODE_DISABLE;
		if (HAL_DMA_Init(&hdma_i2c1_rx) != HAL_OK)
		{ 
		}

		__HAL_LINKDMA(hi2c, hdmarx, hdma_i2c1_rx);

		/* I2C1 interrupt Init */
		HAL_NVIC_SetPriority(I2C1_EV_IRQn, 0, 0);
		HAL_NVIC_EnableIRQ(I2C1_EV_IRQn);
		HAL_NVIC_SetPriority(I2C1_ER_IRQn, 0, 0);
		HAL_NVIC_EnableIRQ(I2C1_ER_IRQn);
		/* USER CODE BEGIN I2C1_MspInit 1 */

		/* USER CODE END I2C1_MspInit 1 */
	}
}

#endif

DECLARE_ALL_AO_PTR
//UserCode_Sectiona_end

void RunSelectedIntegrationTest_I2C_TEST()
{

//UserCode_Sectionb
#ifdef aehal
	AE_Init();  
	
	AEITEST_END_TestsAfterTimer_exeHalTest(5000)
	AEITEST_EXPECT_TEST_TO_RUN_exeHalTest("i2c_returned")
		
#else
	

	AE_Init();  
	
	initI2C();
	
	//msp_init();
		
	
	
#endif
	
//	uint32_t group;
//	uint32_t preemt;
//	uint32_t subpreemt;
//	HAL_NVIC_GetPriority(SysTick_IRQn, 4, &preemt, &subpreemt);
	
	txcmplt = false;
	rxcmplt = false;
	
	//! [timed end]
	//AEITEST_END_TestsAfterTimer_exeHalTest(5000)
	//! [timed end]
		
	//! [expect to run]
	//AEITEST_EXPECT_TEST_TO_RUN_exeHalTest("ADC1 test")
	//! [expect to run]
		
//	AEITestLogData* scsc = 0;
//	scsc->ID = 90;
//	auto svvs = scsc->pcFileName;
//	auto svvss = scsc->ID;
		 
	
#ifdef aehal
		
	i2c1->SetI2C_MasterTxCpltCallback_t([]()->void {
		txcmplt = true;
	});
	i2c1->SetI2C_MasterRxCpltCallback([]()->void {
		rxcmplt = true;
	});
	
	static AELoop* loop1_l = AELoop::GetFromPool(5, AEPriorities::MediumPriority, loopfunc1);
	
	
#else
	while (true)
	{
		Using_I2C_in_DMA_without_Sequential();
		HAL_Delay(100);
	}
#endif
	
		
	
	
#ifdef aehal
		//i2c1->WriteBytes(0x68, 0x3B, 0, nullptr);
	bool firstinit  = 1;
	uint8_t I2Cbuffer2[100];
	while (false)
	{
		
		if (firstinit == 1)
		{
			firstinit = 0; 
			I2Cbuffer2[0] = 0; 
			i2c1->WriteBytes(0x68, 0x6B, 1, I2Cbuffer2);
			WAIT_UNTIL_I2C_READY
//			HAL_I2C_Master_Transmit_IT(&hi2c1, I2CADDRESSOFMPU6050, I2Cbuffer2, 2); 
//			while (HAL_I2C_GetState(&hi2c1) != HAL_I2C_STATE_READY) ;
		}
		
		i2c1->WriteBytes(0x68, 0x3B, 0, nullptr);
		WAIT_UNTIL_I2C_READY
		//i2c1->WriteBytes(0x68, 0xD0, 0, nullptr);
		AEPrint("asd\n");
		//if (false)
		//{
		 
		//If you hit the breakpoint below, one of the interrupts was unhandled in your code. 
	//Define the following function in your code to handle it:
	//	extern "C" void FLASH_IRQHandler();
		
		
		//wait for that tx to finish
		//while (txcmplt == false) {}
		txcmplt = false;
	
		//read from that register (in this case will get the getMotion6 of accelxyz and gyroxyz)
		//TODO: get rid of the pdata arg in this function! it uses it's own buffer for this.
		//i2c1->ReadBytes(0x68, 14, nullptr);
		i2c1->ReadBytes(0x68, 1, nullptr);
		WAIT_UNTIL_I2C_READY
		uint8_t  firstHalf = i2c1->GetI2CBuffer()[0]; 
		i2c1->ReadBytes(0x68, 1, nullptr);
		WAIT_UNTIL_I2C_READY
		uint8_t  secondHalf = i2c1->GetI2CBuffer()[0];
		int16_t accelXValue =  firstHalf << 8 | secondHalf;
	
		//wait for that rx to complete
		//while (rxcmplt == false) {}
		rxcmplt = false;
	
		//from that read buffer, get the accel and gyro values
		int16_t ax = (((int16_t)(i2c1->GetI2CBuffer()[0])) << 8) | i2c1->GetI2CBuffer()[1];
		int16_t ay = (((int16_t)(i2c1->GetI2CBuffer()[2])) << 8) | i2c1->GetI2CBuffer()[3];
		int16_t az = (((int16_t)(i2c1->GetI2CBuffer()[4])) << 8) | i2c1->GetI2CBuffer()[5];
		int16_t gx = (((int16_t)i2c1->GetI2CBuffer()[8]) << 8) | i2c1->GetI2CBuffer()[9];
		int16_t gy = (((int16_t)i2c1->GetI2CBuffer()[10]) << 8) | i2c1->GetI2CBuffer()[11];
		int16_t gz = (((int16_t)i2c1->GetI2CBuffer()[12]) << 8) | i2c1->GetI2CBuffer()[13];
		
		
		
	}
	
#endif
		
	/* Start scheduler */ 
	AEConfigureAndStart();
//UserCode_Sectionb_end

}


//UserCode_Sectionc
#ifdef aehal

bool FirstInit = 1;
void loopfunc1(void* ptr)
{
	
	if (FirstInit == 1)
	{
		FirstInit = 0; 
		I2Cbuffer2[0] = 0; 
		i2c1->WriteBytes(0x68, 0x6B, 1, I2Cbuffer2);
		while (txcmplt == false) {}
		txcmplt = false;
		//			HAL_I2C_Master_Transmit_IT(&hi2c1, I2CADDRESSOFMPU6050, I2Cbuffer2, 2); 
		//			while (HAL_I2C_GetState(&hi2c1) != HAL_I2C_STATE_READY) ;
	}
	
	
	//write to the register I will read from, in this case it is  to register MPU6050_RA_ACCEL_XOUT_H = 0x3B
	i2c1->WriteBytes(0x68, 0x3B, 0, nullptr);
	AEPrint("asd\n");
	//if (false)
	//{
		
	
	//wait for that tx to finish
	while (txcmplt == false) {}
	txcmplt = false;
	
	//read from that register (in this case will get the getMotion6 of accelxyz and gyroxyz)
	//TODO: get rid of the pdata arg in this function! it uses it's own buffer for this.
	//i2c1->ReadBytes(0x68, 14, nullptr);
	
 
	//wait for that rx to complete
//	while (rxcmplt == false) {}
//	rxcmplt = false;
	
		
	i2c1->ReadBytes(0x68, 14, nullptr);
	while (rxcmplt == false) {}
	rxcmplt = false;
	uint8_t  firstHalf = i2c1->GetI2CBuffer()[0]; 
	uint8_t  secondHalf = i2c1->GetI2CBuffer()[1]; 
	//	i2c1->ReadBytes(0x68, 1, nullptr);
	//	while (rxcmplt == false) {}
	//	rxcmplt = false;
	//	uint8_t  secondHalf = i2c1->GetI2CBuffer()[0]; 
	//	int16_t accelXValue =  firstHalf << 8 | secondHalf;
	
		//from that read buffer, get the accel and gyro values
	int16_t ax = (((int16_t)(i2c1->GetI2CBuffer()[0])) << 8) | i2c1->GetI2CBuffer()[1];
	int16_t ay = (((int16_t)(i2c1->GetI2CBuffer()[2])) << 8) | i2c1->GetI2CBuffer()[3];
	int16_t az = (((int16_t)(i2c1->GetI2CBuffer()[4])) << 8) | i2c1->GetI2CBuffer()[5];
	int16_t gx = (((int16_t)i2c1->GetI2CBuffer()[8]) << 8) | i2c1->GetI2CBuffer()[9];
	int16_t gy = (((int16_t)i2c1->GetI2CBuffer()[10]) << 8) | i2c1->GetI2CBuffer()[11];
	int16_t gz = (((int16_t)i2c1->GetI2CBuffer()[12]) << 8) | i2c1->GetI2CBuffer()[13];
	//}
	
#ifdef  SWIL_HWIL_DRIVEN__HWIL
	AEITEST_exeHalTest_MUST_PASS_THIS_MANY("i2c_returned", az > 10000, "mpu returned data with az greater than 10000", 18)
#else 
	AEITEST_exeHalTest_MUST_PASS_THIS_MANY("i2c_returned", az == 0, "mpu returned data with az greater than 10000", 18)
#endif 
	
	
}

#else


#endif
//UserCode_Sectionc_end

#endif
