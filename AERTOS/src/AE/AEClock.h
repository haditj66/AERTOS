#pragma once
#include <cstdint>
#include "FreeRTOS.h"

#include "AEUtils.h"

#include "AELoop.h"




//#include "AEObservorSensor.h"
//#include "AEObservorInterpretorBase.h"
//
//#include "AE_TDUAsService.h"
//#include "AETDUAsPossession.h"



#include "task.h"

#include <cmath>

static int anfoainfo = 84;

//look for the index that has the first null pointer, then fill that spot 
#define  AECLOCKSETOBSERVOR(num)	case AEClock_PrescalerEnum::PRESCALER##num:\
{\
if (observor->GetMyObservorType() & ObservorType::Sensor)\
{\
	configASSERT(NumOfSensorsIWillBeSetTo_Prescale##num > 0);\
	for (uint16_t i = 0; i < NumOfSensorsIWillBeSetTo_Prescale##num; i++)\
	{\
		if (SensorObservorsIamSetToP##num[i] == NULL)\
		{\
			SensorObservorsIamSetToP##num[i] = (TAEObservorSensor*)observor;\
			break;\
		}\
	}\
}\
else if (observor->GetMyObservorType() & ObservorType::Interpretors)\
{\
	configASSERT(NumOfInterpretorsIWillBeSetTo_Prescale##num > 0);\
	for (uint16_t i = 0; i < NumOfInterpretorsIWillBeSetTo_Prescale##num; i++)\
	{\
		if (InterpretorsIamSetToP##num[i] == NULL)\
		{\
			InterpretorsIamSetToP##num[i] = (TAEObservorInterpretorBase*)observor;\
			break;\
		}\
	}\
}\
observor->FrequencyIRefreshAt = _FrequencyOfClock / num; \
break;\
}


#define AECLOCKSET_TDUs(num) 	case AEClock_PrescalerEnum::PRESCALER##num:\
	{\
	configASSERT(NumOfTDUsIWillBeSetTo_Prescale##num > 0);\
	for (uint16_t i = 0; i < NumOfTDUsIWillBeSetTo_Prescale##num; i++)\
	{\
		if (UpdateTasksForTDUsP##num[i] == NULL)\
		{\
			UpdateTasksForTDUsP##num[i] = &TDUToSet->GaurdUpdateTask;\
			break;\
		}\
	}\
	}\
	break;


#define INITIALIZELISTSASNULL(num) \
for (uint16_t i = 0; i < NumOfSensorsIWillBeSetTo_Prescale##num; i++)\
{\
	SensorObservorsIamSetToP##num[i] = NULL;\
}\
for (uint16_t i = 0; i < NumOfInterpretorsIWillBeSetTo_Prescale##num; i++)\
{\
	InterpretorsIamSetToP##num[i] = NULL;\
}\
for (uint16_t i = 0; i < NumOfTDUsIWillBeSetTo_Prescale##num; i++)\
{\
	UpdateTasksForTDUsP##num[i] = NULL;\
}



enum AEClock_PrescalerEnum
{
	PRESCALER1 = 1,
	PRESCALER2 = 2,
	PRESCALER4 = 4,
	PRESCALER8 = 8,
	PRESCALER16 = 16,
	PRESCALER32 = 32,
	PRESCALER64 = 64

};

TEMPLATEFOR_AEClock
class AEClock
{
	friend class AELoop;

public:


	PropertyGet(float, FrequencyOfClock)
		 

		uint16_t Priority;

	//frequencyOfClock: for example 1000 is a period of 1 milli
	//isSoftwareTimerTicked: will you be ticking this through your own clock callback. if false then you dont need to provide the callback.
	//funcPtrForImplOfTick: the callback you need to call the clock.tick in
	AEClock(float frequencyOfClock,  TimerCallbackFunction_t funcPtrForImplOfTick) : _FrequencyOfClock(frequencyOfClock)
	{
          
           
			//The period of the software timer in ticks needs to be divisible with configTICK_RATE_HZ to get an accurate tick period instead 
			//of one the user was not expecting 
			//configASSERT(fmod(configTICK_RATE_HZ ,frequencyOfClock) == 0);

			// I need to create a software timer that will do the tick for this clock.
                  uint32_t ticks = (configTICK_RATE_HZ / frequencyOfClock) <= 1 ? 1 : (configTICK_RATE_HZ / frequencyOfClock);
			xTimerForClockTicks = xTimerCreate("T",				/* The text name assigned to the software timer - for debug only as it is not used by the kernel. */
				ticks,		                /* The period of the software timer in ticks. */
				pdTRUE,			/* xAutoReload is set to true */
				NULL,				/* The timer's ID is not used. */
				funcPtrForImplOfTick);/* The function executed when the timer expires. */
			xTimerReset(xTimerForClockTicks, portMAX_DELAY);

			//the function ptr for the tick cannot be null
			configASSERT(funcPtrForImplOfTick != nullptr);

			TicksFromTimer = true;
 

		_ConstructorInit();


	}

	AEClock(float frequencyOfClock) : _FrequencyOfClock(frequencyOfClock)
	{

		AEClock* pToThisClass = this;

		xTaskCreate([](void* p) {static_cast<AEClock*>(p)->TickWithoutTimerTask(nullptr); },
			"TickTaskHandleFromWithoutTimer", 100, pToThisClass, configTIMER_TASK_PRIORITY, &this->TickTaskHandleFromWithoutTimer);




		TicksFromTimer = false;
	}


	uint16_t GetClockId();
	
	template<class TAEObservorBase>
	void SetObservorToClock(TAEObservorBase* observor, AEClock_PrescalerEnum Prescaler = AEClock_PrescalerEnum::PRESCALER1);
	//void SetInterpretorObservorToClock(AEObservorSensor* observor); 

	template<class TAETDU>
	void SetTDUToClock(TAETDU TDUToSet, AEClock_PrescalerEnum Prescaler = AEClock_PrescalerEnum::PRESCALER1);

	template<class TAETDU, class TAESPBObservor>
		void SetTDUToSPBClock(TAETDU TDUToSet, TAESPBObservor* spbObservorToUpdateWith, float percentageOfDeltaRefresh);

	void SetAELoopToClock(AELoop* AELoop);

	void Tick();

	void TickWithoutTimer();
	


private: 
	 
	TimerHandle_t xTimerForClockTicks;

	TaskHandle_t TickTaskHandleFromWithoutTimer;
	void TickWithoutTimerTask(void* thisptr); 
	bool TicksFromTimer;

	bool _isClockIsOn;
	uint8_t TickCounter;

	uint16_t AELoopsIndex;
	TaskHandle_t* UpdateTasksForAELoops[MaxAELoopsPerClock];

	uint16_t ClockId;
	static uint16_t ClockIdIndex;

	uint16_t indexOfObservors;

	template<class TAETDU >
	void _SetTDUToClock(TAETDU TDUToSet, AEClock_PrescalerEnum Prescaler = AEClock_PrescalerEnum::PRESCALER1); 
	


	void _ConstructorInit() {


		TickCounter = 0;

		AELoopsIndex = 0;

		ClockId = ClockIdIndex + 1;
		ClockIdIndex++;

		//initialize all pointers as null
		INITIALIZELISTSASNULL(1)
			INITIALIZELISTSASNULL(2)
			INITIALIZELISTSASNULL(4)
			INITIALIZELISTSASNULL(8)
			INITIALIZELISTSASNULL(16)
			INITIALIZELISTSASNULL(32)
			INITIALIZELISTSASNULL(64)

	}



	TAEObservorSensor* SensorObservorsIamSetToP1[(NumOfSensorsIWillBeSetTo_Prescale1 == 0) + NumOfSensorsIWillBeSetTo_Prescale1];
	TAEObservorInterpretorBase* InterpretorsIamSetToP1[(NumOfInterpretorsIWillBeSetTo_Prescale1 == 0) + NumOfInterpretorsIWillBeSetTo_Prescale1];
	TaskHandle_t* UpdateTasksForTDUsP1[(NumOfTDUsIWillBeSetTo_Prescale1 == 0) + NumOfTDUsIWillBeSetTo_Prescale1];

	TAEObservorSensor* SensorObservorsIamSetToP2[(NumOfSensorsIWillBeSetTo_Prescale2 == 0) + NumOfSensorsIWillBeSetTo_Prescale2];
	TAEObservorInterpretorBase* InterpretorsIamSetToP2[(NumOfInterpretorsIWillBeSetTo_Prescale2 == 0) + NumOfInterpretorsIWillBeSetTo_Prescale2];
	TaskHandle_t* UpdateTasksForTDUsP2[(NumOfTDUsIWillBeSetTo_Prescale2 == 0) + NumOfTDUsIWillBeSetTo_Prescale2];

	TAEObservorSensor* SensorObservorsIamSetToP4[(NumOfSensorsIWillBeSetTo_Prescale4 == 0) + NumOfSensorsIWillBeSetTo_Prescale4];
	TAEObservorInterpretorBase* InterpretorsIamSetToP4[(NumOfInterpretorsIWillBeSetTo_Prescale4 == 0) + NumOfInterpretorsIWillBeSetTo_Prescale4];
	TaskHandle_t* UpdateTasksForTDUsP4[(NumOfTDUsIWillBeSetTo_Prescale4 == 0) + NumOfTDUsIWillBeSetTo_Prescale4];

	TAEObservorSensor* SensorObservorsIamSetToP8[(NumOfSensorsIWillBeSetTo_Prescale8 == 0) + NumOfSensorsIWillBeSetTo_Prescale8];
	TAEObservorInterpretorBase* InterpretorsIamSetToP8[(NumOfInterpretorsIWillBeSetTo_Prescale8 == 0) + NumOfInterpretorsIWillBeSetTo_Prescale8];
	TaskHandle_t* UpdateTasksForTDUsP8[(NumOfTDUsIWillBeSetTo_Prescale8 == 0) + NumOfTDUsIWillBeSetTo_Prescale8];

	TAEObservorSensor* SensorObservorsIamSetToP16[(NumOfSensorsIWillBeSetTo_Prescale16 == 0) + NumOfSensorsIWillBeSetTo_Prescale16];
	TAEObservorInterpretorBase* InterpretorsIamSetToP16[(NumOfInterpretorsIWillBeSetTo_Prescale16 == 0) + NumOfInterpretorsIWillBeSetTo_Prescale16];
	TaskHandle_t* UpdateTasksForTDUsP16[(NumOfTDUsIWillBeSetTo_Prescale16 == 0) + NumOfTDUsIWillBeSetTo_Prescale16];

	TAEObservorSensor* SensorObservorsIamSetToP32[(NumOfSensorsIWillBeSetTo_Prescale32 == 0) + NumOfSensorsIWillBeSetTo_Prescale32];
	TAEObservorInterpretorBase* InterpretorsIamSetToP32[(NumOfInterpretorsIWillBeSetTo_Prescale32 == 0) + NumOfInterpretorsIWillBeSetTo_Prescale32];
	TaskHandle_t* UpdateTasksForTDUsP32[(NumOfTDUsIWillBeSetTo_Prescale32 == 0) + NumOfTDUsIWillBeSetTo_Prescale32];

	TAEObservorSensor* SensorObservorsIamSetToP64[(NumOfSensorsIWillBeSetTo_Prescale64 == 0) + NumOfSensorsIWillBeSetTo_Prescale64];
	TAEObservorInterpretorBase* InterpretorsIamSetToP64[(NumOfInterpretorsIWillBeSetTo_Prescale64 == 0) + NumOfInterpretorsIWillBeSetTo_Prescale64];
	TaskHandle_t* UpdateTasksForTDUsP64[(NumOfTDUsIWillBeSetTo_Prescale64 == 0) + NumOfTDUsIWillBeSetTo_Prescale64];


	//TaskHandle_t* UpdateTasksAELoops[(NumOfTDUsIWillBeSetTo_Prescale1 == 0) + NumOfTDUsIWillBeSetTo_Prescale1];

};

TEMPLATEFORNoDefaults_AEClock// template<uint16_t NumOfSensorsIWillBeSetTo_Prescale1, uint16_t NumOfInterpretorsIWillBeSetTo_Prescale1, uint16_t NumOfTDUsIWillBeSetTo_Prescale1, uint16_t NumOfSensorsIWillBeSetTo_Prescale2, uint16_t NumOfInterpretorsIWillBeSetTo_Prescale2, uint16_t NumOfTDUsIWillBeSetTo_Prescale2, uint16_t NumOfSensorsIWillBeSetTo_Prescale4, uint16_t NumOfInterpretorsIWillBeSetTo_Prescale4, uint16_t NumOfTDUsIWillBeSetTo_Prescale4, uint16_t NumOfSensorsIWillBeSetTo_Prescale8, uint16_t NumOfInterpretorsIWillBeSetTo_Prescale8, uint16_t NumOfTDUsIWillBeSetTo_Prescale8, uint16_t NumOfSensorsIWillBeSetTo_Prescale16, uint16_t NumOfInterpretorsIWillBeSetTo_Prescale16, uint16_t NumOfTDUsIWillBeSetTo_Prescale16, uint16_t NumOfSensorsIWillBeSetTo_Prescale32, uint16_t NumOfInterpretorsIWillBeSetTo_Prescale32, uint16_t NumOfTDUsIWillBeSetTo_Prescale32, uint16_t NumOfSensorsIWillBeSetTo_Prescale64, uint16_t NumOfInterpretorsIWillBeSetTo_Prescale64, uint16_t NumOfTDUsIWillBeSetTo_Prescale64>
uint16_t AEClock<TEMPLATEFORParams_AEClock>
::ClockIdIndex = 1;


TEMPLATEFORNoDefaults_AEClock// template<uint16_t NumOfSensorsIWillBeSetTo_Prescale1, uint16_t NumOfInterpretorsIWillBeSetTo_Prescale1, uint16_t NumOfTDUsIWillBeSetTo_Prescale1, uint16_t NumOfSensorsIWillBeSetTo_Prescale2, uint16_t NumOfInterpretorsIWillBeSetTo_Prescale2, uint16_t NumOfTDUsIWillBeSetTo_Prescale2, uint16_t NumOfSensorsIWillBeSetTo_Prescale4, uint16_t NumOfInterpretorsIWillBeSetTo_Prescale4, uint16_t NumOfTDUsIWillBeSetTo_Prescale4, uint16_t NumOfSensorsIWillBeSetTo_Prescale8, uint16_t NumOfInterpretorsIWillBeSetTo_Prescale8, uint16_t NumOfTDUsIWillBeSetTo_Prescale8, uint16_t NumOfSensorsIWillBeSetTo_Prescale16, uint16_t NumOfInterpretorsIWillBeSetTo_Prescale16, uint16_t NumOfTDUsIWillBeSetTo_Prescale16, uint16_t NumOfSensorsIWillBeSetTo_Prescale32, uint16_t NumOfInterpretorsIWillBeSetTo_Prescale32, uint16_t NumOfTDUsIWillBeSetTo_Prescale32, uint16_t NumOfSensorsIWillBeSetTo_Prescale64, uint16_t NumOfInterpretorsIWillBeSetTo_Prescale64, uint16_t NumOfTDUsIWillBeSetTo_Prescale64>
uint16_t AEClock<TEMPLATEFORParams_AEClock>
::GetClockId()
{
	return ClockId;
}

TEMPLATEFORNoDefaults_AEClock//template<uint16_t NumOfSensorsIWillBeSetTo_Prescale1, uint16_t NumOfInterpretorsIWillBeSetTo_Prescale1, uint16_t NumOfTDUsIWillBeSetTo_Prescale1, uint16_t NumOfSensorsIWillBeSetTo_Prescale2, uint16_t NumOfInterpretorsIWillBeSetTo_Prescale2, uint16_t NumOfTDUsIWillBeSetTo_Prescale2, uint16_t NumOfSensorsIWillBeSetTo_Prescale4, uint16_t NumOfInterpretorsIWillBeSetTo_Prescale4, uint16_t NumOfTDUsIWillBeSetTo_Prescale4, uint16_t NumOfSensorsIWillBeSetTo_Prescale8, uint16_t NumOfInterpretorsIWillBeSetTo_Prescale8, uint16_t NumOfTDUsIWillBeSetTo_Prescale8, uint16_t NumOfSensorsIWillBeSetTo_Prescale16, uint16_t NumOfInterpretorsIWillBeSetTo_Prescale16, uint16_t NumOfTDUsIWillBeSetTo_Prescale16, uint16_t NumOfSensorsIWillBeSetTo_Prescale32, uint16_t NumOfInterpretorsIWillBeSetTo_Prescale32, uint16_t NumOfTDUsIWillBeSetTo_Prescale32, uint16_t NumOfSensorsIWillBeSetTo_Prescale64, uint16_t NumOfInterpretorsIWillBeSetTo_Prescale64, uint16_t NumOfTDUsIWillBeSetTo_Prescale64>
template<class TAEObservorBase>
inline void AEClock<TEMPLATEFORParams_AEClock>
::SetObservorToClock(TAEObservorBase * observor, AEClock_PrescalerEnum Prescaler)
{

	//sort the observor in such a way of the following order
	//sensor observors
	//interpretor observors
	observor->SetToClock = true;
	observor->ClockIdImSourcedTo = ClockId; 


	switch (Prescaler)
	{
//	case AEClock_PrescalerEnum::PRESCALER1:
//		{
//			if (observor->GetMyObservorType() & ObservorType::Sensor)
//			{
//				configASSERT(NumOfSensorsIWillBeSetTo_Prescale1 > 0);
//				for (uint16_t i = 0; i < NumOfSensorsIWillBeSetTo_Prescale1; i++)
//				{
//					if (SensorObservorsIamSetToP1[i] == NULL)
//					{
//						SensorObservorsIamSetToP1[i] = (TAEObservorSensor*)observor;
//						break;
//					}
//				}
//			}
//		}
				
		AECLOCKSETOBSERVOR(1)
			AECLOCKSETOBSERVOR(2)
			AECLOCKSETOBSERVOR(4)
			AECLOCKSETOBSERVOR(8)
			AECLOCKSETOBSERVOR(16)
			AECLOCKSETOBSERVOR(32)
			AECLOCKSETOBSERVOR(64)
			
			/*
		case AEClock_PrescalerEnum::PRESCALER1:
			if (observor->GetMyObservorType() & ObservorType::Sensor)
			{
				//look for the index that has the first null pointer, then fill that spot
				for (uint16_t i = 0; i < NumOfSensorsIWillBeSetTo_Prescale1; i++)
				{
					if (SensorObservorsIamSetToP1[i] == NULL)
					{
						SensorObservorsIamSetToP1[i] = (AEObservorSensor*)observor;
						break;
					}
				}

				//tell that sensor the frequency that it updates at
				observor->FrequencyIRefreshAt = _FrequencyOfClock;

			}
			else if (observor->GetMyObservorType() & ObservorType::Interpretors)
			{
				for (uint16_t i = 0; i < NumOfInterpretorsIWillBeSetTo_Prescale1; i++)
				{
					if (InterpretorsIamSetToP1[i] == NULL)
					{
						InterpretorsIamSetToP1[i] = (AEObservorInterpretorBase*)observor;
						break;
					}
				}

				//tell that interpretor the frequency that it updates at
				observor->FrequencyIRefreshAt = _FrequencyOfClock;
			}
			break;*/

	default:
		break;
	}

	//initialize the filters now for that observor
	observor->InitializeFilters();
}


/*
template<uint16_t NumOfSensorsIWillBeSetTo_Prescale1, uint16_t NumOfInterpretorsIWillBeSetTo_Prescale1, uint16_t NumOfTDUsIWillBeSetTo_Prescale1, uint16_t NumOfSensorsIWillBeSetTo_Prescale2, uint16_t NumOfInterpretorsIWillBeSetTo_Prescale2, uint16_t NumOfTDUsIWillBeSetTo_Prescale2, uint16_t NumOfSensorsIWillBeSetTo_Prescale4, uint16_t NumOfInterpretorsIWillBeSetTo_Prescale4, uint16_t NumOfTDUsIWillBeSetTo_Prescale4, uint16_t NumOfSensorsIWillBeSetTo_Prescale8, uint16_t NumOfInterpretorsIWillBeSetTo_Prescale8, uint16_t NumOfTDUsIWillBeSetTo_Prescale8, uint16_t NumOfSensorsIWillBeSetTo_Prescale16, uint16_t NumOfInterpretorsIWillBeSetTo_Prescale16, uint16_t NumOfTDUsIWillBeSetTo_Prescale16, uint16_t NumOfSensorsIWillBeSetTo_Prescale32, uint16_t NumOfInterpretorsIWillBeSetTo_Prescale32, uint16_t NumOfTDUsIWillBeSetTo_Prescale32, uint16_t NumOfSensorsIWillBeSetTo_Prescale64, uint16_t NumOfInterpretorsIWillBeSetTo_Prescale64, uint16_t NumOfTDUsIWillBeSetTo_Prescale64>
inline void AEClock<NumOfSensorsIWillBeSetTo_Prescale1, NumOfInterpretorsIWillBeSetTo_Prescale1, NumOfTDUsIWillBeSetTo_Prescale1, NumOfSensorsIWillBeSetTo_Prescale2, NumOfInterpretorsIWillBeSetTo_Prescale2, NumOfTDUsIWillBeSetTo_Prescale2, NumOfSensorsIWillBeSetTo_Prescale4, NumOfInterpretorsIWillBeSetTo_Prescale4, NumOfTDUsIWillBeSetTo_Prescale4, NumOfSensorsIWillBeSetTo_Prescale8, NumOfInterpretorsIWillBeSetTo_Prescale8, NumOfTDUsIWillBeSetTo_Prescale8, NumOfSensorsIWillBeSetTo_Prescale16, NumOfInterpretorsIWillBeSetTo_Prescale16, NumOfTDUsIWillBeSetTo_Prescale16, NumOfSensorsIWillBeSetTo_Prescale32, NumOfInterpretorsIWillBeSetTo_Prescale32, NumOfTDUsIWillBeSetTo_Prescale32, NumOfSensorsIWillBeSetTo_Prescale64, NumOfInterpretorsIWillBeSetTo_Prescale64, NumOfTDUsIWillBeSetTo_Prescale64>::
SetTDUToClock<TAETDUAsService>(AETDUAsService * TDUToSet, AEClock_PrescalerEnum Prescaler)
{
}
*/



		
TEMPLATEFORNoDefaults_AEClock
inline void AEClock<TEMPLATEFORParams_AEClock>
::TickWithoutTimerTask(void* thisptr) {
	while (true)
	{
		//triggered via a tasknotify
		ulTaskNotifyTake(pdTRUE, portMAX_DELAY);


		TicksFromTimer = true;
		this->Tick();
		TicksFromTimer = false;

	}
}

TEMPLATEFORNoDefaults_AEClock
inline void AEClock<TEMPLATEFORParams_AEClock>
::TickWithoutTimer()
{ 
	//you can only use this function if timer is set up as a clock that is ticked WITHOUT a timer;
	configASSERT(TicksFromTimer == false);
	xTaskNotifyGive(this->TickTaskHandleFromWithoutTimer); 
}



TEMPLATEFORNoDefaults_AEClock
inline void AEClock<TEMPLATEFORParams_AEClock>
::Tick()
{

	//you can only use this function if timer is set up as a clock that is ticked WITH a timer;
	configASSERT(TicksFromTimer == true);

		if (TickCounter % 2 == 0)
		{
                    
  
			//go through each sensor observor first and update their values
			for (uint16_t i = 0; i < NumOfSensorsIWillBeSetTo_Prescale2; i++)
			{
				SensorObservorsIamSetToP2[i]->Update();
				//SensorObservorsIamSetTo[i]->UpdateValue();
			}

			//now go through each interpretor observor and get them to Getobservation(). Remember this needs to be done because some interpretor observors
			//need to have their observations from going stale because they publish events
			for (uint16_t i = 0; i < NumOfInterpretorsIWillBeSetTo_Prescale2; i++)
			{
				InterpretorsIamSetToP2[i]->UpdateObservationIfNeededForClock();
			}

			// go through all TDUs and have them update. remmeber the AEClock only holds the Task_Handle to the TDUs
			for (uint16_t i = 0; i < NumOfTDUsIWillBeSetTo_Prescale2; i++)
			{
				xTaskNotifyGive(*UpdateTasksForTDUsP2[i]);
			}
                         

		}
		if (TickCounter % 4 == 0)
		{
			for (uint16_t i = 0; i < NumOfSensorsIWillBeSetTo_Prescale4; i++)
			{
				SensorObservorsIamSetToP4[i]->Update();
				//SensorObservorsIamSetTo[i]->UpdateValue();
			}

			for (uint16_t i = 0; i < NumOfInterpretorsIWillBeSetTo_Prescale4; i++)
			{
				InterpretorsIamSetToP4[i]->UpdateObservationIfNeededForClock();
			}
			for (uint16_t i = 0; i < NumOfTDUsIWillBeSetTo_Prescale4; i++)
			{
				xTaskNotifyGive(*UpdateTasksForTDUsP4[i]);
			}
		}
		if (TickCounter % 8 == 0)
		{
			for (uint16_t i = 0; i < NumOfSensorsIWillBeSetTo_Prescale8; i++)
			{
				SensorObservorsIamSetToP8[i]->Update();
				//SensorObservorsIamSetTo[i]->UpdateValue();
			}

			for (uint16_t i = 0; i < NumOfInterpretorsIWillBeSetTo_Prescale8; i++)
			{
				InterpretorsIamSetToP8[i]->UpdateObservationIfNeededForClock();
			}
			for (uint16_t i = 0; i < NumOfTDUsIWillBeSetTo_Prescale8; i++)
			{
				xTaskNotifyGive(*UpdateTasksForTDUsP8[i]);
			}
		}
		if (TickCounter % 16 == 0)
		{
			for (uint16_t i = 0; i < NumOfSensorsIWillBeSetTo_Prescale16; i++)
			{
				SensorObservorsIamSetToP16[i]->Update();
				//SensorObservorsIamSetTo[i]->UpdateValue();
			}

			for (uint16_t i = 0; i < NumOfInterpretorsIWillBeSetTo_Prescale16; i++)
			{
				InterpretorsIamSetToP16[i]->UpdateObservationIfNeededForClock();
			}
			for (uint16_t i = 0; i < NumOfTDUsIWillBeSetTo_Prescale16; i++)
			{
				xTaskNotifyGive(*UpdateTasksForTDUsP16[i]);
			}
		}
		if (TickCounter % 32 == 0)
		{
			for (uint16_t i = 0; i < NumOfSensorsIWillBeSetTo_Prescale32; i++)
			{
				SensorObservorsIamSetToP32[i]->Update();
				//SensorObservorsIamSetTo[i]->UpdateValue();
			}

			for (uint16_t i = 0; i < NumOfInterpretorsIWillBeSetTo_Prescale32; i++)
			{
				InterpretorsIamSetToP32[i]->UpdateObservationIfNeededForClock();
			}
			for (uint16_t i = 0; i < NumOfTDUsIWillBeSetTo_Prescale32; i++)
			{
				xTaskNotifyGive(*UpdateTasksForTDUsP32[i]);
			}
		}
		if (TickCounter % 64 == 0)
		{
			for (uint16_t i = 0; i < NumOfSensorsIWillBeSetTo_Prescale64; i++)
			{
				SensorObservorsIamSetToP64[i]->Update();
				//SensorObservorsIamSetTo[i]->UpdateValue();
			}

			for (uint16_t i = 0; i < NumOfInterpretorsIWillBeSetTo_Prescale64; i++)
			{
				InterpretorsIamSetToP64[i]->UpdateObservationIfNeededForClock();
			}
			for (uint16_t i = 0; i < NumOfTDUsIWillBeSetTo_Prescale64; i++)
			{
				xTaskNotifyGive(*UpdateTasksForTDUsP64[i]);
			}
		}


		//go through each sensor observor first and update their values
		for (uint16_t i = 0; i < NumOfSensorsIWillBeSetTo_Prescale1; i++)
		{
			SensorObservorsIamSetToP1[i]->Update();
                         
  
		}

		//now go through each interpretor observor and get them to Getobservation(). Remember this needs to be done because some interpretor observors
		//need to have their observations from going stale because they publish events
		for (uint16_t i = 0; i < NumOfInterpretorsIWillBeSetTo_Prescale1; i++)
		{
			InterpretorsIamSetToP1[i]->UpdateObservationIfNeededForClock();
		}

                
                //for debugging
                //TaskHandle_t xHandle;
                //eTaskState  xTaskDetails;
                //xTaskDetails = eTaskGetState( /* The handle of the task being queried. */
                //  *(UpdateTasksForTDUsP16[0])//,
                  /* The TaskStatus_t structure to complete with information
                  on xTask. */
                  //&xTaskDetails,
                  /* Include the stack high water mark value in the
                  TaskStatus_t structure. */
                  //pdTRUE,
                  /* Include the task state in the TaskStatus_t structure. */
                  //eInvalid
                    //);
				
                //if(xTaskDetails == eTaskState::eReady)
                //{
                //     anfoainfo = 887;
                //}
                //else if(xTaskDetails == eTaskState::eReady)
                //{
                //     anfoainfo = 887;
                //}
                //else if(xTaskDetails == eTaskState::eRunning)
                //{
                //     anfoainfo = 887;
                //}
                //else if(xTaskDetails == eTaskState::eBlocked)
                //{
                //     anfoainfo = 887;
                //}
                //else if(xTaskDetails == eTaskState::eSuspended)
                //{
                //     anfoainfo = 887;
                //}
                // else if(xTaskDetails == eTaskState::eDeleted )
                //{
                //     anfoainfo = 887;
                //}
                
		//go through all TDUs and have them update. remmeber the AEClock only holds the Task_Handle to the TDUs
		for (uint16_t i = 0; i < NumOfTDUsIWillBeSetTo_Prescale1; i++)
		{
                  
                  
                   
			xTaskNotifyGive(*UpdateTasksForTDUsP1[i]);
                    
		}


		//go through all AELoops
		/*for (uint16_t i = 0; i < AELoopsIndex; i++)
		{
			xTaskNotifyGive(*UpdateTasksForAELoops[i]);
		}*/

		TickCounter++;
 

}




TEMPLATEFORNoDefaults_AEClock
template<class TAETDU>
inline void AEClock<TEMPLATEFORParams_AEClock>
::SetTDUToClock(TAETDU TDUToSet, AEClock_PrescalerEnum Prescaler)
{

	TDUToSet->SetFrequencyIUpdateAt(_FrequencyOfClock / Prescaler);
	_SetTDUToClock(TDUToSet, Prescaler);



}

TEMPLATEFORNoDefaults_AEClock
template<class TAETDU>
inline void AEClock<TEMPLATEFORParams_AEClock>
::_SetTDUToClock(TAETDU TDUToSet, AEClock_PrescalerEnum Prescaler)
{
	TDUToSet->isSetToClock = true;
	TDUToSet->ClockIdImSourcedTo = ClockId;

	switch (Prescaler)
	{
		AECLOCKSET_TDUs(1)
			AECLOCKSET_TDUs(2)
			AECLOCKSET_TDUs(4)
			AECLOCKSET_TDUs(8)
			AECLOCKSET_TDUs(16)
			AECLOCKSET_TDUs(32)
			AECLOCKSET_TDUs(64)

	default:
		break;
	}
}
 
TEMPLATEFORNoDefaults_AEClock
inline void AEClock<TEMPLATEFORParams_AEClock>
::SetAELoopToClock(AELoop* Loop)
{
	//can only set AE loops to clocks that are ticked from timers so to keep them 
	// to a set frequency
	configASSERT(this->TicksFromTimer == true);

	UpdateTasksForAELoops[AELoopsIndex] = &Loop->LoopUpdateTaskHandle;

	//AEloops is limited to the number MaxAELoopsPerClock that you set in the AEconfig
	configASSERT(AELoopsIndex < MaxAELoopsPerClock);
	AELoopsIndex = AELoopsIndex + 1;
}



#if  RetireThis
TEMPLATEFORNoDefaults_AEClock
template<class TAETDU, class TAESPBObservor>
inline void AEClock<TEMPLATEFORParams_AEClock>
::SetTDUToSPBClock(TAETDU TDU, TAESPBObservor * spbObservorToUpdateWith, float percentageOfDeltaRefresh)
{
 
	// I need to assert that the spbObservorToUpdateWith has already had its frequency configured
	configASSERT(spbObservorToUpdateWith->FrequencyHasBeenConfigured == true);
	//also assert that the SPB the TDU will be going off of is set to this clock
	configASSERT(this->ClockId == spbObservorToUpdateWith->GetClockIdImSourcedTo());

	TDU->IsSetToAnSPBRefresh = true;
	TDU->ClockIdImSourcedTo = ClockId;
	TDU->SetSPBAsRefresher(spbObservorToUpdateWith);
	spbObservorToUpdateWith->SetTDUToMyClock(TDU);

	//I need to calculate what prescaler should be used to match the SPB
	float SPBfrequency = spbObservorToUpdateWith->GetFrequencyIRefreshAt();
	//the frequency MUST be divisible by
	uint16_t spbdivisibleBy = this->_FrequencyOfClock / SPBfrequency;

	//find the prescaler that is JUST below spbdivisibleBy. for example if the spbdivisibleBy == 34 than the prescaler that is just below this would be prescaler = 32

	//this is not needed because either way The tdu will have to go by single prescale ticks of the clock because of the extra time needed to wait for the execution.
	/*
	uint8_t prescalerTheTduShouldTickAt = 0xffff;
	if (64 < spbdivisibleBy)
	{
		prescalerTheTduShouldTickAt = 64;
	}
	else if(32 < spbdivisibleBy)
	{
		prescalerTheTduShouldTickAt = 32;
	}
	else if (16 < spbdivisibleBy)
	{
		prescalerTheTduShouldTickAt = 16;
	}
	else if (8 < spbdivisibleBy)
	{
		prescalerTheTduShouldTickAt = 8;
	}
	else if (4 < spbdivisibleBy)
	{
		prescalerTheTduShouldTickAt = 4;
	}
	else if (2 < spbdivisibleBy)
	{
		prescalerTheTduShouldTickAt = 2;
	}
	else
	{
		prescalerTheTduShouldTickAt = 1;
	}*/

	//Now there is going to be two left over times that is 
	//the extra time to account for the execution of the SPB this tdu is going off of. 
	//percentageOfDeltaRefresh is a value that describes how long  the SPB needs to take to finish its execution before the next tick. Kind of like duty cycle
	//example: if spbFreq = 1000  , than periodSPB = .001  , and with a percentageOfDeltaRefresh = .4  , then TimeNeededForExection = periodSPB * .4 = .001 * .4 = .0004 sec
	float TimeNeededToAccountForExecution = percentageOfDeltaRefresh * (1 / spbObservorToUpdateWith->GetFrequencyIRefreshAt());

	//now convert that time to an amount of ticks the clock takes to reach that time. 
	//for example if the _FrequencyOfClock = 5000 tick/sec , and TimeNeededForExection = .0004 sec    ,  then extraTicks = 5000 * .004 = 2
	uint32_t extraTicks = ceilf((float)this->_FrequencyOfClock * TimeNeededToAccountForExecution);

	//now get the amount of ticks it takes for the spb to refresh
	uint32_t ticksToSPBRefresh = roundf(((float)this->_FrequencyOfClock)* (1 / spbObservorToUpdateWith->GetFrequencyIRefreshAt()));


	//this is the amount of ticks the tdu will wait in order to assume the spb that it is clocked 
	//to will finish execution
	TDU->UpdateClockCount = extraTicks + ticksToSPBRefresh;
	TDU->ExtraTicks = extraTicks;

	//the frequency that this tdu will update at will be the same as the spb
	TDU->SetFrequencyIUpdateAt(spbObservorToUpdateWith->GetFrequencyIRefreshAt());

	//I need to assert that (float)this->_FrequencyOfClock * TimeNeededForExection  is well over 1.8 . otherwise I risk the extraTicks being too close to the frequency of the spb
	//if this assert fails, then it means that the spb's frequency needs to be slower  to give more time for the  extra ticks, or for percentageOfDeltaRefresh to be lower
	configASSERT(((float)this->_FrequencyOfClock * TimeNeededToAccountForExecution) > 1.8);


	//set the tdu to prescale1 as this wil be the one the tdu will tick from
	_SetTDUToClock(TDU, PRESCALER1);


}
#endif