#include <stddef.h>
#include <stdio.h>
long* SumIntPairsToLongs(int ints[], size_t numOfElements)
{
	size_t i = 0;
	long* longs = (long*)ints;
	
	for(i = 0; i < numOfElements / 2; ++i)
	{
		longs[i] = ints[i*2] + ints[i*2 + 1];
	}
	return longs;
}

int main()
{
	size_t i = 0;
	int ints[] = {1,6,456,-3,8,12};
	long* longs = SumIntPairsToLongs(ints, 6);
	
	for(i = 0; i<3; ++i)
	{
		printf("%ld, ", longs[i]);
	}
	
	return 0;
}

