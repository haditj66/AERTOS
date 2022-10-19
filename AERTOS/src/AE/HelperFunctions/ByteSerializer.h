//generated file: ByteSerializer.h




#pragma once

#include <cstdint>


constexpr int GetMax(const int a, const int b) {
	return (a < b) ? b : a;
}

constexpr int GetMax(const int a, const int b, const int c) {
	return GetMax(a, GetMax(b, c));
}

constexpr int GetMax(const int a, const int b, const int c, const int d) {
	return GetMax(a, GetMax(b, c, d));
}


constexpr int GetMax(const int a, const int b, const int c, const int d, const int e) {
	return GetMax(a, GetMax(b, c, d, e));
}

 
#define templateByteSerializer \
class arg1_t

#define templateargsByteSerializer \
arg1_t
 

#define functionargsByteSerializer \
arg1_t* arg1



template<templateByteSerializer>
class ByteSerializer1
{

protected:
	static  ByteSerializer1<templateargsByteSerializer>* getInstance();
	ByteSerializer1(ByteSerializer1<templateargsByteSerializer> const&) = delete;
	void operator=(ByteSerializer1<templateargsByteSerializer> const&) = delete;

	static ByteSerializer1<templateargsByteSerializer>* Instance;
	 
	ByteSerializer1() {};

public:

	static const uint32_t sizeOfCharData = sizeof(arg1_t) ;

	
 

	static void DeSerializeData(char* dataToSerializeFrom, functionargsByteSerializer) {

		uint32_t indexOfDataSerialized = 0;
		 

		 memcpy((void*)arg1, dataToSerializeFrom + indexOfDataSerialized, sizeof(arg1_t));
		indexOfDataSerialized += sizeof(arg1_t);









 


		 
	};

	static void SerializeData(char* dataToSerializeTo, functionargsByteSerializer) {

		uint32_t indexOfDataSerialized = 0;
		//arg1 get size of argument1 and serialize it; 

		 memcpy(dataToSerializeTo+indexOfDataSerialized, arg1, sizeof(arg1_t));
		indexOfDataSerialized += sizeof(arg1_t);









 

	};
	 

};
 


template<templateByteSerializer>
ByteSerializer1<templateargsByteSerializer>* ByteSerializer1<templateargsByteSerializer>::getInstance() {

	if (Instance == 0)
	{
		static ByteSerializer1<templateargsByteSerializer> soleInstance;
		Instance = &soleInstance;
		 
	}
	return Instance;

}
 

template<templateByteSerializer>
ByteSerializer1<templateargsByteSerializer>* ByteSerializer1<templateargsByteSerializer>::Instance = nullptr;




 
#define templateByteSerializer \
class arg1_t ,\
 class arg2_t

#define templateargsByteSerializer \
arg1_t ,\
 arg2_t
 

#define functionargsByteSerializer \
arg1_t* arg1 ,\
 arg2_t* arg2



template<templateByteSerializer>
class ByteSerializer2
{

protected:
	static  ByteSerializer2<templateargsByteSerializer>* getInstance();
	ByteSerializer2(ByteSerializer2<templateargsByteSerializer> const&) = delete;
	void operator=(ByteSerializer2<templateargsByteSerializer> const&) = delete;

	static ByteSerializer2<templateargsByteSerializer>* Instance;
	 
	ByteSerializer2() {};

public:

	static const uint32_t sizeOfCharData = sizeof(arg1_t) 
 + sizeof(arg2_t) ;

	
 

	static void DeSerializeData(char* dataToSerializeFrom, functionargsByteSerializer) {

		uint32_t indexOfDataSerialized = 0;
		 

		 memcpy((void*)arg1, dataToSerializeFrom + indexOfDataSerialized, sizeof(arg1_t));
		indexOfDataSerialized += sizeof(arg1_t);

		 memcpy((void*)arg2, dataToSerializeFrom + indexOfDataSerialized, sizeof(arg2_t));
		indexOfDataSerialized += sizeof(arg2_t);







 


		 
	};

