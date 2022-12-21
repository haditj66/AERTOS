#pragma once

#include "FreeRTOS.h"

#include "AEAO.h"
#include "InlineISubscribeable.h"

#include "AEEventBase.h"

//only FSms should have access to AEObjects
//AECHANGED:
//#include "AEObjects.h"
//AECHANGEDDONE:

#include "AESet.h"


template<TemplateFor_SimpleFSM>
	class AESimpleFSM : public AEAO
	{
		friend class AEPublishSubscribeManager;
		//template<TemplateFor_SimpleFSM_NoDefaults>
		//friend class AESimpleFSM;

	public:

		void CheckIfConfiguredProperly() const override
		{
			//assert everything I need to assert here.
		}

		//function pointer type to a state of a FSM AO  
		typedef TDerivedType TypeOfThisFSM;
		typedef AETransitionType(*StateFuncPtr)(TypeOfThisFSM* const thisFSM, AEEventDiscriminator_t const * const evt);

		TSubMachine1* SubMachine1;
		TSubMachine2* SubMachine2;
		TSubMachine3* SubMachine3;

		AESimpleFSM() {
			isInitialized = false;
			CurrentTimerPeriodInMilli = 0;
			UpdateTimePaused = false;

			HasBeenStartedInTheInitalStateYet = false;

			ActiveType = AEFSMActiveTypeEnum::RESET_TO_ACTIVATE;
			for (uint16_t i = 0; i < _MAX_NumOfAllEvents; i++)
			{
				EventsThatIWasSubscribedToWhenPaused[i] = false;
			}

			static AESet<uint16_t, 3> MyActivatedSubmachinesL(0xffff);
			MyActivatedSubmachines = &MyActivatedSubmachinesL;
			static AESet<uint16_t, 3> MyBaseFSMsL(0xffff);
			MyBaseFSMs = &MyBaseFSMsL;

			BufferSavedSubmachinesPausedIndex = 0;

			Active = false;

			/*
			for (uint16_t i = 0; i < 3; i++)
			{
				AOIDThatAreMyActivatedSubmachine[i] = 0xffff;
				MyBaseFSMs[i] = 0xffff;
		}
		MyActivatedSubmachinesIndex = 0;
		MyBaseFSMsIndex = 0;
		*/
		}
		;

		void Init(bool isSubmachine = false,
			AEPriorities priorityOfThis = AEPriorities::MediumPriority,
			uint16_t intialialTimerPeriodIfAny = 1,
			TSubMachine1* SubMachine1 = nullptr,
			TSubMachine2* SubMachine2 = nullptr,
			TSubMachine3* SubMachine3 = nullptr);

		void AddSubmachine1(TSubMachine1* SubMachine1);
		void AddSubmachine2(TSubMachine2* SubMachine2);
		void AddSubmachine3(TSubMachine3* SubMachine3);


		void StartUpdateTimer(uint16_t timerPeriodInMilli);
		void StopUpdateTimer();

		void SetActiveType(AEFSMActiveTypeEnum ActiveType);
		AEFSMActiveTypeEnum GetActiveType();

		template <class Tevt>
			void Subscribe() const;
		template <uint16_t Tevt>
			void Subscribe() const;
		template <class Tevt>
			void UnSubscribe() const;
		template<uint16_t Tevt>
			void UnSubscribe() const;

		template<class TEventToSubscribeTo>
			void SubscribeEvtFromISR();
		template<class TEventToUnSubscribeTo>
			void UnSubscribeEvtFromISR();
		template<uint16_t Tevt>
			void SubscribeEvtFromISR();
		template<uint16_t Tevt>
			void UnSubscribeEvtFromISR();

		template <class TSubmachine>
			void ActivateSubmachine(TSubmachine* submachine); 
		void ActivateSubmachine(uint16_t submachine);
		template <class TSubmachine>
			void DeActivateSubmachine(TSubmachine* submachine);
		void DeactivateAllSubmachines();

		bool DoAnySubmachinesSubscribeToEvent(EventPoolSize_t evtId);

	protected:

		bool IsSubmachine;

		bool HasBeenStartedInTheInitalStateYet;


		AESet<uint16_t, 3>* MyActivatedSubmachines;
		AESet<uint16_t, 3>* MyBaseFSMs;
		uint16_t BufferSavedSubmachinesPaused[3];
		uint16_t BufferSavedSubmachinesPausedIndex;
		//uint16_t MyActivatedSubmachines[3];
		//uint8_t MyActivatedSubmachinesIndex; 
		//uint16_t MyBaseFSMs[3];
		//uint8_t MyBaseFSMsIndex;

		bool Active;
		bool IsAlreadyActive() { return Active; }
		;

		template<class TSubmachine>
			void SetSubmachine(TSubmachine* submachine);
		template<class TSubmachine>
			void UnSetSubmachine(TSubmachine* submachine);
		template<class TSubmachine>
			void SetBaseFSM(TSubmachine* submachine);
		template<class TSubmachine>
			void UnSetBaseFSM(TSubmachine* submachine);

		void EnterInitialState();

	

		AEFSMActiveTypeEnum ActiveType;
		bool EventsThatIWasSubscribedToWhenPaused[_MAX_NumOfAllEvents];
		bool UpdateTimePaused;

		uint16_t CurrentTimerPeriodInMilli;
		TimerHandle_t xTimerForUpdatingStates;
		static void CallBackToUpdateTimer(TimerHandle_t  timer);

		StateFuncPtr StateToTransitionTo;

		virtual StateFuncPtr InitialState() = 0;

		virtual void Exit() {}
		;

		void UnSubscribeFromAllCurrentlySubbedEvents(bool fromAPause = true);
		void SubscribeTOAllCurrentlySubbedEvents();
		void PauseUpdateTimer();
		void UnPauseUpdateTimer();
	private:

		bool isInitialized;

		StateFuncPtr CurrentState;

		TaskHandle_t GaurdTaskToExecuteForEvtHandle;
		void GaurdTaskToExecuteForEvt(void* pvParameters);


	};

