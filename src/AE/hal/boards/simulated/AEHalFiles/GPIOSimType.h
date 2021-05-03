#pragma once

class GPIOSimType
{
public:

	GPIOSimType() { _stateOfGpio = false; };

	void  GPIO_SetHigh() {
		_stateOfGpio = true;
	}
	void   GPIO_SetLow() {
		_stateOfGpio = false; 
	}

	bool  GPIO_ReadPin() { 
		return _stateOfGpio;
	}

	void  GPIO_TogglePin() { 
		_stateOfGpio = !_stateOfGpio;
	}
	 

private:
	bool _stateOfGpio;
};
 