#include "AEI2C.h"

#include "stm32f4xx_hal.h"
#include "stm32f4xx.h"


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
   
	
	void FLASH_IRQHandler()
	{
		
	}
	
	void DMA1_Stream0_IRQHandler(void)
	{ 
		//HAL_DMA_IRQHandler(I2CPERIPHERAL1_Instance->dmaForI2C.GetDMAHandle()); 
		HAL_DMA_IRQHandler(I2CPERIPHERAL1_Instance->dmaForI2C.GetDMAHandle()); 
	} 
 
	void I2C1_EV_IRQHandler(void)
	{ 
		//I2CPERIPHERAL1_Instance->PeripheralHandle_t.XferISR 
		HAL_I2C_EV_IRQHandler(&I2CPERIPHERAL1_Instance->PeripheralHandle_t); 
	}

	void I2C1_ER_IRQHandler(void)
	{ 
		HAL_I2C_ER_IRQHandler(&I2CPERIPHERAL1_Instance->PeripheralHandle_t); 
	}

	void HAL_I2C_MasterTxCpltCallback(I2C_HandleTypeDef *I2C_Handle)
	{
		
//		auto sr2itflags   = READ_REG(I2C_Handle->Instance->SR2); //7 should be //3
//		auto sr1itflags   = READ_REG(I2C_Handle->Instance->SR1); //130          //1
//		
//		I2C_Handle->Instance->SR2 = 3;
//		I2C_Handle->Instance->SR1 = 1;
		
		AEI2C* fori2c;
			
#ifdef I2CPERIPHERAL1
		if (I2C_Handle->Instance == I2C1)
		{ 
			fori2c = I2CPERIPHERAL1_Name; 
		}
#endif 
#ifdef I2CPERIPHERAL2
		if (I2C_Handle->Instance == I2C2)
		{ 
			fori2c = I2CPERIPHERAL2_Name; 
		}
#endif
#ifdef I2CPERIPHERAL3
		if (I2C_Handle->Instance == I2C3)
		{ 
			fori2c = I2CPERIPHERAL3_Name; 
		}
#endif
		
		fori2c->AE_I2C_MasterTxCpltCallback(fori2c);
		  
		
		
//		static I2C_TXCpltEVT* evtToPublish = PoolManager->GetEvtFromPoolFromISR<I2C_TXCpltEVT>();
//	  
//		evtToPublish->forI2C =
//			I2C_Handle->Instance == I2C1 ? 1 :
//			I2C_Handle->Instance == I2C2 ? 2 :
//			I2C_Handle->Instance == I2C3 ? 3 :
//			0;
//
//		PublishSubscribeManager->PublishEvtFromISR(evtToPublish);
	}

	void HAL_I2C_MasterRxCpltCallback(I2C_HandleTypeDef *I2C_Handle)
	{
		
//		auto sr2itflags   = READ_REG(I2C_Handle->Instance->SR2); //7 should be //3
//		auto sr1itflags   = READ_REG(I2C_Handle->Instance->SR1); //130          //1
//		
//		I2C_Handle->Instance->SR2 = 3;
//		I2C_Handle->Instance->SR1 = 1;
			
		AEI2C* fori2c;
			
#ifdef I2CPERIPHERAL1
		if (I2C_Handle->Instance == I2C1)
		{ 
			fori2c = I2CPERIPHERAL1_Name; 
		}
#endif 
#ifdef I2CPERIPHERAL2
		if (I2C_Handle->Instance == I2C2)
		{ 
			fori2c = I2CPERIPHERAL2_Name; 
		}
#endif
#ifdef I2CPERIPHERAL3
		if (I2C_Handle->Instance == I2C3)
		{ 
			fori2c = I2CPERIPHERAL3_Name; 
		}
#endif
		
		fori2c->AE_I2C_MasterRxCpltCallback(fori2c);
		
		
//		static I2C_RXCpltEVT* evtToPublish = PoolManager->GetEvtFromPoolFromISR<I2C_RXCpltEVT>();
//
//		evtToPublish->forI2C =
//			I2C_Handle->Instance == I2C1 ? 1 :
//			I2C_Handle->Instance == I2C2 ? 2 :
//			I2C_Handle->Instance == I2C3 ? 3 :
//			0;
//
//		PublishSubscribeManager->PublishEvtFromISR(evtToPublish);
	
	}


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