/*
template<TemplateFor_SimpleFSM>
inline AESimpleFSM<TemplateFor_SimpleFSM_Args>::AESimpleFSM()
{



}
*/

///starts the timer for the update of that state
///timerPeriodInMilli: the timer period in milliseconds
template<TemplateFor_SimpleFSM_NoDefaults>
	inline void AESimpleFSM<TemplateFor_SimpleFSM_Args>::StartUpdateTimer(uint16_t timerPeriodInMilli)
	{

		//if new timer period is different than old one, change the period.
		if (CurrentTimerPeriodInMilli != timerPeriodInMilli)
		{
			CurrentTimerPeriodInMilli = timerPeriodInMilli;
			uint16_t periodInTicks = pdMS_TO_TICKS(CurrentTimerPeriodInMilli);
			configASSERT(periodInTicks >= 1);


			xTimerChangePeriod(xTimerForUpdatingStates,
				periodInTicks,
				0);
		}

		xTimerStart(xTimerForUpdatingStates, 0);
	}

template<TemplateFor_SimpleFSM_NoDefaults>
	inline void AESimpleFSM<TemplateFor_SimpleFSM_Args>::StopUpdateTimer()
	{
		xTimerStop(xTimerForUpdatingStates, 0);
	}



template<TemplateFor_SimpleFSM_NoDefaults>
	inline void AESimpleFSM<TemplateFor_SimpleFSM_Args>::CallBackToUpdateTimer(TimerHandle_t  timer)
	{
		// send an update event to this AO
		uint32_t AOId = (uint32_t)pvTimerGetTimerID(timer);
		AEEventDiscriminator_t* ptrToUpdate = &AEEventDiscriminator_t::UpdateEvtInstance;
		xQueueSend(AEAO::AllAO[AOId]->queueExecuteForEvt, &ptrToUpdate, 0);

	}