	static void SerializeData(char* dataToSerializeTo, functionargsByteSerializer) {

		uint32_t indexOfDataSerialized = 0;
		//arg1 get size of argument1 and serialize it; 

		 memcpy(dataToSerializeTo+indexOfDataSerialized, arg1, sizeof(arg1_t));
		indexOfDataSerialized += sizeof(arg1_t);

		 memcpy(dataToSerializeTo+indexOfDataSerialized, arg2, sizeof(arg2_t));
		indexOfDataSerialized += sizeof(arg2_t);







 

	};
	 

};
 


template<templateByteSerializer>
ByteSerializer2<templateargsByteSerializer>* ByteSerializer2<templateargsByteSerializer>::getInstance() {

	if (Instance == 0)
	{
		static ByteSerializer2<templateargsByteSerializer> soleInstance;
		Instance = &soleInstance;
		 
	}
	return Instance;

}
 

template<templateByteSerializer>
ByteSerializer2<templateargsByteSerializer>* ByteSerializer2<templateargsByteSerializer>::Instance = nullptr;




 
#define templateByteSerializer \
class arg1_t ,\
 class arg2_t ,\
 class arg3_t

#define templateargsByteSerializer \
arg1_t ,\
 arg2_t ,\
 arg3_t
 

#define functionargsByteSerializer \
arg1_t* arg1 ,\
 arg2_t* arg2 ,\
 arg3_t* arg3



template<templateByteSerializer>
class ByteSerializer3
{

protected:
	static  ByteSerializer3<templateargsByteSerializer>* getInstance();
	ByteSerializer3(ByteSerializer3<templateargsByteSerializer> const&) = delete;
	void operator=(ByteSerializer3<templateargsByteSerializer> const&) = delete;

	static ByteSerializer3<templateargsByteSerializer>* Instance;
	 
	ByteSerializer3() {};

public:

	static const uint32_t sizeOfCharData = sizeof(arg1_t) 
 + sizeof(arg2_t) 
 + sizeof(arg3_t) ;

	
 

	static void DeSerializeData(char* dataToSerializeFrom, functionargsByteSerializer) {

		uint32_t indexOfDataSerialized = 0;
		 

		 memcpy((void*)arg1, dataToSerializeFrom + indexOfDataSerialized, sizeof(arg1_t));
		indexOfDataSerialized += sizeof(arg1_t);

		 memcpy((void*)arg2, dataToSerializeFrom + indexOfDataSerialized, sizeof(arg2_t));
		indexOfDataSerialized += sizeof(arg2_t);

		 memcpy((void*)arg3, dataToSerializeFrom + indexOfDataSerialized, sizeof(arg3_t));
		indexOfDataSerialized += sizeof(arg3_t);





 


		 
	};

	static void SerializeData(char* dataToSerializeTo, functionargsByteSerializer) {

		uint32_t indexOfDataSerialized = 0;
		//arg1 get size of argument1 and serialize it; 

		 memcpy(dataToSerializeTo+indexOfDataSerialized, arg1, sizeof(arg1_t));
		indexOfDataSerialized += sizeof(arg1_t);

		 memcpy(dataToSerializeTo+indexOfDataSerialized, arg2, sizeof(arg2_t));
		indexOfDataSerialized += sizeof(arg2_t);

		 memcpy(dataToSerializeTo+indexOfDataSerialized, arg3, sizeof(arg3_t));
		indexOfDataSerialized += sizeof(arg3_t);





 

	};
	 

};
 


template<templateByteSerializer>
ByteSerializer3<templateargsByteSerializer>* ByteSerializer3<templateargsByteSerializer>::getInstance() {

	if (Instance == 0)
	{
		static ByteSerializer3<templateargsByteSerializer> soleInstance;
		Instance = &soleInstance;
		 
	}
	return Instance;

}
 

