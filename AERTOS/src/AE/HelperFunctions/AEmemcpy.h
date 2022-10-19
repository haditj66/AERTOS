//generated file: AEmemcpy.h




#pragma once

#include <cstdint>
#include <string.h>

 
static void AEmemcpyManyFromBottomUp1(
void* dst, void* src
	,uint32_t sizeForAllVars)
{

	//for now the sizes can only be the same for all vars
	uint32_t size = sizeForAllVars;

	// copy by the largest it is divisible by
	uint32_t remainder;
	uint32_t timesToCopy;


	if (size < 10)
	{
		memcpy(dst, src, size);




 
 
 
    
	}
	else if (size <= 100)
	{
		char *destp = (char *)dst; char *srcp = (char *)src;








 

		remainder = size % 10;
		timesToCopy = size / 10;

		//copy elements in increments but always start with an increment of 10
		//up to 100 
		for (uint32_t i = 0; i < timesToCopy; i++)
		{
		 memcpy(destp + (i * 10), srcp + (i * 10), 10); 
	 
	 
	 
	 
	 
	 
	 
	 
 
 
 

		}

		memcpy(destp + (timesToCopy * 10), srcp + (timesToCopy * 10), remainder); 
 
 
 
 
 
 
 
    


	}
	else
	{
		for (uint32_t i = 1000; i < 1000000000; i = i * 10)
		{
			if (size <= i)
			{
					char *destp = (char *)dst; char *srcp = (char *)src;











				//copy 100 elments first
				for (uint32_t i = 0; i < 10; i++)
				{
					memcpy(destp + (i * 10), srcp + (i * 10), 10);
			
			
			
			
			 
			 
			 
			 
		 
		 
		 
				}
				size = size - 100;

				uint32_t incrmentby = (i / 10);
				remainder = size % incrmentby;
				timesToCopy = size / incrmentby;

				for (uint32_t i = 0; i < timesToCopy; i++)
				{
					memcpy(destp + ((i * incrmentby) + 100), (srcp + (i * incrmentby) + 100), incrmentby); 
			 
			 
			 
			 
			 
			 
			 
			 
		 
		 
		 
 
				}

				memcpy(destp + ((timesToCopy * incrmentby) + 100), srcp + ((timesToCopy * incrmentby) + 100), remainder);
		
		
		
		
		 
		 
		 
		 
	 
	 
	 

				break;
			}
		}
	}


}



 
static void AEmemcpyManyFromBottomUp2(
void* dst, void* src  
,void* dst2, void* src2
	,uint32_t sizeForAllVars)
{

	//for now the sizes can only be the same for all vars
	uint32_t size = sizeForAllVars;

	// copy by the largest it is divisible by
	uint32_t remainder;
	uint32_t timesToCopy;


	if (size < 10)
	{
		memcpy(dst, src, size);
		memcpy(dst2, src2, size);



 
 
 
    
	}
	else if (size <= 100)
	{
		char *destp = (char *)dst; char *srcp = (char *)src;
		char *destp2 = (char *)dst2; char *srcp2 = (char *)src2;







 

		remainder = size % 10;
		timesToCopy = size / 10;

		//copy elements in increments but always start with an increment of 10
		//up to 100 
		for (uint32_t i = 0; i < timesToCopy; i++)
		{
		 memcpy(destp + (i * 10), srcp + (i * 10), 10); 
		 memcpy(destp2 + (i * 10), srcp2 + (i * 10), 10); 
	 
	 
	 
	 
	 
	 
	 
 
 
 

		}

		memcpy(destp + (timesToCopy * 10), srcp + (timesToCopy * 10), remainder); 
		memcpy(destp2 + (timesToCopy * 10), srcp2 + (timesToCopy * 10), remainder); 
 
 
 
 
 
 
    


	}
	else
	{
		for (uint32_t i = 1000; i < 1000000000; i = i * 10)
		{
			if (size <= i)
			{
					char *destp = (char *)dst; char *srcp = (char *)src;
		char *destp2 = (char *)dst2; char *srcp2 = (char *)src2;










				//copy 100 elments first
				for (uint32_t i = 0; i < 10; i++)
				{
					memcpy(destp + (i * 10), srcp + (i * 10), 10);
					memcpy(destp2 + (i * 10), srcp2 + (i * 10), 10);
			
			
			
			 
			 
			 
			 
		 
		 
		 
				}
				size = size - 100;

				uint32_t incrmentby = (i / 10);
				remainder = size % incrmentby;
				timesToCopy = size / incrmentby;

				for (uint32_t i = 0; i < timesToCopy; i++)
				{
					memcpy(destp + ((i * incrmentby) + 100), (srcp + (i * incrmentby) + 100), incrmentby); 
					memcpy(destp2 + ((i * incrmentby) + 100), (srcp2 + (i * incrmentby) + 100), incrmentby); 
			 
			 
			 
			 
			 
			 
			 
		 
		 
		 
 
				}

				memcpy(destp + ((timesToCopy * incrmentby) + 100), srcp + ((timesToCopy * incrmentby) + 100), remainder);
				memcpy(destp2 + ((timesToCopy * incrmentby) + 100), srcp2 + ((timesToCopy * incrmentby) + 100), remainder);
		
		
		
		 
		 
		 
		 
	 
	 
	 

				break;
			}
		}
	}


}



 
static void AEmemcpyManyFromBottomUp3(
void* dst, void* src  
,void* dst2, void* src2  
,void* dst3, void* src3
	,uint32_t sizeForAllVars)
{

	//for now the sizes can only be the same for all vars
	uint32_t size = sizeForAllVars;

	// copy by the largest it is divisible by
	uint32_t remainder;
	uint32_t timesToCopy;


	if (size < 10)
	{
		memcpy(dst, src, size);
		memcpy(dst2, src2, size);
		memcpy(dst3, src3, size);


 
 
 
    
	}
	else if (size <= 100)
	{
		char *destp = (char *)dst; char *srcp = (char *)src;
		char *destp2 = (char *)dst2; char *srcp2 = (char *)src2;
		char *destp3 = (char *)dst3; char *srcp3 = (char *)src3;






 

		remainder = size % 10;
		timesToCopy = size / 10;

		//copy elements in increments but always start with an increment of 10
		//up to 100 
		for (uint32_t i = 0; i < timesToCopy; i++)
		{
		 memcpy(destp + (i * 10), srcp + (i * 10), 10); 
		 memcpy(destp2 + (i * 10), srcp2 + (i * 10), 10); 
		 memcpy(destp3 + (i * 10), srcp3 + (i * 10), 10); 
	 
	 
	 
	 
	 
	 
 
 
 

		}

		memcpy(destp + (timesToCopy * 10), srcp + (timesToCopy * 10), remainder); 
		memcpy(destp2 + (timesToCopy * 10), srcp2 + (timesToCopy * 10), remainder); 
		memcpy(destp3 + (timesToCopy * 10), srcp3 + (timesToCopy * 10), remainder); 
 
 
 
 
 
    


	}
	else
	{
		for (uint32_t i = 1000; i < 1000000000; i = i * 10)
		{
			if (size <= i)
			{
					char *destp = (char *)dst; char *srcp = (char *)src;
		char *destp2 = (char *)dst2; char *srcp2 = (char *)src2;
		char *destp3 = (char *)dst3; char *srcp3 = (char *)src3;









				//copy 100 elments first
				for (uint32_t i = 0; i < 10; i++)
				{
					memcpy(destp + (i * 10), srcp + (i * 10), 10);
					memcpy(destp2 + (i * 10), srcp2 + (i * 10), 10);
					memcpy(destp3 + (i * 10), srcp3 + (i * 10), 10);
			
			
			 
			 
			 
			 
		 
		 
		 
				}
				size = size - 100;

				uint32_t incrmentby = (i / 10);
				remainder = size % incrmentby;
				timesToCopy = size / incrmentby;

				for (uint32_t i = 0; i < timesToCopy; i++)
				{
					memcpy(destp + ((i * incrmentby) + 100), (srcp + (i * incrmentby) + 100), incrmentby); 
					memcpy(destp2 + ((i * incrmentby) + 100), (srcp2 + (i * incrmentby) + 100), incrmentby); 
					memcpy(destp3 + ((i * incrmentby) + 100), (srcp3 + (i * incrmentby) + 100), incrmentby); 
			 
			 
			 
			 
			 
			 
		 
		 
		 
 
				}

				memcpy(destp + ((timesToCopy * incrmentby) + 100), srcp + ((timesToCopy * incrmentby) + 100), remainder);
				memcpy(destp2 + ((timesToCopy * incrmentby) + 100), srcp2 + ((timesToCopy * incrmentby) + 100), remainder);
				memcpy(destp3 + ((timesToCopy * incrmentby) + 100), srcp3 + ((timesToCopy * incrmentby) + 100), remainder);
		
		
		 
		 
		 
		 
	 
	 
	 

				break;
			}
		}
	}


}



 
static void AEmemcpyManyFromBottomUp4(
void* dst, void* src  
,void* dst2, void* src2  
,void* dst3, void* src3  
,void* dst4, void* src4
	,uint32_t sizeForAllVars)
{

	//for now the sizes can only be the same for all vars
	uint32_t size = sizeForAllVars;

	// copy by the largest it is divisible by
	uint32_t remainder;
	uint32_t timesToCopy;


	if (size < 10)
	{
		memcpy(dst, src, size);
		memcpy(dst2, src2, size);
		memcpy(dst3, src3, size);
		memcpy(dst4, src4, size);

 
 
 
    
	}
	else if (size <= 100)
	{
		char *destp = (char *)dst; char *srcp = (char *)src;
		char *destp2 = (char *)dst2; char *srcp2 = (char *)src2;
		char *destp3 = (char *)dst3; char *srcp3 = (char *)src3;
		char *destp4 = (char *)dst4; char *srcp4 = (char *)src4;





 

		remainder = size % 10;
		timesToCopy = size / 10;

		//copy elements in increments but always start with an increment of 10
		//up to 100 
		for (uint32_t i = 0; i < timesToCopy; i++)
		{
		 memcpy(destp + (i * 10), srcp + (i * 10), 10); 
		 memcpy(destp2 + (i * 10), srcp2 + (i * 10), 10); 
		 memcpy(destp3 + (i * 10), srcp3 + (i * 10), 10); 
		 memcpy(destp4 + (i * 10), srcp4 + (i * 10), 10); 
	 
	 
	 
	 
	 
 
 
 

		}

		memcpy(destp + (timesToCopy * 10), srcp + (timesToCopy * 10), remainder); 
		memcpy(destp2 + (timesToCopy * 10), srcp2 + (timesToCopy * 10), remainder); 
		memcpy(destp3 + (timesToCopy * 10), srcp3 + (timesToCopy * 10), remainder); 
		memcpy(destp4 + (timesToCopy * 10), srcp4 + (timesToCopy * 10), remainder); 
 
 
 
 
    


	}
	else
	{
		for (uint32_t i = 1000; i < 1000000000; i = i * 10)
		{
			if (size <= i)
			{
					char *destp = (char *)dst; char *srcp = (char *)src;
		char *destp2 = (char *)dst2; char *srcp2 = (char *)src2;
		char *destp3 = (char *)dst3; char *srcp3 = (char *)src3;
		char *destp4 = (char *)dst4; char *srcp4 = (char *)src4;








				//copy 100 elments first
				for (uint32_t i = 0; i < 10; i++)
				{
					memcpy(destp + (i * 10), srcp + (i * 10), 10);
					memcpy(destp2 + (i * 10), srcp2 + (i * 10), 10);
					memcpy(destp3 + (i * 10), srcp3 + (i * 10), 10);
					memcpy(destp4 + (i * 10), srcp4 + (i * 10), 10);
			
			 
			 
			 
			 
		 
		 
		 
				}
				size = size - 100;

				uint32_t incrmentby = (i / 10);
				remainder = size % incrmentby;
				timesToCopy = size / incrmentby;

				for (uint32_t i = 0; i < timesToCopy; i++)
				{
					memcpy(destp + ((i * incrmentby) + 100), (srcp + (i * incrmentby) + 100), incrmentby); 
					memcpy(destp2 + ((i * incrmentby) + 100), (srcp2 + (i * incrmentby) + 100), incrmentby); 
					memcpy(destp3 + ((i * incrmentby) + 100), (srcp3 + (i * incrmentby) + 100), incrmentby); 
					memcpy(destp4 + ((i * incrmentby) + 100), (srcp4 + (i * incrmentby) + 100), incrmentby); 
			 
			 
			 
			 
			 
		 
		 
		 
 
				}

				memcpy(destp + ((timesToCopy * incrmentby) + 100), srcp + ((timesToCopy * incrmentby) + 100), remainder);
				memcpy(destp2 + ((timesToCopy * incrmentby) + 100), srcp2 + ((timesToCopy * incrmentby) + 100), remainder);
				memcpy(destp3 + ((timesToCopy * incrmentby) + 100), srcp3 + ((timesToCopy * incrmentby) + 100), remainder);
				memcpy(destp4 + ((timesToCopy * incrmentby) + 100), srcp4 + ((timesToCopy * incrmentby) + 100), remainder);
		
		 
		 
		 
		 
	 
	 
	 

				break;
			}
		}
	}


}



 
static void AEmemcpyManyFromBottomUp5(
void* dst, void* src  
,void* dst2, void* src2  
,void* dst3, void* src3  
,void* dst4, void* src4  
,void* dst5, void* src5
	,uint32_t sizeForAllVars)
{

	//for now the sizes can only be the same for all vars
	uint32_t size = sizeForAllVars;

	// copy by the largest it is divisible by
	uint32_t remainder;
	uint32_t timesToCopy;


	if (size < 10)
	{
		memcpy(dst, src, size);
		memcpy(dst2, src2, size);
		memcpy(dst3, src3, size);
		memcpy(dst4, src4, size);
		memcpy(dst5, src5, size);
 
 
 
    
	}
	else if (size <= 100)
	{
		char *destp = (char *)dst; char *srcp = (char *)src;
		char *destp2 = (char *)dst2; char *srcp2 = (char *)src2;
		char *destp3 = (char *)dst3; char *srcp3 = (char *)src3;
		char *destp4 = (char *)dst4; char *srcp4 = (char *)src4;
		char *destp5 = (char *)dst5; char *srcp5 = (char *)src5;




 

		remainder = size % 10;
		timesToCopy = size / 10;

		//copy elements in increments but always start with an increment of 10
		//up to 100 
		for (uint32_t i = 0; i < timesToCopy; i++)
		{
		 memcpy(destp + (i * 10), srcp + (i * 10), 10); 
		 memcpy(destp2 + (i * 10), srcp2 + (i * 10), 10); 
		 memcpy(destp3 + (i * 10), srcp3 + (i * 10), 10); 
		 memcpy(destp4 + (i * 10), srcp4 + (i * 10), 10); 
		 memcpy(destp5 + (i * 10), srcp5 + (i * 10), 10); 
	 
	 
	 
	 
 
 
 

		}

		memcpy(destp + (timesToCopy * 10), srcp + (timesToCopy * 10), remainder); 
		memcpy(destp2 + (timesToCopy * 10), srcp2 + (timesToCopy * 10), remainder); 
		memcpy(destp3 + (timesToCopy * 10), srcp3 + (timesToCopy * 10), remainder); 
		memcpy(destp4 + (timesToCopy * 10), srcp4 + (timesToCopy * 10), remainder); 
		memcpy(destp5 + (timesToCopy * 10), srcp5 + (timesToCopy * 10), remainder); 
 
 
 
    


	}
	else
	{
		for (uint32_t i = 1000; i < 1000000000; i = i * 10)
		{
			if (size <= i)
			{
					char *destp = (char *)dst; char *srcp = (char *)src;
		char *destp2 = (char *)dst2; char *srcp2 = (char *)src2;
		char *destp3 = (char *)dst3; char *srcp3 = (char *)src3;
		char *destp4 = (char *)dst4; char *srcp4 = (char *)src4;
		char *destp5 = (char *)dst5; char *srcp5 = (char *)src5;







				//copy 100 elments first
				for (uint32_t i = 0; i < 10; i++)
				{
					memcpy(destp + (i * 10), srcp + (i * 10), 10);
					memcpy(destp2 + (i * 10), srcp2 + (i * 10), 10);
					memcpy(destp3 + (i * 10), srcp3 + (i * 10), 10);
					memcpy(destp4 + (i * 10), srcp4 + (i * 10), 10);
					memcpy(destp5 + (i * 10), srcp5 + (i * 10), 10);
			 
			 
			 
			 
		 
		 
		 
				}
				size = size - 100;

				uint32_t incrmentby = (i / 10);
				remainder = size % incrmentby;
				timesToCopy = size / incrmentby;

				for (uint32_t i = 0; i < timesToCopy; i++)
				{
					memcpy(destp + ((i * incrmentby) + 100), (srcp + (i * incrmentby) + 100), incrmentby); 
					memcpy(destp2 + ((i * incrmentby) + 100), (srcp2 + (i * incrmentby) + 100), incrmentby); 
					memcpy(destp3 + ((i * incrmentby) + 100), (srcp3 + (i * incrmentby) + 100), incrmentby); 
					memcpy(destp4 + ((i * incrmentby) + 100), (srcp4 + (i * incrmentby) + 100), incrmentby); 
					memcpy(destp5 + ((i * incrmentby) + 100), (srcp5 + (i * incrmentby) + 100), incrmentby); 
			 
			 
			 
			 
		 
		 
		 
 
				}

				memcpy(destp + ((timesToCopy * incrmentby) + 100), srcp + ((timesToCopy * incrmentby) + 100), remainder);
				memcpy(destp2 + ((timesToCopy * incrmentby) + 100), srcp2 + ((timesToCopy * incrmentby) + 100), remainder);
				memcpy(destp3 + ((timesToCopy * incrmentby) + 100), srcp3 + ((timesToCopy * incrmentby) + 100), remainder);
				memcpy(destp4 + ((timesToCopy * incrmentby) + 100), srcp4 + ((timesToCopy * incrmentby) + 100), remainder);
				memcpy(destp5 + ((timesToCopy * incrmentby) + 100), srcp5 + ((timesToCopy * incrmentby) + 100), remainder);
		 
		 
		 
		 
	 
	 
	 

				break;
			}
		}
	}


}



 
static void AEmemcpyManyFromBottomUp6(
void* dst, void* src  
,void* dst2, void* src2  
,void* dst3, void* src3  
,void* dst4, void* src4  
,void* dst5, void* src5  
,void* dst6, void* src6
	,uint32_t sizeForAllVars)
{

	//for now the sizes can only be the same for all vars
	uint32_t size = sizeForAllVars;

	// copy by the largest it is divisible by
	uint32_t remainder;
	uint32_t timesToCopy;


	if (size < 10)
	{
		memcpy(dst, src, size);
		memcpy(dst2, src2, size);
		memcpy(dst3, src3, size);
		memcpy(dst4, src4, size);
		memcpy(dst5, src5, size);
		memcpy(dst6, src6, size); 
 
 
    
	}
	else if (size <= 100)
	{
		char *destp = (char *)dst; char *srcp = (char *)src;
		char *destp2 = (char *)dst2; char *srcp2 = (char *)src2;
		char *destp3 = (char *)dst3; char *srcp3 = (char *)src3;
		char *destp4 = (char *)dst4; char *srcp4 = (char *)src4;
		char *destp5 = (char *)dst5; char *srcp5 = (char *)src5;
		char *destp6 = (char *)dst6; char *srcp6 = (char *)src6;



 

		remainder = size % 10;
		timesToCopy = size / 10;

		//copy elements in increments but always start with an increment of 10
		//up to 100 
		for (uint32_t i = 0; i < timesToCopy; i++)
		{
		 memcpy(destp + (i * 10), srcp + (i * 10), 10); 
		 memcpy(destp2 + (i * 10), srcp2 + (i * 10), 10); 
		 memcpy(destp3 + (i * 10), srcp3 + (i * 10), 10); 
		 memcpy(destp4 + (i * 10), srcp4 + (i * 10), 10); 
		 memcpy(destp5 + (i * 10), srcp5 + (i * 10), 10); 
		 memcpy(destp6 + (i * 10), srcp6 + (i * 10), 10); 
	 
	 
	 
 
 
 

		}

		memcpy(destp + (timesToCopy * 10), srcp + (timesToCopy * 10), remainder); 
		memcpy(destp2 + (timesToCopy * 10), srcp2 + (timesToCopy * 10), remainder); 
		memcpy(destp3 + (timesToCopy * 10), srcp3 + (timesToCopy * 10), remainder); 
		memcpy(destp4 + (timesToCopy * 10), srcp4 + (timesToCopy * 10), remainder); 
		memcpy(destp5 + (timesToCopy * 10), srcp5 + (timesToCopy * 10), remainder); 
		memcpy(destp6 + (timesToCopy * 10), srcp6 + (timesToCopy * 10), remainder); 
 
 
    


	}
	else
	{
		for (uint32_t i = 1000; i < 1000000000; i = i * 10)
		{
			if (size <= i)
			{
					char *destp = (char *)dst; char *srcp = (char *)src;
		char *destp2 = (char *)dst2; char *srcp2 = (char *)src2;
		char *destp3 = (char *)dst3; char *srcp3 = (char *)src3;
		char *destp4 = (char *)dst4; char *srcp4 = (char *)src4;
		char *destp5 = (char *)dst5; char *srcp5 = (char *)src5;
		char *destp6 = (char *)dst6; char *srcp6 = (char *)src6;






				//copy 100 elments first
				for (uint32_t i = 0; i < 10; i++)
				{
					memcpy(destp + (i * 10), srcp + (i * 10), 10);
					memcpy(destp2 + (i * 10), srcp2 + (i * 10), 10);
					memcpy(destp3 + (i * 10), srcp3 + (i * 10), 10);
					memcpy(destp4 + (i * 10), srcp4 + (i * 10), 10);
					memcpy(destp5 + (i * 10), srcp5 + (i * 10), 10);
					memcpy(destp6 + (i * 10), srcp6 + (i * 10), 10); 
			 
			 
			 
		 
		 
		 
				}
				size = size - 100;

				uint32_t incrmentby = (i / 10);
				remainder = size % incrmentby;
				timesToCopy = size / incrmentby;

				for (uint32_t i = 0; i < timesToCopy; i++)
				{
					memcpy(destp + ((i * incrmentby) + 100), (srcp + (i * incrmentby) + 100), incrmentby); 
					memcpy(destp2 + ((i * incrmentby) + 100), (srcp2 + (i * incrmentby) + 100), incrmentby); 
					memcpy(destp3 + ((i * incrmentby) + 100), (srcp3 + (i * incrmentby) + 100), incrmentby); 
					memcpy(destp4 + ((i * incrmentby) + 100), (srcp4 + (i * incrmentby) + 100), incrmentby); 
					memcpy(destp5 + ((i * incrmentby) + 100), (srcp5 + (i * incrmentby) + 100), incrmentby); 
					memcpy(destp6 + ((i * incrmentby) + 100), (srcp6 + (i * incrmentby) + 100), incrmentby); 
			 
			 
			 
		 
		 
		 
 
				}

				memcpy(destp + ((timesToCopy * incrmentby) + 100), srcp + ((timesToCopy * incrmentby) + 100), remainder);
				memcpy(destp2 + ((timesToCopy * incrmentby) + 100), srcp2 + ((timesToCopy * incrmentby) + 100), remainder);
				memcpy(destp3 + ((timesToCopy * incrmentby) + 100), srcp3 + ((timesToCopy * incrmentby) + 100), remainder);
				memcpy(destp4 + ((timesToCopy * incrmentby) + 100), srcp4 + ((timesToCopy * incrmentby) + 100), remainder);
				memcpy(destp5 + ((timesToCopy * incrmentby) + 100), srcp5 + ((timesToCopy * incrmentby) + 100), remainder);
				memcpy(destp6 + ((timesToCopy * incrmentby) + 100), srcp6 + ((timesToCopy * incrmentby) + 100), remainder); 
		 
		 
		 
	 
	 
	 

				break;
			}
		}
	}


}



 
static void AEmemcpyManyFromBottomUp7(
void* dst, void* src  
,void* dst2, void* src2  
,void* dst3, void* src3  
,void* dst4, void* src4  
,void* dst5, void* src5  
,void* dst6, void* src6   
,void* dst7, void* src7
	,uint32_t sizeForAllVars)
{

	//for now the sizes can only be the same for all vars
	uint32_t size = sizeForAllVars;

	// copy by the largest it is divisible by
	uint32_t remainder;
	uint32_t timesToCopy;


	if (size < 10)
	{
		memcpy(dst, src, size);
		memcpy(dst2, src2, size);
		memcpy(dst3, src3, size);
		memcpy(dst4, src4, size);
		memcpy(dst5, src5, size);
		memcpy(dst6, src6, size); 
		memcpy(dst7, src7, size); 
 
    
	}
	else if (size <= 100)
	{
		char *destp = (char *)dst; char *srcp = (char *)src;
		char *destp2 = (char *)dst2; char *srcp2 = (char *)src2;
		char *destp3 = (char *)dst3; char *srcp3 = (char *)src3;
		char *destp4 = (char *)dst4; char *srcp4 = (char *)src4;
		char *destp5 = (char *)dst5; char *srcp5 = (char *)src5;
		char *destp6 = (char *)dst6; char *srcp6 = (char *)src6;
		char *destp7 = (char *)dst7; char *srcp7 = (char *)src7;


 

		remainder = size % 10;
		timesToCopy = size / 10;

		//copy elements in increments but always start with an increment of 10
		//up to 100 
		for (uint32_t i = 0; i < timesToCopy; i++)
		{
		 memcpy(destp + (i * 10), srcp + (i * 10), 10); 
		 memcpy(destp2 + (i * 10), srcp2 + (i * 10), 10); 
		 memcpy(destp3 + (i * 10), srcp3 + (i * 10), 10); 
		 memcpy(destp4 + (i * 10), srcp4 + (i * 10), 10); 
		 memcpy(destp5 + (i * 10), srcp5 + (i * 10), 10); 
		 memcpy(destp6 + (i * 10), srcp6 + (i * 10), 10); 
		 memcpy(destp7 + (i * 10), srcp7 + (i * 10), 10); 
	 
	 
 
 
 

		}

		memcpy(destp + (timesToCopy * 10), srcp + (timesToCopy * 10), remainder); 
		memcpy(destp2 + (timesToCopy * 10), srcp2 + (timesToCopy * 10), remainder); 
		memcpy(destp3 + (timesToCopy * 10), srcp3 + (timesToCopy * 10), remainder); 
		memcpy(destp4 + (timesToCopy * 10), srcp4 + (timesToCopy * 10), remainder); 
		memcpy(destp5 + (timesToCopy * 10), srcp5 + (timesToCopy * 10), remainder); 
		memcpy(destp6 + (timesToCopy * 10), srcp6 + (timesToCopy * 10), remainder); 
		memcpy(destp7 + (timesToCopy * 10), srcp7 + (timesToCopy * 10), remainder); 
 
    


	}
	else
	{
		for (uint32_t i = 1000; i < 1000000000; i = i * 10)
		{
			if (size <= i)
			{
					char *destp = (char *)dst; char *srcp = (char *)src;
		char *destp2 = (char *)dst2; char *srcp2 = (char *)src2;
		char *destp3 = (char *)dst3; char *srcp3 = (char *)src3;
		char *destp4 = (char *)dst4; char *srcp4 = (char *)src4;
		char *destp5 = (char *)dst5; char *srcp5 = (char *)src5;
		char *destp6 = (char *)dst6; char *srcp6 = (char *)src6;
		char *destp7 = (char *)dst7; char *srcp7 = (char *)src7;





				//copy 100 elments first
				for (uint32_t i = 0; i < 10; i++)
				{
					memcpy(destp + (i * 10), srcp + (i * 10), 10);
					memcpy(destp2 + (i * 10), srcp2 + (i * 10), 10);
					memcpy(destp3 + (i * 10), srcp3 + (i * 10), 10);
					memcpy(destp4 + (i * 10), srcp4 + (i * 10), 10);
					memcpy(destp5 + (i * 10), srcp5 + (i * 10), 10);
					memcpy(destp6 + (i * 10), srcp6 + (i * 10), 10); 
					memcpy(destp7 + (i * 10), srcp7 + (i * 10), 10); 
			 
			 
		 
		 
		 
				}
				size = size - 100;

				uint32_t incrmentby = (i / 10);
				remainder = size % incrmentby;
				timesToCopy = size / incrmentby;

				for (uint32_t i = 0; i < timesToCopy; i++)
				{
					memcpy(destp + ((i * incrmentby) + 100), (srcp + (i * incrmentby) + 100), incrmentby); 
					memcpy(destp2 + ((i * incrmentby) + 100), (srcp2 + (i * incrmentby) + 100), incrmentby); 
					memcpy(destp3 + ((i * incrmentby) + 100), (srcp3 + (i * incrmentby) + 100), incrmentby); 
					memcpy(destp4 + ((i * incrmentby) + 100), (srcp4 + (i * incrmentby) + 100), incrmentby); 
					memcpy(destp5 + ((i * incrmentby) + 100), (srcp5 + (i * incrmentby) + 100), incrmentby); 
					memcpy(destp6 + ((i * incrmentby) + 100), (srcp6 + (i * incrmentby) + 100), incrmentby); 
					memcpy(destp7 + ((i * incrmentby) + 100), (srcp7 + (i * incrmentby) + 100), incrmentby); 
			 
			 
		 
		 
		 
 
				}

				memcpy(destp + ((timesToCopy * incrmentby) + 100), srcp + ((timesToCopy * incrmentby) + 100), remainder);
				memcpy(destp2 + ((timesToCopy * incrmentby) + 100), srcp2 + ((timesToCopy * incrmentby) + 100), remainder);
				memcpy(destp3 + ((timesToCopy * incrmentby) + 100), srcp3 + ((timesToCopy * incrmentby) + 100), remainder);
				memcpy(destp4 + ((timesToCopy * incrmentby) + 100), srcp4 + ((timesToCopy * incrmentby) + 100), remainder);
				memcpy(destp5 + ((timesToCopy * incrmentby) + 100), srcp5 + ((timesToCopy * incrmentby) + 100), remainder);
				memcpy(destp6 + ((timesToCopy * incrmentby) + 100), srcp6 + ((timesToCopy * incrmentby) + 100), remainder); 
				memcpy(destp7 + ((timesToCopy * incrmentby) + 100), srcp7 + ((timesToCopy * incrmentby) + 100), remainder); 
		 
		 
	 
	 
	 

				break;
			}
		}
	}


}



 
static void AEmemcpyManyFromBottomUp8(
void* dst, void* src  
,void* dst2, void* src2  
,void* dst3, void* src3  
,void* dst4, void* src4  
,void* dst5, void* src5  
,void* dst6, void* src6   
,void* dst7, void* src7   
,void* dst8, void* src8
	,uint32_t sizeForAllVars)
{

	//for now the sizes can only be the same for all vars
	uint32_t size = sizeForAllVars;

	// copy by the largest it is divisible by
	uint32_t remainder;
	uint32_t timesToCopy;


	if (size < 10)
	{
		memcpy(dst, src, size);
		memcpy(dst2, src2, size);
		memcpy(dst3, src3, size);
		memcpy(dst4, src4, size);
		memcpy(dst5, src5, size);
		memcpy(dst6, src6, size); 
		memcpy(dst7, src7, size); 
		memcpy(dst8, src8, size); 
    
	}
	else if (size <= 100)
	{
		char *destp = (char *)dst; char *srcp = (char *)src;
		char *destp2 = (char *)dst2; char *srcp2 = (char *)src2;
		char *destp3 = (char *)dst3; char *srcp3 = (char *)src3;
		char *destp4 = (char *)dst4; char *srcp4 = (char *)src4;
		char *destp5 = (char *)dst5; char *srcp5 = (char *)src5;
		char *destp6 = (char *)dst6; char *srcp6 = (char *)src6;
		char *destp7 = (char *)dst7; char *srcp7 = (char *)src7;
		char *destp8 = (char *)dst8; char *srcp8 = (char *)src8;

 

		remainder = size % 10;
		timesToCopy = size / 10;

		//copy elements in increments but always start with an increment of 10
		//up to 100 
		for (uint32_t i = 0; i < timesToCopy; i++)
		{
		 memcpy(destp + (i * 10), srcp + (i * 10), 10); 
		 memcpy(destp2 + (i * 10), srcp2 + (i * 10), 10); 
		 memcpy(destp3 + (i * 10), srcp3 + (i * 10), 10); 
		 memcpy(destp4 + (i * 10), srcp4 + (i * 10), 10); 
		 memcpy(destp5 + (i * 10), srcp5 + (i * 10), 10); 
		 memcpy(destp6 + (i * 10), srcp6 + (i * 10), 10); 
		 memcpy(destp7 + (i * 10), srcp7 + (i * 10), 10); 
		 memcpy(destp8 + (i * 10), srcp8 + (i * 10), 10); 
	 
 
 
 

		}

		memcpy(destp + (timesToCopy * 10), srcp + (timesToCopy * 10), remainder); 
		memcpy(destp2 + (timesToCopy * 10), srcp2 + (timesToCopy * 10), remainder); 
		memcpy(destp3 + (timesToCopy * 10), srcp3 + (timesToCopy * 10), remainder); 
		memcpy(destp4 + (timesToCopy * 10), srcp4 + (timesToCopy * 10), remainder); 
		memcpy(destp5 + (timesToCopy * 10), srcp5 + (timesToCopy * 10), remainder); 
		memcpy(destp6 + (timesToCopy * 10), srcp6 + (timesToCopy * 10), remainder); 
		memcpy(destp7 + (timesToCopy * 10), srcp7 + (timesToCopy * 10), remainder); 
		memcpy(destp8 + (timesToCopy * 10), srcp8 + (timesToCopy * 10), remainder); 
    


	}
	else
	{
		for (uint32_t i = 1000; i < 1000000000; i = i * 10)
		{
			if (size <= i)
			{
					char *destp = (char *)dst; char *srcp = (char *)src;
		char *destp2 = (char *)dst2; char *srcp2 = (char *)src2;
		char *destp3 = (char *)dst3; char *srcp3 = (char *)src3;
		char *destp4 = (char *)dst4; char *srcp4 = (char *)src4;
		char *destp5 = (char *)dst5; char *srcp5 = (char *)src5;
		char *destp6 = (char *)dst6; char *srcp6 = (char *)src6;
		char *destp7 = (char *)dst7; char *srcp7 = (char *)src7;
		char *destp8 = (char *)dst8; char *srcp8 = (char *)src8;




				//copy 100 elments first
				for (uint32_t i = 0; i < 10; i++)
				{
					memcpy(destp + (i * 10), srcp + (i * 10), 10);
					memcpy(destp2 + (i * 10), srcp2 + (i * 10), 10);
					memcpy(destp3 + (i * 10), srcp3 + (i * 10), 10);
					memcpy(destp4 + (i * 10), srcp4 + (i * 10), 10);
					memcpy(destp5 + (i * 10), srcp5 + (i * 10), 10);
					memcpy(destp6 + (i * 10), srcp6 + (i * 10), 10); 
					memcpy(destp7 + (i * 10), srcp7 + (i * 10), 10); 
					memcpy(destp8 + (i * 10), srcp8 + (i * 10), 10); 
			 
		 
		 
		 
				}
				size = size - 100;

				uint32_t incrmentby = (i / 10);
				remainder = size % incrmentby;
				timesToCopy = size / incrmentby;

				for (uint32_t i = 0; i < timesToCopy; i++)
				{
					memcpy(destp + ((i * incrmentby) + 100), (srcp + (i * incrmentby) + 100), incrmentby); 
					memcpy(destp2 + ((i * incrmentby) + 100), (srcp2 + (i * incrmentby) + 100), incrmentby); 
					memcpy(destp3 + ((i * incrmentby) + 100), (srcp3 + (i * incrmentby) + 100), incrmentby); 
					memcpy(destp4 + ((i * incrmentby) + 100), (srcp4 + (i * incrmentby) + 100), incrmentby); 
					memcpy(destp5 + ((i * incrmentby) + 100), (srcp5 + (i * incrmentby) + 100), incrmentby); 
					memcpy(destp6 + ((i * incrmentby) + 100), (srcp6 + (i * incrmentby) + 100), incrmentby); 
					memcpy(destp7 + ((i * incrmentby) + 100), (srcp7 + (i * incrmentby) + 100), incrmentby); 
					memcpy(destp8 + ((i * incrmentby) + 100), (srcp8 + (i * incrmentby) + 100), incrmentby); 
			 
		 
		 
		 
 
				}

				memcpy(destp + ((timesToCopy * incrmentby) + 100), srcp + ((timesToCopy * incrmentby) + 100), remainder);
				memcpy(destp2 + ((timesToCopy * incrmentby) + 100), srcp2 + ((timesToCopy * incrmentby) + 100), remainder);
				memcpy(destp3 + ((timesToCopy * incrmentby) + 100), srcp3 + ((timesToCopy * incrmentby) + 100), remainder);
				memcpy(destp4 + ((timesToCopy * incrmentby) + 100), srcp4 + ((timesToCopy * incrmentby) + 100), remainder);
				memcpy(destp5 + ((timesToCopy * incrmentby) + 100), srcp5 + ((timesToCopy * incrmentby) + 100), remainder);
				memcpy(destp6 + ((timesToCopy * incrmentby) + 100), srcp6 + ((timesToCopy * incrmentby) + 100), remainder); 
				memcpy(destp7 + ((timesToCopy * incrmentby) + 100), srcp7 + ((timesToCopy * incrmentby) + 100), remainder); 
				memcpy(destp8 + ((timesToCopy * incrmentby) + 100), srcp8 + ((timesToCopy * incrmentby) + 100), remainder); 
		 
	 
	 
	 

				break;
			}
		}
	}


}



 
static void AEmemcpyManyFromBottomUp9(
void* dst, void* src  
,void* dst2, void* src2  
,void* dst3, void* src3  
,void* dst4, void* src4  
,void* dst5, void* src5  
,void* dst6, void* src6   
,void* dst7, void* src7   
,void* dst8, void* src8   
,void* dst9, void* src9
	,uint32_t sizeForAllVars)
{

	//for now the sizes can only be the same for all vars
	uint32_t size = sizeForAllVars;

	// copy by the largest it is divisible by
	uint32_t remainder;
	uint32_t timesToCopy;


	if (size < 10)
	{
		memcpy(dst, src, size);
		memcpy(dst2, src2, size);
		memcpy(dst3, src3, size);
		memcpy(dst4, src4, size);
		memcpy(dst5, src5, size);
		memcpy(dst6, src6, size); 
		memcpy(dst7, src7, size); 
		memcpy(dst8, src8, size); 
		memcpy(dst9, src9, size);    
	}
	else if (size <= 100)
	{
		char *destp = (char *)dst; char *srcp = (char *)src;
		char *destp2 = (char *)dst2; char *srcp2 = (char *)src2;
		char *destp3 = (char *)dst3; char *srcp3 = (char *)src3;
		char *destp4 = (char *)dst4; char *srcp4 = (char *)src4;
		char *destp5 = (char *)dst5; char *srcp5 = (char *)src5;
		char *destp6 = (char *)dst6; char *srcp6 = (char *)src6;
		char *destp7 = (char *)dst7; char *srcp7 = (char *)src7;
		char *destp8 = (char *)dst8; char *srcp8 = (char *)src8;
		char *destp9 = (char *)dst9; char *srcp9 = (char *)src9;
 

		remainder = size % 10;
		timesToCopy = size / 10;

		//copy elements in increments but always start with an increment of 10
		//up to 100 
		for (uint32_t i = 0; i < timesToCopy; i++)
		{
		 memcpy(destp + (i * 10), srcp + (i * 10), 10); 
		 memcpy(destp2 + (i * 10), srcp2 + (i * 10), 10); 
		 memcpy(destp3 + (i * 10), srcp3 + (i * 10), 10); 
		 memcpy(destp4 + (i * 10), srcp4 + (i * 10), 10); 
		 memcpy(destp5 + (i * 10), srcp5 + (i * 10), 10); 
		 memcpy(destp6 + (i * 10), srcp6 + (i * 10), 10); 
		 memcpy(destp7 + (i * 10), srcp7 + (i * 10), 10); 
		 memcpy(destp8 + (i * 10), srcp8 + (i * 10), 10); 
		 memcpy(destp9 + (i * 10), srcp9 + (i * 10), 10); 
 
 
 

		}

		memcpy(destp + (timesToCopy * 10), srcp + (timesToCopy * 10), remainder); 
		memcpy(destp2 + (timesToCopy * 10), srcp2 + (timesToCopy * 10), remainder); 
		memcpy(destp3 + (timesToCopy * 10), srcp3 + (timesToCopy * 10), remainder); 
		memcpy(destp4 + (timesToCopy * 10), srcp4 + (timesToCopy * 10), remainder); 
		memcpy(destp5 + (timesToCopy * 10), srcp5 + (timesToCopy * 10), remainder); 
		memcpy(destp6 + (timesToCopy * 10), srcp6 + (timesToCopy * 10), remainder); 
		memcpy(destp7 + (timesToCopy * 10), srcp7 + (timesToCopy * 10), remainder); 
		memcpy(destp8 + (timesToCopy * 10), srcp8 + (timesToCopy * 10), remainder); 
		memcpy(destp9 + (timesToCopy * 10), srcp9 + (timesToCopy * 10), remainder);    


	}
	else
	{
		for (uint32_t i = 1000; i < 1000000000; i = i * 10)
		{
			if (size <= i)
			{
					char *destp = (char *)dst; char *srcp = (char *)src;
		char *destp2 = (char *)dst2; char *srcp2 = (char *)src2;
		char *destp3 = (char *)dst3; char *srcp3 = (char *)src3;
		char *destp4 = (char *)dst4; char *srcp4 = (char *)src4;
		char *destp5 = (char *)dst5; char *srcp5 = (char *)src5;
		char *destp6 = (char *)dst6; char *srcp6 = (char *)src6;
		char *destp7 = (char *)dst7; char *srcp7 = (char *)src7;
		char *destp8 = (char *)dst8; char *srcp8 = (char *)src8;
		char *destp9 = (char *)dst9; char *srcp9 = (char *)src9;



				//copy 100 elments first
				for (uint32_t i = 0; i < 10; i++)
				{
					memcpy(destp + (i * 10), srcp + (i * 10), 10);
					memcpy(destp2 + (i * 10), srcp2 + (i * 10), 10);
					memcpy(destp3 + (i * 10), srcp3 + (i * 10), 10);
					memcpy(destp4 + (i * 10), srcp4 + (i * 10), 10);
					memcpy(destp5 + (i * 10), srcp5 + (i * 10), 10);
					memcpy(destp6 + (i * 10), srcp6 + (i * 10), 10); 
					memcpy(destp7 + (i * 10), srcp7 + (i * 10), 10); 
					memcpy(destp8 + (i * 10), srcp8 + (i * 10), 10); 
					memcpy(destp9 + (i * 10), srcp9 + (i * 10), 10); 
		 
		 
		 
				}
				size = size - 100;

				uint32_t incrmentby = (i / 10);
				remainder = size % incrmentby;
				timesToCopy = size / incrmentby;

				for (uint32_t i = 0; i < timesToCopy; i++)
				{
					memcpy(destp + ((i * incrmentby) + 100), (srcp + (i * incrmentby) + 100), incrmentby); 
					memcpy(destp2 + ((i * incrmentby) + 100), (srcp2 + (i * incrmentby) + 100), incrmentby); 
					memcpy(destp3 + ((i * incrmentby) + 100), (srcp3 + (i * incrmentby) + 100), incrmentby); 
					memcpy(destp4 + ((i * incrmentby) + 100), (srcp4 + (i * incrmentby) + 100), incrmentby); 
					memcpy(destp5 + ((i * incrmentby) + 100), (srcp5 + (i * incrmentby) + 100), incrmentby); 
					memcpy(destp6 + ((i * incrmentby) + 100), (srcp6 + (i * incrmentby) + 100), incrmentby); 
					memcpy(destp7 + ((i * incrmentby) + 100), (srcp7 + (i * incrmentby) + 100), incrmentby); 
					memcpy(destp8 + ((i * incrmentby) + 100), (srcp8 + (i * incrmentby) + 100), incrmentby); 
					memcpy(destp9 + ((i * incrmentby) + 100), (srcp9 + (i * incrmentby) + 100), incrmentby); 
		 
		 
		 
 
				}

				memcpy(destp + ((timesToCopy * incrmentby) + 100), srcp + ((timesToCopy * incrmentby) + 100), remainder);
				memcpy(destp2 + ((timesToCopy * incrmentby) + 100), srcp2 + ((timesToCopy * incrmentby) + 100), remainder);
				memcpy(destp3 + ((timesToCopy * incrmentby) + 100), srcp3 + ((timesToCopy * incrmentby) + 100), remainder);
				memcpy(destp4 + ((timesToCopy * incrmentby) + 100), srcp4 + ((timesToCopy * incrmentby) + 100), remainder);
				memcpy(destp5 + ((timesToCopy * incrmentby) + 100), srcp5 + ((timesToCopy * incrmentby) + 100), remainder);
				memcpy(destp6 + ((timesToCopy * incrmentby) + 100), srcp6 + ((timesToCopy * incrmentby) + 100), remainder); 
				memcpy(destp7 + ((timesToCopy * incrmentby) + 100), srcp7 + ((timesToCopy * incrmentby) + 100), remainder); 
				memcpy(destp8 + ((timesToCopy * incrmentby) + 100), srcp8 + ((timesToCopy * incrmentby) + 100), remainder); 
				memcpy(destp9 + ((timesToCopy * incrmentby) + 100), srcp9 + ((timesToCopy * incrmentby) + 100), remainder); 
	 
	 
	 

				break;
			}
		}
	}


}



 
static void AEmemcpyManyFromBottomUp10(
void* dst, void* src  
,void* dst2, void* src2  
,void* dst3, void* src3  
,void* dst4, void* src4  
,void* dst5, void* src5  
,void* dst6, void* src6   
,void* dst7, void* src7   
,void* dst8, void* src8   
,void* dst9, void* src9   
,void* dst10, void* src10  
	,uint32_t sizeForAllVars)
{

	//for now the sizes can only be the same for all vars
	uint32_t size = sizeForAllVars;

	// copy by the largest it is divisible by
	uint32_t remainder;
	uint32_t timesToCopy;


	if (size < 10)
	{
		memcpy(dst, src, size);
		memcpy(dst2, src2, size);
		memcpy(dst3, src3, size);
		memcpy(dst4, src4, size);
		memcpy(dst5, src5, size);
		memcpy(dst6, src6, size); 
		memcpy(dst7, src7, size); 
		memcpy(dst8, src8, size); 
		memcpy(dst9, src9, size); 
		memcpy(dst10, src10, size);   
	}
	else if (size <= 100)
	{
		char *destp = (char *)dst; char *srcp = (char *)src;
		char *destp2 = (char *)dst2; char *srcp2 = (char *)src2;
		char *destp3 = (char *)dst3; char *srcp3 = (char *)src3;
		char *destp4 = (char *)dst4; char *srcp4 = (char *)src4;
		char *destp5 = (char *)dst5; char *srcp5 = (char *)src5;
		char *destp6 = (char *)dst6; char *srcp6 = (char *)src6;
		char *destp7 = (char *)dst7; char *srcp7 = (char *)src7;
		char *destp8 = (char *)dst8; char *srcp8 = (char *)src8;
		char *destp9 = (char *)dst9; char *srcp9 = (char *)src9;
		char *destp10 = (char *)dst10; char *srcp10 = (char *)src10;
 

		remainder = size % 10;
		timesToCopy = size / 10;

		//copy elements in increments but always start with an increment of 10
		//up to 100 
		for (uint32_t i = 0; i < timesToCopy; i++)
		{
		 memcpy(destp + (i * 10), srcp + (i * 10), 10); 
		 memcpy(destp2 + (i * 10), srcp2 + (i * 10), 10); 
		 memcpy(destp3 + (i * 10), srcp3 + (i * 10), 10); 
		 memcpy(destp4 + (i * 10), srcp4 + (i * 10), 10); 
		 memcpy(destp5 + (i * 10), srcp5 + (i * 10), 10); 
		 memcpy(destp6 + (i * 10), srcp6 + (i * 10), 10); 
		 memcpy(destp7 + (i * 10), srcp7 + (i * 10), 10); 
		 memcpy(destp8 + (i * 10), srcp8 + (i * 10), 10); 
		 memcpy(destp9 + (i * 10), srcp9 + (i * 10), 10); 
		 memcpy(destp10 + (i * 10), srcp10 + (i * 10), 10); 
 
 

		}

		memcpy(destp + (timesToCopy * 10), srcp + (timesToCopy * 10), remainder); 
		memcpy(destp2 + (timesToCopy * 10), srcp2 + (timesToCopy * 10), remainder); 
		memcpy(destp3 + (timesToCopy * 10), srcp3 + (timesToCopy * 10), remainder); 
		memcpy(destp4 + (timesToCopy * 10), srcp4 + (timesToCopy * 10), remainder); 
		memcpy(destp5 + (timesToCopy * 10), srcp5 + (timesToCopy * 10), remainder); 
		memcpy(destp6 + (timesToCopy * 10), srcp6 + (timesToCopy * 10), remainder); 
		memcpy(destp7 + (timesToCopy * 10), srcp7 + (timesToCopy * 10), remainder); 
		memcpy(destp8 + (timesToCopy * 10), srcp8 + (timesToCopy * 10), remainder); 
		memcpy(destp9 + (timesToCopy * 10), srcp9 + (timesToCopy * 10), remainder); 
		memcpy(destp10 + (timesToCopy * 10), srcp10 + (timesToCopy * 10), remainder);   


	}
	else
	{
		for (uint32_t i = 1000; i < 1000000000; i = i * 10)
		{
			if (size <= i)
			{
					char *destp = (char *)dst; char *srcp = (char *)src;
		char *destp2 = (char *)dst2; char *srcp2 = (char *)src2;
		char *destp3 = (char *)dst3; char *srcp3 = (char *)src3;
		char *destp4 = (char *)dst4; char *srcp4 = (char *)src4;
		char *destp5 = (char *)dst5; char *srcp5 = (char *)src5;
		char *destp6 = (char *)dst6; char *srcp6 = (char *)src6;
		char *destp7 = (char *)dst7; char *srcp7 = (char *)src7;
		char *destp8 = (char *)dst8; char *srcp8 = (char *)src8;
		char *destp9 = (char *)dst9; char *srcp9 = (char *)src9;
		char *destp10 = (char *)dst10; char *srcp10 = (char *)src10;



				//copy 100 elments first
				for (uint32_t i = 0; i < 10; i++)
				{
					memcpy(destp + (i * 10), srcp + (i * 10), 10);
					memcpy(destp2 + (i * 10), srcp2 + (i * 10), 10);
					memcpy(destp3 + (i * 10), srcp3 + (i * 10), 10);
					memcpy(destp4 + (i * 10), srcp4 + (i * 10), 10);
					memcpy(destp5 + (i * 10), srcp5 + (i * 10), 10);
					memcpy(destp6 + (i * 10), srcp6 + (i * 10), 10); 
					memcpy(destp7 + (i * 10), srcp7 + (i * 10), 10); 
					memcpy(destp8 + (i * 10), srcp8 + (i * 10), 10); 
					memcpy(destp9 + (i * 10), srcp9 + (i * 10), 10); 
					memcpy(destp10 + (i * 10), srcp10 + (i * 10), 10); 
		 
		 
				}
				size = size - 100;

				uint32_t incrmentby = (i / 10);
				remainder = size % incrmentby;
				timesToCopy = size / incrmentby;

				for (uint32_t i = 0; i < timesToCopy; i++)
				{
					memcpy(destp + ((i * incrmentby) + 100), (srcp + (i * incrmentby) + 100), incrmentby); 
					memcpy(destp2 + ((i * incrmentby) + 100), (srcp2 + (i * incrmentby) + 100), incrmentby); 
					memcpy(destp3 + ((i * incrmentby) + 100), (srcp3 + (i * incrmentby) + 100), incrmentby); 
					memcpy(destp4 + ((i * incrmentby) + 100), (srcp4 + (i * incrmentby) + 100), incrmentby); 
					memcpy(destp5 + ((i * incrmentby) + 100), (srcp5 + (i * incrmentby) + 100), incrmentby); 
					memcpy(destp6 + ((i * incrmentby) + 100), (srcp6 + (i * incrmentby) + 100), incrmentby); 
					memcpy(destp7 + ((i * incrmentby) + 100), (srcp7 + (i * incrmentby) + 100), incrmentby); 
					memcpy(destp8 + ((i * incrmentby) + 100), (srcp8 + (i * incrmentby) + 100), incrmentby); 
					memcpy(destp9 + ((i * incrmentby) + 100), (srcp9 + (i * incrmentby) + 100), incrmentby); 
					memcpy(destp10 + ((i * incrmentby) + 100), (srcp10 + (i * incrmentby) + 100), incrmentby); 
		 
		 
 
				}

				memcpy(destp + ((timesToCopy * incrmentby) + 100), srcp + ((timesToCopy * incrmentby) + 100), remainder);
				memcpy(destp2 + ((timesToCopy * incrmentby) + 100), srcp2 + ((timesToCopy * incrmentby) + 100), remainder);
				memcpy(destp3 + ((timesToCopy * incrmentby) + 100), srcp3 + ((timesToCopy * incrmentby) + 100), remainder);
				memcpy(destp4 + ((timesToCopy * incrmentby) + 100), srcp4 + ((timesToCopy * incrmentby) + 100), remainder);
				memcpy(destp5 + ((timesToCopy * incrmentby) + 100), srcp5 + ((timesToCopy * incrmentby) + 100), remainder);
				memcpy(destp6 + ((timesToCopy * incrmentby) + 100), srcp6 + ((timesToCopy * incrmentby) + 100), remainder); 
				memcpy(destp7 + ((timesToCopy * incrmentby) + 100), srcp7 + ((timesToCopy * incrmentby) + 100), remainder); 
				memcpy(destp8 + ((timesToCopy * incrmentby) + 100), srcp8 + ((timesToCopy * incrmentby) + 100), remainder); 
				memcpy(destp9 + ((timesToCopy * incrmentby) + 100), srcp9 + ((timesToCopy * incrmentby) + 100), remainder); 
				memcpy(destp10 + ((timesToCopy * incrmentby) + 100), srcp10 + ((timesToCopy * incrmentby) + 100), remainder); 
	 
	 

				break;
			}
		}
	}


}



 
static void AEmemcpyManyFromBottomUp11(
void* dst, void* src  
,void* dst2, void* src2  
,void* dst3, void* src3  
,void* dst4, void* src4  
,void* dst5, void* src5  
,void* dst6, void* src6   
,void* dst7, void* src7   
,void* dst8, void* src8   
,void* dst9, void* src9   
,void* dst10, void* src10    
,void* dst11, void* src11   
	,uint32_t sizeForAllVars)
{

	//for now the sizes can only be the same for all vars
	uint32_t size = sizeForAllVars;

	// copy by the largest it is divisible by
	uint32_t remainder;
	uint32_t timesToCopy;


	if (size < 10)
	{
		memcpy(dst, src, size);
		memcpy(dst2, src2, size);
		memcpy(dst3, src3, size);
		memcpy(dst4, src4, size);
		memcpy(dst5, src5, size);
		memcpy(dst6, src6, size); 
		memcpy(dst7, src7, size); 
		memcpy(dst8, src8, size); 
		memcpy(dst9, src9, size); 
		memcpy(dst10, src10, size); 
		memcpy(dst11, src11, size);  
	}
	else if (size <= 100)
	{
		char *destp = (char *)dst; char *srcp = (char *)src;
		char *destp2 = (char *)dst2; char *srcp2 = (char *)src2;
		char *destp3 = (char *)dst3; char *srcp3 = (char *)src3;
		char *destp4 = (char *)dst4; char *srcp4 = (char *)src4;
		char *destp5 = (char *)dst5; char *srcp5 = (char *)src5;
		char *destp6 = (char *)dst6; char *srcp6 = (char *)src6;
		char *destp7 = (char *)dst7; char *srcp7 = (char *)src7;
		char *destp8 = (char *)dst8; char *srcp8 = (char *)src8;
		char *destp9 = (char *)dst9; char *srcp9 = (char *)src9;
		char *destp10 = (char *)dst10; char *srcp10 = (char *)src10;
		char *destp11 = (char *)dst11; char *srcp11 = (char *)src11;
 

		remainder = size % 10;
		timesToCopy = size / 10;

		//copy elements in increments but always start with an increment of 10
		//up to 100 
		for (uint32_t i = 0; i < timesToCopy; i++)
		{
		 memcpy(destp + (i * 10), srcp + (i * 10), 10); 
		 memcpy(destp2 + (i * 10), srcp2 + (i * 10), 10); 
		 memcpy(destp3 + (i * 10), srcp3 + (i * 10), 10); 
		 memcpy(destp4 + (i * 10), srcp4 + (i * 10), 10); 
		 memcpy(destp5 + (i * 10), srcp5 + (i * 10), 10); 
		 memcpy(destp6 + (i * 10), srcp6 + (i * 10), 10); 
		 memcpy(destp7 + (i * 10), srcp7 + (i * 10), 10); 
		 memcpy(destp8 + (i * 10), srcp8 + (i * 10), 10); 
		 memcpy(destp9 + (i * 10), srcp9 + (i * 10), 10); 
		 memcpy(destp10 + (i * 10), srcp10 + (i * 10), 10); 
		 memcpy(destp11 + (i * 10), srcp11 + (i * 10), 10); 
 

		}

		memcpy(destp + (timesToCopy * 10), srcp + (timesToCopy * 10), remainder); 
		memcpy(destp2 + (timesToCopy * 10), srcp2 + (timesToCopy * 10), remainder); 
		memcpy(destp3 + (timesToCopy * 10), srcp3 + (timesToCopy * 10), remainder); 
		memcpy(destp4 + (timesToCopy * 10), srcp4 + (timesToCopy * 10), remainder); 
		memcpy(destp5 + (timesToCopy * 10), srcp5 + (timesToCopy * 10), remainder); 
		memcpy(destp6 + (timesToCopy * 10), srcp6 + (timesToCopy * 10), remainder); 
		memcpy(destp7 + (timesToCopy * 10), srcp7 + (timesToCopy * 10), remainder); 
		memcpy(destp8 + (timesToCopy * 10), srcp8 + (timesToCopy * 10), remainder); 
		memcpy(destp9 + (timesToCopy * 10), srcp9 + (timesToCopy * 10), remainder); 
		memcpy(destp10 + (timesToCopy * 10), srcp10 + (timesToCopy * 10), remainder); 
		memcpy(destp11 + (timesToCopy * 10), srcp11 + (timesToCopy * 10), remainder);  


	}
	else
	{
		for (uint32_t i = 1000; i < 1000000000; i = i * 10)
		{
			if (size <= i)
			{
					char *destp = (char *)dst; char *srcp = (char *)src;
		char *destp2 = (char *)dst2; char *srcp2 = (char *)src2;
		char *destp3 = (char *)dst3; char *srcp3 = (char *)src3;
		char *destp4 = (char *)dst4; char *srcp4 = (char *)src4;
		char *destp5 = (char *)dst5; char *srcp5 = (char *)src5;
		char *destp6 = (char *)dst6; char *srcp6 = (char *)src6;
		char *destp7 = (char *)dst7; char *srcp7 = (char *)src7;
		char *destp8 = (char *)dst8; char *srcp8 = (char *)src8;
		char *destp9 = (char *)dst9; char *srcp9 = (char *)src9;
		char *destp10 = (char *)dst10; char *srcp10 = (char *)src10;
		char *destp11 = (char *)dst11; char *srcp11 = (char *)src11;



				//copy 100 elments first
				for (uint32_t i = 0; i < 10; i++)
				{
					memcpy(destp + (i * 10), srcp + (i * 10), 10);
					memcpy(destp2 + (i * 10), srcp2 + (i * 10), 10);
					memcpy(destp3 + (i * 10), srcp3 + (i * 10), 10);
					memcpy(destp4 + (i * 10), srcp4 + (i * 10), 10);
					memcpy(destp5 + (i * 10), srcp5 + (i * 10), 10);
					memcpy(destp6 + (i * 10), srcp6 + (i * 10), 10); 
					memcpy(destp7 + (i * 10), srcp7 + (i * 10), 10); 
					memcpy(destp8 + (i * 10), srcp8 + (i * 10), 10); 
					memcpy(destp9 + (i * 10), srcp9 + (i * 10), 10); 
					memcpy(destp10 + (i * 10), srcp10 + (i * 10), 10); 
					memcpy(destp11 + (i * 10), srcp11 + (i * 10), 10); 
		 
				}
				size = size - 100;

				uint32_t incrmentby = (i / 10);
				remainder = size % incrmentby;
				timesToCopy = size / incrmentby;

				for (uint32_t i = 0; i < timesToCopy; i++)
				{
					memcpy(destp + ((i * incrmentby) + 100), (srcp + (i * incrmentby) + 100), incrmentby); 
					memcpy(destp2 + ((i * incrmentby) + 100), (srcp2 + (i * incrmentby) + 100), incrmentby); 
					memcpy(destp3 + ((i * incrmentby) + 100), (srcp3 + (i * incrmentby) + 100), incrmentby); 
					memcpy(destp4 + ((i * incrmentby) + 100), (srcp4 + (i * incrmentby) + 100), incrmentby); 
					memcpy(destp5 + ((i * incrmentby) + 100), (srcp5 + (i * incrmentby) + 100), incrmentby); 
					memcpy(destp6 + ((i * incrmentby) + 100), (srcp6 + (i * incrmentby) + 100), incrmentby); 
					memcpy(destp7 + ((i * incrmentby) + 100), (srcp7 + (i * incrmentby) + 100), incrmentby); 
					memcpy(destp8 + ((i * incrmentby) + 100), (srcp8 + (i * incrmentby) + 100), incrmentby); 
					memcpy(destp9 + ((i * incrmentby) + 100), (srcp9 + (i * incrmentby) + 100), incrmentby); 
					memcpy(destp10 + ((i * incrmentby) + 100), (srcp10 + (i * incrmentby) + 100), incrmentby); 
					memcpy(destp11 + ((i * incrmentby) + 100), (srcp11 + (i * incrmentby) + 100), incrmentby); 
		 
 
				}

				memcpy(destp + ((timesToCopy * incrmentby) + 100), srcp + ((timesToCopy * incrmentby) + 100), remainder);
				memcpy(destp2 + ((timesToCopy * incrmentby) + 100), srcp2 + ((timesToCopy * incrmentby) + 100), remainder);
				memcpy(destp3 + ((timesToCopy * incrmentby) + 100), srcp3 + ((timesToCopy * incrmentby) + 100), remainder);
				memcpy(destp4 + ((timesToCopy * incrmentby) + 100), srcp4 + ((timesToCopy * incrmentby) + 100), remainder);
				memcpy(destp5 + ((timesToCopy * incrmentby) + 100), srcp5 + ((timesToCopy * incrmentby) + 100), remainder);
				memcpy(destp6 + ((timesToCopy * incrmentby) + 100), srcp6 + ((timesToCopy * incrmentby) + 100), remainder); 
				memcpy(destp7 + ((timesToCopy * incrmentby) + 100), srcp7 + ((timesToCopy * incrmentby) + 100), remainder); 
				memcpy(destp8 + ((timesToCopy * incrmentby) + 100), srcp8 + ((timesToCopy * incrmentby) + 100), remainder); 
				memcpy(destp9 + ((timesToCopy * incrmentby) + 100), srcp9 + ((timesToCopy * incrmentby) + 100), remainder); 
				memcpy(destp10 + ((timesToCopy * incrmentby) + 100), srcp10 + ((timesToCopy * incrmentby) + 100), remainder); 
				memcpy(destp11 + ((timesToCopy * incrmentby) + 100), srcp11 + ((timesToCopy * incrmentby) + 100), remainder); 
	 

				break;
			}
		}
	}


}



 
static void AEmemcpyManyFromBottomUp12(
void* dst, void* src  
,void* dst2, void* src2  
,void* dst3, void* src3  
,void* dst4, void* src4  
,void* dst5, void* src5  
,void* dst6, void* src6   
,void* dst7, void* src7   
,void* dst8, void* src8   
,void* dst9, void* src9   
,void* dst10, void* src10    
,void* dst11, void* src11    
,void* dst12, void* src12    
	,uint32_t sizeForAllVars)
{

	//for now the sizes can only be the same for all vars
	uint32_t size = sizeForAllVars;

	// copy by the largest it is divisible by
	uint32_t remainder;
	uint32_t timesToCopy;


	if (size < 10)
	{
		memcpy(dst, src, size);
		memcpy(dst2, src2, size);
		memcpy(dst3, src3, size);
		memcpy(dst4, src4, size);
		memcpy(dst5, src5, size);
		memcpy(dst6, src6, size); 
		memcpy(dst7, src7, size); 
		memcpy(dst8, src8, size); 
		memcpy(dst9, src9, size); 
		memcpy(dst10, src10, size); 
		memcpy(dst11, src11, size); 
		memcpy(dst12, src12, size); 
	}
	else if (size <= 100)
	{
		char *destp = (char *)dst; char *srcp = (char *)src;
		char *destp2 = (char *)dst2; char *srcp2 = (char *)src2;
		char *destp3 = (char *)dst3; char *srcp3 = (char *)src3;
		char *destp4 = (char *)dst4; char *srcp4 = (char *)src4;
		char *destp5 = (char *)dst5; char *srcp5 = (char *)src5;
		char *destp6 = (char *)dst6; char *srcp6 = (char *)src6;
		char *destp7 = (char *)dst7; char *srcp7 = (char *)src7;
		char *destp8 = (char *)dst8; char *srcp8 = (char *)src8;
		char *destp9 = (char *)dst9; char *srcp9 = (char *)src9;
		char *destp10 = (char *)dst10; char *srcp10 = (char *)src10;
		char *destp11 = (char *)dst11; char *srcp11 = (char *)src11;
		char *destp12 = (char *)dst12; char *srcp12 = (char *)src12;
 

		remainder = size % 10;
		timesToCopy = size / 10;

		//copy elements in increments but always start with an increment of 10
		//up to 100 
		for (uint32_t i = 0; i < timesToCopy; i++)
		{
		 memcpy(destp + (i * 10), srcp + (i * 10), 10); 
		 memcpy(destp2 + (i * 10), srcp2 + (i * 10), 10); 
		 memcpy(destp3 + (i * 10), srcp3 + (i * 10), 10); 
		 memcpy(destp4 + (i * 10), srcp4 + (i * 10), 10); 
		 memcpy(destp5 + (i * 10), srcp5 + (i * 10), 10); 
		 memcpy(destp6 + (i * 10), srcp6 + (i * 10), 10); 
		 memcpy(destp7 + (i * 10), srcp7 + (i * 10), 10); 
		 memcpy(destp8 + (i * 10), srcp8 + (i * 10), 10); 
		 memcpy(destp9 + (i * 10), srcp9 + (i * 10), 10); 
		 memcpy(destp10 + (i * 10), srcp10 + (i * 10), 10); 
		 memcpy(destp11 + (i * 10), srcp11 + (i * 10), 10); 
		 memcpy(destp12 + (i * 10), srcp12 + (i * 10), 10); 

		}

		memcpy(destp + (timesToCopy * 10), srcp + (timesToCopy * 10), remainder); 
		memcpy(destp2 + (timesToCopy * 10), srcp2 + (timesToCopy * 10), remainder); 
		memcpy(destp3 + (timesToCopy * 10), srcp3 + (timesToCopy * 10), remainder); 
		memcpy(destp4 + (timesToCopy * 10), srcp4 + (timesToCopy * 10), remainder); 
		memcpy(destp5 + (timesToCopy * 10), srcp5 + (timesToCopy * 10), remainder); 
		memcpy(destp6 + (timesToCopy * 10), srcp6 + (timesToCopy * 10), remainder); 
		memcpy(destp7 + (timesToCopy * 10), srcp7 + (timesToCopy * 10), remainder); 
		memcpy(destp8 + (timesToCopy * 10), srcp8 + (timesToCopy * 10), remainder); 
		memcpy(destp9 + (timesToCopy * 10), srcp9 + (timesToCopy * 10), remainder); 
		memcpy(destp10 + (timesToCopy * 10), srcp10 + (timesToCopy * 10), remainder); 
		memcpy(destp11 + (timesToCopy * 10), srcp11 + (timesToCopy * 10), remainder); 
		memcpy(destp12 + (timesToCopy * 10), srcp12 + (timesToCopy * 10), remainder); 


	}
	else
	{
		for (uint32_t i = 1000; i < 1000000000; i = i * 10)
		{
			if (size <= i)
			{
					char *destp = (char *)dst; char *srcp = (char *)src;
		char *destp2 = (char *)dst2; char *srcp2 = (char *)src2;
		char *destp3 = (char *)dst3; char *srcp3 = (char *)src3;
		char *destp4 = (char *)dst4; char *srcp4 = (char *)src4;
		char *destp5 = (char *)dst5; char *srcp5 = (char *)src5;
		char *destp6 = (char *)dst6; char *srcp6 = (char *)src6;
		char *destp7 = (char *)dst7; char *srcp7 = (char *)src7;
		char *destp8 = (char *)dst8; char *srcp8 = (char *)src8;
		char *destp9 = (char *)dst9; char *srcp9 = (char *)src9;
		char *destp10 = (char *)dst10; char *srcp10 = (char *)src10;
		char *destp11 = (char *)dst11; char *srcp11 = (char *)src11;
		char *destp12 = (char *)dst12; char *srcp12 = (char *)src12;



				//copy 100 elments first
				for (uint32_t i = 0; i < 10; i++)
				{
					memcpy(destp + (i * 10), srcp + (i * 10), 10);
					memcpy(destp2 + (i * 10), srcp2 + (i * 10), 10);
					memcpy(destp3 + (i * 10), srcp3 + (i * 10), 10);
					memcpy(destp4 + (i * 10), srcp4 + (i * 10), 10);
					memcpy(destp5 + (i * 10), srcp5 + (i * 10), 10);
					memcpy(destp6 + (i * 10), srcp6 + (i * 10), 10); 
					memcpy(destp7 + (i * 10), srcp7 + (i * 10), 10); 
					memcpy(destp8 + (i * 10), srcp8 + (i * 10), 10); 
					memcpy(destp9 + (i * 10), srcp9 + (i * 10), 10); 
					memcpy(destp10 + (i * 10), srcp10 + (i * 10), 10); 
					memcpy(destp11 + (i * 10), srcp11 + (i * 10), 10); 
					memcpy(destp12 + (i * 10), srcp12 + (i * 10), 10); 
				}
				size = size - 100;

				uint32_t incrmentby = (i / 10);
				remainder = size % incrmentby;
				timesToCopy = size / incrmentby;

				for (uint32_t i = 0; i < timesToCopy; i++)
				{
					memcpy(destp + ((i * incrmentby) + 100), (srcp + (i * incrmentby) + 100), incrmentby); 
					memcpy(destp2 + ((i * incrmentby) + 100), (srcp2 + (i * incrmentby) + 100), incrmentby); 
					memcpy(destp3 + ((i * incrmentby) + 100), (srcp3 + (i * incrmentby) + 100), incrmentby); 
					memcpy(destp4 + ((i * incrmentby) + 100), (srcp4 + (i * incrmentby) + 100), incrmentby); 
					memcpy(destp5 + ((i * incrmentby) + 100), (srcp5 + (i * incrmentby) + 100), incrmentby); 
					memcpy(destp6 + ((i * incrmentby) + 100), (srcp6 + (i * incrmentby) + 100), incrmentby); 
					memcpy(destp7 + ((i * incrmentby) + 100), (srcp7 + (i * incrmentby) + 100), incrmentby); 
					memcpy(destp8 + ((i * incrmentby) + 100), (srcp8 + (i * incrmentby) + 100), incrmentby); 
					memcpy(destp9 + ((i * incrmentby) + 100), (srcp9 + (i * incrmentby) + 100), incrmentby); 
					memcpy(destp10 + ((i * incrmentby) + 100), (srcp10 + (i * incrmentby) + 100), incrmentby); 
					memcpy(destp11 + ((i * incrmentby) + 100), (srcp11 + (i * incrmentby) + 100), incrmentby); 
					memcpy(destp12 + ((i * incrmentby) + 100), (srcp12 + (i * incrmentby) + 100), incrmentby); 
 
				}

				memcpy(destp + ((timesToCopy * incrmentby) + 100), srcp + ((timesToCopy * incrmentby) + 100), remainder);
				memcpy(destp2 + ((timesToCopy * incrmentby) + 100), srcp2 + ((timesToCopy * incrmentby) + 100), remainder);
				memcpy(destp3 + ((timesToCopy * incrmentby) + 100), srcp3 + ((timesToCopy * incrmentby) + 100), remainder);
				memcpy(destp4 + ((timesToCopy * incrmentby) + 100), srcp4 + ((timesToCopy * incrmentby) + 100), remainder);
				memcpy(destp5 + ((timesToCopy * incrmentby) + 100), srcp5 + ((timesToCopy * incrmentby) + 100), remainder);
				memcpy(destp6 + ((timesToCopy * incrmentby) + 100), srcp6 + ((timesToCopy * incrmentby) + 100), remainder); 
				memcpy(destp7 + ((timesToCopy * incrmentby) + 100), srcp7 + ((timesToCopy * incrmentby) + 100), remainder); 
				memcpy(destp8 + ((timesToCopy * incrmentby) + 100), srcp8 + ((timesToCopy * incrmentby) + 100), remainder); 
				memcpy(destp9 + ((timesToCopy * incrmentby) + 100), srcp9 + ((timesToCopy * incrmentby) + 100), remainder); 
				memcpy(destp10 + ((timesToCopy * incrmentby) + 100), srcp10 + ((timesToCopy * incrmentby) + 100), remainder); 
				memcpy(destp11 + ((timesToCopy * incrmentby) + 100), srcp11 + ((timesToCopy * incrmentby) + 100), remainder); 
				memcpy(destp12 + ((timesToCopy * incrmentby) + 100), srcp12 + ((timesToCopy * incrmentby) + 100), remainder); 

				break;
			}
		}
	}


}


