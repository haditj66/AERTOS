#pragma once

#include "FreeRTOS.h"
#include "AEPeripheral.h"

#include "BoardTypes.h"

#include "AEConfig.h"

#ifdef AESIMULATION
#include "SimulatedProperty.h" 
#endif

#ifndef USING_AEGPIOInput 
#error you included this file but you did not provide a AEGPIOInput.h file in AEHalFiles directory.
#endif 



typedef void(*AE_GPIO_extiCallback_t)(void);


class AEGPIOInput {
	AEFRIEND_TEST(AEPeripheral, simple_init);
	 
	//	friend void EXTI0_IRQHandler();
	//	friend void EXTI1_IRQHandler();
	//	friend void EXTI2_IRQHandler();
	//	friend void EXTI3_IRQHandler();
	//	friend void EXTI4_IRQHandler();
	//	friend void EXTI5_IRQHandler();
		friend void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin);
public:
	
	AE_GPIO_extiCallback_t AE_GPIO_extiCallback; 
	
	void SetextiCallback_t(AE_GPIO_extiCallback_t ae_GPIO_extiCallback)
	{
		AE_GPIO_extiCallback = ae_GPIO_extiCallback;
	}
	
	bool GPIO_ReadPin();

	void Init(Port_t port, Pin_t pin, GPIOInput_Handle* gPIO_Handle_inst) {

		//set default external interrupt to do nothing
		AE_GPIO_extiCallback = [](void)->void {};
	 
		GPIO_Handle_inst = gPIO_Handle_inst;
		buttongpio_Port = port;
		buttongpio_Pin = pin;
    
	}
	;

	AEGPIOInput() {

	}
	;

public:
	

	
	GPIOInput_Handle* GPIO_Handle_inst;
	Port_t buttongpio_Port;
	Pin_t  buttongpio_Pin;
	
#ifdef AESIMULATION
	SimulatedProperty *PropertiesIEffect[4];
	uint8_t PropertiesIEffectSoFarIndex;
	uint8_t IAmSetToPropertyGPIONum;

	void AddSimulatedProperty(SimulatedProperty *simulatedPropertytoAdd) {
		PropertiesIEffect[PropertiesIEffectSoFarIndex] = simulatedPropertytoAdd;
		PropertiesIEffectSoFarIndex++;
	}
	;

	UpdateAllPropertiesIEffect() {
		for (uint32_t i = 0; i < PropertiesIEffectSoFarIndex; i++) {
			// update the proper gpio value of the property
			if(IAmSetToPropertyGPIONum == 1) {
				PropertiesIEffect[i]->isGPIOSetHigh1 = this->AE_GPIO_GetCurrentState();
			} else if(IAmSetToPropertyGPIONum == 2) {
				PropertiesIEffect[i]->isGPIOSetHigh2 = this->AE_GPIO_GetCurrentState();
			} else if(IAmSetToPropertyGPIONum == 3) {
				PropertiesIEffect[i]->isGPIOSetHigh3 = this->AE_GPIO_GetCurrentState();
			} else if(IAmSetToPropertyGPIONum == 4) {
				PropertiesIEffect[i]->isGPIOSetHigh4 = this->AE_GPIO_GetCurrentState();
			}

			PropertiesIEffect[i]._UpdatePropWithinSimulation();
		}
	}

	void AddSimulatedProperty(SimulatedProperty *simulatedPropertytoAdd,
		uint8_t GpiosthatEffectMe) {
		IAmSetToPropertyGPIONum = GpiosthatEffectMe;
		PropertiesIEffect[PropertiesIEffectSoFarIndex] = simulatedPropertytoAdd;
		PropertiesIEffectSoFarIndex++;
	}
	;

#endif


};
















#define templateForButton  Portenum Button_buttongpio_Port, PinEnum Button_buttongpio_Pin
#define templateargsForButton  Button_buttongpio_Port, Button_buttongpio_Pin
#define templateargsForHardware  Button_buttongpio_Port, Button_buttongpio_Pin

template <templateForButton>
	class GPIOInputPeripheral : public AEPeripheral<GPIOInputPeripheral<templateargsForButton>, 1, GPIOInput_Handle, templateargsForHardware>
	{
		friend class AEGPIO;
		friend void AE_Init(void);
		AEFRIEND_TEST(AEPeripheral, simple_init);

	public:
	
		Port_t buttongpio_Port;
		Pin_t  buttongpio_Pin;


	

	protected:
		AEGPIOInput GpioInstance;

		// Inherited via HardwarePeripheral
		void _InitializePinSelectors(CreateTypeSelector_funcPtr(
		    &functPtrsToChangeTypeSelectorss)[1]) override;

		// Inherited via HardwarePeripheral
		void _Initialize(Port_t port1,
			Pin_t pin1,
			Port_t port2,
			Pin_t pin2,
			Port_t port3,
			Pin_t pin3,
			Port_t port4,
			Pin_t pin4,
			Port_t port5,
			Pin_t pin5) override;
	
	
		AEGPIOInput*  GetPeripheralInstance();
	};


