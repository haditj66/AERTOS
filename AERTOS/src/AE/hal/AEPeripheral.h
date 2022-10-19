#pragma once

#include "AEPortAndPin.h"

#ifdef BoardModelType2
#include "ModelType2Setup.h"    
#elif BoardModelType1
#include "ModelType1Setup.h"   
#elif BoardSeries
#include "SeriesSetup.h"   
#elif BoardVendor
#include "BoardVendorSetup.h"   
#elif IsPC
#include "BoardVendorSetup.h" 
#endif

//#include "stm32f4xx_hal.h"
 

//helper macro for the pinselector
#define StartPinSelectorForPin(forPin) this->functPtrsToChangeTypeSelectors[forPin - 1] = []() -> void	{
#define M_IncludePossiblePin(portEnum, pinEnum) PinSelector::getInstance()->IncludePossiblePin(portEnum, pinEnum);
#define M_AnyPinIsPossible PinSelector::getInstance()->AnyPinIsPossible();
#define M_OnlyThisPinPossible(portEnum, pinEnum)  PinSelector::getInstance()->OnlyThisPinPossible(portEnum, pinEnum);
#define EndPinSelectorForPin };



enum class PeripheralEnum
{
	UART,
	SPI,
	I2C,
	GPIOInput,
	GPIOOutput,
	None
}
;




typedef void (*CreateTypeSelector_funcPtr)(void);



template <TemplateFor_AEPeripherals>
class AEPeripheral
{

	friend void AE_Init(void);
	AEFRIEND_TEST(AEPeripheral, simple_init);

  public:
	
	
	static DerivedType *getInstance();
	AEPeripheral(AEPeripheral<TemplateArgs_AEPeripherals> const &) = delete;
	void operator=(AEPeripheral<TemplateArgs_AEPeripherals> const &) = delete;

	PeripheralHandleTypeDef PeripheralHandle_t;

  protected:
	uint8_t ForWhichPeripheralNumber;
	static DerivedType *Instance;

	static bool isAlreadyInitialized;

#ifdef AESIMULATION
	SimulatedProperty *PropertiesIEffect[4];
	uint8_t PropertiesIEffectSoFarIndex;

	void AddSimulatedProperty(SimulatedProperty *simulatedPropertytoAdd)
	{
		PropertiesIEffect[PropertiesIEffectSoFarIndex] = simulatedPropertytoAdd;
		PropertiesIEffectSoFarIndex++;
	};

	typedef void (*DoToPropertyFncPtr)(SimulatedProperty *);
	DoThisToAllPropertiesIEffect_AndUpdateThem(DoToPropertyFncPtr doToPropertyFncPtr)
	{
		for (uint32_t i = 0; i < PropertiesIEffectSoFarIndex; i++)
		{
			doToPropertyFncPtr(PropertiesIEffect[i]);
			PropertiesIEffect[i]._UpdatePropWithinSimulation();
		}
	}

#endif

