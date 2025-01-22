#include <stdio.h>
#include <stdlib.h>
#include "atoi.h"

#define IS_LITTLE_ENDIAN() *(short*)"\0\x1" == 0x0100

static void TestAtoi(char* str)
{
	printf("original atoi on %s: %d\n", str, atoi(str));
	printf("my atoi on %s: %d\n", str, StringToIntBase10(str));
	printf("\n");
}

static void AtoiEdgeCasesTest()
{
	printf("STRING TO INT BASE 10 EDGE CASE TESTS:\n");
	TestAtoi("0");
	TestAtoi("-0");
	TestAtoi("1");
	TestAtoi("-1");
}

static void IntToStringTest()
{
	char test1[100];
	char test2[100];
	
	printf("INT TO STRING TESTS:\n");
	printf("IntToStringBase10 for value 255: %s\n", IntToStringBase10(test1, 255));
	printf("Itoa_base, base 16, for value 255: %s\n", Itoa_base(test2, 255, 16));
	printf("\n");
}

static void StringToIntTest()
{
	printf("STRING TO INT TESTS:\n");
	printf("Atoi_base: string of base 16 to int base 10 for value FF: %d\n", Atoi_base("FF", 16));
	printf("StringToIntBase10 on FF: %d\n", StringToIntBase10("FF"));
	printf("\n");
}

static void PrintLettersTest()
{
	char arr1[4] = {'a', '@', 'c', 'd'};
	char arr2[5] = {'a', '@', 'c', 'e', 'd'};
	char arr3[2] = {'a', 'c'};
	
	printf("PRINT LETTERS TESTS:\n");
	printf("arr1: a@cd\narr2: a@ced \narr3: ac\nresult: ");
	PrintLetters(arr1, arr2, arr3, 4, 5, 2);
	printf("\n");
}

static void CheckLittleEndianTest()
{
	printf("CHECK LITTLE ENDIAN TESTS\n");
	printf("function check little endian: %d\n", CheckLittleEndian());
	printf("macro check little endian: %d\n", IS_LITTLE_ENDIAN());
	printf("\n");
}

int main()
{
	IntToStringTest();
	StringToIntTest();
	AtoiEdgeCasesTest();
	PrintLettersTest();
	CheckLittleEndianTest();
	return 0;
}