template<templateByteSerializer>
ByteSerializer3<templateargsByteSerializer>* ByteSerializer3<templateargsByteSerializer>::Instance = nullptr;




 
#define templateByteSerializer \
class arg1_t ,\
 class arg2_t ,\
 class arg3_t ,\
 class arg4_t

#define templateargsByteSerializer \
arg1_t ,\
 arg2_t ,\
 arg3_t ,\
 arg4_t
 

#define functionargsByteSerializer \
arg1_t* arg1 ,\
 arg2_t* arg2 ,\
 arg3_t* arg3 ,\
 arg4_t* arg4



template<templateByteSerializer>
class ByteSerializer4
{

protected:
	static  ByteSerializer4<templateargsByteSerializer>* getInstance();
	ByteSerializer4(ByteSerializer4<templateargsByteSerializer> const&) = delete;
	void operator=(ByteSerializer4<templateargsByteSerializer> const&) = delete;

	static ByteSerializer4<templateargsByteSerializer>* Instance;
	 
	ByteSerializer4() {};

public:

	static const uint32_t sizeOfCharData = sizeof(arg1_t) 
 + sizeof(arg2_t) 
 + sizeof(arg3_t) 
 + sizeof(arg4_t) ;

	
 

	static void DeSerializeData(char* dataToSerializeFrom, functionargsByteSerializer) {

		uint32_t indexOfDataSerialized = 0;
		 

		 memcpy((void*)arg1, dataToSerializeFrom + indexOfDataSerialized, sizeof(arg1_t));
		indexOfDataSerialized += sizeof(arg1_t);

		 memcpy((void*)arg2, dataToSerializeFrom + indexOfDataSerialized, sizeof(arg2_t));
		indexOfDataSerialized += sizeof(arg2_t);

		 memcpy((void*)arg3, dataToSerializeFrom + indexOfDataSerialized, sizeof(arg3_t));
		indexOfDataSerialized += sizeof(arg3_t);

		 memcpy((void*)arg4, dataToSerializeFrom + indexOfDataSerialized, sizeof(arg4_t));
		indexOfDataSerialized += sizeof(arg4_t);



 


		 
	};

	static void SerializeData(char* dataToSerializeTo, functionargsByteSerializer) {

		uint32_t indexOfDataSerialized = 0;
		//arg1 get size of argument1 and serialize it; 

		 memcpy(dataToSerializeTo+indexOfDataSerialized, arg1, sizeof(arg1_t));
		indexOfDataSerialized += sizeof(arg1_t);

		 memcpy(dataToSerializeTo+indexOfDataSerialized, arg2, sizeof(arg2_t));
		indexOfDataSerialized += sizeof(arg2_t);

		 memcpy(dataToSerializeTo+indexOfDataSerialized, arg3, sizeof(arg3_t));
		indexOfDataSerialized += sizeof(arg3_t);

		 memcpy(dataToSerializeTo+indexOfDataSerialized, arg4, sizeof(arg4_t));
		indexOfDataSerialized += sizeof(arg4_t);



 

	};
	 

};
 


template<templateByteSerializer>
ByteSerializer4<templateargsByteSerializer>* ByteSerializer4<templateargsByteSerializer>::getInstance() {

	if (Instance == 0)
	{
		static ByteSerializer4<templateargsByteSerializer> soleInstance;
		Instance = &soleInstance;
		 
	}
	return Instance;

}
 

template<templateByteSerializer>
ByteSerializer4<templateargsByteSerializer>* ByteSerializer4<templateargsByteSerializer>::Instance = nullptr;




 
#define templateByteSerializer \
class arg1_t ,\
 class arg2_t ,\
 class arg3_t ,\
 class arg4_t ,\
 class arg5_t

#define templateargsByteSerializer \
arg1_t ,\
 arg2_t ,\
 arg3_t ,\
 arg4_t ,\
 arg5_t
 