	void initializePeripheral()
	{
		
		//create instances of PinandPorts
		if(PIN1 != PinEnum::PINMaxNum)
		{GPIOPinSelected1._Init(PORT1, PIN1); }
		if (PIN2 != PinEnum::PINMaxNum)
		{GPIOPinSelected2._Init(PORT2, PIN2); }
		if (PIN3 != PinEnum::PINMaxNum) 
		{GPIOPinSelected3._Init(PORT3, PIN3); }
		if (PIN4 != PinEnum::PINMaxNum)
		{GPIOPinSelected4._Init(PORT4, PIN4); }
		if (PIN5 != PinEnum::PINMaxNum)
		{GPIOPinSelected5._Init(PORT5, PIN5); }
		

#ifdef AESIMULATION
		PropertiesIEffectSoFarIndex = 0;
#endif

		_InitializePinSelectors(this->functPtrsToChangeTypeSelectors);
		//assert that the this->functPtrsToChangeTypeSelectors did not come back null
		//you must have forgettent to specify pins selections on a peripheral.
		for (int i = 0; i < NumOfGpioPinsNeeded; i++)
		{
			configASSERT(this->functPtrsToChangeTypeSelectors[i] != nullptr);
		}

        if (NumOfGpioPinsNeeded >= 1) {

			//check that all pins are of a valid selection
			//first run the function for pinselection of pin one.
			//only check if not null
			PinSelector::getInstance()->ResetSelector();
			if (PIN1 != PinEnum::PINMaxNum)
			{

				this->functPtrsToChangeTypeSelectors[0]();
				configASSERT(PinSelector::getInstance()->CheckIfPinIsValid(GPIOPinSelected1.GetThePortenum(), GPIOPinSelected1.GetThePinenum()));  
				PinSelector::getInstance()->ResetSelector();
                                 
			}

			if (PIN2 != PinEnum::PINMaxNum)
			{
				this->functPtrsToChangeTypeSelectors[1]();
				configASSERT(PinSelector::getInstance()->CheckIfPinIsValid(GPIOPinSelected2.GetThePortenum(), GPIOPinSelected2.GetThePinenum()));
				PinSelector::getInstance()->ResetSelector();
			}

			if (PIN3 != PinEnum::PINMaxNum)
			{
				this->functPtrsToChangeTypeSelectors[2]();
				configASSERT(PinSelector::getInstance()->CheckIfPinIsValid(GPIOPinSelected3.GetThePortenum(), GPIOPinSelected3.GetThePinenum()));
				PinSelector::getInstance()->ResetSelector();
			}

			if (PIN4 != PinEnum::PINMaxNum)
			{
				this->functPtrsToChangeTypeSelectors[3]();
				configASSERT(PinSelector::getInstance()->CheckIfPinIsValid(GPIOPinSelected4.GetThePortenum(), GPIOPinSelected4.GetThePinenum()));
				PinSelector::getInstance()->ResetSelector();
			}

			if (PIN5 != PinEnum::PINMaxNum)
			{
				this->functPtrsToChangeTypeSelectors[4]();
				configASSERT(PinSelector::getInstance()->CheckIfPinIsValid(GPIOPinSelected5.GetThePortenum(), GPIOPinSelected5.GetThePinenum()));
				PinSelector::getInstance()->ResetSelector();
			}

			/*
			if (NumOfGpioPinsNeeded == 0)
			{
				_Initialize();
			}*/

				// I need to check if the ports that will be used for this peripheral have been started yet.
				// if they have not been started yet, I need to start them here. each platform will have it's
				//own way of starting the peripheral.
	//
	//			if (HasPortBeenInitYet[GPIOPinSelected1.thePORT] == false && (GPIOPinSelected1.thePORT != Portenum::PortsMaxNum))
	//			{
	//				functPtrsToInitializePorts[GPIOPinSelected1.thePORT]();
	//				HasPortBeenInitYet[GPIOPinSelected1.thePORT] = true;
	//			}
	//			if (HasPortBeenInitYet[GPIOPinSelected2.thePORT] == false && (GPIOPinSelected2.thePORT != Portenum::PortsMaxNum))
	//			{
	//				functPtrsToInitializePorts[GPIOPinSelected2.thePORT]();
	//				HasPortBeenInitYet[GPIOPinSelected2.thePORT] = true;
	//			}
	//			if (HasPortBeenInitYet[GPIOPinSelected3.thePORT] == false && (GPIOPinSelected3.thePORT != Portenum::PortsMaxNum))
	//			{
	//				functPtrsToInitializePorts[GPIOPinSelected3.thePORT]();
	//				HasPortBeenInitYet[GPIOPinSelected3.thePORT] = true;
	//			}
	//			if (HasPortBeenInitYet[GPIOPinSelected4.thePORT] == false && (GPIOPinSelected4.thePORT != Portenum::PortsMaxNum))
	//			{
	//				functPtrsToInitializePorts[GPIOPinSelected4.thePORT]();
	//				HasPortBeenInitYet[GPIOPinSelected4.thePORT] = true;
	//			}
	//			if (HasPortBeenInitYet[GPIOPinSelected5.thePORT] == false && (GPIOPinSelected5.thePORT != Portenum::PortsMaxNum))
	//			{
	//				functPtrsToInitializePorts[GPIOPinSelected5.thePORT]();
	//				HasPortBeenInitYet[GPIOPinSelected5.thePORT] = true;
	//			}

				Pre_Initialize(
					GPIOPinSelected1.GetThePort(), GPIOPinSelected1.GetThePin(),
					GPIOPinSelected2.GetThePort(), GPIOPinSelected2.GetThePin(),
					GPIOPinSelected3.GetThePort(), GPIOPinSelected3.GetThePin(),
					GPIOPinSelected4.GetThePort(), GPIOPinSelected4.GetThePin(),
					GPIOPinSelected5.GetThePort(), GPIOPinSelected5.GetThePin());
			
                	_Initialize(
					GPIOPinSelected1.GetThePort(), GPIOPinSelected1.GetThePin(),
					GPIOPinSelected2.GetThePort(), GPIOPinSelected2.GetThePin(),
					GPIOPinSelected3.GetThePort(), GPIOPinSelected3.GetThePin(),
					GPIOPinSelected4.GetThePort(), GPIOPinSelected4.GetThePin(),
					GPIOPinSelected5.GetThePort(), GPIOPinSelected5.GetThePin());  
			}

		
	};


	
	virtual void _InitializePinSelectors(CreateTypeSelector_funcPtr (&functPtrsToChangeTypeSelectors)[NumOfGpioPinsNeeded]) = 0;

	
	CreateTypeSelector_funcPtr functPtrsToChangeTypeSelectors[NumOfGpioPinsNeeded];


	
	AEPortAndPin GPIOPinSelected1; 
	AEPortAndPin GPIOPinSelected2; 
	AEPortAndPin GPIOPinSelected3; 
	AEPortAndPin GPIOPinSelected4; 
	AEPortAndPin GPIOPinSelected5; 

