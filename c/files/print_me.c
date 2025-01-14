#include <stdio.h>

void Print(int num);

typedef struct print
{
	int num;
	void (*Print)(int); /* pointer to a func, pointer name is Print */
	
} print_me;

void Print(int num)
{
	printf("%d\n", num);	
}

int main()
{
	print_me print_me_arr[10];
	int i;
	for(i = 0;i<10;++i)
	{
		print_me_arr[i].num = i;
		print_me_arr[i].Print = &Print;
		print_me_arr[i].Print(print_me_arr[i].num);
	}
	return 0;
}

