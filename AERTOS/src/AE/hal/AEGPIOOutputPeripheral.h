#pragma once

#include "FreeRTOS.h"
#include "AEPeripheral.h"

#include "BoardTypes.h"

//#include  "stm32f4xx_hal.h"
//#include "AE_Init.h"

#include "AEConfig.h"

#ifdef AESIMULATION
#include "SimulatedProperty.h"
#endif


#ifndef USING_AEGPIOOutput 
#error you included this file but you did not provide a AEGPIOOutput.h file in AEHalFiles directory.
#endif 

class AEGPIOOutput {
  AEFRIEND_TEST(AEPeripheral, simple_init);
 
  
public:
  void GPIO_SetHigh();
  void GPIO_SetLow();
  void GPIO_TogglePin();
  bool GPIO_ReadPin();

 void Init(Port_t port, Pin_t pin, GPIO_Handle* gPIO_Handle_inst ) {

    GPIO_Handle_inst = gPIO_Handle_inst;
    Port = port;
    Pin = pin;
    
  };

	AEGPIOOutput() {

  };

private:
#ifdef AESIMULATION
  SimulatedProperty *PropertiesIEffect[4];
  uint8_t PropertiesIEffectSoFarIndex;
  uint8_t IAmSetToPropertyGPIONum;

  void AddSimulatedProperty(SimulatedProperty *simulatedPropertytoAdd) {
    PropertiesIEffect[PropertiesIEffectSoFarIndex] = simulatedPropertytoAdd;
    PropertiesIEffectSoFarIndex++;
  };

