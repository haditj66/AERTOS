#pragma once
#include "AEObservorBase.h"


enum SensorResolution : uint8_t {
	Resolution0Bit = 0,
	Resolution8Bit = 8,
	Resolution12Bit = 12,
	Resolution16Bit = 16,
	Resolution32Bit = 32,
	Resolution64Bit = 64

};

class AEObservorSensor : public AEObservorBase
{
public:
	TEMPLATEFORNoDefaults_AEClock
		friend class AEClock;

	float GetObservation() const;

	uint32_t* GetDataAddress();

	uint32_t* Dataptr;


	// Inherited via AEObservorBase
	void Update();


protected:

      bool MapValue;

	enum dataTypeEnum : uint8_t {
		type_uint32_t ,
		type_int32_t ,
		type_uint16_t ,
		type_int16_t ,
		type_uint8_t ,
		type_int8_t,
		type_float

	};

	dataTypeEnum dataType;

	float _sensorValue;

	SensorResolution ResolutionOfSensor;
	uint8_t SizeOfData;
	uint32_t RangeOfData;

	float MapsToAFLoatOfLowerBound;
	float MapsToAFLoatOfUpperBound;

	float* outputs;
	uint8_t NumOfFilters;
	 

	float ConvertPtrValueToFloat();
	AEObservorSensor(uint32_t* dataPtr, SensorResolution resolutionOfSensor);
	AEObservorSensor(int32_t* dataPtr, SensorResolution resolutionOfSensor);
	AEObservorSensor(uint16_t* dataPtr, SensorResolution resolutionOfSensor);
	AEObservorSensor(int16_t* dataPtr, SensorResolution resolutionOfSensor);
	AEObservorSensor(uint8_t* dataPtr, SensorResolution resolutionOfSensor);
	AEObservorSensor(int8_t* dataPtr, SensorResolution resolutionOfSensor);
	AEObservorSensor(float* dataPtr, SensorResolution resolutionOfSensor);

	void Init(SensorResolution resolutionOfSensor);

	AEObservorSensor() {};

	virtual void InitializeFilters() = 0;

	virtual void UpdateOVERRIDE(float* arroutput) {};
};

