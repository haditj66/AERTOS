
#include "AEPort.h"
#include "AEPin.h"
#include "AEDMA.h"

AEPort UserDefinedAEPorts[] = {
	AEPort(Portenum::PortA, 'a', [](void) -> void {  }),
	AEPort(Portenum::PortB, 'b', [](void) -> void {  }),
	AEPort(Portenum::PortC, 'c', [](void) -> void {  }),
	AEPort(Portenum::PortD, 'd', [](void) -> void {  }),
	AEPort(Portenum::PortE, 'e', [](void) -> void {  }),
	AEPort(Portenum::PortF, 'f', [](void) -> void {  }),
	AEPort(Portenum::PortG, 'g', [](void) -> void {  }),
	AEPort(Portenum::PortH, 'h', [](void) -> void {  }),
	AEPort(Portenum::PortI, 'i', [](void) -> void {  }),
	AEPort(Portenum::PortsMaxNum, 'z', [](void) -> void {})
	};


AEPin UserDefinedAEPins[] = {
	AEPin(PinEnum::PIN0, 0x0001),
	AEPin(PinEnum::PIN1, 0x0002),
	AEPin(PinEnum::PIN2, 0x0004),
	AEPin(PinEnum::PIN3, 0x0008),
	AEPin(PinEnum::PIN4, 0x00010),
	AEPin(PinEnum::PIN5, 0x00020),
	AEPin(PinEnum::PIN6, 0x00040),
	AEPin(PinEnum::PIN7, 0x00080),
	AEPin(PinEnum::PIN8, 0x000100),
	AEPin(PinEnum::PIN9, 0x000200),
	AEPin(PinEnum::PIN10, 0x000400),
	AEPin(PinEnum::PIN11, 0x000800),
	AEPin(PinEnum::PIN12, 0x0001000),
	AEPin(PinEnum::PIN13, 0x0002000),
	AEPin(PinEnum::PIN14, 0x0004000),
	AEPin(PinEnum::PIN15, 0x0008000),
	AEPin(PinEnum::PINMaxNum, 0x000ffff)
};


AEDMA_Stream UserDefinedAEDMA_streams[] = { 
	AEDMA_Stream(2, DMA_StreamEnum::DMAStream_0, 'a', []()->void{  }),
	AEDMA_Stream(1, DMA_StreamEnum::DMAStream_6, 'b', []()->void{  })
		
};  
AEDMA_Channel UserDefinedAEDMA_chs[]
{
	AEDMA_Channel(DMACHEnum::DMACH0, 'a'),
	AEDMA_Channel(DMACHEnum::DMACH1, 'b'),
	AEDMA_Channel(DMACHEnum::DMACH2, 'c'),
	AEDMA_Channel(DMACHEnum::DMACH3, 'd'),
	AEDMA_Channel(DMACHEnum::DMACH4, 'e'),
	AEDMA_Channel(DMACHEnum::DMACH5, 'f'),
	AEDMA_Channel(DMACHEnum::DMACH6, 'g'),
	AEDMA_Channel(DMACHEnum::DMACH7, 'h')
}
;