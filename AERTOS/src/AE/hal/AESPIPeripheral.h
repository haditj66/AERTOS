#pragma once
//#pragma warning( push )
//#pragma warning( disable : 4005)

//#include "AEConfig.h"
#include "AEPeripheral.h"
 


#ifndef USING_AESPI
#error you included this file but you did not provide a AESPI.h file in AEHalFiles directory.
#endif 

#ifdef USING_AEDMA 
#include "AEDMA.h"
#endif 

#define  SPIRecieveBufferSize  200

typedef void(*AE_SPI_TxCpltCallback_t)(void);
typedef void(*AE_SPI_RxCpltCallback_t)(void);

class AESPI
{ 
#ifdef BOARD_USED__STM32F411RE
//	friend void HAL_I2C_MasterTxCpltCallback(I2C_HandleTypeDef *I2C_Handle);
//	friend void HAL_I2C_MasterRxCpltCallback(I2C_HandleTypeDef *I2C_Handle);
#endif
	
public:
	AESPI() {
		AE_SPI_MasterTxCpltCallback = []()->void {};
		AE_SPI_MasterRxCpltCallback = []()->void {}; }; 
	
	
#ifdef USING_AEDMA 
	//AEDMA dmaForI2C;
	
	//DMA_HandleTypeDef dmaForI2C;
#endif 
	
	uint32_t GetSPIBufferSize()
	{
		return SPIRecieveBufferSize;
	}
	
	uint8_t* GetSPIBuffer()
	{
		return bufferForSPI;
	}
	
	void SetSPI_MasterTxCpltCallback_t(AE_SPI_TxCpltCallback_t ae_SPI_MasterTxCpltCallback)
	{
		AE_SPI_MasterTxCpltCallback = ae_SPI_MasterTxCpltCallback;
	}
	
	void SetI2C_MasterRxCpltCallback(AE_SPI_RxCpltCallback_t ae_SPI_MasterRxCpltCallback)
	{
		AE_SPI_MasterRxCpltCallback = ae_SPI_MasterRxCpltCallback;
	}
	
	
	void AE_SPI_Transmit(uint8_t* data, uint16_t size); 
	
	void AE_SPI_Receive(uint8_t* data, uint16_t size);
	void AE_SPI_TransmitReceive(uint8_t* dataToTransmit, uint16_t sizeToTransmit, uint8_t* dataToReceive, uint16_t sizeToReceive);
	 
	
	
	void Init(SPI_Handle* spi_Handle, Port_t nssPort, Pin_t nssPin)//, I2C_Handle* gPIO_Handle_inst) 
	{ 
		_spi_Handle = spi_Handle; 
		NssPort = nssPort;
		NssPin = nssPin;
	} 
	
	Port_t NssPort;
	Pin_t NssPin;
	
	SPI_Handle* _spi_Handle; 
	AE_SPI_TxCpltCallback_t AE_SPI_MasterTxCpltCallback; 
	AE_SPI_RxCpltCallback_t AE_SPI_MasterRxCpltCallback; 
private:  
	 
	
	uint8_t bufferForSPI[SPIRecieveBufferSize];
	
	
};

#define NumOFPinsNeeded 4

 

#define templateForSPI uint16_t WhichInstanceOfSPI, bool SLAVEMODE, Portenum SPI_SCK_Port, PinEnum SPI_SCK_Pin, Portenum SPI_MISO_Port, PinEnum SPI_MISO_Pin, Portenum SPI_MOSI_Port, PinEnum SPI_MOSI_Pin, Portenum SPI_NSS_Port, PinEnum SPI_NSS_Pin
#define templateargsForSPI WhichInstanceOfSPI, SLAVEMODE, SPI_SCK_Port, SPI_SCK_Pin, SPI_MISO_Port, SPI_MISO_Pin, SPI_MOSI_Port, SPI_MOSI_Pin, SPI_NSS_Port, SPI_NSS_Pin
#define templateargsForHardware  SPI_SCK_Port, SPI_SCK_Pin, SPI_MISO_Port, SPI_MISO_Pin, SPI_MOSI_Port, SPI_MOSI_Pin, SPI_NSS_Port, SPI_NSS_Pin