template <templateForButton>
	inline	AEGPIOInput* GPIOInputPeripheral<templateargsForButton>::GetPeripheralInstance() 
	{ this->GpioInstance.Init(buttongpio_Port, buttongpio_Pin, &(this->PeripheralHandle_t)); return &GpioInstance;}






#ifdef GPIOInputPERIPHERAL1
extern GPIOInputPERIPHERAL1 *GPIOInputPERIPHERAL1_Instance;
#define GPIOInputPERIPHERAL1_INITIALIZE  GPIOInputPERIPHERAL1_Instance = GPIOInputPERIPHERAL1::getInstance(); GPIOInputPERIPHERAL1_Instance->initializePeripheral(); GPIOInputPERIPHERAL1_Name = GPIOInputPERIPHERAL1_Instance->GetPeripheralInstance();
#ifndef GPIOInputPERIPHERAL1_Name
#error You need to define GPIOInputPERIPHERAL1_Name
#else
extern  AEGPIOInput *GPIOInputPERIPHERAL1_Name;
#endif
#endif
 

#ifdef GPIOInputPERIPHERAL2
extern GPIOInputPERIPHERAL2 *GPIOInputPERIPHERAL2_Instance;
#define GPIOInputPERIPHERAL2_INITIALIZE  GPIOInputPERIPHERAL2_Instance = GPIOInputPERIPHERAL2::getInstance(); GPIOInputPERIPHERAL2_Instance->initializePeripheral(); GPIOInputPERIPHERAL2_Name = GPIOInputPERIPHERAL2_Instance->GetPeripheralInstance();
#ifndef GPIOInputPERIPHERAL2_Name
#error You need to define GPIOInputPERIPHERAL2_Name
#else
extern  AEGPIOInput *GPIOInputPERIPHERAL2_Name;
#endif
#endif
 


#ifdef GPIOInputPERIPHERAL3
extern GPIOInputPERIPHERAL3 *GPIOInputPERIPHERAL3_Instance;
#define GPIOInputPERIPHERAL3_INITIALIZE  GPIOInputPERIPHERAL3_Instance = GPIOInputPERIPHERAL3::getInstance(); GPIOInputPERIPHERAL3_Instance->initializePeripheral(); GPIOInputPERIPHERAL3_Name = GPIOInputPERIPHERAL3_Instance->GetPeripheralInstance();
#ifndef GPIOInputPERIPHERAL3_Name
#error You need to define GPIOInputPERIPHERAL3_Name
#else
extern  AEGPIOInput *GPIOInputPERIPHERAL3_Name;
#endif
#endif
 

#ifdef GPIOInputPERIPHERAL4
extern GPIOInputPERIPHERAL4 *GPIOInputPERIPHERAL4_Instance;
#define GPIOInputPERIPHERAL4_INITIALIZE  GPIOInputPERIPHERAL4_Instance = GPIOInputPERIPHERAL4::getInstance(); GPIOInputPERIPHERAL4_Instance->initializePeripheral(); GPIOInputPERIPHERAL4_Name = GPIOInputPERIPHERAL4_Instance->GetPeripheralInstance();
#ifndef GPIOInputPERIPHERAL4_Name
#error You need to define GPIOInputPERIPHERAL4_Name
#else
extern  AEGPIOInput *GPIOInputPERIPHERAL4_Name;
#endif
#endif
 

#ifdef GPIOInputPERIPHERAL5
extern GPIOInputPERIPHERAL5 *GPIOInputPERIPHERAL5_Instance;
#define GPIOInputPERIPHERAL5_INITIALIZE  GPIOInputPERIPHERAL5_Instance = GPIOInputPERIPHERAL5::getInstance(); GPIOInputPERIPHERAL5_Instance->initializePeripheral(); GPIOInputPERIPHERAL5_Name = GPIOInputPERIPHERAL5_Instance->GetPeripheralInstance();
#ifndef GPIOInputPERIPHERAL5_Name
#error You need to define GPIOInputPERIPHERAL5_Name
#else
extern  AEGPIOInput *GPIOInputPERIPHERAL5_Name;
#endif
#endif
 

#ifdef GPIOInputPERIPHERAL6
extern GPIOInputPERIPHERAL6 *GPIOInputPERIPHERAL6_Instance;
#define GPIOInputPERIPHERAL6_INITIALIZE  GPIOInputPERIPHERAL6_Instance = GPIOInputPERIPHERAL6::getInstance(); GPIOInputPERIPHERAL6_Instance->initializePeripheral(); GPIOInputPERIPHERAL6_Name = GPIOInputPERIPHERAL6_Instance->GetPeripheralInstance();
#ifndef GPIOInputPERIPHERAL6_Name
#error You need to define GPIOInputPERIPHERAL6_Name
#else
extern  AEGPIOInput *GPIOInputPERIPHERAL6_Name;
#endif
#endif
 

