#include <stdio.h>

/* Reviewed by Omri */



/* multiplies x by 2^y */
long Pow2(unsigned int x, unsigned int y)
{	
	return x << y;
}

/* check if a number is a power of 2 */
int IsPowOf2(unsigned int n)
{
	return 0 == ((0 == n) || (n & (n - 1))); /* if n is not 0 or n&(n-1) is 0 its pow of 2*/
}

/* check if a number is a power of 2 with a loop */
int IsPowOf2Loop(unsigned int n)
{
	size_t i;
	int foundOne = 0;
	
	if(0 == n)
	{
		return 0;
	}
	
	for(i = 0; i < 32; ++i) /* iterate through 32 (bit 0 to 31) bits to check they are 0*/
	{	
		if(1 == ((n >> i) & 0x1)) /* AND with 0x1 will produce 1 only if current iteration bit of n is 1 */
		{
			if(1 == foundOne)
			{
				return 0;
			}			
			foundOne = 1;
		}
	}
	return 1;
}

/* increments number by one without arithmetic operators */
unsigned int AddOne(unsigned int num)
{
	int m = 1; 
     
	/* Flip all 1 bits until we find a 0, then flip that 0 to 1, mimicing a binary increment by 1 */
	while(num & m) /* while current bit of num is 1, flip to 0, itirate until a 0 bit */
	{ 
        	num = num ^ m;  /* the '1' bit and the '1' from m are in same position, XOR will flip it to 0 (1^1=0), keeping other bits same value (xor other bits with 0)*/
        	m <<= 1; /* next iteration mask next bit */
	} 
     
    return num ^ m;      /* flip the 0 bit with XOR (0^1=1), keeps other bits same value. (xor other bits wih 0) */
} 	

/* for each element, check if it has at least 3 bits on, if condition is met, print it. */
void Print3Bit(unsigned int* arr, size_t size)
{
	size_t i, j;
	int bit_count = 0;
	
	for(i = 0;i < size;++i)
	{
		for(j = 0;j<32;++j) /* go over all bits of current element */
		{
			if(1 == (1 & (arr[i] >> j))) /* if current iteration bit is 1 */
			{
				if(3 == ++bit_count)
				{
					printf("%u, ", arr[i]);
					break;
				}
			}
		}
		bit_count = 0;
	}	
	
}

unsigned int MirrorBitsLoop(unsigned int num)
{
    unsigned int result = 0;
    int i;
    for (i = 0; i < 32; ++i) 
    {
        if((num & (1 << i)))
        {
            result |= 1 << (31 - i);
        }
    }
    return result;
}

unsigned int MirrorBits(unsigned int num)
{
	num = ((num & 0xFFFF0000) >> 16 | (num & 0x0000FFFF) << 16); /* turn off first 16 bits, shift last 16 bits to the right, OR with first 16 bits shifted 16 to the left (swap) */
	num = ((num & 0xFF00FF00) >> 8 | (num & 0x00FF00FF) << 8);
	num = ((num & 0xF0F0F0F0) >> 4 | (num & 0x0F0F0F0F) << 4);
	num = ((num & 0xCCCCCCCC) >> 2 | (num & 0x33333333) << 2);
	num = ((num & 0xAAAAAAAA) >> 1 | (num & 0x55555555) << 1);	
	return (num);
}

int Bits2And6(unsigned char byte)
{	
	int result = -1;
	result += byte & (1 << 1);
	result += byte & (1 << 5);
	return (result);
}

int Bits2Or6(unsigned char byte)
{
	int first_bit = byte & (1 << 1);
	int second_bit = byte & (1 << 5);
	
	return (first_bit | second_bit)
}


unsigned int ClosestDiv16(unsigned int num)
{
	return (num & 0xFFFFFFF0); 
}

void XorSwap(unsigned int* num1, unsigned int* num2)
{
	*num1 = *num1 ^ *num2;
	*num2 = *num1 ^ *num2;
	*num1 = *num1 ^ *num2;
}

/* Reviewed by Ori,
 * Counts the number of bits that are on in an unsigned int
 */
size_t numSetBitsLoop(unsigned int num)
{
	int i;
	int count = 0;
	
	for(i = 0; i < 32; ++i)
	{
		count += (num >> i) & 0x1; /* if current iteration bit is 1, 1&1=1 (count += 1), otherwise 0&1=0 (count += 0) */
	}
	return count;
}

/* yeah */
size_t numSetBits(unsigned int num)
{
	num = ((num & 0xAAAAAAAA) >> 1) + (num & 0x55555555);
	num = ((num & 0xCCCCCCCC) >> 2) + (num & 0x33333333);
	num = ((num & 0xF0F0F0F0) >> 4) + (num & 0x0F0F0F0F);
	num = ((num & 0xFF00FF00) >> 8) + (num & 0x00FF00FF);
	num = ((num & 0xFFFF0000) >> 16) + (num & 0x0000FFFF);	
	
	return num;
}

/* prints bits of floating point value */
void printFloatBits(float num)
{
	int i = 0;
	for(i = 31; 0 <= i; --i)
	{
		printf("%d", (((int)num>>i) & 0x1));
	}
	printf("\n");
}


int main()
{
	/*printf("%ld\n", Pow2(3,0));*/ /* 3 * 2^2 */
	/*printf("%ld\n", Pow2(3,4));*/ /* 3 * 2^4 */
	/*printf("%d\n", IsPowOf2(0));*/
/*	printf("%d\n", IsPowOf2Loop(8));*/

	/*printf("%d", IsPowOf2Loop(0));*/
/*	printf("9 + 1 = %d", AddOne(9));*/

	/*unsigned int arr[3] = { 7, 15, 0 };
	Print3Bit(arr, 3);*/
	
	/*printf("%u", MirrorBits((unsigned int)num));*/
	
	/*printf("%d", Bits2Or6(34));*/
	/*printf("%u", ClosestDiv16(48));*/
	
	/*unsigned int a = 5;
	unsigned int b = 6;
	XorSwap(&a,&b);
	printf("a = %u, b = %u", a,b);*/
	
	/*printf("%lu", numSetBits(8));*/
	
	/*printFloatBits(5);*/
	return 0;	
}