template<TemplateFor_SimpleFSM_NoDefaults>
	inline void AESimpleFSM<TemplateFor_SimpleFSM_Args>::EnterInitialState()
	{
		AE_UpdateALLSPBSubscriptions
			AE_UpdateALLWritableVariables
			this->isCurrentlyExecuting = true;
		CurrentState = InitialState();
		this->isCurrentlyExecuting = false;
		CurrentState(static_cast<TDerivedType*>(this), &AEEventDiscriminator_t::EnterEvtInstance);
		HasBeenStartedInTheInitalStateYet = true;
		Active = true;
	}


template<TemplateFor_SimpleFSM_NoDefaults>
	inline void AESimpleFSM<TemplateFor_SimpleFSM_Args>::AddSubmachine1(TSubMachine1* subMachine1)
	{
		SubMachine1 = subMachine1;
	}
template<TemplateFor_SimpleFSM_NoDefaults>
	inline void AESimpleFSM<TemplateFor_SimpleFSM_Args>::AddSubmachine2(TSubMachine2* subMachine2) {
		SubMachine2 = subMachine2;
	}
template<TemplateFor_SimpleFSM_NoDefaults>
	inline void AESimpleFSM<TemplateFor_SimpleFSM_Args>::AddSubmachine3(TSubMachine3* subMachine3)
	{
		SubMachine3 = subMachine3;
	}


template<TemplateFor_SimpleFSM_NoDefaults>
	inline void AESimpleFSM<TemplateFor_SimpleFSM_Args>::Init(bool isSubmachine, AEPriorities priorityOfThis, uint16_t intialialTimerPeriodIfAny, TSubMachine1 * subMachine1, TSubMachine2 * subMachine2, TSubMachine3 * subMachine3)
	{
		_Priority = priorityOfThis;
	
	
		this->queueExecuteForEvt = xQueueCreate(20, sizeof(AEEventDiscriminator_t*));
		xTaskCreate([](void* p) {
				static_cast<AESimpleFSM*>(p)->GaurdTaskToExecuteForEvt(nullptr); 
			},
			"GaurdTaskToExecuteForEvt",
			configMINIMAL_STACK_SIZE,
			this,
			AOPRIORITYMEDIUM,
			&GaurdTaskToExecuteForEvtHandle);

		IsSubmachine = isSubmachine;
		Active = !isSubmachine;

		//subscribe to activation and deactivation events 
		//this->SubscribeEvtFromISR<ActivateFSM_Sig>();
		//this->SubscribeEvtFromISR<DeActivateFSM_Sig>();

		//create the timer used for updating
		CurrentTimerPeriodInMilli = intialialTimerPeriodIfAny;


		//I need to convert the period to ticks  s/t  .0005
		uint16_t periodInTicks = pdMS_TO_TICKS(CurrentTimerPeriodInMilli); // CurrentTimerPeriodInMilli / configTICK_RATE_HZ;

		//asser that the periodInTicks  is greater than 1
		configASSERT(periodInTicks >= 1);

		xTimerForUpdatingStates = xTimerCreate
		( /* Just a text name, not used by the RTOS
		  kernel. */
			"Timer",
			/* The timer period in ticks, must be
			greater than 0. */
			periodInTicks,
			/* The timers will auto-reload themselves
			when they expire. */
			pdTRUE,
			/* The ID is used to store the AO id*/
			(void *)this->GetAO_ID(),
			/* Each timer calls the same callback when
			it expires. */
			AESimpleFSM<TemplateFor_SimpleFSM_Args>::CallBackToUpdateTimer//[](void* p) {static_cast<AESimpleFSM*>(p)->CallBackToUpdateTimer(static_cast<AESimpleFSM*>(p)->xTimerForUpdatingStates); }
		);
		StopUpdateTimer();

		//assert that if a utility was specified, that a nullptr was not passed

		if (!TypeChecker::IsAENullFSMUtility<TSubMachine1>())
		{
			//configASSERT(subMachine1 != nullptr);

			SubMachine1 = subMachine1;
			//set this AO as the exclusive possessor
			//UtilityINeedPossessionOf1->SetExclusivePossessor(this);
		}
		if (!TypeChecker::IsAENullFSMUtility<TSubMachine2>())
		{
			//configASSERT(subMachine2 != nullptr);

			SubMachine2 = subMachine2;
			//UtilityINeedPossessionOf2->SetExclusivePossessor(this);
		}
		if (!TypeChecker::IsAENullFSMUtility<TSubMachine3>())
		{
			//configASSERT(subMachine3 != nullptr);

			SubMachine3 = subMachine3;
			//UtilityINeedPossessionOf3->SetExclusivePossessor(this);
		}

		isInitialized = true;

	}

