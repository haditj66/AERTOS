#pragma once
//#pragma warning( push )
//#pragma warning( disable : 4005)

//#include "AEConfig.h"
#include "AEPeripheral.h"
 


#ifndef USING_AEPWM
#error you included this file but you did not provide a AEPWM.h file in AEHalFiles directory.
#endif 

#ifdef USING_AEDMA 
#include "AEDMA.h"
#endif 
 


#define NumOFPinsNeeded 1

 

#define templateForPWM  uint16_t WhichInstanceOfPWM, Portenum PWM_PwmPinOut_Port, PinEnum PWM_PwmPinOut_Pin
#define templateargsForPWM WhichInstanceOfPWM, PWM_PwmPinOut_Port, PWM_PwmPinOut_Pin
#define templateargsForHardware  PWM_PwmPinOut_Port, PWM_PwmPinOut_Pin


class AEPWM
{ 
#ifdef BOARD_USED__STM32F411RE
//	friend void HAL_I2C_MasterTxCpltCallback(I2C_HandleTypeDef *I2C_Handle);
//	friend void HAL_I2C_MasterRxCpltCallback(I2C_HandleTypeDef *I2C_Handle);
#endif
	
	template<templateForPWM>
	 friend class PWMPeripheral;
	
public:
	AEPWM() {  }; 
	
	
#ifdef USING_AEDMA 
	//AEDMA dmaForI2C;
	
	//DMA_HandleTypeDef dmaForI2C;
#endif 
	 
	 
//	TIM_TypeDef* TimerInstance; 
//	TIM_OC_InitTypeDef sConfigOC;
private:
	float DutyCycle;
	uint32_t Period;
public:
	void StartPWM();// { HAL_TIM_PWM_Start(&this->PeripheralHandle_t, PWMChannel); } 
	void StopPWM(); // { HAL_TIM_PWM_Stop(&this->PeripheralHandle_t, PWMChannel); } 
	void ChangeDutyCycle(float dutycycleBetween1To100); 
//	{
//		//first find the pulse value that corresponds to this ratio
//		uint32_t period = __HAL_TIM_GET_AUTORELOAD(&this->PeripheralHandle_t);
//		uint32_t pulseValue = (uint32_t)((float)(dutycycleBetween1To100 / 100) * (float)period);
//
//		__HAL_TIM_SET_COMPARE(&this->PeripheralHandle_t, PWMChannel, pulseValue); 
//		DutyCycle = dutycycleBetween1To100;
//	} 

	void ChangePeriodOfSignal(uint32_t period); 
//	{ 
//		__HAL_TIM_SET_AUTORELOAD(&this->PeripheralHandle_t, period);
//		Period = period;  
//	} 
	
	uint32_t GetPeriod() { return Period; }
	
	float GetDutyCycle()  { return DutyCycle; }
	
	
	  
	
	void Init(PWM_Handle* pwm_Handle, uint16_t pWMChannel)//, I2C_Handle* gPIO_Handle_inst) 
	{ 
		_pwm_Handle = pwm_Handle;  
		PWMChannel = pWMChannel;
	} 
	
	
	PWM_Handle* _pwm_Handle; 
	
private:  
	 
	uint16_t PWMChannel;
	
	
};



