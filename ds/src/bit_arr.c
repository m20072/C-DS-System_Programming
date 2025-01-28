#include <stdio.h>
#include <assert.h>
#include "../include/bit_arr.h"

#define NUM_BITS sizeof(bit_arr_t) * 8

bit_arr_t BitArrSetOn(bit_arr_t bit_arr, size_t k)
{
	assert(NUM_BITS > k);
	return (bit_arr | ((bit_arr_t)1 << k)); /* need to cast or is it implicit due to left part? */
}

bit_arr_t BitArrSetOff(bit_arr_t bit_arr, size_t k)
{
	assert(NUM_BITS > k);
	return (bit_arr & ~((bit_arr_t)1 << k));
}

bit_arr_t BitArrSetAll(bit_arr_t bit_arr)
{
	return (bit_arr | ~(bit_arr_t)0);
	/*return ~(bit_arr_t)0;*/
}

bit_arr_t BitArrResetAll(bit_arr_t bit_arr)
{
	return (bit_arr & 0);
	/*return (bit_arr_t)0;*/
}

bit_arr_t BitArrSetBit(bit_arr_t bit_arr, size_t k, int val)
{
	assert(NUM_BITS > k && (1 == val || 0 == val));
	bit_arr =  (bit_arr & ~((bit_arr_t)1 << k)); /*i stay with bit_arr where that bit is 0'd out*/
	return  (bit_arr | ((bit_arr_t)val << k));
}

int BitArrGetVal(bit_arr_t bit_arr, size_t k)
{
	assert(NUM_BITS > k);
	return ((bit_arr >> k) & 0x1); /* can do << k on the 0x1 instead too */
}

bit_arr_t BitArrFlip(bit_arr_t bit_arr, size_t k)
{
	assert(NUM_BITS > k);
	return (bit_arr ^ ((bit_arr_t)1 << k));
}

bit_arr_t BitArrRotateR(bit_arr_t bit_arr)
{
	return (bit_arr >> 1 | bit_arr << ((sizeof(bit_arr_t) * 8) - 1));
}

bit_arr_t BitArrRotateL(bit_arr_t bit_arr)
{
	return (bit_arr << 1 | bit_arr >> ((sizeof(bit_arr_t) * 8) - 1));
}

bit_arr_t BitArrMirror(bit_arr_t bit_arr)
{


	/*size_t i = 0;
	size_t num_bits = sizeof(bit_arr_t) * 8;
	size_t shift = num_bits >> 1;*/
	/*while(0 != shift)
	{
		bit_arr += ((bit_arr & ~(0) << ) >> shift | (bit_arr & 0x55555555) << shift);
		shift >>= 1;
	}*/
	
}

size_t BitArrCountOn(bit_arr_t bit_arr)
{
	size_t i = 0;
	int count = 0;
	char byte = 0; /* = bit_arr */
	for(i = 0; i < sizeof(bit_arr_t); ++i)
	{
		byte = bit_arr >> i * 8;
		byte = ((byte & 0xAA) >> 1) + (byte & 0x55);
		byte = ((byte & 0xCC) >> 2) + (byte & 0x33);
		byte = ((byte & 0xF0) >> 4) + (byte & 0x0F);
		count += byte;
	}
	return count;
	
	/*while(0 != bit_arr)
	{
		byte = ((byte & 0xAA) >> 1) + (byte & 0x55);
		byte = ((byte & 0xCC) >> 2) + (byte & 0x33);
		byte = ((byte & 0xF0) >> 4) + (byte & 0x0F);
		count += byte;
		bit_arr >>= 8;
		byte = bit_arr;
	}*/
}

size_t BitArrCountOff(bit_arr_t bit_arr)
{
	return sizeof(bit_arr_t) * 8 - BitArrCountOn(bit_arr);
}

char* BitArrToString(bit_arr_t bit_arr, char* buffer)
{
	size_t i = 0;
	size_t num_bits = sizeof(bit_arr_t) * 8;
	size_t shift_size = num_bits - 1;
	
	assert(NULL != buffer);
	
	for(i = 0; i < num_bits; ++i)
	{
		buffer[i] = ((bit_arr >> (shift_size - i)) & 0x1) + '0';
	}
	*(buffer + num_bits) = '\0';
	return buffer;
}





