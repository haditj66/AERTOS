#pragma once


#include <cstdint>
#include "AE.h"


#define CircularBuffMutexTake xSemaphoreTake(MutexForThisCircularBuffer, portMAX_DELAY);
#define CircularBuffMutexGive xSemaphoreGive(MutexForThisCircularBuffer);


template<class ContainerType, uint16_t MaxSize>
class AECircularBuffer
{
public: 

	AECircularBuffer(); 



	void Push(ContainerType item, bool withFullCheck = true) {
		CircularBuffMutexTake Push_IMPL(item, withFullCheck);  CircularBuffMutexGive;
	};
	ContainerType* Peek();
	void Pop() {
		CircularBuffMutexTake Pop_IMPL( );  CircularBuffMutexGive
	};
	void Reset() {
		CircularBuffMutexTake Reset_IMPL();  CircularBuffMutexGive
	};
	void Clear() {
		CircularBuffMutexTake Clear_IMPL();   CircularBuffMutexGive
	};

	bool isEmpty() const { CircularBuffMutexTake bool isEmpt = isEmpty_IMPL(); CircularBuffMutexGive return  isEmpt; }
	bool isFull() const { CircularBuffMutexTake bool isfull = isFull_IMPL(); CircularBuffMutexGive  return isfull; }
	uint16_t GetSize() const { CircularBuffMutexTake uint16_t theSize = GetSize_IMPL(); CircularBuffMutexGive  return theSize; };

	

	ContainerType &operator[] (uint16_t index);

private:  

  
	xSemaphoreHandle MutexForThisCircularBuffer;

	bool full;
	uint16_t size;
	uint16_t head;
	uint16_t tail; 

	ContainerType buffer[(MaxSize == 0) + MaxSize];



	void Push_IMPL(ContainerType item, bool withFullCheck = true);
	ContainerType* Peek_IMPL();
	void Pop_IMPL();
	void Reset_IMPL();
	void Clear_IMPL();

	bool isEmpty_IMPL() const { return (size == 0);}
	bool isFull_IMPL() const { return full; }
	uint16_t GetSize_IMPL() const { return size; };

	void AdvancePointers();
};

template<class ContainerType, uint16_t MaxSize>
inline AECircularBuffer<ContainerType, MaxSize>::AECircularBuffer()
{

	//create mutex for this
	MutexForThisCircularBuffer = xSemaphoreCreateMutex();

	Reset_IMPL();
}



template<class ContainerType, uint16_t MaxSize>
inline void AECircularBuffer<ContainerType, MaxSize>::Push_IMPL(ContainerType item, bool withFullCheck )
{ 

	//if max size is just one then just treat this as a buffer
	if (MaxSize == 1)
	{
		buffer[0] = item;
		full = true;
		size = 1;
		return;
	}

	if (withFullCheck == false)
	{
		if ((size > MaxSize))
		{
			this->Pop_IMPL();
		}
	}
	else
	{
        //assert that the size of this circular buffer is not full 
           configASSERT(size <= MaxSize);
	}

  
	buffer[head] = item;

	size++;
	AdvancePointers();

	 

}


template<class ContainerType, uint16_t MaxSize>
inline ContainerType* AECircularBuffer<ContainerType, MaxSize>::Peek()
{  
  CircularBuffMutexTake ContainerType* returnthing = Peek_IMPL();   CircularBuffMutexGive return returnthing;
 
}

template<class ContainerType, uint16_t MaxSize>
inline ContainerType* AECircularBuffer<ContainerType, MaxSize>::Peek_IMPL()
{ 

  ContainerType* ContToReturn;
	//if max size is just one 
	if (MaxSize == 1)
	{ 
		ContToReturn = &buffer[0];
	}
        else
        {
          ContToReturn =&buffer[tail];
        }
	 

	return ContToReturn;
}

template<class ContainerType, uint16_t MaxSize>
inline void AECircularBuffer<ContainerType, MaxSize>::Pop_IMPL()
{ 

	//if max size is just one 
	if (MaxSize == 1)
	{ 
		size == 0;
		full = false;
		return;
	}

	tail = (tail + 1) % MaxSize;
	size--;
	full = false; 
}

template<class ContainerType, uint16_t MaxSize>
inline void AECircularBuffer<ContainerType, MaxSize>::Reset_IMPL()
{ 

	size = 0;
	full = false;
	head = 0;
	tail = 0;
	 
}

template<class ContainerType, uint16_t MaxSize>
inline void AECircularBuffer<ContainerType, MaxSize>::Clear_IMPL()
{ 

	while (size != 0)
	{
		Pop_IMPL();
	}
	 

}

template<class ContainerType, uint16_t MaxSize>
inline ContainerType & AECircularBuffer<ContainerType, MaxSize>::operator[](uint16_t index)
{ 

	//index you gave for circularbuffer not within size
	configASSERT(index < MaxSize);

	//if this curcular buffer is not full, i want to be able to just get the tail value so to not get an undefined value.
	//this is a special case of this particular kind of circularbuffer
	if (full == false)
	{
		//get the last value inputted (head-1) only if the index points to a spot not defined yet (index >= head)
		if ((index >= head))
		{
			return buffer[tail];
		} 
	}

	if ((head - index) <= 0)
	{
		return buffer[head-1 - index + MaxSize];
	}
	 

	return buffer[head-1 - index];

	//return buffer[(tail + index) % MaxSize];
	//head+index%maxsize  expexted   result
	//11 + 19 % 20  10  30 % 20 = 10
	//19 + 19 % 20  18  38 % 20 = 18
	//15 + 8  % 20   3  23 % 20 = 3
	//13 + 5  % 20  18  18 % 20 = 18
	//13 + 5  % 20  18  18 % 20 = 18 

}

 

template<class ContainerType, uint16_t MaxSize>
inline void AECircularBuffer<ContainerType, MaxSize>::AdvancePointers()
{
	if (full == true)
	{
		tail = (tail + 1) % MaxSize;
	}

	head = (head + 1) % MaxSize;
	full = (head == tail);
}
