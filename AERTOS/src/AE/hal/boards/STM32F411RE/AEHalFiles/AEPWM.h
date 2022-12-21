#pragma once

#include "AEPWMPeripheral.h"
 


inline void AEPWM::StartPWM() { HAL_TIM_PWM_Start(this->_pwm_Handle, PWMChannel); } 
inline void AEPWM::StopPWM() { HAL_TIM_PWM_Stop(this->_pwm_Handle, PWMChannel); } 
inline void AEPWM::ChangeDutyCycle(float dutycycleBetween1To100)
{
	//first find the pulse value that corresponds to this ratio
	uint32_t period = __HAL_TIM_GET_AUTORELOAD(this->_pwm_Handle);
	uint32_t pulseValue = (uint32_t)((float)(dutycycleBetween1To100 / 100) * (float)period);

	__HAL_TIM_SET_COMPARE(this->_pwm_Handle, PWMChannel, pulseValue); 
	DutyCycle = dutycycleBetween1To100;
} 

void ChangePeriodOfSignal(uint32_t period); 
 
  

template<templateForPWM>
	inline void PWMPeripheral<templateargsForPWM>::_InitializePinSelectors(CreateTypeSelector_funcPtr(&functPtrsToChangeTypeSelectorss)[1])
	{
		
  
		this->functPtrsToChangeTypeSelectors[0] = []() -> void
		{
			PinSelector::getInstance()->IncludePossiblePin(Portenum::PortE, PinEnum::PIN14); //tim1 ch4
		//pA0 is not working for some reason. Just dont use it if you dont have to
		//PinSelector::getInstance()->IncludePossiblePin(Portenum::PortA, PinEnum::PIN0);	//tim2 ch1
			PinSelector::getInstance()->IncludePossiblePin(Portenum::PortA, PinEnum::PIN1); //tim2 ch2
			PinSelector::getInstance()->IncludePossiblePin(Portenum::PortA, PinEnum::PIN2); //tim2 ch3
			PinSelector::getInstance()->IncludePossiblePin(Portenum::PortA, PinEnum::PIN3); //tim2 ch4
			PinSelector::getInstance()->IncludePossiblePin(Portenum::PortA, PinEnum::PIN6); //tim3 ch1
			PinSelector::getInstance()->IncludePossiblePin(Portenum::PortA, PinEnum::PIN7); //tim3 ch2
			PinSelector::getInstance()->IncludePossiblePin(Portenum::PortB, PinEnum::PIN0); //tim3 ch3
			PinSelector::getInstance()->IncludePossiblePin(Portenum::PortB, PinEnum::PIN1); //tim3 ch4
			PinSelector::getInstance()->IncludePossiblePin(Portenum::PortD, PinEnum::PIN12); //tim4 ch1
			PinSelector::getInstance()->IncludePossiblePin(Portenum::PortD, PinEnum::PIN13); //tim4 ch2
			PinSelector::getInstance()->IncludePossiblePin(Portenum::PortD, PinEnum::PIN14); //tim4 ch3
			PinSelector::getInstance()->IncludePossiblePin(Portenum::PortD, PinEnum::PIN15); //tim4 ch4 	
		}; 
		 
  
	}
 


