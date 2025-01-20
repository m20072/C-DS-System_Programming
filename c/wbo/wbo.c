#include "wbo.h"

#define WORD_SIZE_BYTES sizeof(void*)
#define WORD_SIZE_BITS sizeof(void*) * 8

/* Fills a contiguous block of n bytes in memory with a specific value */
void* MemSet(void* str, int c, size_t n)
{
	ptr_t p;
	size_t word = c;
	size_t alingment_remainder = *(size_t*)&str % WORD_SIZE_BYTES;
	size_t shift = 8;
	p.ch = str;
	
	while (shift < WORD_SIZE_BITS)
    {
        word |= word << shift;
        shift <<= 1;
    }
	
	if(n < WORD_SIZE_BYTES)
	{
		while(0 < n)
		{
			*(p.ch++) = c;
			--n;
		}
		return str;
	}
	
	while(alingment_remainder > 0)
	{
		*(p.ch++) = c;
		--alingment_remainder;
	}
	n -= p.ch - (char*)str;
	
	/* aligned */
	p.st = (size_t*)p.ch;
	while(WORD_SIZE_BYTES < n)
	{
		*(p.st++) = word;
		n -= WORD_SIZE_BYTES;
	}

	/* byte by byte */
	p.ch = (char*)p.st;
	while(0 < n)
	{
		*(p.ch++) = c;
		--n;
	}
	return str;
}

void* MemCpy(void *dest_str, const void* src_str, size_t n) /* assume both are aligned*/
{
	ptr_t p_dest;
	ptr_t p_src;
	
	/* byte by byte if n is less than WORD_SIZE_BYTES */
	if(n < WORD_SIZE_BYTES)
	{
		p_dest.ch = (char*)dest_str;
		p_src.ch = (char*)src_str;
		while(0 < n)
		{
			*(p_dest.ch++) = *(p_src.ch++);
			--n;
		}
		return dest_str;
	}
	
	/* chunks until n is less than WORD_SIZE_BYTES */
	p_dest.st = (size_t*)dest_str;
	p_src.st = (size_t*)src_str;
	
	while(WORD_SIZE_BYTES < n)
	{
		*(p_dest.st++) = *(p_src.st++);
		n -= WORD_SIZE_BYTES;
	}
	
	/* byte by byte if anything left */
	p_dest.ch = (char*)p_dest.st;
	p_src.ch = (char*)p_src.st;
	
	while(0 < n)
	{
		*(p_dest.ch++) = *(p_src.ch++);
		--n;
	}
	return dest_str;
}

void* MemMove(void *dest_str, const void* src_str, size_t n)
{
	const char* src_ptr = src_str;
	char* dest_ptr = dest_str;
	int sign = 1;
	
	if(src_ptr < dest_ptr)
	{
		sign = -sign;
		src_ptr += n - 1;
		dest_ptr += n - 1;
	}
	
	while(0 < n)
	{
		*dest_ptr = *src_ptr;
		dest_ptr += sign;
		src_ptr += sign;
		--n;
	}
	return dest_str;
}

