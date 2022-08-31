#include "AEEventBase.h"
#include "QueueArgStructures.h"
#include "AEPoolManager.h"
 


EventPoolSize_t AEEventBase::EvtIdStatic = 60000; // this default value should not be changed as it is used to check for error

EventPoolSize_t ENTEREvent::EvtIdStatic = ENTEREVENT_Id;
EventPoolSize_t EXITEvent::EvtIdStatic = EXITEVENT_Id;

AEEventDiscriminator_t AEEventDiscriminator_t::EnterEvtInstance(Enter_Sig);
AEEventDiscriminator_t AEEventDiscriminator_t::ExitEvtInstance(Exit_Sig);
AEEventDiscriminator_t AEEventDiscriminator_t::UpdateEvtInstance(Update_Sig);
AEEventDiscriminator_t AEEventDiscriminator_t::ActivateFSMEvtInstance(ActivateFSM_Sig);
AEEventDiscriminator_t AEEventDiscriminator_t::DeActivateFSMEvtInstance(DeActivateFSM_Sig);

MAKE_SINGLETON_PUT_IN_CPP(ENTEREvent)
MAKE_SINGLETON_PUT_IN_CPP(EXITEvent)


bool isInitialized;
void AEEventBase::init(EventPoolSize_t evtId)
{
	if (!isInitialized)
	{  
		isInitialized = true;
	}
}



AEEventBase * AEEventBase::GetNewEvt()
{
	//get a pointer to a unused instance of this event type from the poolmanager
	 
	return nullptr;
}

void AEEventBase::DecrementRefCounter()
{
	//arg1 evtId. arg2 poolid
	//the gaurd task for decrementing a reference counter is needed
	//because AO of varying priorities may be calling decrement
	//at the same time
	TwoIntArgStructure args(this->GetEvtID(),this->poolId);
	
	xQueueSend(PoolManager->queueToDecrement, &args, 0);
}

void AEEventBase::Reset()
{
	//TODO this->ResetlambdaForDerived() 
	this->RefCounter = 0;
	this->isInUse = false;
}