template<templateForPWM>
	inline void PWMPeripheral<templateargsForPWM>::_Initialize(Port_t port1, Pin_t pin1, Port_t port2, Pin_t pin2, Port_t port3, Pin_t pin3, Port_t port4, Pin_t pin4, Port_t port5, Pin_t pin5)
	{
		TIM_TypeDef* TimerInstance;
		TIM_OC_InitTypeDef sConfigOC;
		
		uint32_t gpioalternate  = 1;
		if (port1 == GPIOE && pin1 == GPIO_PIN_14)
		{
			TimerInstance = TIM1;
			PWMChannel = TIM_CHANNEL_4;
			__HAL_RCC_TIM1_CLK_ENABLE();
			gpioalternate = GPIO_AF1_TIM2;
		}
		else if (port1 == GPIOA && pin1 == GPIO_PIN_0)
		{
			TimerInstance = TIM2;
			PWMChannel = TIM_CHANNEL_1;
			__HAL_RCC_TIM2_CLK_ENABLE();
			gpioalternate = GPIO_AF1_TIM2;
		}
		else if (port1 == GPIOA && pin1 == GPIO_PIN_1)
		{
			TimerInstance = TIM2;
			PWMChannel = TIM_CHANNEL_2;
			__HAL_RCC_TIM2_CLK_ENABLE();
			gpioalternate = GPIO_AF1_TIM2;
		}
		else if (port1 == GPIOA && pin1 == GPIO_PIN_2)
		{
			TimerInstance = TIM2;
			PWMChannel = TIM_CHANNEL_3;
			__HAL_RCC_TIM2_CLK_ENABLE();
			gpioalternate = GPIO_AF1_TIM2;
		}
		else if (port1 == GPIOA && pin1 == GPIO_PIN_3)
		{
			TimerInstance = TIM2;
			PWMChannel = TIM_CHANNEL_4;
			__HAL_RCC_TIM2_CLK_ENABLE();
			gpioalternate = GPIO_AF1_TIM2;
		}
		else if (port1 == GPIOA && pin1 == GPIO_PIN_6)
		{
			TimerInstance = TIM3;
			PWMChannel = TIM_CHANNEL_1;
			__HAL_RCC_TIM3_CLK_ENABLE();
			gpioalternate = GPIO_AF2_TIM3;
		}
		else if (port1 == GPIOA && pin1 == GPIO_PIN_7)
		{
			TimerInstance = TIM3;
			PWMChannel = TIM_CHANNEL_2;
			__HAL_RCC_TIM3_CLK_ENABLE();
			gpioalternate = GPIO_AF1_TIM2;
		}
		else if (port1 == GPIOB && pin1 == GPIO_PIN_0)
		{
			TimerInstance = TIM3;
			PWMChannel = TIM_CHANNEL_3;
			__HAL_RCC_TIM3_CLK_ENABLE();
			gpioalternate = GPIO_AF2_TIM3;
		}
		else if (port1 == GPIOB && pin1 == GPIO_PIN_1)
		{
			TimerInstance = TIM3;
			PWMChannel = TIM_CHANNEL_4;
			__HAL_RCC_TIM3_CLK_ENABLE();
			gpioalternate = GPIO_AF2_TIM3;
		}
		else if (port1 == GPIOD && pin1 == GPIO_PIN_12)
		{
			TimerInstance = TIM4;
			PWMChannel = TIM_CHANNEL_1;
			__HAL_RCC_TIM4_CLK_ENABLE();
			gpioalternate = GPIO_AF2_TIM4;
		}
		else if (port1 == GPIOD && pin1 == GPIO_PIN_13)
		{
			TimerInstance = TIM4;
			PWMChannel = TIM_CHANNEL_2;
			__HAL_RCC_TIM4_CLK_ENABLE();
			gpioalternate = GPIO_AF2_TIM4;
		}
		else if (port1 == GPIOD && pin1 == GPIO_PIN_14)
		{
			TimerInstance = TIM4;
			PWMChannel = TIM_CHANNEL_3;
			__HAL_RCC_TIM4_CLK_ENABLE();
			gpioalternate = GPIO_AF2_TIM4;
		}
		else if (port1 == GPIOD && pin1 == GPIO_PIN_15)
		{
			TimerInstance = TIM4;
			PWMChannel = TIM_CHANNEL_4;
			__HAL_RCC_TIM4_CLK_ENABLE();
			gpioalternate = GPIO_AF2_TIM4;
		}
		else  
		{
			//there was no pin port combo with a timer instance and channel specified for it here. 
			configASSERT(false);
		}
		this->PeripheralHandle_t.Instance = TimerInstance;
		this->PeripheralHandle_t.Init.Prescaler = 199; //499;
		this->PeripheralHandle_t.Init.Period = 2749; //1999; 
		HAL_TIM_PWM_Init(&this->PeripheralHandle_t);

		TIM_MasterConfigTypeDef sMasterConfig;
		sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
		sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
		if (HAL_TIMEx_MasterConfigSynchronization(&this->PeripheralHandle_t, &sMasterConfig) != HAL_OK)
		{ 
		}
        
		sConfigOC.OCMode = TIM_OCMODE_PWM1;
		sConfigOC.Pulse = 0; //this sets the on time of the pulse. since the period is 999, a pulse of 500 is a 50% duty cycle.
		sConfigOC.OCPolarity = TIM_OCPOLARITY_HIGH;
		sConfigOC.OCFastMode = TIM_OCFAST_DISABLE;
		HAL_TIM_PWM_ConfigChannel(&this->PeripheralHandle_t, &sConfigOC, PWMChannel);

		GPIO_InitTypeDef GPIO_InitStruct;
		GPIO_InitStruct.Pin = pin1;
		GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
		GPIO_InitStruct.Pull = GPIO_NOPULL;
		GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
		GPIO_InitStruct.Alternate = GPIO_AF2_TIM3;
		HAL_GPIO_Init(port1, &GPIO_InitStruct);
        
        
		this->InstanceOfPWM.Period = this->PeripheralHandle_t.Init.Period;
		this->InstanceOfPWM.DutyCycle = (((float)sConfigOC.Pulse / (float)this->InstanceOfPWM.Period) * 100);
 
	}
 