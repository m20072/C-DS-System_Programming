#include <stdio.h>
#include <stdlib.h>


int* copyArr(int* arr, int size)
{
	int* newArr = (int*)malloc(sizeof(int) * size);
	int i;
	if(!newArr)
		return NULL;

	for(i = 0; i < size;i++)
		newArr[i] = arr[i];

	return newArr;
}

int main()
{
	int arr[] = {1,2,3,4,5};
	int* arr2 = copyArr(arr, 5);
	int i;
	
	for(i = 0;i<5;i++)
	{
		printf("%d ",arr2[i]);
	}
		
	return 0;
}
