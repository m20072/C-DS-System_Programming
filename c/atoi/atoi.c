#include <stddef.h>
#include <assert.h>
#include <stdio.h>
#include "atoi.h"

static char	IntToAscii(int num);
static int AsciiToInt(char ascii);
static size_t BaseNumDigits(int num, int base);
static void FillCharIndexes(int dst[][3], size_t col_index, char* src, size_t src_size);

static char	IntToAscii(int num)
{
	return (num < 10) ? (num + '0') : (num + '7');
}

static int AsciiToInt(char ascii)
{	
	return (ascii <= '9') ? ascii - '0': ascii - '7';
}

/* Given a decimal number, returns the number of digits for a given base */
static size_t BaseNumDigits(int num, int base)
{
    size_t count = 0;
    while(0 != num)
    {
        num /= base;
        ++count;
    }
    return count;
}

/*	Converts an int (base 10) into a string base 10 */
char* IntToStringBase10(char* buffer, int num)
{
	size_t num_digits = BaseNumDigits(num, 10);
	int negative = 0;
	assert(NULL != buffer);
	
	if(num < 0)
	{
		negative = 1;
		num = -num;
		*buffer = '-';
	}
	
	buffer += num_digits + negative;
	*buffer = '\0';
	
	while(0 != num)
	{
		*(--buffer) = IntToAscii(num % 10);
		
		num /= 10;
	}
	

	return (buffer - negative);	
}

/* Converts a string in base 10 into an int */
int StringToIntBase10(const char* str)
{
	int res = 0;
	int sign = 1;
	if(*str == '-')
	{
		++str;
		sign = -1;
	}
	
	while('\0' != *str)
	{
		res = res * 10 + AsciiToInt(*str);
		++str;
	}
	return sign * res;
}

/* Converts a string in a given base into a base 10 integer */
int Atoi_base(const char* str, size_t base)
{
	int res = 0;
	int sign = 1;
	
	if('-' == *str)
	{
		++str;
		sign = -1;
	}
	
	while('\0' != *str)
	{
		res = res * base + AsciiToInt(*str);
		++str;
	}
	return sign * res;
}

/* Converts a decimal integer into a string in a given base */
char* Itoa_base(char* buffer, int num, size_t base)
{
	size_t num_digits = BaseNumDigits(num, base);
	int negative = 0;
	assert(NULL != buffer);
	
	if(num < 0)
	{
		negative = 1;
		num = -num;
		*buffer = '-';
	}
	
	buffer += num_digits + negative;
	*buffer = '\0';
	
	while(0 != num)
	{
		*(--buffer) = IntToAscii(num % base);
		
		num /= base;
	}
	
	return buffer - negative;	
}

/* Only print characters that are in both arr1 arr2, but not in arr3 */
void PrintLetters(char* arr1, char* arr2, char* arr3, size_t size1, size_t size2, size_t size3)
{
	int i = 0;
	int count_arr[256][3] = { 0 };
	
	FillCharIndexes(count_arr, 0, arr1, size1);
	FillCharIndexes(count_arr, 1, arr2, size2);
	FillCharIndexes(count_arr, 2, arr3, size3);
	
	for(i = 0; i < 256; ++i)
	{
		if(0 == count_arr[i][2] && 1 == count_arr[i][0] && 1 == count_arr[i][1])
		{
			printf("%c, ", i);
		}
	}
	printf("\n");
}

/* Iterates through array of chars and fills with 1 on indexes of those chars in the array dst */
static void FillCharIndexes(int dst[][3], size_t col_index, char* src, size_t src_size)
{
	size_t i = 0;
	for(i = 0; i < src_size ; ++i)
	{
		dst[src[i]][col_index] = 1;
	}
}

/* n is an int with value 1, meaning that the LEAST significant byte has 00000001, currently unkown if that LSB is at the lowest address of the word, or the highest address of it.
 * if we look at the address of n (&n) as though it was a char, 
 * and then derference, we get the byte value of the start of the word (the lowest address of the word), if its 00000001 that means the LSB is at the lowest address of the word
 * if its 00000000 theat means the LSB is at the highest address of the word  */
int CheckLittleEndian()
{
	int n = 1;
	return 1 == *(char*)&n;
}



