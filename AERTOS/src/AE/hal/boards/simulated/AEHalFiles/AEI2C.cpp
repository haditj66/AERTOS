#include "AEI2C.h"
 


#ifdef __cplusplus
extern "C" {
#endif 
	
	
#ifndef  aehal
	extern DMA_HandleTypeDef hdma_i2c1_rx;
	extern I2C_HandleTypeDef hi2c1;

	 
		void DMA1_Stream0_IRQHandler(void)
		{ 
			HAL_DMA_IRQHandler(&hdma_i2c1_rx); 
		}

		/**
		* @brief This function handles I2C1 event interrupt.
		*/
		void I2C1_EV_IRQHandler(void)
		{ 
			HAL_I2C_EV_IRQHandler(&hi2c1); 
			auto hi2c = &hi2c1; 

		}

		/**
		* @brief This function handles I2C1 error interrupt.
		*/
		void I2C1_ER_IRQHandler(void)
		{ 
			HAL_I2C_ER_IRQHandler(&hi2c1); 
		}

		void HAL_I2C_MasterRxCpltCallback(I2C_HandleTypeDef *hi2c)
		{
  
		}
		void HAL_I2C_MasterTxCpltCallback(I2C_HandleTypeDef *hi2c)
		{
  
		} 
#endif
	

#ifdef I2CPERIPHERAL1
   
	  

#endif



#ifdef I2CPERIPHERAL2

	void I2C2_EV_IRQHandler(void)
	{ 
		HAL_I2C_EV_IRQHandler(&I2CPERIPHERAL2_Instance->PeripheralHandle_t); 
	}

	void I2C2_ER_IRQHandler(void)
	{ 
		HAL_I2C_ER_IRQHandler(&I2CPERIPHERAL2_Instance->PeripheralHandle_t); 
	}

	void DMA1_Stream1_IRQHandler(void)
	{ 
		HAL_DMA_IRQHandler(&I2CPERIPHERAL2_Instance->hdma_i2c1_rx); 
	} 
#endif



#ifdef I2CPERIPHERAL3

	void I2C3_EV_IRQHandler(void)
	{ 
		HAL_I2C_EV_IRQHandler(&I2CPERIPHERAL3_Instance->PeripheralHandle_t); 
	}

	void I2C3_ER_IRQHandler(void)
	{ 
		HAL_I2C_ER_IRQHandler(&I2CPERIPHERAL3_Instance->PeripheralHandle_t); 
	}
	void DMA1_Stream2_IRQHandler(void)
	{ 
		HAL_DMA_IRQHandler(&I2CPERIPHERAL3_Instance->hdma_i2c1_rx); 
	} 
 
#endif
	//UserCode_Section0_end

#ifdef __cplusplus
}
#endif  