template<TemplateFor_SimpleFSM_NoDefaults>
	inline void AESimpleFSM<TemplateFor_SimpleFSM_Args>::GaurdTaskToExecuteForEvt(void * pvParameters)
	{
		AEEventDiscriminator_t* evt;

		//assert that init function was called
		configASSERT(isInitialized == true);


		//get the initial transition to the first state.
		//But only do this if this is NOT a SubMachine
		if (IsSubmachine == false)
		{
			EnterInitialState();
		}

		for (;;)
		{
			xQueueReceive(this->queueExecuteForEvt, &evt, portMAX_DELAY);

			auto evtId = evt->GetEvtID();

			// I need to be sure that this event is not already being handled by a submachine that is being set
			//or by a submachine of that submachine. If there is one, then do nothing to handle the event.
			//but only do this for events that are of ID lower than _MAX_NumOfAllEvents. exit, enter and update events post directly to the right AO so they are safe.
			bool EvtHandledBySubmachine = false;
			if (evtId < _MAX_NumOfAllEvents)
			{
				if (MyActivatedSubmachines->Size() > 0)
				{ 

					if (this->DoAnySubmachinesSubscribeToEvent(evtId))
					{
						EvtHandledBySubmachine = true;
					}
				}

			}


			if (EvtHandledBySubmachine == false)
			{

				AETransitionType typeOfTransition;
				//if this is a call for activation, do this instead
				if (evtId == ActivateFSM_Sig)
				{
					typeOfTransition = ACTIVATE;
				}
				else if (evtId == DeActivateFSM_Sig)
				{
					//if here then I know that this deactivation came from the request of the base fsm
					typeOfTransition = DEACTIVE;
				}
				else
				{
					//call the current state this AO is in passing the event to it. 
					AE_UpdateALLSPBSubscriptions
						AE_UpdateALLWritableVariables
						this->isCurrentlyExecuting = true;
					typeOfTransition = CurrentState(static_cast<TDerivedType*>(this), evt);
					this->isCurrentlyExecuting = false;
				}



				if (typeOfTransition == TRANSITION)
				{
					//check that all utilities needed for the new state are of either already in possesion
					//of this AO or are free for this AO to take possession of or are a utility-as-a-service
					//in which case they dont need to be taken as possession. 


					//TODO: there is a timing issue here where a baseFSM will check if a  submachine subscribes
					//to a incoming event right when the submachine transitions from one state to another thus
					// un subscribing then resubscribing upon entering. To workaround this for now just make sure 
					// Always NOT unsubscribe from an event if the next state will just resubscribe to it.
							//--to solve this timing issue, events that are subscribed to are held in a pending state
			//when they leave the enter event. then when exit event runs, the events that are unsubscribed 
			//to are also held in a pending state. the events are then 


			//run the exit event for the state I am leaving from
					AETransitionType transType = CurrentState(static_cast<TDerivedType*>(this), &AEEventDiscriminator_t::ExitEvtInstance);
					//assert that the exit event may not return a TRANSITION to another state
					configASSERT(transType != TRANSITION);

					//change to the new current state.
					CurrentState = StateToTransitionTo;

					//start the enter event for this new transition state
					AETransitionType transType2 = CurrentState(static_cast<TDerivedType*>(this), &AEEventDiscriminator_t::EnterEvtInstance);
					//assert that the enter event may not return a TRANSITION to another state
					configASSERT(transType2 != TRANSITION);

				}

				else if (typeOfTransition == DEACTIVE)
				{
					if (this->ActiveType == RESET_TO_ACTIVATE)
					{
						//deactivate with reset

						// I need to NOT transition to the default state yet and to just exit the current state
						AETransitionType transType = CurrentState(static_cast<TDerivedType*>(this), &AEEventDiscriminator_t::ExitEvtInstance);
						configASSERT(transType != TRANSITION);

						//make sure all events are completely unsubscribed to and that the update timer is off
						this->UnSubscribeFromAllCurrentlySubbedEvents(false);
						xTimerStop(xTimerForUpdatingStates, 0);


						//deactivate all submachines as well 
						this->DeactivateAllSubmachines();

						//empty the current event queue so that no events in queue run later on.
						xQueueReset(this->queueExecuteForEvt);

					}
					if (this->ActiveType == PAUSE_TO_ACTIVATE)
					{
						//deactivate with pause
						// I need to unsubscribe from the currently subscribed events so to make sure this 
						//FSM does not respond to anything. these events are stored in an array
						this->UnSubscribeFromAllCurrentlySubbedEvents();

						//deactivate all submachines but save the ones currently active so you can reactivate
						//them later
						auto lamToSave = [](void* thisptr, uint16_t aoId) {
							static_cast<AESimpleFSM*>(thisptr)->BufferSavedSubmachinesPaused[static_cast<AESimpleFSM*>(thisptr)->BufferSavedSubmachinesPausedIndex] = aoId;
							static_cast<AESimpleFSM*>(thisptr)->BufferSavedSubmachinesPausedIndex++;
						};
						this->MyActivatedSubmachines->ForEach(this, lamToSave);
						this->DeactivateAllSubmachines();

						//pause the update timer
						this->PauseUpdateTimer();

					}

					//exit the state machine handle
					Exit();

					this->Active = false;

					//deactivate all of the submachines of this fsm as well
					auto lamToAccessDeactivation = [](void* thisBaseSubmachine, uint16_t ItsSubmachineIds) {
						ForUseInPrivateDeactivation(static_cast<AESimpleFSM*>(thisBaseSubmachine), (AESimpleFSM*)(AEAO::AllAO[ItsSubmachineIds]));
					};
					MyActivatedSubmachines->ForEach(this, lamToAccessDeactivation);
				}

				else if (typeOfTransition == ACTIVATE)
				{

					if (this->ActiveType == RESET_TO_ACTIVATE)
					{
						//activate with reset

						//start the initial state and enter the state so to reset this fsm
						EnterInitialState();

					}
					if (this->ActiveType == PAUSE_TO_ACTIVATE)
					{
						//activate with pause

						if (HasBeenStartedInTheInitalStateYet == false)
						{
							//if this is the first activation then I need to start the initial start thing first
							EnterInitialState();
						}

						//reactivate the submachines that were activated before the pause
						for (uint16_t i = 0; i < BufferSavedSubmachinesPausedIndex; i++)
						{
							ActivateSubmachine(BufferSavedSubmachinesPaused[i]);
						}
						BufferSavedSubmachinesPausedIndex = 0;

						//subscribe to all events that were previously unsubscribed to
						this->SubscribeTOAllCurrentlySubbedEvents();


						//unpause the update timer
						this->UnPauseUpdateTimer();
					}
					Active = true;
				}
			
			}



			if (evt->type == 1)
			{
				evt->evt->DecrementRefCounter();
			}
		}
	}