#define functionargsByteSerializer \
arg1_t* arg1 ,\
 arg2_t* arg2 ,\
 arg3_t* arg3 ,\
 arg4_t* arg4 ,\
 arg5_t* arg5



template<templateByteSerializer>
class ByteSerializer5
{

protected:
	static  ByteSerializer5<templateargsByteSerializer>* getInstance();
	ByteSerializer5(ByteSerializer5<templateargsByteSerializer> const&) = delete;
	void operator=(ByteSerializer5<templateargsByteSerializer> const&) = delete;

	static ByteSerializer5<templateargsByteSerializer>* Instance;
	 
	ByteSerializer5() {};

public:

	static const uint32_t sizeOfCharData = sizeof(arg1_t) 
 + sizeof(arg2_t) 
 + sizeof(arg3_t) 
 + sizeof(arg4_t) 
 + sizeof(arg5_t) ;

	
 

	static void DeSerializeData(char* dataToSerializeFrom, functionargsByteSerializer) {

		uint32_t indexOfDataSerialized = 0;
		 

		 memcpy((void*)arg1, dataToSerializeFrom + indexOfDataSerialized, sizeof(arg1_t));
		indexOfDataSerialized += sizeof(arg1_t);

		 memcpy((void*)arg2, dataToSerializeFrom + indexOfDataSerialized, sizeof(arg2_t));
		indexOfDataSerialized += sizeof(arg2_t);

		 memcpy((void*)arg3, dataToSerializeFrom + indexOfDataSerialized, sizeof(arg3_t));
		indexOfDataSerialized += sizeof(arg3_t);

		 memcpy((void*)arg4, dataToSerializeFrom + indexOfDataSerialized, sizeof(arg4_t));
		indexOfDataSerialized += sizeof(arg4_t);

		 memcpy((void*)arg5, dataToSerializeFrom + indexOfDataSerialized, sizeof(arg5_t));
		indexOfDataSerialized += sizeof(arg5_t);

 


		 
	};

	static void SerializeData(char* dataToSerializeTo, functionargsByteSerializer) {

		uint32_t indexOfDataSerialized = 0;
		//arg1 get size of argument1 and serialize it; 

		 memcpy(dataToSerializeTo+indexOfDataSerialized, arg1, sizeof(arg1_t));
		indexOfDataSerialized += sizeof(arg1_t);

		 memcpy(dataToSerializeTo+indexOfDataSerialized, arg2, sizeof(arg2_t));
		indexOfDataSerialized += sizeof(arg2_t);

		 memcpy(dataToSerializeTo+indexOfDataSerialized, arg3, sizeof(arg3_t));
		indexOfDataSerialized += sizeof(arg3_t);

		 memcpy(dataToSerializeTo+indexOfDataSerialized, arg4, sizeof(arg4_t));
		indexOfDataSerialized += sizeof(arg4_t);

		 memcpy(dataToSerializeTo+indexOfDataSerialized, arg5, sizeof(arg5_t));
		indexOfDataSerialized += sizeof(arg5_t);

 

	};
	 

};
 


template<templateByteSerializer>
ByteSerializer5<templateargsByteSerializer>* ByteSerializer5<templateargsByteSerializer>::getInstance() {

	if (Instance == 0)
	{
		static ByteSerializer5<templateargsByteSerializer> soleInstance;
		Instance = &soleInstance;
		 
	}
	return Instance;

}
 

template<templateByteSerializer>
ByteSerializer5<templateargsByteSerializer>* ByteSerializer5<templateargsByteSerializer>::Instance = nullptr;




 
#define templateByteSerializer \
class arg1_t ,\
 class arg2_t ,\
 class arg3_t ,\
 class arg4_t ,\
 class arg5_t ,\
 class arg6_t

#define templateargsByteSerializer \
arg1_t ,\
 arg2_t ,\
 arg3_t ,\
 arg4_t ,\
 arg5_t ,\
 arg6_t
 

