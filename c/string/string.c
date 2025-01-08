#include <stddef.h>
#include <stdlib.h>
#include <assert.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "string.h"

int main()
{
/*	char str1[] = "hello";
	char str2[6] = "abcde";
	char str3[50] = "up to 50 chars: ";
	char ch = 'e';
	char str4[] = "ll";*/
	/*printf("StrCmp: %d\n", StrCmp(str1, str2)); 
	printf("StrLen: %lu\n", StrLen(str1));
	printf("StrCpy: %s\n", StrCpy(str2,str1));
	printf("StrnCpy n = 5: %s\n", StrnCpy(str2, str1, 5));
	printf("StrnCmp n = 2: %d\n", StrnCmp(str1, str2, 2));
	printf("changing 2nd char of str2 to E (while str1 2nd char is e) and tyring again\n");
	str2[1] = 'E';
	printf("StrnCmp n = 2: %d\n", StrnCmp(str1, str2, 2));
	printf("StrCaseCmp (should give 0 bcz ignores char case diifference between e and E): %d\n", StrCaseCmp(str1, str2));
	printf("strchr hello with e: %s\n", strchr(str1, ch));
	printf("strdup: %s\n", StrDup(str1));
	printf("strcat: %s\n", StrCat(str3, str1));
	printf("strncat n=2 (hellohe due to last strcat): %s\n", StrnCat(str3,str1, 2));
	printf("StrStr hello and ll: %s", StrStr(str1, str4));
	printf("strncmp ll and ll: %d", StrnCmp("llo","ll", 2));
	printf("strspn: %lu\n",StrSpn("4096 bytes should be enough","0123456789"));
	printf("is abc palindrome: %d\n", isPalindrome("abcb"));
	char str1[] = "hi hi    ";
	printf("spaceReview on: hi  hi: %s", SpaceReview(str1));
	printf("strspn hello: %lu", StrSpn("hello", "he"));
	*/
	char str1[] = "abcba";
	printf("is abcba palindrome: %d\n", IsPalindrome(str1)); 
	/*IsPalindrome("abcba");*/
	return 0;

}

/* Reviewed By: Denis
 */
int IsPalindrome(const char* str)
{
	const char* p_str_end = str + StrLen(str) - 1; /*-1 to be on last character instead of \0*/
	assert(NULL != str);
	
	while(str < p_str_end)
	{
		if(*str != *p_str_end)
		{
			return 0;
		}
		++str;
		--p_str_end;
	}

	return 1;
}

/* Reviewed By: Liel & Denis
 * removes extra white spaces from string
 */
char* SpaceReview(char* str)
{
	char* p_write = str;
	const char* p_read = str;
	int is_last_space = 1; /*init to 1, makes sure first char wouldn't be a white space*/

	assert(NULL != str);

	while('\0' != *p_read)
	{
		if(' ' != *p_read && '\t' != *p_read) /*if current char is not a space write it*/
		{
			*p_write = *p_read;
			++p_write;
			is_last_space = 0; /*for next iteration, know that previous iteration was not a space (as per the condition)*/
		}
		else if (0 == is_last_space) /*last was not a space, so its ok to print a space*/
		{
			*p_write = *p_read;
			++p_write;
			is_last_space = 1;
		}
		++p_read;
	}

	/*makes sure last character is not a white space*/
	if(1 == is_last_space)
	{
		*(p_write-1) = '\0';
	}
	else
	{
		*p_write = '\0';
	}

	return str;
}

/* Reviewed By: Denis
 */
size_t StrSpn(const char* str, const char* accept)
{
    const char* start_str = str;
    assert(NULL != str && NULL != accept);

    while ('\0' != *str && NULL != strchr(accept, *str)) /*NULL vs \0 ????*/
    {
        ++str;
    }

	return str - start_str;
}

/* OOPS, but pretty good! */
size_t StrSpn_oops(const char* str, const char* accept)
{
	/*itirate through s until find a char that is in accept, then
	 if there are more characters from accept add more, until something not from accept*/
	size_t size = 0;
	const char* p_accept = accept;

	assert(NULL != str && NULL != accept);

	while('\0' != *str)
	{
		while('\0' != *p_accept)
		{
			if(*str == *p_accept)
			{
				p_accept = accept;
				++size;
				++str;
				continue;
			}
			/*if wasnt equal, still want to go over all of accept*/
			++p_accept;
		}
		if(0 != size)
			return size;

		p_accept = accept;
		++str;
	}
	return 0;	
}

