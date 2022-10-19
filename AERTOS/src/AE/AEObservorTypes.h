#pragma once

enum ObservorType : uint32_t
{
	Sensor = 1 << 2,// = 4, //1 << 2,
	Interpretors= (1 << 3), // = 8, //(1 << 3),
	SPB = 1 << 4//= 16//1 << 4
};