template<TemplateFor_SimpleFSM_NoDefaults>
	inline bool AESimpleFSM<TemplateFor_SimpleFSM_Args>::DoAnySubmachinesSubscribeToEvent(EventPoolSize_t evtId)
	{
		if (MyActivatedSubmachines->Size() == 0)
		{
			return false;
		}

		return MyActivatedSubmachines->ForEachIsAnyTrueWithItem(evtId,
			[](uint16_t evtIDarg, uint16_t submachineAOId) {
		
				//see if this submachine subscribes to the event and if any of its submachines subscribe
				if (PublishSubscribeManager->IsAOSubscribedToEvent(submachineAOId, evtIDarg) == true)
				{
					return true;
				}
		
				if (((AESimpleFSM*)AEAO::AllAO[submachineAOId])->DoAnySubmachinesSubscribeToEvent(evtIDarg) == true)
				{
					return true;
				}
				//see if any of its submachines of submachines subscribe
				return false;

			});
	 
	}

//only events that are less than _MAX_NumOfAllEvents should be subscribed 
//or unsubscribed to. events passed then are always considered to be subbed to.

template<TemplateFor_SimpleFSM_NoDefaults>
	template<class Tevt>
		inline void AESimpleFSM<TemplateFor_SimpleFSM_Args>::Subscribe() const
		{ 

			_InlineSubscribe<Tevt>(this->GetAO_ID());
		}

