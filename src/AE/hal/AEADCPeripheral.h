//generated file: ADCPeripheral.h


#pragma once
//#pragma warning( push )
//#pragma warning( disable : 4005)

//#include "AEConfig.h"
#include "AEPeripheral.h"
 


#ifndef USING_AEADC 
#error you included this file but you did not provide a AEADC.h file in AEHalFiles directory.
#endif 

#ifdef USING_AEDMA 
#include "AEDMA.h"
#endif 


typedef void(*AE_ADC_ConvCpltCallback_t)(void);

class AEADC
{
public:
	AEADC() {AE_ADC_ConvCpltCallback = []()->void {};}; 
	
	
	AE_ADC_ConvCpltCallback_t AE_ADC_ConvCpltCallback; 
	
	void SetADC_ConvCpltCallback_t(AE_ADC_ConvCpltCallback_t ae_ADC_ConvCpltCallback_t)
	{
		AE_ADC_ConvCpltCallback = ae_ADC_ConvCpltCallback_t;
	}
	
	inline uint16_t GetADCData() const
	{return *ADCData;}
	
	inline uint16_t* GetADCDataAddress() const
	{return ADCData;}
	
	
	void Init(Port_t port, Pin_t pin, uint16_t* adcData)//, ADC_Handle* gPIO_Handle_inst) 
	{ 
		ADCData = adcData;
		ADC_Port = port;
		ADC_Pin = pin; 
	} 
	
	

private: 
	uint16_t* ADCData;
	
	Port_t ADC_Port;
	Pin_t  ADC_Pin;
};

#define NumOFPinsNeeded 5  




#define templateForADC_def uint16_t WhichInstanceOfADC, Portenum ADC_ch1_Port = PortsMaxNum, PinEnum ADC_ch1_Pin = PINMaxNum, Portenum ADC_ch2_Port = PortsMaxNum, PinEnum ADC_ch2_Pin = PINMaxNum, Portenum ADC_ch3_Port = PortsMaxNum, PinEnum ADC_ch3_Pin = PINMaxNum, Portenum ADC_ch4_Port = PortsMaxNum, PinEnum ADC_ch4_Pin = PINMaxNum, Portenum ADC_ch5_Port = PortsMaxNum, PinEnum ADC_ch5_Pin = PINMaxNum
#define templateForADC uint16_t WhichInstanceOfADC, Portenum ADC_ch1_Port, PinEnum ADC_ch1_Pin, Portenum ADC_ch2_Port, PinEnum ADC_ch2_Pin, Portenum ADC_ch3_Port, PinEnum ADC_ch3_Pin, Portenum ADC_ch4_Port, PinEnum ADC_ch4_Pin, Portenum ADC_ch5_Port, PinEnum ADC_ch5_Pin
#define templateargsForADC WhichInstanceOfADC, ADC_ch1_Port, ADC_ch1_Pin, ADC_ch2_Port, ADC_ch2_Pin, ADC_ch3_Port, ADC_ch3_Pin, ADC_ch4_Port, ADC_ch4_Pin, ADC_ch5_Port, ADC_ch5_Pin 

#define templateargsForHardware  ADC_ch1_Port, ADC_ch1_Pin, ADC_ch2_Port, ADC_ch2_Pin, ADC_ch3_Port, ADC_ch3_Pin, ADC_ch4_Port, ADC_ch4_Pin, ADC_ch5_Port, ADC_ch5_Pin 


