#pragma once

#include "FreeRTOS.h"
#include "task.h"

#include "AESPBObservor.h"

class TaskSPBChain
{

	friend class TaskPoolForSPBChain; 
protected:
	bool isInUse;
	TaskHandle_t TheTask;

	AESPBObservor* SPBsRefreshToRun;

	TaskSPBChain() {};

	void Init(uint32_t stackSize) {
		TaskSPBChain *pToThisClass = this;
		xTaskCreate([](void* p) {static_cast<TaskSPBChain*>(p)->SPBTaskChainGaurd(nullptr); }, "RefreshGaurdTask",
			stackSize, pToThisClass, AOPRIORITYMEDIUM, &TheTask);
	}


	void SPBTaskChainGaurd(void*) {
		uint32_t ulNotifiedValueCurrentSession;

		while (true)
		{ 
			xTaskNotifyWait(pdFALSE, pdTRUE, &ulNotifiedValueCurrentSession, portMAX_DELAY);

			//run the spb's refresh that will I need to run. All other spbs will run subsequently from the inputsignal.
			SPBsRefreshToRun->_RefreshFromBaseClass();


			isInUse = false;
		}
	
	}
};


class TaskPoolForSPBChain
{
	 

public:

	uint8_t PoolSize; uint32_t StackSizeOfEachTask;

	TaskSPBChain TasksOfPool[MAXSPB_CHAIN_POOLSIZE];

	TaskPoolForSPBChain(uint8_t poolSize, uint32_t stackSizeOfEachTask)
		: PoolSize(poolSize), StackSizeOfEachTask(stackSizeOfEachTask)
	{

		//currently this only supports task pool sizes less than 0xff
		configASSERT(poolSize <= 0xff);
		//pool size you selected is greater than the MAXSPB_CHAIN_POOLSIZE specified in the config.
		configASSERT(poolSize <= MAXSPB_CHAIN_POOLSIZE);

		for (uint16_t i = 0; i < poolSize; i++)
		{
			TasksOfPool[i].Init(stackSizeOfEachTask);
		} 

	} 


	void HaveTaskFromPoolRunRefreshOfThisSPB(AESPBObservor* spbToRunRefresh) {
		//look for an available avialableTask
		uint8_t avialableTask = 0xff;
		for (uint16_t i = 0; i < PoolSize; i++)
		{
			if (TasksOfPool[i].isInUse == false)
			{
				avialableTask = i;
				TasksOfPool[avialableTask].isInUse = true;
				TasksOfPool[avialableTask].SPBsRefreshToRun = spbToRunRefresh;
				xTaskNotifyGive(TasksOfPool[avialableTask].TheTask);
				break;
			} 
		}

		//you ran out of tasks to run in this task pool. try increasing the number of tasks in 
		//the pool or maybe change the style of the spbs
		configASSERT(avialableTask != 0xff);
		 
	}

private:

};
 