#pragma once
#include "AEObservorSensor.h"
#include "AEMultiChannelFilter.h"
#include <cstdint>


#define ConstructorTemplate(type)	AEObservorSensorFilterOut(type* dataPtr,\
SensorResolution resolutionOfSensor,\
float mapsToAFLoatOfLowerBound = 0,\
float mapsToAFLoatOfUpperBound = 0) : AEObservorSensor(dataPtr,resolutionOfSensor)\
{\
	Init(resolutionOfSensor, mapsToAFLoatOfLowerBound, mapsToAFLoatOfUpperBound);\
};

template<uint8_t NUMOFFILTERS = 0, class TFilter1 = AENullClass, class TFilter2 = AENullClass, uint8_t Filter2LinksFrom = 0, class TFilter3 = AENullClass, uint8_t Filter3LinksFrom = 0, class TFilter4 = AENullClass, uint8_t Filter4LinksFrom = 0, class TFilter5 = AENullClass, uint8_t Filter5LinksFrom = 0>
class AEObservorSensorFilterOut : public AEObservorSensor
{
public:
	 

	ConstructorTemplate(uint32_t)
		ConstructorTemplate(int32_t)
		ConstructorTemplate(uint16_t)
		ConstructorTemplate(int16_t)
		ConstructorTemplate(uint8_t)
		ConstructorTemplate(int8_t)
		ConstructorTemplate(float)





	float GetObservationFromFilter(uint8_t filterNum);





	uint8_t multifiltersSetSoFar;
	void SetMultiChannelFilter(AEMultiChannelFilter* filterToSet,
		uint16_t channel1InputsFromthisFilter = 0xffff,
		uint16_t channel2InputsFromthisFilter = 0xffff,
		uint16_t channel3InputsFromthisFilter = 0xffff,
		uint16_t channel4InputsFromthisFilter = 0xffff,
		uint16_t channel5InputsFromthisFilter = 0xffff,
		uint16_t channel6InputsFromthisFilter = 0xffff,
		uint16_t channel7InputsFromthisFilter = 0xffff,
		uint16_t channel8InputsFromthisFilter = 0xffff,
		uint16_t channel9InputsFromthisFilter = 0xffff,
		uint16_t channel10InputsFromthisFilter = 0xffff);



public: //protected:


#if MAXNUMBEROF_FILTERS_From_A_Sensor >= 1  
	TFilter1 Filter1;
#endif 
#if MAXNUMBEROF_FILTERS_From_A_Sensor >= 2  
	TFilter2 Filter2;
#endif 
#if MAXNUMBEROF_FILTERS_From_A_Sensor >= 3 
	TFilter3 Filter3;
#endif
#if MAXNUMBEROF_FILTERS_From_A_Sensor >= 4
	TFilter4 Filter4;
#endif
#if MAXNUMBEROF_FILTERS_From_A_Sensor >= 5
	TFilter5 Filter5;
#endif 


	void Init(
		SensorResolution resolutionOfSensor,
		float mapsToAFLoatOfLowerBound,
		float mapsToAFLoatOfUpperBound)
	{
		ResolutionOfSensor = resolutionOfSensor;
		MapsToAFLoatOfLowerBound = mapsToAFLoatOfLowerBound;
		MapsToAFLoatOfUpperBound = mapsToAFLoatOfUpperBound;
		 
		if ((MapsToAFLoatOfLowerBound == 0) && (MapsToAFLoatOfUpperBound == 0))//((ResolutionOfSensor != Resolution0Bit))
		{
			MapValue = false;

		}
		else
		{
			MapValue = true;
			configASSERT(ResolutionOfSensor != SensorResolution::Resolution0Bit);
			configASSERT(MapsToAFLoatOfUpperBound != 0);
			configASSERT(MapsToAFLoatOfUpperBound > MapsToAFLoatOfLowerBound);
		}



		NumOfFilters = NUMOFFILTERS;
		multifiltersSetSoFar = 0;

		/*
		for (uint16_t i = 0; i < NUMOFMultiChannelFILTERS; i++)
		{
			MultiChannelFilters[i] = NULL;
		}*/
	}

	



	void InitializeFilters() override;
	void UpdateOVERRIDE(float* outputOfNonFilter) override;
	//AEMultiChannelFilter* MultiChannelFilters[(NUMOFMultiChannelFILTERS == 0) + NUMOFMultiChannelFILTERS];

	float OutputsOfFilters[(NUMOFFILTERS == 0) + NUMOFFILTERS];// +NUMOFMultiChannelFILTERS];




};




