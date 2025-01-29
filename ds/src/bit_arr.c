/******************************************************************************
* File: bit_arr.c
*
* Purpose:
*   implements bit_arr.h
*   
* Author:
*   Matan Chen
*
* Review History:
*   - Yonatan Fainer
*
******************************************************************************/

#include <assert.h> /* for assert */
#include <limits.h> /* For CHAR_BIT */
#include "../include/bit_arr.h"

#define BIT_ARR_BYTES sizeof(bit_arr_t)
#define BIT_ARR_BITS (BIT_ARR_BYTES * CHAR_BIT)

/* look-up table for counting set bits in a byte */
static unsigned char BitsSetTable256[256] = {0};

/* look-up table for mirroring a byte */
static unsigned char ByteMirrorTable256[256] = {0};

static void InitMirrorLUT()
{
	size_t i = 0;
	unsigned char byte = 0;

	for (i = 0; i < 256; ++i)
	{
	    byte = i;
		byte = ((byte & 0xF0) >> 4 | (byte & 0x0F) << 4);
		byte = ((byte & 0xCC) >> 2 | (byte & 0x33) << 2);
		byte = ((byte & 0xAA) >> 1 | (byte & 0x55) << 1);
 		ByteMirrorTable256[i] = byte;
	}
} 

static void InitCountOnLUT()
{
	size_t i = 0;
	
	for (i = 0; i < 256; ++i)
	{
	    BitsSetTable256[i] = (i & 1) + BitsSetTable256[i / 2]; /* how to explain */
	}
} 

bit_arr_t BitArrSetOn(bit_arr_t bit_arr, size_t k)
{
	assert(k < BIT_ARR_BITS);
	return (bit_arr | ((bit_arr_t)1 << k));
}

bit_arr_t BitArrSetOff(bit_arr_t bit_arr, size_t k)
{
	assert(k < BIT_ARR_BITS);
	return (bit_arr & ~((bit_arr_t)1 << k));
}

bit_arr_t BitArrSetAll(bit_arr_t bit_arr)
{
	return (bit_arr | ~(bit_arr_t)0);
}

bit_arr_t BitArrResetAll(bit_arr_t bit_arr)
{
	return (bit_arr & 0);
}

bit_arr_t BitArrSetBit(bit_arr_t bit_arr, size_t k, int val)
{
	assert(k < BIT_ARR_BITS);
	assert(1 == val || 0 == val);
	return ((bit_arr & ~((bit_arr_t)1 << k)) | ((bit_arr_t)val << k)); /* turn off the k'th bit then OR with the desired value */
}

int BitArrGetVal(bit_arr_t bit_arr, size_t k)
{
	assert(BIT_ARR_BITS > k);
	return ((bit_arr >> k) & 1);
}

bit_arr_t BitArrFlip(bit_arr_t bit_arr, size_t k)
{
	assert(k < BIT_ARR_BITS);
	return (bit_arr ^ ((bit_arr_t)1 << k));
}

bit_arr_t BitArrRotateR(bit_arr_t bit_arr, size_t n)
{
	n &= BIT_ARR_BITS - 1;
	return ((bit_arr >> n) | (bit_arr << (BIT_ARR_BITS - n)));
}

bit_arr_t BitArrRotateL(bit_arr_t bit_arr, size_t n)
{
	n &= BIT_ARR_BITS - 1;
	return ((bit_arr << n) | (bit_arr >> (BIT_ARR_BITS - n)));
}


bit_arr_t BitArrMirror(bit_arr_t bit_arr)
{
	bit_arr_t result = 0;
	unsigned char byte = 0;
    size_t i = 0;
    
    
    for (i = 0 ; i < BIT_ARR_BYTES; ++i)
	{
		result <<= CHAR_BIT;
		byte = bit_arr & 0xFF; 
		
		byte = (byte & 0xF0) >> 4 | (byte & 0x0F) << 4; 
		byte = (byte & 0xCC) >> 2 | (byte & 0x33) << 2; 
		byte = (byte & 0xAA) >> 1 | (byte & 0x55) << 1; 

		result |= byte;
		bit_arr >>= CHAR_BIT;
	}
    return result;
}

bit_arr_t BitArrMirrorLUT(bit_arr_t bit_arr)
{
	static int initialized = 0;
	bit_arr_t result = 0;
	bit_arr_t byte_mirror = 0;
	size_t i = 0;
	
	if(0 == initialized)
	{
		InitMirrorLUT();
		initialized = 1;
	}

	for(i = 0; i < BIT_ARR_BYTES; ++i)
	{
		byte_mirror = ByteMirrorTable256[bit_arr & 0xFF];
		byte_mirror <<= (((CHAR_BIT - 1) - i) * CHAR_BIT);
		result |= byte_mirror;
		bit_arr >>= CHAR_BIT;
	}
	return result;
}

size_t BitArrCountOn(bit_arr_t bit_arr)
{
	size_t i = 0;
	int count = 0;
	char byte = 0;
	for(i = 0; i < BIT_ARR_BYTES; ++i)
	{
		byte = bit_arr >> i * CHAR_BIT;
		byte = ((byte & 0xAA) >> 1) + (byte & 0x55);
		byte = ((byte & 0xCC) >> 2) + (byte & 0x33);
		byte = ((byte & 0xF0) >> 4) + (byte & 0x0F);
		count += byte;
	}
	return count;
}

size_t BitArrCountOnLUT(bit_arr_t bit_arr) 
{
	static int initialized = 0;
	size_t count = 0;
	
	if(0 == initialized)
	{
		InitCountOnLUT();
		initialized = 1;
	}
	
	while(0 != bit_arr)
	{
		count += BitsSetTable256[bit_arr & 0xff];
		bit_arr >>= CHAR_BIT;
	}
	return count;
}

size_t BitArrCountOff(bit_arr_t bit_arr)
{
	return BIT_ARR_BITS - BitArrCountOn(bit_arr);
}

char* BitArrToString(bit_arr_t bit_arr, char* buffer)
{
	size_t i = 0;
	size_t shift_size = BIT_ARR_BITS - 1;
	char* buffer_start = buffer;
	
	assert(NULL != buffer);
	
	for(i = 0; i < BIT_ARR_BITS; ++i)
	{
		*buffer = ((bit_arr >> (shift_size - i)) & 1) + '0';
		++buffer;
	}
	*buffer = '\0';
	return buffer_start;
}
