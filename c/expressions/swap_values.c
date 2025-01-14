#include <stdio.h>
#include <assert.h>
void swapval(int* a, int* b)
{
	int tmp;
	assert(NULL != a && NULL != b);
	tmp = *a;
	
	*a = *b;
	*b = tmp;
}

int main()
{
	int a = 1;
	int b = 2;
	swapval(&a,&b);
	printf("a = %d, b = %d\n", a, b);
	return 0;
}
