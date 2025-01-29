#include <stdio.h> /* for printing */
#include <assert.h> /* for assert */
#include <string.h> /* for strcmp */
#include "../include/bit_arr.h"

/*****************************************************************************
* File: bit_arr_test.c
*
* Purpose:
* Tests for bit array implementation.
* 
*
* Written by: Yonatan Fainer
* Reviewed by: Yonatan Fainer
******************************************************************************/

void BitArrSetOnTest();
void BitArrSetOffTest();
void BitArrSetAllTest();
void BitArrResetAllTest();
void BitArrSetBitTest();
void BitArrGetValTest();
void BitArrFlipTest();
void BitArrRotateRTest();
void BitArrRotateLTest();
void BitArrMirrorTest();
void BitArrCountOnTest();
void BitArrCountOffTest();
void BitArrToStringTest();
void BitArrCountOnLutTest();
void BitArrMirrorLutTest();
void SuccessPrint();

int main()
{	
	printf("Start tests:\n...\n");
	BitArrSetOnTest();
	BitArrSetOffTest();
	BitArrSetAllTest();
	BitArrResetAllTest();
	BitArrSetBitTest();
	BitArrGetValTest();
	BitArrFlipTest();
	BitArrRotateRTest();
	BitArrRotateLTest();
	BitArrMirrorTest();
	BitArrCountOnTest();
	BitArrCountOffTest();
	BitArrToStringTest();
	BitArrCountOnLutTest();
	BitArrMirrorLutTest();

	printf("\nAll tests passed successfully!\n");
	SuccessPrint();
	
	return 0;
}

void BitArrSetOnTest()
{
	assert(7 == BitArrSetOn(5, 1));
	assert(13 ==  BitArrSetOn(9, 2));
	
	assert(5619 == BitArrSetOn(5555,6));
	assert(24 == BitArrSetOn(8,4));
	assert(8 == BitArrSetOn(8,3));
	assert(16 == BitArrSetOn(0,4));
}

void BitArrSetOffTest()
{
	assert(5 == BitArrSetOff(7, 1));
	assert(8 == BitArrSetOff(10, 1));
	
	assert(4531 == BitArrSetOff(5555,10));
	assert(0 == BitArrSetOff(8,3));
	assert(0 == BitArrSetOff(0,4));
	assert(5555 == BitArrSetOff(5555,3));

}

void BitArrSetAllTest()
{
	assert(0xffffffffffffffff == BitArrSetAll(5555));
	assert(0xffffffffffffffff == BitArrSetAll(0));
	assert(0xffffffffffffffff == BitArrSetAll(8));

}

void BitArrResetAllTest()
{
	assert(0 == BitArrResetAll(5555));
	assert(0 == BitArrResetAll(0));
	assert(0 == BitArrResetAll(8));

}

void BitArrSetBitTest()
{
	assert(5 == BitArrSetBit(7, 1, 0));
	assert(7 == BitArrSetBit(15, 3, 0));
	
	assert(4531 == BitArrSetBit(5555,10,0));
	assert(12 == BitArrSetBit(8,2,1));
	assert(16 == BitArrSetBit(0,4,1));
	assert(5555 == BitArrSetBit(5555,10,1));

}
void BitArrGetValTest()
{
	assert(1 == BitArrGetVal(15, 1));
	assert(1 == BitArrGetVal(34, 1));
	assert(0 == BitArrGetVal(64, 5));
	
	assert(1 == BitArrGetVal(5555,10));
	assert(1 == BitArrGetVal(8,3));
	assert(0 == BitArrGetVal(0,4));
	assert(0 == BitArrGetVal(5555,3));

}

void BitArrFlipTest()
{
	assert(8 == BitArrFlip(10, 1));
	assert(14 == BitArrFlip(10, 2));
	assert(15 == BitArrFlip(7, 3));
	
	assert(4531 == BitArrFlip(5555,10));
	assert(0 == BitArrFlip(8,3));
	assert(16 == BitArrFlip(0,4));
	assert(5563 == BitArrFlip(5555,3));
}

void BitArrRotateRTest()
{
	assert(5 == BitArrRotateR(10, 1));
	assert(1 == BitArrRotateR(4, 2));

	assert(0x8000000000000000 == BitArrRotateR(1,1));
	assert(0x8000000000000000 == BitArrRotateR(1,129));
	assert(4 == BitArrRotateR(16,2));

	
}