template<TEMPLATESPB_FiltersFunctionParams>
inline void  AEObservorSensorFilterOut<TEMPLATESPB_FilterParams>::SetMultiChannelFilter(AEMultiChannelFilter * filterToSet,
	uint16_t channel1InputsFromthisFilter,
	uint16_t channel2InputsFromthisFilter,
	uint16_t channel3InputsFromthisFilter,
	uint16_t channel4InputsFromthisFilter,
	uint16_t channel5InputsFromthisFilter,
	uint16_t channel6InputsFromthisFilter,
	uint16_t channel7InputsFromthisFilter,
	uint16_t channel8InputsFromthisFilter,
	uint16_t channel9InputsFromthisFilter,
	uint16_t channel10InputsFromthisFilter)
{
  /*
	//assert that this channel has not been set yet.
	configASSERT(MultiChannelFilters[multifiltersSetSoFar] == NULL);
	MultiChannelFilters[multifiltersSetSoFar] = filterToSet;

	//set the channels for this multichannels filter. a value of 0xffff means that there is no filter from this sensor that
	// will link up to that channel (must be to a different sensor)
	if (channel1InputsFromthisFilter != 0xffff)
	{
		filterToSet->SetInputtingFilterToChannel(OutputsOfFilters[channel1InputsFromthisFilter], 1);
	}

	multifiltersSetSoFar++;*/
}




template<TEMPLATESPB_FiltersFunctionParams>
inline void AEObservorSensorFilterOut<TEMPLATESPB_FilterParams>::InitializeFilters()
{
#if MAXNUMBEROF_FILTERS_From_A_Sensor >= 1  
	this->Filter1.Initialize(1 / this->GetFrequencyIRefreshAt());
#endif 
#if MAXNUMBEROF_FILTERS_From_A_Sensor >= 2  
	this->Filter2.Initialize(1 / this->GetFrequencyIRefreshAt());
#endif 
#if MAXNUMBEROF_FILTERS_From_A_Sensor >= 3 
	this->Filter3.Initialize(1 / this->GetFrequencyIRefreshAt());
#endif
#if MAXNUMBEROF_FILTERS_From_A_Sensor >= 4
	this->Filter4.Initialize(1 / this->GetFrequencyIRefreshAt());
#endif
#if MAXNUMBEROF_FILTERS_From_A_Sensor >= 5
	this->Filter5.Initialize(1 / this->GetFrequencyIRefreshAt());
#endif 
}

 

template<TEMPLATESPB_FiltersFunctionParams>
inline float AEObservorSensorFilterOut<TEMPLATESPB_FilterParams>::GetObservationFromFilter(uint8_t filterNum)
{
	switch (filterNum)
	{
#if MAXNUMBEROF_FILTERS_From_A_Sensor >= 1  
	case 1:
		return Filter1.GetObservation();
		break;
#endif 
#if MAXNUMBEROF_FILTERS_From_A_Sensor >= 2  
	case 2:
		return Filter2.GetObservation();
		break;
#endif 
#if MAXNUMBEROF_FILTERS_From_A_Sensor >= 3 
	case 3:
		return Filter3.GetObservation();
		break;
#endif
#if MAXNUMBEROF_FILTERS_From_A_Sensor >= 4
	case 4:
		return Filter4.GetObservation();
		break;
#endif
#if MAXNUMBEROF_FILTERS_From_A_Sensor >= 5
	case 5:
		return Filter5.GetObservation();
		break;
#endif 

	default:
		break;
	}

	//a valid filter was not chosen
	configASSERT(false);
	return 1;
}

