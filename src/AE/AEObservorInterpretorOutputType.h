#pragma once

#include "AEObservorInterpretorBase.h"

template<class TObservationType>
class AEObservorInterpretorOutputType : public AEObservorInterpretorBase
{
public:
	AEObservorInterpretorOutputType(); 


	//this will update the observors observation and return a refreshed observation.
	TObservationType UpdateObservationIfNeededAndGet(int& inSession);

	//TODO: get this to work so that the compiler is aware that this can only be called in a refresh function!
	///THIS SHOULD ONLY BE CALLED IN A REFRESH TO GET OTHER OBVSERVATION A OBSERVOR RELIES ON.
	TObservationType  GetObservation();
	TObservationType*  GetObservationAddress();


protected:

	TObservationType Observation;
	TObservationType ObservationToChangeInRefresh;

	virtual void Refresh() = 0; // todo: this needs to be CRTP inherited
	virtual void CopyDeterminedValues() = 0;// todo: this needs to be CRTP inherited

private:

	

	
};
 
template<class TObservationType>
inline TObservationType AEObservorInterpretorOutputType<TObservationType>::UpdateObservationIfNeededAndGet(int & inSession)
{
	//local currentsession to make sure it is not changed while within this funcion
	uint8_t currentSessionL = CurrentSession;

	if (AlreadyInSession)
	{
		inSession = 0;
		xSemaphoreTake(MutexHandles[currentSessionL], portMAX_DELAY);
		xSemaphoreGive(MutexHandles[currentSessionL]);
		//xQueuePeek(MutexHandles[currentSessionL], NULL, portMAX_DELAY);
		return Observation;
		//todo: return observation; I need a template for this somehow
	}
	else if (DoINeedARefresh == false)
	{
		inSession = 1;
		//if it doesnt even need a refresh, then just return the observation
		return Observation;
	}

	//NO LONGER VALID
	//if This observor pointed to some deterministic interpretors, Then I would need to call Updates on those to make sure
	// they had not gone stale. however, if it has no interpretor that it depends on and if HasThereBeenARefreshOAnyDeterministicObservors
	//is false, then there would be nothing to check and I can be sure that HasThereBeenARefreshOAnyDeterministicObservors == false
	//is in fact false.
	//else if (HasThereBeenARefreshOAnyDeterministicObservors == false && numOfDeterministicLinksIPointThatAreInterpretors == 0)
	//{
	//	return Observation;
	//}
	else
	{// if it is not in a session then go ahead and start a new session and wait for an incremented currentsession
		inSession = 3;
		xTaskNotify(GaurdTaskToObjectExecutionHandle, currentSessionL, eSetValueWithOverwrite);
		xSemaphoreTake(MutexHandles[currentSessionL], portMAX_DELAY);
		xSemaphoreGive(MutexHandles[currentSessionL]);
                 
                /*GetObservationUPDATEIFNEEDED() should never be called from an interrupt. The reason for this is because 
                this will imply needing to use a mutex to wait for the updateTask to finish the update. However I cant use mutexes from 
                an interrupt nor can I preempt the interrupt to wait for the update to finish anyways.
                 Therefor only call the GetObservation() WITHOUT the update from an interrupt.*/
		//BaseType_t  xHigherPriorityTaskWoken = pdFALSE;
               // xTaskNotifyFromISR(GaurdTaskToObjectExecutionHandle, currentSessionL, eSetValueWithOverwrite, &xHigherPriorityTaskWoken);
		//portYIELD_FROM_ISR(xHigherPriorityTaskWoken); 
		//xSemaphoreTakeFromISR(MutexHandles[currentSessionL], &xHigherPriorityTaskWoken);
		//xSemaphoreGiveFromISR(MutexHandles[currentSessionL], &xHigherPriorityTaskWoken);
		//portYIELD_FROM_ISR(xHigherPriorityTaskWoken);
		//xQueuePeek(MutexHandles[currentSessionL], NULL, portMAX_DELAY);
		return Observation;
		//todo: return observation; I need a template for this somehow

		/* Set the notification value of the task referenced by xTask4Handle to 0xfff,
		but only if to do so would not overwrite the task's existing notification
		value before the task had obtained it (by a call to xTaskNotifyWait()
		or ulTaskNotifyTake()). */
		//if (xTaskNotify(RefreshObservationGaurdTask, currentSessionL, ); == pdPASS)

	}

}

template<class TObservationType>
inline TObservationType AEObservorInterpretorOutputType<TObservationType>::GetObservation()
{
	return Observation; 
}
template<class TObservationType>
inline TObservationType* AEObservorInterpretorOutputType<TObservationType>::GetObservationAddress()
{
	return &Observation;
}
 
template<class TObservationType>
inline AEObservorInterpretorOutputType<TObservationType>::AEObservorInterpretorOutputType()
{
}
