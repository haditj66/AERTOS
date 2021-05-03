#pragma once

#include "cstdint"
#include "AEUtils.h"



//helper macro for the pinselector
#define StartPinSelectorForPin(forPin) this->functPtrsToChangeTypeSelectors[forPin - 1] = []() -> void	{
#define M_IncludePossiblePin(portEnum, pinEnum) PinSelector::getInstance()->IncludePossiblePin(portEnum, pinEnum);
#define M_AnyPinIsPossible PinSelector::getInstance()->AnyPinIsPossible();
#define M_OnlyThisPinPossible(portEnum, pinEnum)  PinSelector::getInstance()->OnlyThisPinPossible(portEnum, pinEnum);
#define EndPinSelectorForPin };






enum Portenum : uint8_t
{
	PortA       = 0,
	PortB,
	PortC,
	PortD,
	PortE,
	PortF,
	PortG,
	PortH,
	PortI,
	PortsMaxNum

}
;



enum PinEnum : uint16_t
{
	PIN0      = 0,
	PIN1,
	PIN2,
	PIN3,
	PIN4,
	PIN5,
	PIN6,
	PIN7,
	PIN8,
	PIN9,
	PIN10,
	PIN11,
	PIN12,
	PIN13,
	PIN14,
	PIN15,
	PINMaxNum

};






#define MaxNumOfPinPossibilities 20

class PinSelector
{
	
	AEFRIEND_TEST(PinSelector, pin_validation);

	template <TemplateFor_AEPeripherals_NoDefaults>
	friend class AEPeripheral; 

	
		friend class AEPortAndPin;

public:

	//make it a singleton as this will be reset and used again for checking pins
public :
	static PinSelector* getInstance();
	PinSelector(PinSelector const&) = delete;
	void operator=(PinSelector const&) = delete;
private:
	static PinSelector* instance;
	PinSelector() { ResetSelector(); }
	;
public:
	// ----------------------------------------

	Portenum ports[MaxNumOfPinPossibilities];
	PinEnum pins[MaxNumOfPinPossibilities];
	 
	void IncludePossiblePin(Portenum port, PinEnum pin) {
 
		//configASSERT(pinIndex <= NumOfPossiblePins); 
		//assert that you have not selected AnyPinIsPossible()
		configASSERT(isAnyPinPossible == false);
		ports[pinIndex] = port;
		pins[pinIndex] = pin;
		pinIndex++;
	}
	;
	void AnyPinIsPossible() {
		AEAssertRuntime(pinIndex == 0,"assert that no other pin was included as possible or not possible");
		isAnyPinPossible = true;
	}
	;
	//template<Portenum PORT, PinEnum PINNum>
	//void ExcludePossiblePin(); 
	void OnlyThisPinPossible(Portenum port, PinEnum pin) { 
		AEAssertRuntime(isAnyPinPossible == false, "assert that you have not selected AnyPinIsPossible()"); 
		AEAssertRuntime(0 == pinIndex, "to use this, only 1 possible pin should be set");
		ports[pinIndex] = port;
		pins[pinIndex] = pin;
		pinIndex++;
	}
	;

	bool CheckIfPinIsValid(Portenum port, PinEnum pin)
	{
		//if pin selector has isAnyPinPossible == true, than all pins are valid
		if(isAnyPinPossible == true)
		{
			return true;
		}

		bool isValid = false;
		for (uint16_t i = 0; i < PinSelector::getInstance()->pinIndex; i++)
		{
			//if both the port and pin are the same as just one valid pin, then it is valid
			if((PinSelector::getInstance()->ports[i] == port)
				&& (PinSelector::getInstance()->pins[i] == pin))
			{
				isValid = true;
				break;
			}
		}
		return isValid;
	}

protected:

	//resets all the pins for a new selectors of rules.  
	void ResetSelector()
	{
		pinIndex = 0;
		isAnyPinPossible = false;
	}
	;

private:
	uint16_t pinIndex;
	bool isAnyPinPossible;
};


//MAKE_SINGLETON_PUT_IN_CPP(PinSelector)







