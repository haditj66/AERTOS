#pragma once
#include <cstdint>

#include "AEUtils.h"
#include "BoardTypes.h"
#include "AEPeripheral.h"


#ifndef USING_AEDMA 
#error you included this file but you did not provide a AEDMA.h file in AEHalFiles directory.
#endif 


enum class DMA_StreamEnum 
{
	DMAStream_0 = 0,
	DMAStream_1,
	DMAStream_2,
	DMAStream_3,
	DMAStream_4,
	DMAStream_5,
	DMAStream_6,
	DMAStream_7,
	DMAStream_8,
	DMAStream_9,
	DMAStream_10
		
};

enum class DMACHEnum 
{
	DMACH0 = 0,
	DMACH1,
	DMACH2,
	DMACH3,
	DMACH4,
	DMACH5,
	DMACH6,
	DMACH7,
	DMACH8,
	DMACH9,
	DMACH10, 
	DMACH11,
	DMACH12,
	DMACH13,
	DMACH14,
	DMACH15
		
};


class AEDMA_Channel;
extern AEDMA_Channel UserDefinedAEDMA_chs[];

class AEDMA_Channel
{
public:
	static AEDMA_Channel* GetDMAChInstance(DMACHEnum indexEnum)
	{
		for (int i = 0; i < _numDMACHCreatedSoFar; i++)
		{
			if (UserDefinedAEDMA_chs[i].GetEnumType() == indexEnum)
			{
				return &UserDefinedAEDMA_chs[i];
			} 
		}
		AEAssertRuntime(false, "you attempted to get a dma_channel with an enum type that was never user defined.");
	}
	
	AEDMA_Channel(DMACHEnum dMA_CH, uint32_t valueOfChannel)
	{
		ValueOfChannel = valueOfChannel;
		DMA_CH = dMA_CH;
		
		for (int i = 0; i < _numDMACHCreatedSoFar; i++)
		{
			AEAssertRuntime(UserDefinedAEDMA_chs[i].GetEnumType() != dMA_CH, "make sure that the channel defined has not been one defined already");
			
		}
		_numDMACHCreatedSoFar++;
	}
	
	
	DMACHEnum GetEnumType() const
	{return DMA_CH;	}
	
	uint32_t GetChannel() const
	{return ValueOfChannel;	}
	
	AEDMA_Channel* GetChannelInstance();
	
private:
	uint32_t ValueOfChannel;
	DMACHEnum DMA_CH;
	
	static uint32_t _numDMACHCreatedSoFar;
};






#if DMA_Numbers_Of_DMA >= 1
extern DMAHandleType_t* DMA1HandleForStream0;
extern DMAHandleType_t* DMA1HandleForStream1;
extern DMAHandleType_t* DMA1HandleForStream2;
extern DMAHandleType_t* DMA1HandleForStream3;
extern DMAHandleType_t* DMA1HandleForStream4;
extern DMAHandleType_t* DMA1HandleForStream5;
extern DMAHandleType_t* DMA1HandleForStream6;
extern DMAHandleType_t* DMA1HandleForStream7;
#endif

#if DMA_Numbers_Of_DMA >= 2
extern DMAHandleType_t* DMA2HandleForStream0;
extern DMAHandleType_t* DMA2HandleForStream1;
extern DMAHandleType_t* DMA2HandleForStream2;
extern DMAHandleType_t* DMA2HandleForStream3;
extern DMAHandleType_t* DMA2HandleForStream4;
extern DMAHandleType_t* DMA2HandleForStream5;
extern DMAHandleType_t* DMA2HandleForStream6;
extern DMAHandleType_t* DMA2HandleForStream7;
#endif

#if DMA_Numbers_Of_DMA >= 3
extern DMAHandleType_t* DMA3HandleForStream0;
extern DMAHandleType_t* DMA3HandleForStream1;
extern DMAHandleType_t* DMA3HandleForStream2;
extern DMAHandleType_t* DMA3HandleForStream3;
extern DMAHandleType_t* DMA3HandleForStream4;
extern DMAHandleType_t* DMA3HandleForStream5;
extern DMAHandleType_t* DMA3HandleForStream6;
extern DMAHandleType_t* DMA3HandleForStream7;
#endif
#if DMA_Numbers_Of_DMA >= 4
extern DMAHandleType_t* DMA4HandleForStream0;
extern DMAHandleType_t* DMA4HandleForStream1;
extern DMAHandleType_t* DMA4HandleForStream2;
extern DMAHandleType_t* DMA4HandleForStream3;
extern DMAHandleType_t* DMA4HandleForStream4;
extern DMAHandleType_t* DMA4HandleForStream5;
extern DMAHandleType_t* DMA4HandleForStream6;
extern DMAHandleType_t* DMA4HandleForStream7;
#endif

typedef void(*InitializationfuncPtr_t)(void);


