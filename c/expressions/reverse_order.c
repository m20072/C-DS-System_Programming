#include <stdio.h>

int flipOrder(int num)
{
	int res = 0;
	while(0 != num)
	{
		res*=10;
		res += num%10;
		num /= 10;
	}
	return res;

}

int main()
{
	printf("%d\n", flipOrder(123));
	return 0;
}

