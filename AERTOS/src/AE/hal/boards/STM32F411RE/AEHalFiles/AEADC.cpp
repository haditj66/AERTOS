#include "AEADC.h"






#ifdef __cplusplus
extern "C" {
#endif 
   


 
	//put all your interupt calls in here
	//UserCode_Section0
	void ADC_IRQHandler(void)
	{
#if defined(ADCPERIPHERAL1_Name_CH1) || defined(ADCPERIPHERAL1_Name_CH2) || defined(ADCPERIPHERAL1_Name_CH3) || defined(ADCPERIPHERAL1_Name_CH4) || defined(ADCPERIPHERAL1_Name_CH5)
		HAL_ADC_IRQHandler(&ADCPERIPHERAL1_Instance->PeripheralHandle_t);
#endif
	}
//	void DMA2_Stream0_IRQHandler(void)
//	{
//		HAL_DMA_IRQHandler(ADCPERIPHERAL1_Instance->dmaForADC.GetDMAHandle());  //(&ADCPERIPHERAL1_Instance->hdma_adcc); //(&hdma_adc_inst); //(&ADCPERIPHERAL1_Instance->hdma_adc);
//	}
	
 
	 
	

	void HAL_ADC_ConvCpltCallback(ADC_HandleTypeDef* hadc)
	{
		
		
		if (hadc->Instance == ADC1)
		{  
#ifdef ADCPERIPHERAL1_Name_CH1
			ADCPERIPHERAL1_Name_CH1->AE_ADC_ConvCpltCallback();
#endif
#ifdef ADCPERIPHERAL1_Name_CH2
			ADCPERIPHERAL1_Name_CH2->AE_ADC_ConvCpltCallback();
#endif
#ifdef ADCPERIPHERAL1_Name_CH3
			ADCPERIPHERAL1_Name_CH3->AE_ADC_ConvCpltCallback();
#endif
#ifdef ADCPERIPHERAL1_Name_CH4
			ADCPERIPHERAL1_Name_CH4->AE_ADC_ConvCpltCallback();
#endif
#ifdef ADCPERIPHERAL1_Name_CH5
			ADCPERIPHERAL1_Name_CH5->AE_ADC_ConvCpltCallback(); 
#endif 
		}
		
		
	}
	//UserCode_Section0_end

#ifdef __cplusplus
}
#endif  