template<templateForSPI>
	class SPIPeripheral :
		public AEPeripheral <SPIPeripheral<templateargsForSPI>,
		NumOFPinsNeeded, 
		SPI_Handle, 
		templateargsForHardware>
	{
		
		friend void AE_Init(void);
		
	public:
//		DMA_HandleTypeDef hdma_adcc;
#ifdef USING_AEDMA 
		
		AEDMA dmaForSPI;
#endif 
		 
		
 
		AESPI InstanceOfSPI; 
//		AEI2C AEI2C_inst2;
//		AEI2C AEI2C_inst3;
//		AEI2C AEI2C_inst4;
//		AEI2C AEI2C_inst5;

		protected:
 
//		Port_t ch1_Port;
//		Pin_t  ch1_Pin;
//		Port_t ch2_Port;
//		Pin_t  ch2_Pin;
//		Port_t ch3_Port;
//		Pin_t  ch3_Pin;
//		Port_t ch4_Port;
//		Pin_t  ch4_Pin;
//		Port_t ch5_Port;
//		Pin_t  ch5_Pin;
		
		AESPI* GetPeripheralInstance() { 
			this->InstanceOfSPI.Init(&(this->PeripheralHandle_t), this->GPIOPinSelected4.GetThePort(), this->GPIOPinSelected4.GetThePin()); 
			return &InstanceOfSPI;}

		// Inherited via AEPeripheral 
		void _InitializePinSelectors(CreateTypeSelector_funcPtr(&functPtrsToChangeTypeSelectorss)[NumOFPinsNeeded]) override;
 

		// Inherited via AEPeripheral
		void _Initialize(Port_t port1, Pin_t pin1, Port_t port2, Pin_t pin2, Port_t port3, Pin_t pin3, Port_t port4, Pin_t pin4, Port_t port5, Pin_t pin5)override;
		
//		void Pre_Initialize(Port_t port1, Pin_t pin1, Port_t port2, Pin_t pin2, Port_t port3, Pin_t pin3, Port_t port4, Pin_t pin4, Port_t port5, Pin_t pin5) override {
//		if (this->ForWhichPeripheralNumber == 1)
//		{
//#ifdef I2CPERIPHERAL1_Name_CH1
//			AEAssertRuntime(this->GPIOPinSelected1.isInitialized() , "you did not give a pin and port for this channel but you gave a name for the channel I2CPERIPHERAL1_Name_CH1 in AEConfig")
//#endif
//#ifdef I2CPERIPHERAL1_Name_CH2
//			AEAssertRuntime(this->GPIOPinSelected2.isInitialized() , "you did not give a pin and port for this channel but you gave a name for the channel I2CPERIPHERAL1_Name_CH2 in AEConfig")
//#endif
//#ifdef I2CPERIPHERAL1_Name_CH3
//			AEAssertRuntime(this->GPIOPinSelected3.isInitialized() , "you did not give a pin and port for this channel but you gave a name for the channel I2CPERIPHERAL1_Name_CH3 in AEConfig")
//#endif
//#ifdef I2CPERIPHERAL1_Name_CH4
//			AEAssertRuntime(this->GPIOPinSelected4.isInitialized() , "you did not give a pin and port for this channel but you gave a name for the channel I2CPERIPHERAL1_Name_CH4 in AEConfig")
//#endif
//#ifdef I2CPERIPHERAL1_Name_CH5
//			AEAssertRuntime(this->GPIOPinSelected5.isInitialized() , "you did not give a pin and port for this channel but you gave a name for the channel I2CPERIPHERAL1_Name_CH5 in AEConfig")
//#endif
//		}
//			
//		if (this->ForWhichPeripheralNumber == 2)
//		{
//#ifdef I2CPERIPHERAL2_Name_CH1
//			AEAssertRuntime(this->GPIOPinSelected1.isInitialized() , "you did not give a pin and port for this channel but you gave a name for the channel I2CPERIPHERAL2_Name_CH1 in AEConfig")
//#endif
//#ifdef I2CPERIPHERAL2_Name_CH2
//			AEAssertRuntime(this->GPIOPinSelected2.isInitialized() , "you did not give a pin and port for this channel but you gave a name for the channel I2CPERIPHERAL2_Name_CH2 in AEConfig")
//#endif
//#ifdef I2CPERIPHERAL2_Name_CH3
//			AEAssertRuntime(this->GPIOPinSelected3.isInitialized() , "you did not give a pin and port for this channel but you gave a name for the channel I2CPERIPHERAL2_Name_CH3 in AEConfig")
//#endif
//#ifdef I2CPERIPHERAL2_Name_CH4
//			AEAssertRuntime(this->GPIOPinSelected4.isInitialized() , "you did not give a pin and port for this channel but you gave a name for the channel I2CPERIPHERAL2_Name_CH4 in AEConfig")
//#endif
//#ifdef I2CPERIPHERAL2_Name_CH5
//			AEAssertRuntime(this->GPIOPinSelected5.isInitialized() , "you did not give a pin and port for this channel but you gave a name for the channel I2CPERIPHERAL2_Name_CH5 in AEConfig")
//#endif
	//}
		
		
		//};
 


		
		
//		AEI2C* GetPeripheralInstanceCh1() 
//{	 	this->AEI2C_inst1.Init(this->GPIOPinSelected1.GetThePort(), this->GPIOPinSelected1.GetThePin(), &I2Cdata[0]); return &AEI2C_inst1;}
//		AEI2C* GetPeripheralInstanceCh2() 
//{		this->AEI2C_inst2.Init(this->GPIOPinSelected2.GetThePort(), this->GPIOPinSelected2.GetThePin(), &I2Cdata[1]); return &AEI2C_inst2;}
//		AEI2C* GetPeripheralInstanceCh3() 
//{		this->AEI2C_inst3.Init(this->GPIOPinSelected3.GetThePort(), this->GPIOPinSelected3.GetThePin(), &I2Cdata[2]); return &AEI2C_inst3;}
//		AEI2C* GetPeripheralInstanceCh4() 
//{		this->AEI2C_inst4.Init(this->GPIOPinSelected4.GetThePort(), this->GPIOPinSelected4.GetThePin(), &I2Cdata[3]); return &AEI2C_inst4;}
//		AEI2C* GetPeripheralInstanceCh5() 
//{		this->AEI2C_inst5.Init(this->GPIOPinSelected5.GetThePort(), this->GPIOPinSelected5.GetThePin(), &I2Cdata[4]); return &AEI2C_inst5;}
	};
	

 





 

 //global pheripherals declaration
#ifdef SPIPERIPHERAL1
extern SPIPERIPHERAL1* SPIPERIPHERAL1_Instance;  
#define SPIPERIPHERAL1_INITIALIZE SPIPERIPHERAL1_Instance->ForWhichPeripheralNumber = 1; SPIPERIPHERAL1_Instance->initializePeripheral(); SPIPERIPHERAL1_Name = SPIPERIPHERAL1_Instance->GetPeripheralInstance();
#ifndef SPIPERIPHERAL1_Name
#error You need to define SPIPERIPHERAL1_Name
#else
extern  AESPI* SPIPERIPHERAL1_Name;
#endif
#endif 

 

 
 
//#endif //target_stm32f4



//#pragma warning( pop ) 








