


#include "AEDMAPeripheral.h"




//
//template<class PeriphOrMemType>
//inline void AEDMA::_Init(PeriphOrMemType* periphOrMem)
//	{
//
//		 
//		_dMAHandle.Instance = *(_dmaStream->GetDMAStream());
//		_dMAHandle.Init.Channel = _dmaCH->GetChannel();
//		_dMAHandle.Init.Direction = DMA_PERIPH_TO_MEMORY;
//		_dMAHandle.Init.PeriphBurst = DMA_PINC_DISABLE;
//		_dMAHandle.Init.MemInc = DMA_MINC_ENABLE;
//		_dMAHandle.Init.PeriphDataAlignment = DMA_PDATAALIGN_HALFWORD;
//		_dMAHandle.Init.MemDataAlignment = DMA_MDATAALIGN_HALFWORD;
//		_dMAHandle.Init.Mode = DMA_CIRCULAR;
//		_dMAHandle.Init.Priority = DMA_PRIORITY_LOW;
//		_dMAHandle.Init.FIFOMode = DMA_FIFOMODE_DISABLE;
//		HAL_DMA_Init(&_dMAHandle);
//
//		__HAL_LINKDMA(periphOrMem, DMA_Handle, _dMAHandle);
//
//		//		HAL_NVIC_SetPriority(DMA2_Stream0_IRQn, 5, 0);
//		//		HAL_NVIC_EnableIRQ(DMA2_Stream0_IRQn); 
//		
//	}
	

extern "C"
{
	void DMA2_Stream0_IRQHandler(void)
	{
		HAL_DMA_IRQHandler(DMA2HandleForStream0); 
		//	AEDMA_Stream::GetDMAStreamInstance(DMA_StreamEnum::DMA_2)
		//	HAL_DMA_IRQHandler(ADCPERIPHERAL1_Instance->dmaForADC.GetDMAHandle());   //(&ADCPERIPHERAL1_Instance->hdma_adcc); //(&hdma_adc_inst); //(&ADCPERIPHERAL1_Instance->hdma_adc);
	}
	
	void DMA1_Stream6_IRQHandler(void)
	{
		HAL_DMA_IRQHandler(DMA1HandleForStream6); 
	}
		
}