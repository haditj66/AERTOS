#pragma once

#include "PinSelector.h"
#include "BoardTypes.h"

#include "AEConfig.h"

//todo: find out still why # include "stm32f4xx_hal.h" is needed in the config. dont spend to omuch time. if that's how it'll work than fine!

//#include "stm32f4xx_hal.h"
//#include "ModelType2Setup.h"  
//#include "SeriesSetup.h"
// #include "AE_Init.h"


typedef void (*portClockInitializationfuncPtr_t)(void);


class AEPort;
extern AEPort UserDefinedAEPorts[];



class AEPort
{

	
	friend class AEPortAndPin;
public:
	AEPort(Portenum portenumType, Port_t halPort, portClockInitializationfuncPtr_t portClockInitialization)
	{
		_hasPortBeenInitYet = false;
		_portenumType = portenumType;
		_halPort = halPort;
		_portClockInitialization = portClockInitialization;

		
		for (int i = 0; i < _numPortsCreatedSoFar; i++)
		{
			AEAssertRuntime(UserDefinedAEPorts[i].GetPortEnum() != portenumType, "make sure that the portenum defined has not been one defined already");
			
		}
//		UserDefinedAEPorts[_numPortsCreatedSoFar] = this;
		_numPortsCreatedSoFar++;
	}

	void Initialize()
	{
		if (_hasPortBeenInitYet == false)
		{
			_portClockInitialization(); 
		}
		
		_hasPortBeenInitYet = true;
	}
	Portenum GetPortEnum() { return _portenumType; }
	Port_t GetPort() { return _halPort; }

private:
	bool _hasPortBeenInitYet;
	Portenum _portenumType;
	Port_t _halPort;
	portClockInitializationfuncPtr_t _portClockInitialization;

	static uint32_t _numPortsCreatedSoFar;
//	static AEPort* ALLPorts[15];
};



