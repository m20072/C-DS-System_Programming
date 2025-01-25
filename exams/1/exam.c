#include <stddef.h>
#include <assert.h>
#include <stdio.h>

int FlipDigitsInNum(int num)
{
	int res = 0;
	int sign = 1;
	
	if(num < 0)
	{
		num = -num;
		sign = -1;
	}
	
	while(0 < num)
	{
		res = res * 10 + num % 10;
		num /= 10;
	}
	return res * sign;
}

unsigned char MirrorByte(unsigned char byte)
{
	byte = (byte << 4) | (byte >> 4);
	byte = (((byte & 0x33) << 2) | ((byte & 0xcc) >> 2));
	return (((byte & 0x55) << 1) | ((byte & 0xaa) >> 1));
}

int FlipBit(int val, unsigned int n)
{
	return (val ^ (0x1 << n));
}

char CountSetBits(unsigned char byte)
{
	byte = ((0xaa & byte) >> 1) + (0x55 & byte); 
	byte = ((0xcc & byte) >> 2) + (0x33 & byte);
	return ((0xf0 & byte) >> 4) + (0x0f & byte);
}

char RotateLeft(unsigned char byte, unsigned int nbits)
{
	nbits &= 0x7;
	return ((byte << nbits) | (byte >> (8 - nbits)));
}

void SwapIntPtr(int** ptr1, int** ptr2)
{
	int* ptr_tmp = NULL;
	assert(NULL != ptr1 && NULL != ptr2);

	ptr_tmp = *ptr1;
	*ptr1 = *ptr2;
	*ptr2 = ptr_tmp;
}

size_t Strlen(const char* str)
{
	const char* start_str = str;
	
	while('\0' != *str)
	{
		++str;
	}
	
	return str - start_str;
}

int Strcmp(const char* str1, const char* str2)
{
	assert(NULL != str1 && NULL != str2);

	while(('\0' != *str1) && (*str1 == *str2))
	{
		++str1;
		++str2;
	}
	return (*str1 - *str2);
}

char* Strcpy(char* dst, const char* src)
{
	char* dst_start = dst;
	assert(NULL != dst && NULL != src);

	while('\0' != *src)
	{
		*dst = *src;
		++dst;
		++src;
	}
	*dst = '\0';
	return dst_start;
}

char* Strncpy(char* dst, const char* src, size_t n)
{
	char* dst_start = dst;
	assert(NULL != dst && NULL != src);
	
	while('\0' != *src && n > 0)
	{
		*dst = *src;
		++dst;
		++src;
		--n;
	}
	*dst = '\0';
	return dst_start;
}

char* Strcat(char* dst, const char* src)
{
	char* dst_start = dst;
	assert(NULL != dst && NULL != src);

	dst += Strlen(dst);
	Strcpy(dst, src);
	return dst_start;
}

unsigned long GetNFibonacciElement(unsigned int n)
{
	unsigned long a = 0;
	unsigned long b = 1;
	unsigned long c = 1;
	
	while(1 < n)
	{
		c = a + b;
		a = b;
		b = c;
		--n;
	}
	return c;
}

char* IntToString(int num, char* buffer)
{
	assert(NULL != buffer);
	sprintf(buffer, "%d", num);
	return buffer;
}


int Mult8(int num)
{
	return (num << 3);
}

void IntSwap1(int* num1, int* num2)
{
	int tmp = 0;
	assert(NULL != num1 && NULL != num2);

	tmp = *num1;
	*num1 = *num2;
	*num2 = tmp;
}

void IntSwap2(int* num1, int* num2)
{
	assert(NULL != num1 && NULL != num2);
	if(num1 == num2)
	{
		return;
	}
	*num1 = *num1 ^ *num2;
	*num2 = *num1 ^ *num2;
	*num1 = *num1 ^ *num2;
}

void IntSwap3(int* num1, int* num2)
{
	assert(NULL != num1 && NULL != num2);
	if(num1 == num2)
	{
		return;
	}
	*num1 = *num1 + *num2;
	*num2 = *num1 - *num2;
	*num1 = *num1 - *num2;
}