template<TemplateFor_SimpleFSM_NoDefaults>
	template <uint16_t Tevt>
		inline void AESimpleFSM<TemplateFor_SimpleFSM_Args>::Subscribe() const
		{
			_InlineSubscribe<Tevt>(this->GetAO_ID());
		}
;

template<TemplateFor_SimpleFSM_NoDefaults>
	template<class Tevt>
		inline void AESimpleFSM<TemplateFor_SimpleFSM_Args>::UnSubscribe() const
		{
			_InlineUnSubscribe<Tevt>(this->GetAO_ID());
		}

template<TemplateFor_SimpleFSM_NoDefaults>
	template<uint16_t Tevt>
		inline void AESimpleFSM<TemplateFor_SimpleFSM_Args>::UnSubscribe() const
		{
			_InlineUnSubscribe<Tevt>(this->GetAO_ID());
		}

template<TemplateFor_SimpleFSM_NoDefaults>
	template<class TEventToSubscribeTo>
		inline void AESimpleFSM<TemplateFor_SimpleFSM_Args>::SubscribeEvtFromISR()
		{
			_InlineSubscribeFROMISR<TEventToSubscribeTo>(this->GetAO_ID());

		}

template<TemplateFor_SimpleFSM_NoDefaults>
	template<class TEventToUnSubscribeTo>
		inline void AESimpleFSM<TemplateFor_SimpleFSM_Args>::UnSubscribeEvtFromISR()
		{
			_InlineUnSubscribeFROMISR<TEventToUnSubscribeTo>(this->GetAO_ID());
		}

template<TemplateFor_SimpleFSM_NoDefaults>
	template<uint16_t Tevt>
		inline void AESimpleFSM<TemplateFor_SimpleFSM_Args>::SubscribeEvtFromISR()
		{
			_InlineSubscribeFROMISR<Tevt>(this->GetAO_ID());

		}

template<TemplateFor_SimpleFSM_NoDefaults>
	template<uint16_t Tevt>
		inline void AESimpleFSM<TemplateFor_SimpleFSM_Args>::UnSubscribeEvtFromISR()
		{
			_InlineUnSubscribeFROMISR<Tevt>(this->GetAO_ID());
		}



template<TemplateFor_SimpleFSM_NoDefaults> 
	inline void AESimpleFSM<TemplateFor_SimpleFSM_Args>::ActivateSubmachine(uint16_t submachine)
	{
		ActivateSubmachine(AEAO::AllAO[submachine]);
	}

template<TemplateFor_SimpleFSM_NoDefaults>
	template<class TSubmachine>
		inline void AESimpleFSM<TemplateFor_SimpleFSM_Args>::ActivateSubmachine(TSubmachine* submachine)
		{
			//static_assert(std::is_convertible<TSubmachine*, AESimpleFSM*>::value, "AO you are trying to activate must ");
			//auto ikl=static_cast<AESimpleFSM*>(submachine);
			//check that the fsm has not already been activated, perhaps from a different fsm
			if (((AESimpleFSM*)submachine)->IsAlreadyActive() == false)
			{
				//Post an Activate event directly to that AO.
				this->PostEvtToAOToTheFront(submachine->GetAO_ID(), &AEEventDiscriminator_t::ActivateFSMEvtInstance);

				//set this AO as a submachine
				SetSubmachine(submachine);

				//((AESimpleFSM*)submachine)->Active = true;

			}
			else
			{
				//if it's already active then I jest need to set it as a submachine and not try to activate it
				SetSubmachine(submachine);
			}


		}