	AEPeripheral()
	{

 
		AEAssertRuntime(isAlreadyInitialized == false, " AEPeripherals are singletons. If more than one even attempt to be intialized, than there must be some config error");
		isAlreadyInitialized = true;

		Instance = static_cast<DerivedType *>(this); // GetSingletonInstance();//static_cast<DerivedType*>(this);
	};

//	virtual void _Initialize()
//	{
//		if (NumOfGpioPinsNeeded == 0)
//		{
//			//this function needs to be overridden to implement periperal initalization
//			configASSERT(false);
//		}
//		if (NumOfGpioPinsNeeded != 0)
//		{
//			//this initialization function is the wrong overloaded one to call.
//			configASSERT(false);
//		}
//	};


	
	virtual void _Initialize(
		Port_t port1, Pin_t pin1,
		Port_t port2, Pin_t pin2,
		Port_t port3, Pin_t pin3,
		Port_t port4, Pin_t pin4,
		Port_t port5, Pin_t pin5) = 0;

	//this initialization of the peripheral needs to happen before the other _initialize.
	virtual void Pre_Initialize(
		Port_t port1, Pin_t pin1,
		Port_t port2, Pin_t pin2,
		Port_t port3, Pin_t pin3,
		Port_t port4, Pin_t pin4,
		Port_t port5, Pin_t pin5);
};


template <TemplateFor_AEPeripherals_NoDefaults>
void AEPeripheral<TemplateArgs_AEPeripherals>::Pre_Initialize(Port_t port1, Pin_t pin1,
		Port_t port2, Pin_t pin2,
		Port_t port3, Pin_t pin3,
		Port_t port4, Pin_t pin4,
		Port_t port5, Pin_t pin5)
{ 
}


template <TemplateFor_AEPeripherals_NoDefaults>
DerivedType *AEPeripheral<TemplateArgs_AEPeripherals>::getInstance()
{

	if (Instance == 0)
	{
		static DerivedType soleInstance;
		Instance = &soleInstance;

		// I also want to initialize the peripheral here
		//Instance->initializePeripheral();
	}
	return Instance;
}

template <TemplateFor_AEPeripherals_NoDefaults>
bool AEPeripheral<TemplateArgs_AEPeripherals>::isAlreadyInitialized = false;

template <TemplateFor_AEPeripherals_NoDefaults>
DerivedType *AEPeripheral<TemplateArgs_AEPeripherals>::Instance = nullptr;





