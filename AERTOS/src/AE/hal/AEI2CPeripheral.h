#pragma once
//#pragma warning( push )
//#pragma warning( disable : 4005)

//#include "AEConfig.h"
#include "AEPeripheral.h"
 


#ifndef USING_AEI2C 
#error you included this file but you did not provide a AEI2C.h file in AEHalFiles directory.
#endif 

#ifdef USING_AEDMA 
#include "AEDMA.h"
#endif 

class AEI2C;
typedef void(*AE_I2C_MasterTxCpltCallback_t)(AEI2C*);
typedef void(*AE_I2C_MasterRxCpltCallback_t)(AEI2C*);

class AEI2C
{ 
#ifdef BOARD_USED__STM32F411RE
	friend void HAL_I2C_MasterTxCpltCallback(I2C_HandleTypeDef *I2C_Handle);
	friend void HAL_I2C_MasterRxCpltCallback(I2C_HandleTypeDef *I2C_Handle);
#endif
	
public:
	AEI2C() {
		TotalNumOfI2cID++;
		ID = TotalNumOfI2cID;
		AE_I2C_MasterTxCpltCallback = [](AEI2C* p) ->void {};
		AE_I2C_MasterRxCpltCallback = [](AEI2C* p)->void {};
	}; 
	
	
#ifdef USING_AEDMA 
	//AEDMA dmaForI2C;
	
	//DMA_HandleTypeDef dmaForI2C;
#endif 
	
	
	uint16_t GetId() const
	{
		return ID;
	}
	
	uint8_t* GetI2CBuffer()
	{
		return I2Cbuffer22;
	}
	
	void SetI2C_MasterTxCpltCallback(AE_I2C_MasterTxCpltCallback_t ae_I2C_MasterTxCpltCallback_t)
	{
		AE_I2C_MasterTxCpltCallback = ae_I2C_MasterTxCpltCallback_t;
	}
	
	void SetI2C_MasterRxCpltCallback(AE_I2C_MasterRxCpltCallback_t ae_I2C_MasterRxCpltCallback_t)
	{
		AE_I2C_MasterRxCpltCallback = ae_I2C_MasterRxCpltCallback_t;
	}
	
	
	bool writeBit(uint8_t devAddr, uint8_t regAddr, uint8_t bitNum, uint8_t datatoWrite) {
		uint8_t b;
		//readByte(devAddr, regAddr, &b, 400);
		//b = (data != 0) ? (b | (1 << bitNum)) : (b & ~(1 << bitNum));
		return WriteByte(devAddr, regAddr, b);
	}
	
	bool WriteByte(uint8_t devAddr, uint8_t regAddr, uint8_t datatoWrite) {
		return WriteBytes(devAddr, regAddr, 1, &datatoWrite);
	}  


	int8_t readByte(uint8_t devAddr, uint8_t *data, uint16_t timeout) {
		return ReadBytes(devAddr, 1, data, timeout);
	}
 

	bool WriteBytes(uint8_t devAddr, uint8_t regAddr, uint8_t length, uint8_t* datatoWrite);
	int8_t ReadBytes(uint8_t devAddr, uint8_t length, uint8_t *pdata, uint16_t timeout = 100000);
	
	
	void Init(I2C_Handle* i2c_Handle)//, I2C_Handle* gPIO_Handle_inst) 
	{ 
		_i2c_Handle = i2c_Handle; 
	} 
	
	I2C_Handle* _i2c_Handle;

private:  
	
	static uint8_t TotalNumOfI2cID;
	uint8_t ID;
	
	AE_I2C_MasterTxCpltCallback_t AE_I2C_MasterTxCpltCallback; 
	AE_I2C_MasterRxCpltCallback_t AE_I2C_MasterRxCpltCallback; 
	
	uint8_t I2Cbuffer22[100];
	
	
};

#define NumOFPinsNeeded 2 

 

#define templateForI2C_def uint16_t WhichInstanceOfI2C, Portenum I2C_SCL_Port, PinEnum I2C_SCL_Pin, Portenum I2C_SDA_Port, PinEnum I2C_SDA_Pin, uint32_t Clockspeed
#define templateargsForI2C WhichInstanceOfI2C, I2C_SCL_Port, I2C_SCL_Pin, I2C_SDA_Port, I2C_SDA_Pin, Clockspeed
#define templateargsForHardware I2C_SCL_Port, I2C_SCL_Pin, I2C_SDA_Port, I2C_SDA_Pin

template<templateForI2C_def>
	class I2CPeripheral :
		public AEPeripheral <I2CPeripheral<templateargsForI2C>,
		NumOFPinsNeeded, 
		I2C_Handle, 
		templateargsForHardware>
	{
		
		friend void AE_Init(void);
		
	public:
//		DMA_HandleTypeDef hdma_adcc;
#ifdef USING_AEDMA 
		//AEDMA dmaForI2C;
		AEDMA dmaForI2C;
#endif 
		
		
		
 
		AEI2C InstanceOfI2C; 
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
		
		AEI2C* GetPeripheralInstance(){ 
			this->InstanceOfI2C.Init(&(this->PeripheralHandle_t)); 
			return &InstanceOfI2C;}

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
#ifdef I2CPERIPHERAL1
extern I2CPERIPHERAL1* I2CPERIPHERAL1_Instance;  
#define I2CPERIPHERAL1_INITIALIZE I2CPERIPHERAL1_Instance->ForWhichPeripheralNumber = 1; I2CPERIPHERAL1_Instance->initializePeripheral(); I2CPERIPHERAL1_Name = I2CPERIPHERAL1_Instance->GetPeripheralInstance();
#ifndef I2CPERIPHERAL1_Name
#error You need to define I2CPERIPHERAL1_Name
#else
extern  AEI2C* I2CPERIPHERAL1_Name;
#endif
#endif 

 

 
 
//#endif //target_stm32f4



//#pragma warning( pop ) 








