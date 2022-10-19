#include "AEDMAPeripheral.h"


uint32_t AEDMA_Channel::_numDMACHCreatedSoFar = 0;

uint32_t AEDMA_Stream::_numCreatedSoFar = 0;
uint32_t AEDMA::_numCreatedSoFar = 0;

 
#if DMA_Numbers_Of_DMA >= 1
DMAHandleType_t* DMA1HandleForStream0;
DMAHandleType_t* DMA1HandleForStream1;
DMAHandleType_t* DMA1HandleForStream2;
DMAHandleType_t* DMA1HandleForStream3;
DMAHandleType_t* DMA1HandleForStream4;
DMAHandleType_t* DMA1HandleForStream5;
DMAHandleType_t* DMA1HandleForStream6;
DMAHandleType_t* DMA1HandleForStream7;
#endif
#if DMA_Numbers_Of_DMA >= 2
DMAHandleType_t* DMA2HandleForStream0;
DMAHandleType_t* DMA2HandleForStream1;
DMAHandleType_t* DMA2HandleForStream2;
DMAHandleType_t* DMA2HandleForStream3;
DMAHandleType_t* DMA2HandleForStream4;
DMAHandleType_t* DMA2HandleForStream5;
DMAHandleType_t* DMA2HandleForStream6;
DMAHandleType_t* DMA2HandleForStream7;
#endif

#if DMA_Numbers_Of_DMA >= 3
DMAHandleType_t* DMA3HandleForStream0;
DMAHandleType_t* DMA3HandleForStream1;
DMAHandleType_t* DMA3HandleForStream2;
DMAHandleType_t* DMA3HandleForStream3;
DMAHandleType_t* DMA3HandleForStream4;
DMAHandleType_t* DMA3HandleForStream5;
DMAHandleType_t* DMA3HandleForStream6;
DMAHandleType_t* DMA3HandleForStream7;
#endif
#if DMA_Numbers_Of_DMA >= 4
DMAHandleType_t* DMA4HandleForStream0;
DMAHandleType_t* DMA4HandleForStream1;
DMAHandleType_t* DMA4HandleForStream2;
DMAHandleType_t* DMA4HandleForStream3;
DMAHandleType_t* DMA4HandleForStream4;
DMAHandleType_t* DMA4HandleForStream5;
DMAHandleType_t* DMA4HandleForStream6;
DMAHandleType_t* DMA4HandleForStream7;
#endif

void AEDMA_Stream::Initialize(AEDMA* parentDMA)
{
	_parentDMA = parentDMA;
	
	uint32_t streamID = (uint32_t)GetDMAEnum();
		
	//set all global DMA handles for interrupt purposes.
#if DMA_Numbers_Of_DMA >= 1
	if (_parentDMA->GetForNumDMA() == 1)
	{	
		if (streamID == 0){DMA1HandleForStream0 = _parentDMA->GetDMAHandle(); }
		else if (streamID == 1){DMA1HandleForStream1 = _parentDMA->GetDMAHandle(); }
		else if (streamID == 2){DMA1HandleForStream2 = _parentDMA->GetDMAHandle(); }
		else if (streamID == 3){DMA1HandleForStream3 = _parentDMA->GetDMAHandle(); }
		else if (streamID == 4){DMA1HandleForStream4 = _parentDMA->GetDMAHandle(); }
		else if (streamID == 5){DMA1HandleForStream5 = _parentDMA->GetDMAHandle(); }
		else if (streamID == 6){DMA1HandleForStream6 = _parentDMA->GetDMAHandle(); }
		else if (streamID == 7){DMA1HandleForStream7 = _parentDMA->GetDMAHandle(); }
	}
#endif
#if DMA_Numbers_Of_DMA >= 2
	if (_parentDMA->GetForNumDMA() == 2)
	{	
		if (streamID == 0){DMA2HandleForStream0 = _parentDMA->GetDMAHandle(); }
		else if (streamID == 1){DMA2HandleForStream1 = _parentDMA->GetDMAHandle(); }
		else if (streamID == 2){DMA2HandleForStream2 = _parentDMA->GetDMAHandle(); }
		else if (streamID == 3){DMA2HandleForStream3 = _parentDMA->GetDMAHandle(); }
		else if (streamID == 4){DMA2HandleForStream4 = _parentDMA->GetDMAHandle(); }
		else if (streamID == 5){DMA2HandleForStream5 = _parentDMA->GetDMAHandle(); }
		else if (streamID == 6){DMA2HandleForStream6 = _parentDMA->GetDMAHandle(); }
		else if (streamID == 7){DMA2HandleForStream7 = _parentDMA->GetDMAHandle(); }
	}
#endif
#if DMA_Numbers_Of_DMA >= 3
	if (_parentDMA->GetForNumDMA() == 3)
	{	
		if (streamID == 0){DMA3HandleForStream0 = _parentDMA->GetDMAHandle(); }
		else if (streamID == 1){DMA3HandleForStream1 = _parentDMA->GetDMAHandle(); }
		else if (streamID == 2){DMA3HandleForStream2 = _parentDMA->GetDMAHandle(); }
		else if (streamID == 3){DMA3HandleForStream3 = _parentDMA->GetDMAHandle(); }
		else if (streamID == 4){DMA3HandleForStream4 = _parentDMA->GetDMAHandle(); }
		else if (streamID == 5){DMA3HandleForStream5 = _parentDMA->GetDMAHandle(); }
		else if (streamID == 6){DMA3HandleForStream6 = _parentDMA->GetDMAHandle(); }
		else if (streamID == 7){DMA3HandleForStream7 = _parentDMA->GetDMAHandle(); }
	}
#endif
#if DMA_Numbers_Of_DMA >= 4
	if (_parentDMA->GetForNumDMA() == 4)
	{	
		if (streamID == 0){DMA4HandleForStream0 = _parentDMA->GetDMAHandle(); }
		else if (streamID == 1){DMA4HandleForStream1 = _parentDMA->GetDMAHandle(); }
		else if (streamID == 2){DMA4HandleForStream2 = _parentDMA->GetDMAHandle(); }
		else if (streamID == 3){DMA4HandleForStream3 = _parentDMA->GetDMAHandle(); }
		else if (streamID == 4){DMA4HandleForStream4 = _parentDMA->GetDMAHandle(); }
		else if (streamID == 5){DMA4HandleForStream5 = _parentDMA->GetDMAHandle(); }
		else if (streamID == 6){DMA4HandleForStream6 = _parentDMA->GetDMAHandle(); }
		else if (streamID == 7){DMA4HandleForStream7 = _parentDMA->GetDMAHandle(); }
	}
#endif
	
	
	if (_hasBeenInitYet == false)
	{
		_InitializationFuncptr(); 
	}
		
	_hasBeenInitYet = true;
}