template<class TBasemachine, class TSubmachineToDeactivate>
	static void ForUseInPrivateDeactivation(TBasemachine* x, TSubmachineToDeactivate* y)
	{
		x->DeActivateSubmachine(y);
	}
;


template<TemplateFor_SimpleFSM_NoDefaults>
	template<class TSubmachine>
		inline void AESimpleFSM<TemplateFor_SimpleFSM_Args>::DeActivateSubmachine(TSubmachine* submachine)
		{
			//check that the fsm is activated
			if (((AESimpleFSM*)submachine)->IsAlreadyActive() == true)
			{
				// I need to check that there are no other fsms that possess this fsm. 
				if (((AESimpleFSM*)submachine)->MyBaseFSMs->Size() <= 1)
				{
					//Post an Activate event directly to that AO.
					this->PostEvtToAOToTheFront(submachine->GetAO_ID(), &AEEventDiscriminator_t::DeActivateFSMEvtInstance);

					//but also deactivate ALL submachines that that submachine has
					((AESimpleFSM*)submachine)->DeactivateAllSubmachines();

					//unset this AO as a submachine
					UnSetSubmachine(submachine);

					//NOT THREAD SAFE
					//((AESimpleFSM*)submachine)->Active = false;

				}
				else
				{
					//if there is a fsm still in possesion, then just unset this fsm 
					UnSetSubmachine(submachine);
				}

			}
			else
			{
				//if it's already deactive then just unset submachine 
				UnSetSubmachine(submachine);

				//((AESimpleFSM*)submachine)->Active = false;
			}



		}

template<TemplateFor_SimpleFSM_NoDefaults>
	inline void AESimpleFSM<TemplateFor_SimpleFSM_Args>::DeactivateAllSubmachines()
	{
		auto lamToAccessDeactivation = [](void* x, uint16_t aoId) {
			ForUseInPrivateDeactivation(static_cast<AESimpleFSM*>(x), AEAO::AllAO[aoId]);
		};
		this->MyActivatedSubmachines->ForEach(this, lamToAccessDeactivation);
	}


template<TemplateFor_SimpleFSM_NoDefaults>
	template<class TSubmachine>
		inline void AESimpleFSM<TemplateFor_SimpleFSM_Args>::SetSubmachine(TSubmachine* submachine)
		{
			//configASSERT(MyActivatedSubmachinesIndex < 3); 
			//MyActivatedSubmachines[MyActivatedSubmachinesIndex] = iDOfSubmachine;
			MyActivatedSubmachines->Insert(submachine->GetAO_ID());
 
			//tell that AO to set me as one of its base FSM
			((AESimpleFSM*)submachine)->SetBaseFSM(this);

		}

template<TemplateFor_SimpleFSM_NoDefaults>
	template<class TSubmachine>
		inline void AESimpleFSM<TemplateFor_SimpleFSM_Args>::UnSetSubmachine(TSubmachine* submachine)
		{
			/*
			configASSERT(MyActivatedSubmachinesIndex > -1 );
			bool SubmachineFound = false;
			for (uint8_t i = 0; i < 3; i++)
			{
				if (true)
				{
					MyActivatedSubmachines[MyActivatedSubmachinesIndex] = iDOfSubmachine;
			}

		}
		MyActivatedSubmachines[MyActivatedSubmachinesIndex] = iDOfSubmachine;
		*/
			MyActivatedSubmachines->Remove(submachine->GetAO_ID());

			//tell that AO to UNset me as one of its base FSM
			((AESimpleFSM*)submachine)->UnSetBaseFSM(this);

			//MyActivatedSubmachinesIndex++;
		}