template<templateForPWM>
	class PWMPeripheral :
		public AEPeripheral <PWMPeripheral<templateargsForPWM>,
		NumOFPinsNeeded, 
		PWM_Handle, 
		templateargsForHardware>
	{
		
		friend void AE_Init(void);
		
	public:
//		DMA_HandleTypeDef hdma_adcc;
#ifdef USING_AEDMA 
		
		AEDMA dmaForPWM;
#endif 
		 
		
 
		AEPWM InstanceOfPWM; 
//		AEI2C AEI2C_inst2;
//		AEI2C AEI2C_inst3;
//		AEI2C AEI2C_inst4;
//		AEI2C AEI2C_inst5;

		protected:
 
		uint16_t PWMChannel;
		
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
		
		AEPWM* GetPeripheralInstance() { 
			this->InstanceOfPWM.Init(&(this->PeripheralHandle_t), PWMChannel); 
			return &InstanceOfPWM;}

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
#ifdef PWMPERIPHERAL1
extern PWMPERIPHERAL1* PWMPERIPHERAL1_Instance;  
#define PWMPERIPHERAL1_INITIALIZE PWMPERIPHERAL1_Instance->ForWhichPeripheralNumber = 1; PWMPERIPHERAL1_Instance->initializePeripheral(); PWMPERIPHERAL1_Name = PWMPERIPHERAL1_Instance->GetPeripheralInstance();
#ifndef PWMPERIPHERAL1_Name
#error You need to define PWMPERIPHERAL1_Name
#else
extern  AEPWM* PWMPERIPHERAL1_Name;
#endif
#endif 

#ifdef PWMPERIPHERAL2
extern PWMPERIPHERAL2* PWMPERIPHERAL2_Instance;  
#define PWMPERIPHERAL2_INITIALIZE PWMPERIPHERAL2_Instance->ForWhichPeripheralNumber = 2; PWMPERIPHERAL2_Instance->initializePeripheral(); PWMPERIPHERAL2_Name = PWMPERIPHERAL2_Instance->GetPeripheralInstance();
#ifndef PWMPERIPHERAL2_Name
#error You need to define PWMPERIPHERAL2_Name
#else
extern  AEPWM* PWMPERIPHERAL2_Name;
#endif
#endif 

#ifdef PWMPERIPHERAL3
extern PWMPERIPHERAL3* PWMPERIPHERAL3_Instance;  
#define PWMPERIPHERAL3_INITIALIZE PWMPERIPHERAL3_Instance->ForWhichPeripheralNumber = 3; PWMPERIPHERAL3_Instance->initializePeripheral(); PWMPERIPHERAL3_Name = PWMPERIPHERAL3_Instance->GetPeripheralInstance();
#ifndef PWMPERIPHERAL3_Name
#error You need to define PWMPERIPHERAL3_Name
#else
extern  AEPWM* PWMPERIPHERAL3_Name;
#endif
#endif 

#ifdef PWMPERIPHERAL4
extern PWMPERIPHERAL4* PWMPERIPHERAL4_Instance;  
#define PWMPERIPHERAL4_INITIALIZE PWMPERIPHERAL4_Instance->ForWhichPeripheralNumber = 4; PWMPERIPHERAL4_Instance->initializePeripheral(); PWMPERIPHERAL4_Name = PWMPERIPHERAL4_Instance->GetPeripheralInstance();
#ifndef PWMPERIPHERAL4_Name
#error You need to define PWMPERIPHERAL4_Name
#else
extern  AEPWM* PWMPERIPHERAL4_Name;
#endif
#endif 

#ifdef PWMPERIPHERAL5
extern PWMPERIPHERAL5* PWMPERIPHERAL5_Instance;  
#define PWMPERIPHERAL5_INITIALIZE PWMPERIPHERAL5_Instance->ForWhichPeripheralNumber = 5; PWMPERIPHERAL5_Instance->initializePeripheral(); PWMPERIPHERAL5_Name = PWMPERIPHERAL5_Instance->GetPeripheralInstance();
#ifndef PWMPERIPHERAL5_Name
#error You need to define PWMPERIPHERAL5_Name
#else
extern  AEPWM* PWMPERIPHERAL5_Name;
#endif
#endif 

#ifdef PWMPERIPHERAL6
extern PWMPERIPHERAL6* PWMPERIPHERAL6_Instance;  
#define PWMPERIPHERAL6_INITIALIZE PWMPERIPHERAL6_Instance->ForWhichPeripheralNumber = 6; PWMPERIPHERAL6_Instance->initializePeripheral(); PWMPERIPHERAL6_Name = PWMPERIPHERAL6_Instance->GetPeripheralInstance();
#ifndef PWMPERIPHERAL6_Name
#error You need to define PWMPERIPHERAL6_Name
#else
extern  AEPWM* PWMPERIPHERAL6_Name;
#endif
#endif 
 
 

 
 
//#endif //target_stm32f4



//#pragma warning( pop ) 








