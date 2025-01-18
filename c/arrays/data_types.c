#include <stdio.h>
/*test*/
int main()
{
	int arr1[5];
	int mat[5][5];
	printf("int: %lu \n char: %lu \n float: %lu \n double: %lu \n long: %lu \n int*: %lu \n", sizeof(int), sizeof(char), sizeof(float), sizeof(double), sizeof(long), sizeof(int*));
	printf("arr1[5]: %lu\n mat[5][5]: %lu\n",sizeof(arr1),sizeof(mat));
	
	return 0;
}