template<TemplateFor_SimpleFSM_NoDefaults>
	template<class TSubmachine>
		inline void AESimpleFSM<TemplateFor_SimpleFSM_Args>::SetBaseFSM(TSubmachine* submachine)
		{
			MyBaseFSMs->Insert(submachine->GetAO_ID());
		}

template<TemplateFor_SimpleFSM_NoDefaults>
	template<class TSubmachine>
		inline void AESimpleFSM<TemplateFor_SimpleFSM_Args>::UnSetBaseFSM(TSubmachine* submachine)
		{
			MyBaseFSMs->Remove(submachine->GetAO_ID());
		}





template<TemplateFor_SimpleFSM_NoDefaults>
	inline void AESimpleFSM<TemplateFor_SimpleFSM_Args>::UnSubscribeFromAllCurrentlySubbedEvents(bool fromAPause)
	{
		//go through all events and unsubscribe from all events EXCEPT for:
		//enter
		//exit
		//update
		//ActivateFSM
		//DeActivateFSM
		//these are all above the _MAX_NumOfAllEvents enum value
		for (uint16_t i = 0; i < _MAX_NumOfAllEvents; i++)
		{
			if (PublishSubscribeManager->EventSubscribers[i][this->GetAO_ID()] == true)
			{
				if (fromAPause == true)
				{
					EventsThatIWasSubscribedToWhenPaused[i] = true;
				}
				PublishSubscribeManager->EventSubscribers[i][this->GetAO_ID()] = false;
			}

		}

	}

template<TemplateFor_SimpleFSM_NoDefaults>
	inline void AESimpleFSM<TemplateFor_SimpleFSM_Args>::SubscribeTOAllCurrentlySubbedEvents()
	{
		//subscribe to all events that were unsubscribed to when there was a pause
		for (uint16_t i = 0; i < _MAX_NumOfAllEvents; i++)
		{
			if (EventsThatIWasSubscribedToWhenPaused[i] = true)
			{
				PublishSubscribeManager->EventSubscribers[i][this->GetAO_ID()] = true;
				EventsThatIWasSubscribedToWhenPaused[i] = false;
			}

		}

	}

template<TemplateFor_SimpleFSM_NoDefaults>
	inline void AESimpleFSM<TemplateFor_SimpleFSM_Args>::PauseUpdateTimer()
	{
		//this will pause the timer only if it is active
		if (xTimerIsTimerActive(xTimerForUpdatingStates) != pdFALSE)
		{
			//TODO: first maybe I need to grab the ticks remaining for when there is an unpause?
			//auto xRemainingTime = xTimerGetExpiryTime(xTimerForUpdatingStates) - xTaskGetTickCount();
			xTimerStop(xTimerForUpdatingStates, 0);

			UpdateTimePaused = true;
		}
		else
		{
			UpdateTimePaused = false;
		}

	}

template<TemplateFor_SimpleFSM_NoDefaults>
	inline void AESimpleFSM<TemplateFor_SimpleFSM_Args>::UnPauseUpdateTimer()
	{
		//Only unpause the timer if it was paused in the first place
		if (UpdateTimePaused == true)
		{
			//TODO: grab ticks remaining and fulfill at least from there?

			xTimerStart(xTimerForUpdatingStates, 0);

			UpdateTimePaused = false;
		}
		else
		{
			UpdateTimePaused = false;
		}

	}

template<TemplateFor_SimpleFSM_NoDefaults>
	inline void AESimpleFSM<TemplateFor_SimpleFSM_Args>::SetActiveType(AEFSMActiveTypeEnum activeType)
	{
		ActiveType = activeType;
	}

template<TemplateFor_SimpleFSM_NoDefaults>
	inline AEFSMActiveTypeEnum AESimpleFSM<TemplateFor_SimpleFSM_Args>::GetActiveType()
	{
		return ActiveType;
	}