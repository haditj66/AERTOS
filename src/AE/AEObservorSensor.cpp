#include "AEObservorSensor.h"

#include "AELinkDeterministic.h";

#include <cmath>

uint32_t * AEObservorSensor::GetDataAddress()
{
	return Dataptr;
}

AEObservorSensor::AEObservorSensor(uint32_t* dataPtr, SensorResolution resolutionOfSensor)
{
	dataType = dataTypeEnum::type_uint32_t;
	Dataptr = (uint32_t*)dataPtr;
	Init(resolutionOfSensor);

}
AEObservorSensor::AEObservorSensor(int32_t* dataPtr, SensorResolution resolutionOfSensor)
{
	dataType = dataTypeEnum::type_int32_t;
	Dataptr = (uint32_t*)dataPtr;
	Init(resolutionOfSensor);
}
AEObservorSensor::AEObservorSensor(uint16_t* dataPtr, SensorResolution resolutionOfSensor)
{
	dataType = dataTypeEnum::type_uint16_t;
	Dataptr = (uint32_t*)dataPtr;
	Init(resolutionOfSensor);
}
AEObservorSensor::AEObservorSensor(int16_t* dataPtr, SensorResolution resolutionOfSensor)
{
	dataType = dataTypeEnum::type_int16_t;
	Dataptr = (uint32_t*)dataPtr;
	Init(resolutionOfSensor);
}
AEObservorSensor::AEObservorSensor(uint8_t* dataPtr, SensorResolution resolutionOfSensor)
{
	dataType = dataTypeEnum::type_uint8_t;
	Dataptr = (uint32_t*)dataPtr;
	Init(resolutionOfSensor);
}
AEObservorSensor::AEObservorSensor(int8_t* dataPtr, SensorResolution resolutionOfSensor)
{
	dataType = dataTypeEnum::type_int8_t;
	Dataptr = (uint32_t*)dataPtr;
	Init(resolutionOfSensor);
}
AEObservorSensor::AEObservorSensor(float* dataPtr, SensorResolution resolutionOfSensor)
{
	dataType = dataTypeEnum::type_float;
	Dataptr = (uint32_t*)dataPtr;

	Init(resolutionOfSensor);
}


void  AEObservorSensor::Init(SensorResolution resolutionOfSensor)
{



	ResolutionOfSensor = resolutionOfSensor;
	SetMyObservorType(ObservorType::Sensor);

	if (ResolutionOfSensor == Resolution8Bit)
	{
		SizeOfData = 1;
	}
	else if (ResolutionOfSensor == Resolution32Bit) {
		SizeOfData = 4;
	}
	else {
		SizeOfData = 2;
	}
	RangeOfData = pow(2, (float)this->ResolutionOfSensor);
}


float AEObservorSensor::ConvertPtrValueToFloat()
{
	if (dataType == type_uint32_t)
	{
		return (float)(uint32_t)*Dataptr;
	}
	else if (dataType == type_int32_t)
	{
		return (float)(int32_t)*Dataptr;
	}
	else if (dataType == type_uint16_t)
	{
		return (float)(uint16_t)*Dataptr;
	}
	else if (dataType == type_int16_t)
	{
		return (float)(int16_t)*Dataptr;
	}
	else if (dataType == type_uint8_t)
	{
		return (float)(uint8_t)*Dataptr;
	}
	else if (dataType == type_int8_t)
	{
		return (float)(int8_t)*Dataptr;
	}
	else if (dataType == type_float)
	{
		return (float)*Dataptr;
	}
}


float AEObservorSensor::GetObservation() const
{

	return _sensorValue;
}


void AEObservorSensor::Update()
{
	//only do something if this observor is on.
	if (this->isObservorOn)
	{

		//there's really not much point in checking wether the data has changed when there has been a 
		//refresh because over 99% of the time it will have changed. So just inform all that point to this observor 
		// that there has been a refresh.

		//the way that it informs all observors in the chain is described in onenote "How/Why endchain observors should..."
		//IF this is an END_OF_CHAIN observor, than I know that updating the refresh valiues in the chain will be done in an interrupt
		//as sensor updates should ?always? be in an interrupt. because of this, there should be no chance of synchronization problems.

		for (int i = 0; i < numOfObservorsOfInfluence; i++)
		{
			*ObservorsOfInfluenceNeedARefeshValues[i] = true;
		}





		//TODO: cast this uint32_t* pointer to a float pointer better here as I am only doing the first one so far.
		float arr[1];

		//if there are mapping values, than I  need to map the value.
		if (this->MapValue == true)
		{

			//you cant map sensor values this way if the data type is of float.
			configASSERT(this->dataType != type_float);

			//if the type is of signed type then the valofSensor can be of a signed type
			float mappedValue;
			if ((this->dataType == type_int32_t) || (this->dataType == type_int16_t) || (this->dataType == type_int8_t))
			{
				int32_t valofSensor = 0;// = (uint16_t)*Dataptr;
				memcpy(&valofSensor, (void*)Dataptr, SizeOfData);
				mappedValue = (((MapsToAFLoatOfUpperBound - MapsToAFLoatOfLowerBound) / RangeOfData) //delta value per resolution increment
					* valofSensor) + MapsToAFLoatOfLowerBound;
			}
			else
			{
				uint32_t valofSensor = 0;// = (uint16_t)*Dataptr;
				memcpy(&valofSensor, (void*)Dataptr, SizeOfData);
				mappedValue = (((MapsToAFLoatOfUpperBound - MapsToAFLoatOfLowerBound) / RangeOfData) //delta value per resolution increment
					* valofSensor) + MapsToAFLoatOfLowerBound;

			}



			arr[0] = mappedValue;

		}
		//else just use the raw value
		else
		{
			arr[0] = ConvertPtrValueToFloat();//Dataptr[0]; 
		}

		_sensorValue = arr[0];

		//input the data into all SPbs that I signalflowlink to

		//run the proper filters on the proper outputs
		if (NumOfFilters > 0)
		{
			UpdateOVERRIDE(arr);
		}
		else
		{
			for (int i = 0; i < NumOfSPBObservorsIPointTo; i++)
			{
				SPBObservorsIPointTo[i]->InputSignal(arr, ChannelIdsIConnectTo[i]);

			}
		}





		//this will no longer be done. instead the endchain observor will update all observors that depend on it.
		/*
		for (int i = 0; i < numOfDeterministicLinksPointToMe; i++)
		{
			AELinkDeterministic::Links[MyDeterministicLinksPointingToMe[i]].GetTheObservorIPointFrom()->HasThereBeenARefreshOAnyDeterministicObservors = true;
		}
		*/

	}
}

