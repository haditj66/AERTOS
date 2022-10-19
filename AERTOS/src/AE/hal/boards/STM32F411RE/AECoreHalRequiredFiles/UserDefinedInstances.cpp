
#include "AEPort.h"
#include "AEPin.h"
#include "AEDMA.h"

AEPort UserDefinedAEPorts[] = {
	AEPort(Portenum::PortA, GPIOA, [](void) -> void { __GPIOA_CLK_ENABLE(); }),
	AEPort(Portenum::PortB, GPIOB, [](void) -> void { __GPIOB_CLK_ENABLE(); }),
	AEPort(Portenum::PortC, GPIOC, [](void) -> void { __GPIOC_CLK_ENABLE(); }),
	AEPort(Portenum::PortD, GPIOD, [](void) -> void { __GPIOD_CLK_ENABLE(); }),
	AEPort(Portenum::PortE, GPIOE, [](void) -> void { __GPIOE_CLK_ENABLE(); }),
	AEPort(Portenum::PortH, GPIOH, [](void) -> void { __GPIOH_CLK_ENABLE(); }),
	AEPort(Portenum::PortsMaxNum, nullptr, [](void) -> void {}) 
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
	AEPin(PinEnum::PINMaxNum, 0xffff)
};

 
AEDMA_Stream UserDefinedAEDMA_streams[] = { 
	AEDMA_Stream(2, DMA_StreamEnum::DMAStream_0, DMA2_Stream0, []()->void{ HAL_NVIC_SetPriority(DMA2_Stream0_IRQn, 6, 0); HAL_NVIC_EnableIRQ(DMA2_Stream0_IRQn); __HAL_RCC_DMA2_CLK_ENABLE(); }),
	AEDMA_Stream(1, DMA_StreamEnum::DMAStream_6, DMA1_Stream6, []()->void{ HAL_NVIC_SetPriority(DMA1_Stream6_IRQn, 6, 0); HAL_NVIC_EnableIRQ(DMA1_Stream6_IRQn); __HAL_RCC_DMA1_CLK_ENABLE(); })
		
};  
AEDMA_Channel UserDefinedAEDMA_chs[]
{
	AEDMA_Channel(DMACHEnum::DMACH0, DMA_CHANNEL_0),
	AEDMA_Channel(DMACHEnum::DMACH1, DMA_CHANNEL_1),
	AEDMA_Channel(DMACHEnum::DMACH2, DMA_CHANNEL_2),
	AEDMA_Channel(DMACHEnum::DMACH3, DMA_CHANNEL_3),
	AEDMA_Channel(DMACHEnum::DMACH4, DMA_CHANNEL_4),
	AEDMA_Channel(DMACHEnum::DMACH5, DMA_CHANNEL_5),
	AEDMA_Channel(DMACHEnum::DMACH6, DMA_CHANNEL_6),
	AEDMA_Channel(DMACHEnum::DMACH7, DMA_CHANNEL_7)
}
;