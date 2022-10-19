#include <gtest/gtest.h>
#include <stdio.h>

#include "AEConfig.h"
#include "AE_Init.h"
 



/*
	This is a very basic sample demonstrating the GoogleTest framework.
	Read more about CppUTest syntax here: https://github.com/google/googletest
*/


#include "PinSelector.h"
//
TEST(PinSelector, pin_validation)
{ 
	//including pins
	auto psel = PinSelector::getInstance(); 
	psel->IncludePossiblePin(Portenum::PortA, PinEnum::PIN0);
	psel->IncludePossiblePin(Portenum::PortA, PinEnum::PIN1);
	psel->IncludePossiblePin(Portenum::PortA, PinEnum::PIN2);
	
	bool isValidfalse = psel->CheckIfPinIsValid(Portenum::PortA, PinEnum::PIN4);
	bool isValidtrue = psel->CheckIfPinIsValid(Portenum::PortA, PinEnum::PIN0);
	
	 
	EXPECT_TRUE(isValidfalse == false);
	EXPECT_TRUE(isValidtrue == true);
	 
	//if any pin is possible
	psel->ResetSelector();
	psel->AnyPinIsPossible();
	
	
	bool isValid3 = psel->CheckIfPinIsValid(Portenum::PortA, PinEnum::PIN0);
	bool isValid4 = psel->CheckIfPinIsValid(Portenum::PortB, PinEnum::PIN0);
	
	EXPECT_TRUE(isValid3 == true);
	EXPECT_TRUE(isValid4 == true);
	
	
	//only one pin is possible
	psel->ResetSelector();
	psel->OnlyThisPinPossible(Portenum::PortB, PinEnum::PIN5); 
	
	bool isValid5 = psel->CheckIfPinIsValid(Portenum::PortC, PinEnum::PIN2); 
	
	EXPECT_TRUE(isValid5 == false);
}

 

#include "AEPortAndPin.h"

TEST(AEGPIO, simple_init)
{ 
	
	static AEPortAndPin pina;
	pina._Init(PortA, PIN0);

    static  AEPortAndPin pina2;
AE_Expect_Assert_To_Fail("GPIOPinReused"); 
	pina2._Init(PortA, PIN0);
AE_Clear_Expectations_Of_Asserts
	 
	EXPECT_TRUE(pina.GetThePortenum() == Portenum::PortA);

	

	static AEPortAndPin pinc; 
	pinc._Init(PortC, PIN3);

AE_Expect_Assert_To_Fail("GPIOPinReused");
	static AEPortAndPin pincc;  
	pincc._Init(PortC, PIN3);
AE_Clear_Expectations_Of_Asserts 
}

//
//#include "AEGPIOPeripheral_BSP.h" 
//#include "AllPeripheralObjects.h"
//#include "AEGPIO.h" 
//#include "AEConfig.h"
 

TEST(AEPeripheral, simple_init)
{

//	InitializeAllPeripheral
	
  //  //initializing through the peripheral class ----------------

  GPIOPeripheral<PortD, PIN13> pina; 
  pina.initializePeripheral();
  auto pinled13 = pina.GetPeripheralInstance();
  pinled13->GPIO_SetHigh();
  EXPECT_TRUE(pinled13->GPIO_ReadPin() == true);
  pinled13->GPIO_SetLow();
  EXPECT_TRUE(pinled13->GPIO_ReadPin() == false);
  


  //initializing through hal class ----------------

  //  GPIOPERIPHERAL1_Instance = GPIOPERIPHERAL1::getInstance();
  //  GPIOPERIPHERAL1_Instance->initializePeripheral();
  //  GPIOPERIPHERAL1_Name = GPIOPERIPHERAL1_Instance->GetPeripheralInstance();
//  GPIOPERIPHERAL1_INITIALIZE
//InitializeAllPeripheral
		
  GpioLed1->GPIO_SetHigh();
  EXPECT_TRUE(GpioLed1->GPIO_ReadPin() == true);
  GpioLed1->GPIO_SetLow();
  EXPECT_TRUE(GpioLed1->GPIO_ReadPin() == false);

  GpioLed2->GPIO_SetHigh();
  EXPECT_TRUE(GpioLed2->GPIO_ReadPin() == true);
  GpioLed2->GPIO_SetLow();
  EXPECT_TRUE(GpioLed2->GPIO_ReadPin() == false);

  // timer tests
  AEStartTimer(1)  
#ifdef HARDWARE
  GPIOD->BSRR = GPIO_PIN_12;
  GPIOD->BSRR = (uint32_t)GPIO_PIN_12 << 16U;
#endif
  AEStopTimer(1)
  AELogTimer(1, "pin_blink_register");
  
  AEStartTimer(1)  
  GpioLed1->GPIO_SetHigh(); 
  GpioLed1->GPIO_SetLow();
  AEStopTimer(1)
  AELogTimer(1, "pin_blink_hal");
}