/* Reviewed By: Denis
 *
 */
char* StrStr(const char* haystack, const char *needle)
{
	int needle_len = StrLen(needle);
	int haystack_len = StrLen(haystack);
	assert(NULL != haystack && NULL != needle);

	while('\0' != *haystack && haystack_len >= needle_len)
	{
		if(0 == StrnCmp(haystack, needle, needle_len))
		{
			return (char*)haystack;
		}

		++haystack;
		--haystack_len;
	}
	return NULL;
}

/* Reviewed By: Denis
 *Append first n src string characters to the end of dst string, dst must be large enough to store, otherwise segmentation fault error
 */
char* StrnCat(char* dst, const char* src, size_t ssize)
{
	char* p_dst_end = dst + StrLen(dst);
	assert(NULL != dst && NULL != src);

	while('\0' != *src && ssize > 0)
	{
		*p_dst_end = *src; /*on first iteration replaces the null termintor with h*/
		++src;
		++p_dst_end;
		--ssize;
	}

	*p_dst_end = '\0';
	return dst;
}

/* Reviewed By: Denis
 * Append src string to the end of dst string, dst must be large enough to store, otherwise segmentation fault error
 */
char* StrCat(char* dst, const char* src)
{
	char* p_dst_end = dst + StrLen(dst); /*on \0 */
	assert(NULL != dst && NULL != src);

	while('\0' != *src)
	{
		*p_dst_end = *src;
		++src;
		++p_dst_end;
	}

	*p_dst_end = '\0';
	return dst;
}


/* Reviewed By: Denis
 * 
 */
char* StrDup(const char* str)
{
	size_t size = StrLen(str) + 1;
	char* dup;

	assert(NULL != str);

	dup = (char*)malloc((size)*sizeof(char));

	while('\0' != *str)
	{
		*dup = *str;
		++dup;
		++str;
	}

	*dup = '\0';
	return dup - size;
}

/* Reviewed By: Denis
 * 
 */
char* StrChr(const char* str, int ch)
{
	assert(NULL != str);

	while('\0' != *str)
	{
		if(ch == *str)
		{
			return (char*)str;
		}
		++str;
	}
	return NULL; /*return NULL if couldn't find that char in the string*/
}

/* Reviewed By: Denis
 * 
 */
char* StrnCpy(char* dest, const char* src, size_t n)
{
	char* p_dest = dest;
	assert(NULL != dest && NULL != src);

	while(n > 0 && '\0' != *src) /* if n is shorter than src or reached end of src, stop*/
	{
		*p_dest = *src;
		++p_dest;
		++src;
		--n;
	}

	while(n > 0)
	{
		*p_dest = '\0'; /*cant tell if goes outside bound?*/
		++p_dest;
		--n;
	}
	return dest;
}
/* Reviewed By: Denis
 * 
 */
char* StrCpy(char* dest, const char* src)
{
	char* p_dest = dest;
	assert(NULL != dest && NULL != src);

	while('\0' != *src)
	{
		*p_dest = *src;
		++p_dest;
		++src;
	}
	*p_dest = '\0';
	
	return dest;
}


/* Reviewed By: Denis
 * 
 */
int StrnCmp(const char* str1, const char* str2, size_t n)
{
	assert(NULL != str1 && NULL != str2);

	if(0 == n)
	{
		return 0;
	}

	while (*str1 == *str2 && '\0' != *str1 && n > 0)
	{
		++str1;
		++str2;
		--n;
	}

	return *str1 - *str2;
}

/* Reviewed By: Denis
 * 
 */
int StrCmp(const char* str1, const char* str2)
{
	assert(NULL != str1 && NULL != str2);

	while(*str1 == *str2 && '\0' != *str1)
	{
		++str1;
		++str2;
	}

	return *str1 - *str2;
}	

/* Reviewed By: Denis
 * 
 */
int StrCaseCmp(const char* str1, const char* str2)
{
	assert(NULL != str1 && NULL != str2);
	
	while(tolower(*str1) == tolower(*str2) && '\0' != *str1)
	{
		++str1;
		++str2;
	}
	return *str1 - *str2;
}

/*reviewed by Denis*/
size_t StrLen(const char* str)
{
	const char* pStr = str;
	assert(NULL != str);

	while('\0' != *pStr) 
	{
		++pStr;
	}

	return pStr - str;
}