class AEDMA;

class AEDMA_Stream;
extern AEDMA_Stream UserDefinedAEDMA_streams[];


class AEDMA_Stream
{
	friend class AEDMA;
public:
	AEDMA_Stream(uint32_t forDMA, DMA_StreamEnum dmaenumType, DMAStreamType_t haldma, InitializationfuncPtr_t InitializationFuncptr)
	{
		_forDMA = forDMA;
		_InitializationFuncptr = InitializationFuncptr;
		_hasBeenInitYet = false; 
		_dmaenumType = dmaenumType;
		_haldma = haldma; 
 
		
		for (int i = 0; i < _numCreatedSoFar; i++)
		{
			//dma match
			if(UserDefinedAEDMA_streams[i]._forDMA == forDMA)
			{ 
				//stream match
				AEAssertRuntime(UserDefinedAEDMA_streams[i].GetDMAEnum() != _dmaenumType, "make sure that the dmaenumType defined has not been one defined already");
			} 

		}
 
		//		UserDefinedAEPorts[_numPortsCreatedSoFar] = this;
		_numCreatedSoFar++;
	}
  
	
	static AEDMA_Stream* GetDMAStreamInstance(uint32_t forDMA, DMA_StreamEnum indexStreamEnum)
	{ 
		
		for (int i = 0; i < _numCreatedSoFar; i++)
		{
			//dma match
			if(UserDefinedAEDMA_streams[i]._forDMA == forDMA)
			{ 
				//stream match
				if(UserDefinedAEDMA_streams[i].GetDMAEnum() == indexStreamEnum)
				{
					return &UserDefinedAEDMA_streams[i];
				} 
			} 

		}
		AEAssertRuntime(false, "you attempted to get a dmastream with an enum type that was never user defined.");
	}  

	DMA_StreamEnum GetDMAEnum() { return _dmaenumType; }
	DMAStreamType_t* GetDMAStream() { return &_haldma; }

private:
	
	AEDMA* _parentDMA;
	
	InitializationfuncPtr_t _InitializationFuncptr;
	bool _hasBeenInitYet;
	DMA_StreamEnum _dmaenumType;
	uint32_t _forDMA;
	
	DMAStreamType_t _haldma; 

	static uint32_t _numCreatedSoFar;
	
	void Initialize(AEDMA* parentDMA);

	
	//	static AEPort* ALLPorts[15];
};






typedef void(*CustomInitializationfuncPtr_t)(DMAHandleType_t* DMAHandle, DMAStreamType_t* DMAStream, uint32_t dmaChannel);

class AEDMA
{
	
//	template<templateForADC>
//	friend class ADCPeripheral;
//	template<templateForUART>
//	friend class UARTPeripheral;
	
public: 
		
	AEDMA(  ) { 
		_customInitializationfuncPtr = nullptr;  

	};
	
	
	
	uint8_t GetForNumDMA()
	{return _forDMA;}
	 
	
	void SetCustomInitialization(CustomInitializationfuncPtr_t customInitializationfuncPtr)
	{
		_customInitializationfuncPtr = customInitializationfuncPtr;
	}
	
	DMAHandleType_t* GetDMAHandle() {return &_dMAHandle;};
	
	
	
	
	template<class PeriphOrMemType>
		void Init(PeriphOrMemType* periphOrMem, uint8_t forDMA, DMA_StreamEnum dmaenumType, DMACHEnum dmaCHenum, uint32_t mode)
		{
			
//			AEAssertRuntime(_peripheralEnum != PeripheralEnum::None , "this dma instance was not preinitialized which should be done by the AEhal somewhere and not the user.");
			AEAssertRuntime(forDMA <= DMA_Numbers_Of_DMA, "make sure dma selected is less than number of dmas for this board");
			_forDMA = forDMA;
			
			//get the asociated instance of the enums
			_dmaStream = AEDMA_Stream::GetDMAStreamInstance(forDMA, dmaenumType); 
			_dmaCH = AEDMA_Channel::GetDMAChInstance(dmaCHenum); 
			
			_dmaStream->Initialize(this);
		
			if (_customInitializationfuncPtr != nullptr)
			{
				_customInitializationfuncPtr(&_dMAHandle, _dmaStream->GetDMAStream(), _dmaCH->GetChannel());
				return;
			} 
			
			_Init(periphOrMem, mode);
		}
	 
	

private:
	
 
	uint8_t _forDMA;
	 
	CustomInitializationfuncPtr_t _customInitializationfuncPtr;
	
	DMAHandleType_t _dMAHandle;
	
	
	static uint32_t _numCreatedSoFar;
	
	AEDMA_Stream* _dmaStream;
	AEDMA_Channel* _dmaCH;
	
 
	
		//user defined
	template<class PeriphOrMemType>
		void _Init(PeriphOrMemType* periphOrMem, uint32_t mode);
};