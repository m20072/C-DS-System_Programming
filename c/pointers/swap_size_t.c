#include <stdio.h>
#include <assert.h>

void swap_size_t(size_t* a, size_t* b)
{
	size_t tmp;
	assert(NULL != a && NULL != b);
	
	tmp = *a;
	*a = *b;
	*b = tmp;
}

void swap_p_size_t(size_t** a, size_t** b)
{
	assert(NULL != a && NULL != b);
	swap_size_t((size_t*)a, (size_t*)b);
}

int main()
{
	size_t a = 5, b = 6;
	size_t* Pa = &a;
	size_t* Pb = &b;
	swap_p_size_t(&Pa, &Pb);
	printf("Pa = %lu Pb = %lu", *Pa, *Pb);
	return 0;
}