void BitArrRotateLTest()
{
	assert(16 == BitArrRotateL(4, 2));
	assert(224 == BitArrRotateL(7, 5));
	assert(0 == BitArrRotateL(0, 5));
	
	assert(1 == BitArrRotateL(0x8000000000000000,1));
	assert(1 == BitArrRotateL(0x8000000000000000,129));
	assert(64 == BitArrRotateL(16,2));

}
void BitArrMirrorTest()
{
	char buffer[65];
	
	assert(0 == strcmp(BitArrToString(BitArrMirror(48),buffer),   "0000110000000000000000000000000000000000000000000000000000000000"));
	assert(0 == strcmp(BitArrToString(BitArrMirror(0),buffer),    "0000000000000000000000000000000000000000000000000000000000000000"));
	assert(0 == strcmp(BitArrToString(BitArrMirror(8),buffer),    "0001000000000000000000000000000000000000000000000000000000000000"));
	assert(0 == strcmp(BitArrToString(BitArrMirror(5555),buffer), "1100110110101000000000000000000000000000000000000000000000000000"));

}

void BitArrCountOnTest()
{
	assert(2 == BitArrCountOn(34));
	assert(3 == BitArrCountOn(7));
	assert(4 == BitArrCountOn(15));
	assert(0 == BitArrCountOn(0));
	
	assert(8 == BitArrCountOn(5555));
	assert(1 == BitArrCountOn(8));
	assert(0 == BitArrCountOn(0));
	assert(2 == BitArrCountOn(48));

}


void BitArrCountOffTest()
{
	assert(64 == BitArrCountOff(0));
	assert(61 == BitArrCountOff(7));
	
	assert(56 == BitArrCountOff(5555));
	assert(63 == BitArrCountOff(8));
	assert(64 == BitArrCountOff(0));
	assert(62 == BitArrCountOff(48));

}

void BitArrToStringTest()
{
	char buffer[65];
	
	assert(0 == strcmp(BitArrToString(48,buffer),   "0000000000000000000000000000000000000000000000000000000000110000"));
	assert(0 == strcmp(BitArrToString(0,buffer),    "0000000000000000000000000000000000000000000000000000000000000000"));
	assert(0 == strcmp(BitArrToString(8,buffer),    "0000000000000000000000000000000000000000000000000000000000001000"));
	assert(0 == strcmp(BitArrToString(5555,buffer), "0000000000000000000000000000000000000000000000000001010110110011"));

}

void BitArrCountOnLutTest()
{	
	assert(10 == BitArrCountOnLUT(1023));
	assert(3 == BitArrCountOnLUT(7));
	assert(1 == BitArrCountOnLUT(1024));
	
	assert(8 == BitArrCountOnLUT(5555));
	assert(1 == BitArrCountOnLUT(8));
	assert(0 == BitArrCountOnLUT(0));
	assert(2 == BitArrCountOnLUT(48));

}
void BitArrMirrorLutTest()
{
	char buffer[65];
	
	assert(0 == strcmp(BitArrToString(BitArrMirrorLUT(48),buffer),   "0000110000000000000000000000000000000000000000000000000000000000"));
	assert(0 == strcmp(BitArrToString(BitArrMirrorLUT(0),buffer),    "0000000000000000000000000000000000000000000000000000000000000000"));
	assert(0 == strcmp(BitArrToString(BitArrMirrorLUT(8),buffer),    "0001000000000000000000000000000000000000000000000000000000000000"));
	assert(0 == strcmp(BitArrToString(BitArrMirrorLUT(5555),buffer), "1100110110101000000000000000000000000000000000000000000000000000"));

}

void SuccessPrint()
{
	printf("🙂️🙂️🙂️🙂️🙂️🙂️🙂️🙂️🙂️🙂️\n");
	printf("🙂️🙂️🙂️🙂️🙂️🙂️🙂️🙂️🙂️🙂️\n");
	printf("🙂️🙂️🙂️🙂️🙂️🙂️🙂️🙂️🙂️🙂️\n");
	printf("🙂️🙂️🙂️🙂️🙂️🙂️🙂️🙂️🙂️🙂️\n");
	printf("🙂️🙂️🙂️🙂️🙂️🙂️🙂️🙂️🙂️🙂️\n");
	printf("🙂️🙂️🙂️🙂️🙂️🙂️🙂️🙂️🙂️🙂️\n");
}

