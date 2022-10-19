 

#include "AEGPIOInput.h"
 








	
#ifdef __cplusplus
extern "C" {
#endif 
   



	void EXTI0_IRQHandler()
	{
#ifdef GPIOInputPERIPHERAL1
		if (GPIOInputPERIPHERAL1_Name->buttongpio_Pin == GPIO_PIN_0)
		{
			HAL_GPIO_EXTI_IRQHandler(GPIOInputPERIPHERAL1_Name->buttongpio_Pin);
		}
#endif 
#ifdef GPIOInputPERIPHERAL2
		if (GPIOInputPERIPHERAL2_Name->buttongpio_Pin == GPIO_PIN_0)
		{
			HAL_GPIO_EXTI_IRQHandler(GPIOInputPERIPHERAL2_Name->buttongpio_Pin);
		}
#endif 
		
#ifdef GPIOInputPERIPHERAL3
		if (GPIOInputPERIPHERAL3_Name->buttongpio_Pin == GPIO_PIN_0)
		{
			HAL_GPIO_EXTI_IRQHandler(GPIOInputPERIPHERAL3_Name->buttongpio_Pin);
		}
#endif 
		
#ifdef GPIOInputPERIPHERAL4
		if (GPIOInputPERIPHERAL4_Name->buttongpio_Pin == GPIO_PIN_0)
		{
			HAL_GPIO_EXTI_IRQHandler(GPIOInputPERIPHERAL4_Name->buttongpio_Pin);
		}
#endif 

#ifdef GPIOInputPERIPHERAL5
		if (GPIOInputPERIPHERAL5_Name->buttongpio_Pin == GPIO_PIN_0)
		{
			HAL_GPIO_EXTI_IRQHandler(GPIOInputPERIPHERAL5_Name->buttongpio_Pin);
		}
#endif
		
#ifdef GPIOInputPERIPHERAL6
		if (GPIOInputPERIPHERAL6_Name->buttongpio_Pin == GPIO_PIN_0)
		{
			HAL_GPIO_EXTI_IRQHandler(GPIOInputPERIPHERAL6_Name->buttongpio_Pin);
		}
#endif
	}
	
	 
	
	void EXTI1_IRQHandler()
	{
#ifdef GPIOInputPERIPHERAL1
		if (GPIOInputPERIPHERAL1_Name->buttongpio_Pin == GPIO_PIN_1)
		{
			HAL_GPIO_EXTI_IRQHandler(GPIOInputPERIPHERAL1_Name->buttongpio_Pin);
		}
#endif 
#ifdef GPIOInputPERIPHERAL2
		if (GPIOInputPERIPHERAL2_Name->buttongpio_Pin == GPIO_PIN_1)
		{
			HAL_GPIO_EXTI_IRQHandler(GPIOInputPERIPHERAL2_Name->buttongpio_Pin);
		}
#endif 
		
#ifdef GPIOInputPERIPHERAL3
		if (GPIOInputPERIPHERAL3_Name->buttongpio_Pin == GPIO_PIN_1)
		{
			HAL_GPIO_EXTI_IRQHandler(GPIOInputPERIPHERAL3_Name->buttongpio_Pin);
		}
#endif 
		
#ifdef GPIOInputPERIPHERAL4
		if (GPIOInputPERIPHERAL4_Name->buttongpio_Pin == GPIO_PIN_1)
		{
			HAL_GPIO_EXTI_IRQHandler(GPIOInputPERIPHERAL4_Name->buttongpio_Pin);
		}
#endif 

#ifdef GPIOInputPERIPHERAL5
		if (GPIOInputPERIPHERAL5_Name->buttongpio_Pin == GPIO_PIN_1)
		{
			HAL_GPIO_EXTI_IRQHandler(GPIOInputPERIPHERAL5_Name->buttongpio_Pin);
		}
#endif
		
#ifdef GPIOInputPERIPHERAL6
		if (GPIOInputPERIPHERAL6_Name->buttongpio_Pin == GPIO_PIN_1)
		{
			HAL_GPIO_EXTI_IRQHandler(GPIOInputPERIPHERAL6_Name->buttongpio_Pin);
		}
#endif
	}
	
	
	void EXTI2_IRQHandler()
	{
#ifdef GPIOInputPERIPHERAL1
		if (GPIOInputPERIPHERAL1_Name->buttongpio_Pin == GPIO_PIN_2)
		{
			HAL_GPIO_EXTI_IRQHandler(GPIOInputPERIPHERAL1_Name->buttongpio_Pin);
		}
#endif 
#ifdef GPIOInputPERIPHERAL2
		if (GPIOInputPERIPHERAL2_Name->buttongpio_Pin == GPIO_PIN_2)
		{
			HAL_GPIO_EXTI_IRQHandler(GPIOInputPERIPHERAL2_Name->buttongpio_Pin);
		}
#endif 
		
#ifdef GPIOInputPERIPHERAL3
		if (GPIOInputPERIPHERAL3_Name->buttongpio_Pin == GPIO_PIN_2)
		{
			HAL_GPIO_EXTI_IRQHandler(GPIOInputPERIPHERAL3_Name->buttongpio_Pin);
		}
#endif 
		
#ifdef GPIOInputPERIPHERAL4
		if (GPIOInputPERIPHERAL4_Name->buttongpio_Pin == GPIO_PIN_2)
		{
			HAL_GPIO_EXTI_IRQHandler(GPIOInputPERIPHERAL4_Name->buttongpio_Pin);
		}
#endif 

#ifdef GPIOInputPERIPHERAL5
		if (GPIOInputPERIPHERAL5_Name->buttongpio_Pin == GPIO_PIN_2)
		{
			HAL_GPIO_EXTI_IRQHandler(GPIOInputPERIPHERAL5_Name->buttongpio_Pin);
		}
#endif
		
#ifdef GPIOInputPERIPHERAL6
		if (GPIOInputPERIPHERAL6_Name->buttongpio_Pin == GPIO_PIN_2)
		{
			HAL_GPIO_EXTI_IRQHandler(GPIOInputPERIPHERAL6_Name->buttongpio_Pin);
		}
#endif
	}
	

	void EXTI3_IRQHandler()
	{
#ifdef GPIOInputPERIPHERAL1
		if (GPIOInputPERIPHERAL1_Name->buttongpio_Pin == GPIO_PIN_3)
		{
			HAL_GPIO_EXTI_IRQHandler(GPIOInputPERIPHERAL1_Name->buttongpio_Pin);
		}
#endif 
#ifdef GPIOInputPERIPHERAL2
		if (GPIOInputPERIPHERAL2_Name->buttongpio_Pin == GPIO_PIN_3)
		{
			HAL_GPIO_EXTI_IRQHandler(GPIOInputPERIPHERAL2_Name->buttongpio_Pin);
		}
#endif 
		
#ifdef GPIOInputPERIPHERAL3
		if (GPIOInputPERIPHERAL3_Name->buttongpio_Pin == GPIO_PIN_3)
		{
			HAL_GPIO_EXTI_IRQHandler(GPIOInputPERIPHERAL3_Name->buttongpio_Pin);
		}
#endif 
		
#ifdef GPIOInputPERIPHERAL4
		if (GPIOInputPERIPHERAL4_Name->buttongpio_Pin == GPIO_PIN_3)
		{
			HAL_GPIO_EXTI_IRQHandler(GPIOInputPERIPHERAL4_Name->buttongpio_Pin);
		}
#endif 

#ifdef GPIOInputPERIPHERAL5
		if (GPIOInputPERIPHERAL5_Name->buttongpio_Pin == GPIO_PIN_3)
		{
			HAL_GPIO_EXTI_IRQHandler(GPIOInputPERIPHERAL5_Name->buttongpio_Pin);
		}
#endif
		
#ifdef GPIOInputPERIPHERAL6
		if (GPIOInputPERIPHERAL6_Name->buttongpio_Pin == GPIO_PIN_3)
		{
			HAL_GPIO_EXTI_IRQHandler(GPIOInputPERIPHERAL6_Name->buttongpio_Pin);
		}
#endif
	}
	
	
	void EXTI4_IRQHandler()
	{
#ifdef GPIOInputPERIPHERAL1
		if (GPIOInputPERIPHERAL1_Name->buttongpio_Pin == GPIO_PIN_4)
		{
			HAL_GPIO_EXTI_IRQHandler(GPIOInputPERIPHERAL1_Name->buttongpio_Pin);
		}
#endif 
#ifdef GPIOInputPERIPHERAL2
		if (GPIOInputPERIPHERAL2_Name->buttongpio_Pin == GPIO_PIN_4)
		{
			HAL_GPIO_EXTI_IRQHandler(GPIOInputPERIPHERAL2_Name->buttongpio_Pin);
		}
#endif 
		
#ifdef GPIOInputPERIPHERAL3
		if (GPIOInputPERIPHERAL3_Name->buttongpio_Pin == GPIO_PIN_4)
		{
			HAL_GPIO_EXTI_IRQHandler(GPIOInputPERIPHERAL3_Name->buttongpio_Pin);
		}
#endif 
		
#ifdef GPIOInputPERIPHERAL4
		if (GPIOInputPERIPHERAL4_Name->buttongpio_Pin == GPIO_PIN_4)
		{
			HAL_GPIO_EXTI_IRQHandler(GPIOInputPERIPHERAL4_Name->buttongpio_Pin);
		}
#endif 

#ifdef GPIOInputPERIPHERAL5
		if (GPIOInputPERIPHERAL5_Name->buttongpio_Pin == GPIO_PIN_4)
		{
			HAL_GPIO_EXTI_IRQHandler(GPIOInputPERIPHERAL5_Name->buttongpio_Pin);
		}
#endif
		
#ifdef GPIOInputPERIPHERAL6
		if (GPIOInputPERIPHERAL6_Name->buttongpio_Pin == GPIO_PIN_4)
		{
			HAL_GPIO_EXTI_IRQHandler(GPIOInputPERIPHERAL6_Name->buttongpio_Pin);
		}
#endif
	}
	
	
	
	void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
	{
#ifdef GPIOInputPERIPHERAL1
		if (GPIOInputPERIPHERAL1_Name->buttongpio_Pin == GPIO_Pin)
		{
			GPIOInputPERIPHERAL1_Name->AE_GPIO_extiCallback(); 
		}
#endif 
		
#ifdef GPIOInputPERIPHERAL2
		if (GPIOInputPERIPHERAL2_Name->buttongpio_Pin == GPIO_Pin)
		{
			GPIOInputPERIPHERAL2_Name->AE_GPIO_extiCallback(); 
		}
#endif 
		
#ifdef GPIOInputPERIPHERAL3
		if (GPIOInputPERIPHERAL3_Name->buttongpio_Pin == GPIO_Pin)
		{
			GPIOInputPERIPHERAL3_Name->AE_GPIO_extiCallback(); 
		}
#endif 
		
#ifdef GPIOInputPERIPHERAL4
		if (GPIOInputPERIPHERAL4_Name->buttongpio_Pin == GPIO_Pin)
		{
			GPIOInputPERIPHERAL4_Name->AE_GPIO_extiCallback(); 
		}
#endif 
		
		
#ifdef GPIOInputPERIPHERAL5
		if (GPIOInputPERIPHERAL5_Name->buttongpio_Pin == GPIO_Pin)
		{
			GPIOInputPERIPHERAL5_Name->AE_GPIO_extiCallback(); 
		}
#endif 
		
#ifdef GPIOInputPERIPHERAL6
		if (GPIOInputPERIPHERAL6_Name->buttongpio_Pin == GPIO_Pin)
		{
			GPIOInputPERIPHERAL6_Name->AE_GPIO_extiCallback(); 
		}
#endif 

	}
	
	 
	
	
	
	
	
#ifdef __cplusplus
}
#endif  