  UpdateAllPropertiesIEffect() {
    for (uint32_t i = 0; i < PropertiesIEffectSoFarIndex; i++) {
      // update the proper gpio value of the property
      if (IAmSetToPropertyGPIONum == 1) {
        PropertiesIEffect[i]->isGPIOSetHigh1 = this->AE_GPIO_GetCurrentState();
      } else if (IAmSetToPropertyGPIONum == 2) {
        PropertiesIEffect[i]->isGPIOSetHigh2 = this->AE_GPIO_GetCurrentState();
      } else if (IAmSetToPropertyGPIONum == 3) {
        PropertiesIEffect[i]->isGPIOSetHigh3 = this->AE_GPIO_GetCurrentState();
      } else if (IAmSetToPropertyGPIONum == 4) {
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
  };

#endif

GPIO_Handle* GPIO_Handle_inst;
  Port_t Port;
  Pin_t Pin;
};
















#define templateForGPIO Portenum Gpio_port, PinEnum Gpio_pin
#define templateargsForGPIO Gpio_port, Gpio_pin


template <templateForGPIO>
class GPIOPeripheral : public AEPeripheral<GPIOPeripheral<templateargsForGPIO>, 1, GPIO_Handle, templateargsForGPIO>
{
	friend class AEGPIO;
    friend void AE_Init(void);
    AEFRIEND_TEST(AEPeripheral, simple_init);

  public:
	
	Port_t Port;
	Pin_t Pin;

	static bool IsAlreadyInUse;

  protected:
	AEGPIOOutput GpioInstance;

    // Inherited via HardwarePeripheral
    void _InitializePinSelectors(CreateTypeSelector_funcPtr (
        &functPtrsToChangeTypeSelectorss)[1]) override;

    // Inherited via HardwarePeripheral
    void _Initialize(Port_t port1, Pin_t pin1, Port_t port2, Pin_t pin2,
                     Port_t port3, Pin_t pin3, Port_t port4, Pin_t pin4,
                     Port_t port5, Pin_t pin5) override;

	AEGPIOOutput* GetPeripheralInstance() { GpioInstance.Init(Port, Pin, &this->PeripheralHandle_t); return &GpioInstance;}
};


template <templateForGPIO>
	bool GPIOPeripheral<templateargsForGPIO>::IsAlreadyInUse = false;








#ifdef GPIOPERIPHERAL1
extern GPIOPERIPHERAL1 *GPIOPERIPHERAL1_Instance;
#define GPIOPERIPHERAL1_INITIALIZE  GPIOPERIPHERAL1_Instance = GPIOPERIPHERAL1::getInstance(); GPIOPERIPHERAL1_Instance->initializePeripheral(); GPIOPERIPHERAL1_Name = GPIOPERIPHERAL1_Instance->GetPeripheralInstance();
#ifndef GPIOPERIPHERAL1_Name
#error You need to define GPIOPERIPHERAL1_Name
#else
extern  AEGPIOOutput *GPIOPERIPHERAL1_Name;
#endif
#endif

#ifdef GPIOPERIPHERAL2
extern GPIOPERIPHERAL2 *GPIOPERIPHERAL2_Instance;
#define GPIOPERIPHERAL2_INITIALIZE  GPIOPERIPHERAL2_Instance = GPIOPERIPHERAL2::getInstance(); GPIOPERIPHERAL2_Instance->initializePeripheral(); GPIOPERIPHERAL2_Name = GPIOPERIPHERAL2_Instance->GetPeripheralInstance();
#ifndef GPIOPERIPHERAL2_Name
#error You need to define GPIOPERIPHERAL2_Name
#else
extern  AEGPIOOutput *GPIOPERIPHERAL2_Name;
#endif
#endif

#ifdef GPIOPERIPHERAL3
extern GPIOPERIPHERAL3 *GPIOPERIPHERAL3_Instance;
#define GPIOPERIPHERAL3_INITIALIZE  GPIOPERIPHERAL3_Instance = GPIOPERIPHERAL3::getInstance(); GPIOPERIPHERAL3_Instance->initializePeripheral(); GPIOPERIPHERAL3_Name = GPIOPERIPHERAL3_Instance->GetPeripheralInstance();
#ifndef GPIOPERIPHERAL3_Name
#error You need to define GPIOPERIPHERAL3_Name
#else
extern  AEGPIOOutput *GPIOPERIPHERAL3_Name;
#endif
#endif


#ifdef GPIOPERIPHERAL4
extern GPIOPERIPHERAL4 *GPIOPERIPHERAL4_Instance;
#define GPIOPERIPHERAL4_INITIALIZE  GPIOPERIPHERAL4_Instance = GPIOPERIPHERAL4::getInstance(); GPIOPERIPHERAL4_Instance->initializePeripheral(); GPIOPERIPHERAL4_Name = GPIOPERIPHERAL4_Instance->GetPeripheralInstance();
#ifndef GPIOPERIPHERAL4_Name
#error You need to define GPIOPERIPHERAL4_Name
#else
extern  AEGPIOOutput *GPIOPERIPHERAL4_Name;
#endif
#endif


#ifdef GPIOPERIPHERAL5
extern GPIOPERIPHERAL5 *GPIOPERIPHERAL5_Instance;
#define GPIOPERIPHERAL5_INITIALIZE  GPIOPERIPHERAL5_Instance = GPIOPERIPHERAL5::getInstance(); GPIOPERIPHERAL5_Instance->initializePeripheral(); GPIOPERIPHERAL5_Name = GPIOPERIPHERAL5_Instance->GetPeripheralInstance();
#ifndef GPIOPERIPHERAL5_Name
#error You need to define GPIOPERIPHERAL5_Name
#else
extern  AEGPIOOutput *GPIOPERIPHERAL5_Name;
#endif
#endif

#ifdef GPIOPERIPHERAL6
extern GPIOPERIPHERAL6 *GPIOPERIPHERAL6_Instance;
#define GPIOPERIPHERAL6_INITIALIZE  GPIOPERIPHERAL6_Instance = GPIOPERIPHERAL6::getInstance(); GPIOPERIPHERAL6_Instance->initializePeripheral(); GPIOPERIPHERAL6_Name = GPIOPERIPHERAL6_Instance->GetPeripheralInstance();
#ifndef GPIOPERIPHERAL6_Name
#error You need to define GPIOPERIPHERAL6_Name
#else
extern  AEGPIOOutput *GPIOPERIPHERAL6_Name;
#endif
#endif


 




