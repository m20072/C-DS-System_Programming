#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include "wbo.h"


void* MemSet(void* str, int c, size_t n)
{
	ptr_t p;
	size_t word = c;
	size_t word_size = sizeof(void*);
	size_t alingment_remainder = *(size_t*)&str % word_size; /* holds the remainder to check for alingment */
	p.ch = str;
	
	word |= (word << 8); /* 2 bytes occupied */
	word |= (word << 16); /* 4 bytes occupied */
	word |= (word << 32); /* 8 bytes occupied */
	
	/* if setting memory for less than a word, do byte by byte and return */
	if(n < word_size)
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
		--n;
	}
	/*printf("%lu\n", n);
	n = p.ch - (char*)str;
	printf("str = %p, p.ch = %p\n", str, p.ch);
	printf("%lu\n", n);*/
	p.st = (size_t*)p.ch;
	
	/* p is currently aligned (address it points to is multiply of a WORD), now send chunks of 8 as long as n > 8 */
	while(word_size < n)
	{
		*(p.st++) = word; /* ++ jumps 8 bytes */
		n-= word_size;
	}
	
	p.ch = (char*)p.st;
	
	/* byte by byte again*/
	while(0 < n)
	{
		*(p.ch++) = c;
		--n;
	}
	return str;
}


	/*  byte by byte if n is less than WORD */
	/* else, chunks of words while word_size < n */
	/* byte by byte at the end if n>0 left */
void* MemCpy(void *dest_str, const void* src_str, size_t n) /* assume both are aligned*/
{
	ptr_t p_dest;
	ptr_t p_src;
	/*size_t word;*/
	size_t word_size = sizeof(void*);
	
	if(n < word_size) /* byte by byte if n is less than word_size */
	{
		p_dest.ch = dest_str;
		p_src.ch = (char*)src_str;
		while(0 < n)
		{
			*(p_dest.ch++) = *(p_src.ch++);
			--n;
		}
		return dest_str;
	}
	
	/* chunks until n is less than word_size */
	p_dest.st = (size_t*)dest_str; /* can remove size_t cast?*/
	p_src.st = (size_t*)src_str;
	/*word = *(size_t*)src_str;*/ /* WORD(8) bytes chunk? */
	
	while(word_size < n)
	{
		*(p_dest.st++) = *(p_src.st++);
		n-= word_size;
	}
	
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
	
	if(src_ptr < dest_ptr) /* copy from end of src to start if met */
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

