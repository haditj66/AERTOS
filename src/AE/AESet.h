#pragma once

#include <cstdint>

#ifdef USING_FREERTOS 
#include "FreeRTOS.h"
#include "task.h"
#include "timers.h"
#include "queue.h"
#include "semphr.h"
#include "event_groups.h"

#endif // USING_FREERTOS 



template<class TItemType, uint32_t SIZE>
class AESet
{
public:

	//typedef bool(*AESetCompareFunc)(TItemType itemToCompare1, TItemType itemToCompare2);
	typedef void(*ForEachFunc_t)(void* thisptr, TItemType itemInSet);
	typedef bool(*ForEachFuncTrue_t)(TItemType itemToPass, TItemType itemInSet);
	 
	///defaultNullValue: is meant to show a value that signifies not in the set
	AESet(TItemType defaultNullValue) {
		mutexForInsertRemove = xSemaphoreCreateMutex();

		DefaultNullValue = defaultNullValue;
		size = 0;
		for (uint32_t i = 0; i < SIZE; i++)
		{
			buffer[i] = DefaultNullValue;
		}
	};

	void Insert(TItemType itemToInsert);
	void Remove(TItemType itemToRemove);
	void RemoveAll();
	void ForEach(void* thisptr, ForEachFunc_t forEachFunc) const;
	bool ForEachIsAnyTrueWithItem(TItemType itemToPass, ForEachFuncTrue_t forEachFunc) const;
	
	uint32_t Size() const;

private:

	xSemaphoreHandle mutexForInsertRemove;

	uint32_t size;
	//AESetCompareFunc AESetComparefunc;
	TItemType buffer[SIZE];
	TItemType DefaultNullValue;


};

template<class TItemType, uint32_t SIZE>
inline void AESet<TItemType, SIZE>::Remove(TItemType itemToInsert)
{
	xSemaphoreTake(this->mutexForInsertRemove, portMAX_DELAY);

	bool foundItemToRemove = false;
	for (uint32_t i = 0; i < SIZE; i++)
	{
		if (this->buffer[i] == itemToInsert)
		{
			foundItemToRemove = true;
			this->buffer[i] = this->DefaultNullValue;
			break;
		}
	}
	//assert that the item you tried to remove was in fact in the set.
	//configASSERT(foundItemToRemove);
	if (foundItemToRemove == true)
	{
		this->size--;
	}

	xSemaphoreGive(this->mutexForInsertRemove);
	
}

template<class TItemType, uint32_t SIZE>
inline void AESet<TItemType, SIZE>::RemoveAll()
{
	xSemaphoreTake(this->mutexForInsertRemove, portMAX_DELAY);

	for (uint32_t i = 0; i < SIZE; i++)
	{
		this->buffer[i] = this->DefaultNullValue;
	}

	this->size = 0;

	xSemaphoreGive(this->mutexForInsertRemove);
}

template<class TItemType, uint32_t SIZE>
inline void AESet<TItemType, SIZE>::ForEach(void* thisptr,ForEachFunc_t forEachFunc) const
{
	if (this->size > 0)
	{
		for (uint16_t i = 0; i < SIZE; i++)
		{
			if (this->buffer[i] != this->DefaultNullValue)
			{
				forEachFunc(thisptr, this->buffer[i]);
			}
		}
	} 

}

template<class TItemType, uint32_t SIZE>
inline bool AESet<TItemType, SIZE>::ForEachIsAnyTrueWithItem(TItemType itemToPass, ForEachFuncTrue_t forEachFuncTrue) const
{

	if (this->size > 0)
	{
		for (uint16_t i = 0; i < SIZE; i++)
		{
			if (this->buffer[i] != this->DefaultNullValue)
			{
				bool istrue = forEachFuncTrue(itemToPass, this->buffer[i]);
				if (istrue == true)
				{
					return istrue;
				}
			}
		}
	}

	return false;

}

template<class TItemType, uint32_t SIZE>
inline uint32_t AESet<TItemType, SIZE>::Size() const
{
	return this->size;
}
 

template<class TItemType, uint32_t SIZE>
inline void AESet<TItemType, SIZE>::Insert(TItemType itemToInsert)
{
	xSemaphoreTake(mutexForInsertRemove, portMAX_DELAY);
  
	bool BufferWasFull = true;
	for (uint32_t i = 0; i < SIZE; i++)
	{
		if (this->buffer[i] == this->DefaultNullValue)
		{
			BufferWasFull = false;
			this->buffer[i] = itemToInsert;
			break;
		}
	}

	//assert that Buffer is not full
	configASSERT(!BufferWasFull);

	this->size++;

	xSemaphoreGive(mutexForInsertRemove);
}

/*
typedef bool(*IntTypeCompare)(int, int);

static IntTypeCompare kk = [](int x, int y) {x = y; };
*/