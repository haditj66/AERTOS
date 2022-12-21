#include "AESPI.h"

#include "stm32f4xx_hal.h"
#include "stm32f4xx.h"


#ifdef __cplusplus
extern "C" {
#endif 
	
	
	
	
#ifdef SPIPERIPHERAL1
	void SPI1_IRQHandler(void)
	{
		HAL_SPI_IRQHandler(&SPIPERIPHERAL1_Instance->PeripheralHandle_t);

	}
#endif 
#ifdef SPIPERIPHERAL2
	void SPI2_IRQHandler(void)
	{
		HAL_SPI_IRQHandler(&SPIPERIPHERAL2_Instance->PeripheralHandle_t);

	}

#endif 
	
	
#ifdef SPIPERIPHERAL1 
	
	
	void HAL_SPI_RxCpltCallback(SPI_HandleTypeDef *hspi)
	{
		
		AESPI* forspi;
			
#ifdef SPIPERIPHERAL1
		if (hspi->Instance == SPI1)
		{ 
			forspi = SPIPERIPHERAL1_Name; 
		}
#endif 
#ifdef SPIPERIPHERAL2
		if (hspi->Instance == SPI2)
		{ 
			forspi = SPIPERIPHERAL2_Name; 
		}
#endif 
#ifdef SPIPERIPHERAL3
		if (hspi->Instance == SPI3)
		{ 
			forspi = SPIPERIPHERAL3_Name; 
		}
#endif 
		
		if (forspi->AE_SPI_MasterRxCpltCallback != nullptr)
		{
			forspi->AE_SPI_MasterRxCpltCallback();
		}
		HAL_SPI_Receive_IT(forspi->_spi_Handle, (uint8_t*)forspi->GetSPIBuffer(), (uint16_t)forspi->GetSPIBufferSize());
 
		

	}
	
	
	
#endif 
	 
	
#ifdef __cplusplus
}
#endif  