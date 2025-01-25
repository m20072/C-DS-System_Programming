/******************************************************************************
* File: exam1_test.c
*
* Purpose:
*   Test suite for exam1.h
*
* Notes:
*   - <insert notes here>
*   
* Author:
*   Shani Zuniga
*
******************************************************************************/

#include <stdio.h>						/* printf */
#include <string.h>						/* strcmp */
#include <assert.h>                     /* assert */
#include "exam.h"						/* own header */

static void TestFlipDigitsInNum(void)
{
    assert(FlipDigitsInNum(123) == 321);
    assert(FlipDigitsInNum(0) == 0);
    assert(FlipDigitsInNum(-123) == -321);
    printf("FlipDigitsInNum tests passed\n");
}

static void TestMirrorByte(void)
{
    assert(MirrorByte(0x12) == 0x48);
    assert(MirrorByte(0xFF) == 0xFF);
    assert(MirrorByte(0x00) == 0x00);
    printf("MirrorByte tests passed\n");
}

static void TestFlipBit(void)
{
    assert(FlipBit(0, 0) == 1);
    assert(FlipBit(1, 0) == 0);
    assert(FlipBit(0, 31) == (1 << 31));
    printf("FlipBit tests passed\n");
}

static void TestCountSetBits(void)
{
    assert(CountSetBits(0xFF) == 8);
    assert(CountSetBits(0x00) == 0);
    assert(CountSetBits(0xA5) == 4);
    printf("CountSetBits tests passed\n");
}

static void TestRotateLeft(void)
{
    assert(RotateLeft(0x85, 1) == 0x0B);
    assert(RotateLeft(0x85, 8) == 0x85);
    assert(RotateLeft(0x00, 3) == 0x00);
    printf("RotateLeft tests passed\n");
}

static void TestSwapPointers(void)
{
    int a = 1, b = 2;
    int *ptr1 = &a, *ptr2 = &b;
    SwapIntPtr(&ptr1, &ptr2);
    assert(ptr1 == &b && ptr2 == &a);
    printf("SwapPointers tests passed\n");
}

static void TestStrFunctions(void)
{
    char str1[50] = "Hello";
    char str2[50] = "World";
    char dest[100];

    assert(Strlen(str1) == 5);
    assert(Strcmp(str1, "Hello") == 0);
    assert(Strcmp(str1, str2) < 0);
    
    assert(Strcpy(dest, str1) == dest);
    assert(strcmp(dest, str1) == 0);
    
    Strncpy(dest, str2, 3);
    assert(strncmp(dest, str2, 3) == 0);
    
    Strcat(str1, str2);
    assert(strcmp(str1, "HelloWorld") == 0);
    
    printf("String function tests passed\n");
}

static void TestFibonacci(void)
{
    assert(GetNFibonacciElement(1) == 1);
    assert(GetNFibonacciElement(2) == 1);
    assert(GetNFibonacciElement(3) == 2);
    assert(GetNFibonacciElement(4) == 3);
    printf("Fibonacci tests passed\n");
}

static void TestIntToString(void)
{
    char buffer[20];
    assert(strcmp(IntToString(123, buffer), "123") == 0);
    assert(strcmp(IntToString(-456, buffer), "-456") == 0);
    assert(strcmp(IntToString(0, buffer), "0") == 0);
    printf("IntToString tests passed\n");
}

static void TestMultiplyBy8(void)
{
    assert(Mult8(1) == 8);
    assert(Mult8(0) == 0);
    assert(Mult8(16) == 128);
    printf("MultiplyBy8 tests passed\n");
}

static void TestSwapFunctions(void)
{
    int a = 5, b = 10;
    

    IntSwap1(&a, &b);
    assert(a == 10 && b == 5);

    IntSwap2(&a, &b);
    assert(a == 5 && b == 10);

    IntSwap3(&a, &b);
    assert(a == 10 && b == 5);
    
    printf("Swap function tests passed\n");
}

int main(void)
{	
	printf("Beginning exam1.c tests...\n\n");
	
    TestFlipDigitsInNum();
    TestMirrorByte();
    TestFlipBit();
    TestCountSetBits();
    TestRotateLeft();
    TestSwapPointers();
    TestStrFunctions();
    TestFibonacci();
    TestIntToString();
    TestMultiplyBy8();
    TestSwapFunctions();

	printf("\nAll tests completed successfully\n");
	return 0;
}