#define functionargsByteSerializer \
arg1_t* arg1 ,\
 arg2_t* arg2 ,\
 arg3_t* arg3 ,\
 arg4_t* arg4 ,\
 arg5_t* arg5 ,\
 arg6_t* arg6



template<templateByteSerializer>
class ByteSerializer6
{

protected:
	static  ByteSerializer6<templateargsByteSerializer>* getInstance();
	ByteSerializer6(ByteSerializer6<templateargsByteSerializer> const&) = delete;
	void operator=(ByteSerializer6<templateargsByteSerializer> const&) = delete;

	static ByteSerializer6<templateargsByteSerializer>* Instance;
	 
	ByteSerializer6() {};

public:

	static const uint32_t sizeOfCharData = sizeof(arg1_t) 
 + sizeof(arg2_t) 
 + sizeof(arg3_t) 
 + sizeof(arg4_t) 
 + sizeof(arg5_t) 
 + sizeof(arg6_t) ;

	
 

	static void DeSerializeData(char* dataToSerializeFrom, functionargsByteSerializer) {

		uint32_t indexOfDataSerialized = 0;
		 

		 memcpy((void*)arg1, dataToSerializeFrom + indexOfDataSerialized, sizeof(arg1_t));
		indexOfDataSerialized += sizeof(arg1_t);

		 memcpy((void*)arg2, dataToSerializeFrom + indexOfDataSerialized, sizeof(arg2_t));
		indexOfDataSerialized += sizeof(arg2_t);

		 memcpy((void*)arg3, dataToSerializeFrom + indexOfDataSerialized, sizeof(arg3_t));
		indexOfDataSerialized += sizeof(arg3_t);

		 memcpy((void*)arg4, dataToSerializeFrom + indexOfDataSerialized, sizeof(arg4_t));
		indexOfDataSerialized += sizeof(arg4_t);

		 memcpy((void*)arg5, dataToSerializeFrom + indexOfDataSerialized, sizeof(arg5_t));
		indexOfDataSerialized += sizeof(arg5_t);

		 memcpy((void*)arg6, dataToSerializeFrom + indexOfDataSerialized, sizeof(arg6_t));
		indexOfDataSerialized += sizeof(arg6_t); 


		 
	};

	static void SerializeData(char* dataToSerializeTo, functionargsByteSerializer) {

		uint32_t indexOfDataSerialized = 0;
		//arg1 get size of argument1 and serialize it; 

		 memcpy(dataToSerializeTo+indexOfDataSerialized, arg1, sizeof(arg1_t));
		indexOfDataSerialized += sizeof(arg1_t);

		 memcpy(dataToSerializeTo+indexOfDataSerialized, arg2, sizeof(arg2_t));
		indexOfDataSerialized += sizeof(arg2_t);

		 memcpy(dataToSerializeTo+indexOfDataSerialized, arg3, sizeof(arg3_t));
		indexOfDataSerialized += sizeof(arg3_t);

		 memcpy(dataToSerializeTo+indexOfDataSerialized, arg4, sizeof(arg4_t));
		indexOfDataSerialized += sizeof(arg4_t);

		 memcpy(dataToSerializeTo+indexOfDataSerialized, arg5, sizeof(arg5_t));
		indexOfDataSerialized += sizeof(arg5_t);

		 memcpy(dataToSerializeTo+indexOfDataSerialized, arg6, sizeof(arg6_t));
		indexOfDataSerialized += sizeof(arg6_t); 

	};
	 

};
 


template<templateByteSerializer>
ByteSerializer6<templateargsByteSerializer>* ByteSerializer6<templateargsByteSerializer>::getInstance() {

	if (Instance == 0)
	{
		static ByteSerializer6<templateargsByteSerializer> soleInstance;
		Instance = &soleInstance;
		 
	}
	return Instance;

}
 

template<templateByteSerializer>
ByteSerializer6<templateargsByteSerializer>* ByteSerializer6<templateargsByteSerializer>::Instance = nullptr;



