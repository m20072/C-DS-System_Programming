#include <stdio.h>
#include <stdlib.h>
int main()
{
	static int s_i = 7;
	int i = 7;
	int *ptr = &i;
	int *ptr2 = (int *)malloc(sizeof(int));

	if(ptr)
	{
		int **ptr3 = &ptr;
		printf("ptr3 = %p, ", &ptr3);
	}
	printf("s_i: %p, i: %p, ptr: %p, ptr2: %p\n", &s_i, &i, &ptr, &ptr2);
	

	free(ptr2);
	return 0;
}
