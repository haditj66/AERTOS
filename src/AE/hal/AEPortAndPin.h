#pragma once
#include "cstdint"

#include "AEUtils.h"

#include "AEPort.h"
#include "AEPin.h"
#include <iostream>
using namespace std;

 
///this class is meant to  check for valid port and pins combo as well as to transition between enum port/pin to its hal type.
class AEPortAndPin
{

	AEFRIEND_TEST(AEGPIO, simple_init);

	template <TemplateFor_AEPeripherals_NoDefaults>
	friend class AEPeripheral;  
	
  private:
	void _Init(Portenum PORT, PinEnum PINNum)
	{
 

		AEAssertRuntime(_isInitialized == false, "you attempted to initialize this AEPortAndPin twice.")
			_isInitialized = true;

		//get the AEPort from the given port enum
		_port = nullptr; 
		
		for(int i = 0 ; i < AEPort::_numPortsCreatedSoFar ; i++) 
		{
			if (UserDefinedAEPorts[i].GetPortEnum() == PORT)
			{
				_port = &UserDefinedAEPorts[i];
				break;
			}
		}
		AEAssertRuntime(_port != nullptr, "you have selected a port that is not available to you from your user defined ports.");

		//get the AEPin next
		_pin = nullptr;
		for (int i = 0; i < AEPin::_numPinsCreatedSoFar; i++)
		{
			if (UserDefinedAEPins[i].GetPinEnum() == PINNum)
			{
				_pin = &UserDefinedAEPins[i];
				break;
			}
		}
		AEAssertRuntime(_pin != nullptr, "you have selected a pin that is not available to you from your user defined pins.");
		
		
		//make sure that this port/pin combination has never been used before in any other hardware peripheral. This will make sure that
		//the same pin does not get used for two different peripherals.
		for (int i = 0; i < _numPortsAndPinsCreatedSoFar; i++)
		{
			if ((ALLPortsAndPins[i]->GetThePortenum() == PORT) && (ALLPortsAndPins[i]->GetThePinenum() == PINNum))
			{
				AEAssertRuntimeWithAssertCodeToTest(false, "GPIOPinReused", "this port and pin combo has already been used for something else.")
			}
		}
		
		_port->Initialize();
		

		ALLPortsAndPins[_numPortsAndPinsCreatedSoFar] = this;
		_numPortsAndPinsCreatedSoFar++;
		AEAssertRuntime(_numPortsAndPinsCreatedSoFar <= MaxNumOfGPIOPinsToUse, "you exceeded the max number of gpio pins. change the MaxNumOfGPIOPinsToUse in AEConfig")
	}

	bool _isInitialized;
	static uint32_t _numPortsAndPinsCreatedSoFar;
	static AEPortAndPin* ALLPortsAndPins[MaxNumOfGPIOPinsToUse];
	//	static AEPortAndPin *instance;

	AEPortAndPin()
	{  
          //set port and pins to default values
          _port = &UserDefinedAEPorts[Portenum::PortsMaxNum];
          _pin = &UserDefinedAEPins[PinEnum::PINMaxNum];
		_isInitialized = false;
	};
	// -----------------------------------

  public :
	
	bool isInitialized() const {return _isInitialized;}
	Port_t GetThePort()
	{
		return _port->_halPort; // Ports[(uint8_t)thePORT];
	};
	Pin_t GetThePin()
	{
		return _pin->_halPin; //Pins[(uint8_t)thePIN];
	};

	Portenum GetThePortenum()
	{
		return _port->GetPortEnum();
	};
	PinEnum GetThePinenum()
	{
		return _pin->GetPinEnum();
	};

	uint8_t GetThePortID()
	{
		return (uint8_t)_port->GetPortEnum();
	};
	uint8_t GetThePinID()
	{
		return (uint8_t)_pin->GetPinEnum();
	};

	

  protected:
	AEPort* _port;
	AEPin* _pin;
  
	
};



 