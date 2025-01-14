#include <stdio.h>

int tenPown(int n)
{	
	int res = 1;
	while(--n)
	{
		res *= 10;
	}
	return res;
}

int main()
{
	printf("%d", tenPown(3));
	return 0;
}