template<TEMPLATESPB_FiltersFunctionParams>
inline void AEObservorSensorFilterOut<TEMPLATESPB_FilterParams>::UpdateOVERRIDE(float* outputOfNonFilter)
{

	//AEObservorSensorFilterOut<NumOfFilters, NUMOFMultiChannelFILTERS, TFilter1, TFilter2, Filter2LinksFrom, TFilter3, Filter3LinksFrom, TFilter4, Filter4LinksFrom, TFilter5, Filter5LinksFrom>* dcdc=
		//(AEObservorSensorFilterOut<NumOfFilters, NUMOFMultiChannelFILTERS, TFilter1, TFilter2, Filter2LinksFrom, TFilter3, Filter3LinksFrom, TFilter4, Filter4LinksFrom, TFilter5, Filter5LinksFrom>*)(this);

	//TFilter2 svsv = (TFilter2)this;

	switch (NumOfFilters)
	{
#if MAXNUMBEROF_FILTERS_From_A_Sensor >= 1 
	case 1:
         //static int16_t df = (int16_t)*this->Dataptr;
		OutputsOfFilters[0] = this->Filter1(this->ConvertPtrValueToFloat());


		break;
#endif 
#if MAXNUMBEROF_FILTERS_From_A_Sensor >= 2
	case 2:
		//filter1 cannot link from any other output except for the main one. so

		this->OutputsOfFilters[0] = this->Filter1(this->ConvertPtrValueToFloat());

		//check if the output of filter connects FROM another filter
		// a value of zero means that it does not.
		if (Filter2LinksFrom != 0)
		{
			OutputsOfFilters[1] = this->Filter2(OutputsOfFilters[Filter2LinksFrom - 1]);
		}
		else
		{
			OutputsOfFilters[1] = this->Filter2(this->ConvertPtrValueToFloat());
		}
#ifdef IARBuild
		StopTimer(2)
#endif // DEBUG


			break;

#endif 
#if MAXNUMBEROF_FILTERS_From_A_Sensor >= 3
	case 3:
		//filter1 cannot link from any other output except for the main one. so
		OutputsOfFilters[0] = Filter1(this->ConvertPtrValueToFloat());

		//check if the output of filter connects FROM another filter
		// a value of zero means that it does not.
		if (Filter2LinksFrom != 0)
		{
			OutputsOfFilters[1] = Filter2(OutputsOfFilters[Filter2LinksFrom]);
		}
		else
		{
			OutputsOfFilters[1] = Filter2(this->ConvertPtrValueToFloat());
		}

		if (Filter3LinksFrom != 0)
		{
			OutputsOfFilters[2] = Filter3(OutputsOfFilters[Filter3LinksFrom]);
		}
		else
		{
			OutputsOfFilters[2] = Filter3(this->ConvertPtrValueToFloat());
		}


		break;
#endif 
#if MAXNUMBEROF_FILTERS_From_A_Sensor >= 4
	case 4:
		//filter1 cannot link from any other output except for the main one. so
		OutputsOfFilters[0] = Filter1(this->ConvertPtrValueToFloat());

		//check if the output of filter connects FROM another filter
		// a value of zero means that it does not.
		if (Filter2LinksFrom != 0)
		{
			OutputsOfFilters[1] = Filter2(OutputsOfFilters[Filter2LinksFrom]);
		}
		else
		{
			OutputsOfFilters[1] = Filter2(this->ConvertPtrValueToFloat());
		}

		if (Filter3LinksFrom != 0)
		{
			OutputsOfFilters[2] = Filter3(OutputsOfFilters[Filter3LinksFrom]);
		}
		else
		{
			OutputsOfFilters[2] = Filter3(this->ConvertPtrValueToFloat());
		}

		if (Filter4LinksFrom != 0)
		{
			OutputsOfFilters[3] = Filter4(OutputsOfFilters[Filter4LinksFrom]);
		}
		else
		{
			OutputsOfFilters[3] = Filter4(this->ConvertPtrValueToFloat());
		}


		break;
#endif 
#if MAXNUMBEROF_FILTERS_From_A_Sensor >= 5
	case 5:
		//filter1 cannot link from any other output except for the main one. so
		OutputsOfFilters[0] = Filter1(this->ConvertPtrValueToFloat());

		//check if the output of filter connects FROM another filter
		// a value of zero means that it does not.
		if (Filter2LinksFrom != 0)
		{
			OutputsOfFilters[1] = Filter2(OutputsOfFilters[Filter2LinksFrom]);
		}
		else
		{
			OutputsOfFilters[1] = Filter2(this->ConvertPtrValueToFloat());
		}

		if (Filter3LinksFrom != 0)
		{
			OutputsOfFilters[2] = Filter3(OutputsOfFilters[Filter3LinksFrom]);
		}
		else
		{
			OutputsOfFilters[2] = Filter3(this->ConvertPtrValueToFloat());
		}

		if (Filter4LinksFrom != 0)
		{
			OutputsOfFilters[3] = Filter4(OutputsOfFilters[Filter4LinksFrom]);
		}
		else
		{
			OutputsOfFilters[3] = Filter4(this->ConvertPtrValueToFloat());
		}

		if (Filter5LinksFrom != 0)
		{
			OutputsOfFilters[4] = Filter5(OutputsOfFilters[Filter5LinksFrom]);
		}
		else
		{
			OutputsOfFilters[4] = Filter5(this->ConvertPtrValueToFloat());
		}

		break;
#endif 
	default:
		break;
	}


	//go through any multichannels that I have and run their filters
	/*for (uint8_t i = 0; i < NUMOFMultiChannelFILTERS; i++)
	{
		MultiChannelFilters[i]->inputsSoFar++;
		if (MultiChannelFilters[i]->inputsSoFar >= MultiChannelFilters[i]->_NumOfInputs)
		{
			OutputsOfFilters[i + NumOfFilters] = (*MultiChannelFilters[i])();
		}
	}*/
	for (int i = 0; i < NumOfSPBObservorsIPointTo; i++)
	{ 

		//this 0xff means that it is not set to a filter
		if (OutputFilterThatSignalGoesFrom[i] == 0xff)
		{
			SPBObservorsIPointTo[i]->InputSignal(outputOfNonFilter, ChannelIdsIConnectTo[i]);

		}
		else
		{
			float arrFil[1];
			arrFil[0] = OutputsOfFilters[OutputFilterThatSignalGoesFrom[i]];
			SPBObservorsIPointTo[i]->InputSignal(arrFil, ChannelIdsIConnectTo[i]);
		}

	}
	/*
	//input the data into all SPbs that I signalflowlink to
	for (int i = 0; i < NumOfSPBObservorsIPointTo; i++)
	{
		float arr[1];
		arr[0] = OutputsOfFilters[OutputFilterThatSignalGoesFrom[i]];
		SPBObservorsIPointTo[i]->InputSignal(arr, ChannelIdsIConnectTo[i]);

	}*/



}
