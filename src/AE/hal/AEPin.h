#pragma once
 

#include "BoardTypes.h"
#include "PinSelector.h"


class AEPin;
extern AEPin UserDefinedAEPins[];

class AEPin
{

	friend class AEPortAndPin;

  public:
	AEPin(PinEnum pinenumType, Pin_t halPin)
	{
		_pinenumType = pinenumType;
		_halPin = halPin;

		for (int i = 0; i < _numPinsCreatedSoFar; i++)
		{
			AEAssertRuntime(UserDefinedAEPins[i].GetPinEnum() != pinenumType, "make sure that the pinenum defined has not been one defined already");
		}
		//		UserDefinedAEPorts[_numPortsCreatedSoFar] = this;
		_numPinsCreatedSoFar++;
	}


	
	PinEnum GetPinEnum() { return _pinenumType; }
	Pin_t GetPin() { return _halPin; }

  private: 
	PinEnum _pinenumType;
	Pin_t _halPin; 

	static uint32_t _numPinsCreatedSoFar;
	//	static AEPort* ALLPorts[15];
};
