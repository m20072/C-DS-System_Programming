#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include "wbo.h"

int main()
{
	/*void* ptr = (void*)0x3;*/ /* ptr points to address 0x3 */
	/*printf("%lu", *(size_t*)&ptr);*/
	
	
	/* works memset*/
	/*******************************************************************/
	/*
	void* ptr = calloc(24,1);
	size_t i = 0;
	MemSet(ptr, 3, 9);
	
	for(i = 0; i < 24; ++i)
	{
		printf("%d, ", *((char*)ptr+i));
	}
	*/
	/*******************************************************************/
	
	/* works memcpy*/
	/*******************************************************************/
	/*
	void* ptr1 = calloc(10,1);
	void* ptr2 = calloc(10,1);
	size_t i = 0;
	
	printf("ptr1 before memset: ");
	for(i = 0; i < 10; ++i)
	{
		printf("%d, ", *((char*)ptr1+i));
	}
	
	
	MemSet(ptr1, 3, 10);
	printf("\n");
	
	
	printf("ptr1 after memset: ");
	for(i = 0; i < 10; ++i)
	{
		printf("%d, ", *((char*)ptr1+i));
	}
	printf("\n");
	
	
	printf("ptr2 before memcpy: ");
	for(i = 0; i < 10; ++i)
	{
		printf("%d, ", *((char*)ptr2+i));
	}
	
	
	MemCpy(ptr2, ptr1, 10);
	printf("\n");
	
		printf("ptr2 after memcpy: ");
	for(i = 0; i < 10; ++i)
	{
		printf("%d, ", *((char*)ptr2+i));
	}
	printf("\n");
	*/
	/*******************************************************************/
	
	/*char src[50] = "Tutorialspoint";
	char dest1[50] = "Heloooo!!";
	char* dest2 = src+5;
	
	printf("Before Memmove dest = %s\n", dest1);
	MemMove(dest1, src, strlen(src)+1);
	printf("After Memmove dest = %s\n", dest1);
	
	printf("Before Memmove dest = %s\n", src);
	MemMove(dest2, src, strlen(dest2)+1);
	printf("After Memmove dest = %s\n", src);*/
	
	char src[50] = "abcdefghij";
	char* dst = src + 4;
	
	printf("Before Memmove src = %s\n", src); /* should give abcdefghij */
	MemMove(dst, src, 6);
	printf("After Memmove src = %s\n", src); /* should give abcdabcdef */
	
	
	
	return 0;
}