template<templateForADC_def>
	class ADCPeripheral :
		public AEPeripheral <ADCPeripheral<templateargsForADC>,
		NumOFPinsNeeded, 
		ADC_Handle, 
		templateargsForHardware>
	{
		
		friend void AE_Init(void);
		
	public:
//		DMA_HandleTypeDef hdma_adcc;
#ifdef USING_AEDMA 
		AEDMA dmaForADC;
#endif 
		
		

		uint16_t ADCdata[10];
 
		AEADC AEADC_inst1;
		AEADC AEADC_inst2;
		AEADC AEADC_inst3;
		AEADC AEADC_inst4;
		AEADC AEADC_inst5;

		protected :
 
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

		// Inherited via AEPeripheral 
		void _InitializePinSelectors(CreateTypeSelector_funcPtr(&functPtrsToChangeTypeSelectorss)[NumOFPinsNeeded]) override;
 

		// Inherited via AEPeripheral
		void _Initialize(Port_t port1, Pin_t pin1, Port_t port2, Pin_t pin2, Port_t port3, Pin_t pin3, Port_t port4, Pin_t pin4, Port_t port5, Pin_t pin5)override;
		
		void Pre_Initialize(Port_t port1, Pin_t pin1, Port_t port2, Pin_t pin2, Port_t port3, Pin_t pin3, Port_t port4, Pin_t pin4, Port_t port5, Pin_t pin5) override {
		if (this->ForWhichPeripheralNumber == 1)
		{
#ifdef ADCPERIPHERAL1_Name_CH1
			AEAssertRuntime(this->GPIOPinSelected1.isInitialized() , "you did not give a pin and port for this channel but you gave a name for the channel ADCPERIPHERAL1_Name_CH1 in AEConfig")
#endif
#ifdef ADCPERIPHERAL1_Name_CH2
			AEAssertRuntime(this->GPIOPinSelected2.isInitialized() , "you did not give a pin and port for this channel but you gave a name for the channel ADCPERIPHERAL1_Name_CH2 in AEConfig")
#endif
#ifdef ADCPERIPHERAL1_Name_CH3
			AEAssertRuntime(this->GPIOPinSelected3.isInitialized() , "you did not give a pin and port for this channel but you gave a name for the channel ADCPERIPHERAL1_Name_CH3 in AEConfig")
#endif
#ifdef ADCPERIPHERAL1_Name_CH4
			AEAssertRuntime(this->GPIOPinSelected4.isInitialized() , "you did not give a pin and port for this channel but you gave a name for the channel ADCPERIPHERAL1_Name_CH4 in AEConfig")
#endif
#ifdef ADCPERIPHERAL1_Name_CH5
			AEAssertRuntime(this->GPIOPinSelected5.isInitialized() , "you did not give a pin and port for this channel but you gave a name for the channel ADCPERIPHERAL1_Name_CH5 in AEConfig")
#endif
		}
			
		if (this->ForWhichPeripheralNumber == 2)
		{
#ifdef ADCPERIPHERAL2_Name_CH1
			AEAssertRuntime(this->GPIOPinSelected1.isInitialized() , "you did not give a pin and port for this channel but you gave a name for the channel ADCPERIPHERAL2_Name_CH1 in AEConfig")
#endif
#ifdef ADCPERIPHERAL2_Name_CH2
			AEAssertRuntime(this->GPIOPinSelected2.isInitialized() , "you did not give a pin and port for this channel but you gave a name for the channel ADCPERIPHERAL2_Name_CH2 in AEConfig")
#endif
#ifdef ADCPERIPHERAL2_Name_CH3
			AEAssertRuntime(this->GPIOPinSelected3.isInitialized() , "you did not give a pin and port for this channel but you gave a name for the channel ADCPERIPHERAL2_Name_CH3 in AEConfig")
#endif
#ifdef ADCPERIPHERAL2_Name_CH4
			AEAssertRuntime(this->GPIOPinSelected4.isInitialized() , "you did not give a pin and port for this channel but you gave a name for the channel ADCPERIPHERAL2_Name_CH4 in AEConfig")
#endif
#ifdef ADCPERIPHERAL2_Name_CH5
			AEAssertRuntime(this->GPIOPinSelected5.isInitialized() , "you did not give a pin and port for this channel but you gave a name for the channel ADCPERIPHERAL2_Name_CH5 in AEConfig")
#endif
		}
			
//			
		};
 


		
		
		AEADC* GetPeripheralInstanceCh1() 
{	 	this->AEADC_inst1.Init(this->GPIOPinSelected1.GetThePort(), this->GPIOPinSelected1.GetThePin(), &ADCdata[0]); return &AEADC_inst1;}
		AEADC* GetPeripheralInstanceCh2() 
{		this->AEADC_inst2.Init(this->GPIOPinSelected2.GetThePort(), this->GPIOPinSelected2.GetThePin(), &ADCdata[1]); return &AEADC_inst2;}
		AEADC* GetPeripheralInstanceCh3() 
{		this->AEADC_inst3.Init(this->GPIOPinSelected3.GetThePort(), this->GPIOPinSelected3.GetThePin(), &ADCdata[2]); return &AEADC_inst3;}
		AEADC* GetPeripheralInstanceCh4() 
{		this->AEADC_inst4.Init(this->GPIOPinSelected4.GetThePort(), this->GPIOPinSelected4.GetThePin(), &ADCdata[3]); return &AEADC_inst4;}
		AEADC* GetPeripheralInstanceCh5() 
{		this->AEADC_inst5.Init(this->GPIOPinSelected5.GetThePort(), this->GPIOPinSelected5.GetThePin(), &ADCdata[4]); return &AEADC_inst5;}
	};
	

 





 

 //global pheripherals declaration
