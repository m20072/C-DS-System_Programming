#include <stdio.h>
#include "../include/bit_arr.h"


int main(void)
{
	bit_arr_t test = 0;
	char buffer[100];
	
	test = BitArrSetOn(test, 0);
	printf("%s\n", BitArrToString(test, buffer));
	test = BitArrSetOn(test, 1);
	printf("%s\n", BitArrToString(test, buffer));
	test = BitArrSetOff(test, 0);
	printf("%s\n", BitArrToString(test, buffer));
	test = BitArrSetAll(test);
	printf("%s\n", BitArrToString(test, buffer));
	test = BitArrResetAll(test);
	printf("%s\n", BitArrToString(test, buffer));
	test = BitArrSetBit(test, 1, 1);
	printf("%s\n", BitArrToString(test, buffer));
	test = BitArrSetBit(test, 1, 0);
	printf("%s\n", BitArrToString(test, buffer));
	
	test = BitArrSetBit(test, 1, 1);
	printf("%s\n", BitArrToString(test, buffer));
	
	printf("%d\n", BitArrGetVal(test, 0));
	printf("%d\n", BitArrGetVal(test, 1));
	
	printf("%s\n", BitArrToString(test, buffer));

	test = BitArrFlip(test, 0);
	printf("%s\n", BitArrToString(test, buffer));
	test = BitArrFlip(test, 0);
	printf("%s\n", BitArrToString(test, buffer));
	
	test = BitArrRotateR(test);
	printf("%s\n", BitArrToString(test, buffer));

	test = BitArrRotateR(test);
	printf("%s\n", BitArrToString(test, buffer));	
	
	test = BitArrRotateR(test);
	printf("%s\n", BitArrToString(test, buffer));
	
	test = BitArrRotateL(test);
	printf("%s\n", BitArrToString(test, buffer));
	
	test = BitArrRotateL(test);
	printf("%s\n", BitArrToString(test, buffer));
	
	/*printf("%lu\n", BitArrCountOn(test));
	
	test = BitArrSetBit(test, 1, 1);
	printf("%lu\n", BitArrCountOn(test));
	printf("%s\n", BitArrToString(test, buffer));*/
	
	test = BitArrSetBit(test, 1, 1);
	printf("%s\n", BitArrToString(test, buffer));
	printf("%lu\n", BitArrCountOn(test));
	
	test = BitArrSetBit(test, 63, 1);
	printf("%s\n", BitArrToString(test, buffer));
	printf("%lu\n", BitArrCountOn(test));
	
	printf("%s\n", BitArrToString(test, buffer));
	printf("%lu\n", BitArrCountOff(test));
	
	
	return 0;
}
