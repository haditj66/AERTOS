#pragma once


#include "AEDMAPeripheral.h"





template<class PeriphOrMemType>
inline void AEDMA::_Init(PeriphOrMemType* periphOrMem, uint32_t mode)
	{

		 

		
		if(mode == DMA_NORMAL)
		{
//			__HAL_RCC_DMA1_CLK_ENABLE();
//			_dMAHandle.Instance = DMA1_Stream6;
//			_dMAHandle.Init.Channel = DMA_CHANNEL_4;
//			_dMAHandle.Init.Direction = DMA_MEMORY_TO_PERIPH;
//			_dMAHandle.Init.PeriphInc = DMA_PINC_DISABLE;
//			_dMAHandle.Init.MemInc = DMA_MINC_ENABLE;
//			_dMAHandle.Init.PeriphDataAlignment = DMA_PDATAALIGN_BYTE;
//			_dMAHandle.Init.MemDataAlignment = DMA_MDATAALIGN_BYTE;
//			_dMAHandle.Init.Mode = DMA_NORMAL;
//			_dMAHandle.Init.Priority = DMA_PRIORITY_MEDIUM;
//			_dMAHandle.Init.FIFOMode = DMA_FIFOMODE_DISABLE;
//			_dMAHandle.Init.FIFOThreshold = DMA_FIFO_THRESHOLD_FULL;
//			_dMAHandle.Init.MemBurst = DMA_MBURST_INC4;
//			_dMAHandle.Init.PeriphBurst = DMA_PBURST_INC4;
//			//hdma_uart2_TX.XferCpltCallback = &DMATransferComplete;
//			HAL_DMA_Init(&_dMAHandle);
//			return;
		
		}
		
		_dMAHandle.Instance = *(_dmaStream->GetDMAStream());
		_dMAHandle.Init.Channel = _dmaCH->GetChannel();
		_dMAHandle.Init.Direction = DMA_PERIPH_TO_MEMORY;
		_dMAHandle.Init.PeriphBurst = DMA_PINC_DISABLE;
		_dMAHandle.Init.MemInc = DMA_MINC_ENABLE;
		_dMAHandle.Init.PeriphDataAlignment = DMA_PDATAALIGN_HALFWORD;
		_dMAHandle.Init.MemDataAlignment = DMA_MDATAALIGN_HALFWORD;
		_dMAHandle.Init.Mode = mode;
		_dMAHandle.Init.Priority = DMA_PRIORITY_LOW;
		_dMAHandle.Init.FIFOMode = DMA_FIFOMODE_DISABLE;
		HAL_DMA_Init(&_dMAHandle);

		
		 
		
	}
	