#ifdef ADCPERIPHERAL1
#define ADC_CH1_INIT
#define ADC_CH2_INIT
#define ADC_CH3_INIT
#define ADC_CH4_INIT
#define ADC_CH5_INIT

extern ADCPERIPHERAL1* ADCPERIPHERAL1_Instance;  

#ifndef ADCPERIPHERAL1_Name_CH1
#error You need to define ADCPERIPHERAL1_Name_CH1
#else
#define ADC_CH1_INIT ADCPERIPHERAL1_Name_CH1 = ADCPERIPHERAL1_Instance->GetPeripheralInstanceCh1();
extern  AEADC *ADCPERIPHERAL1_Name_CH1; 
#endif

#ifdef ADCPERIPHERAL1_Name_CH2
#define ADC_CH2_INIT ADCPERIPHERAL1_Name_CH2 = ADCPERIPHERAL1_Instance->GetPeripheralInstanceCh2();
extern  AEADC *ADCPERIPHERAL1_Name_CH2; 
#endif

#ifdef ADCPERIPHERAL1_Name_CH3
#define ADC_CH3_INIT ADCPERIPHERAL1_Name_CH3 = ADCPERIPHERAL1_Instance->GetPeripheralInstanceCh3();
extern  AEADC *ADCPERIPHERAL1_Name_CH3; 
#endif

#ifdef ADCPERIPHERAL1_Name_CH4
#define ADC_CH4_INIT ADCPERIPHERAL1_Name_CH4 = ADCPERIPHERAL1_Instance->GetPeripheralInstanceCh4();
extern  AEADC *ADCPERIPHERAL1_Name_CH4; 
#endif

#ifdef ADCPERIPHERAL1_Name_CH5
#define ADC_CH5_INIT ADCPERIPHERAL1_Name_CH5 = ADCPERIPHERAL1_Instance->GetPeripheralInstanceCh5();
extern  AEADC *ADCPERIPHERAL1_Name_CH5; 
#endif

#define ADCPERIPHERAL1_INITIALIZE ADCPERIPHERAL1_Instance = ADCPERIPHERAL1::getInstance(); ADCPERIPHERAL1_Instance->ForWhichPeripheralNumber = 1; ADCPERIPHERAL1_Instance->initializePeripheral(); \
ADC_CH1_INIT ADC_CH2_INIT ADC_CH3_INIT ADC_CH4_INIT ADC_CH5_INIT

#endif 

 

 
 
//#endif //target_stm32f4



//#pragma warning( pop ) 








