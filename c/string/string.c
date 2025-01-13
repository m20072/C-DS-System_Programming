#include <stdlib.h> /* Dynamic allocations */
#include <assert.h> /* Assert macro */
#include <stdio.h> /* printf */
#include <ctype.h> /* toLower  */
#include "string.h" /* Functions for string manipulation  */

/* Reviewed By: Denis
 * Returns the length of str.
 */
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

/* Reviewed By: Denis
 * Duplicates str into a dynamically allocated memory block.
 */
char* StrDup(const char* str)
{
	char* dup = malloc((StrLen(str) + 1) * sizeof(char));
	char* dup_start;
	assert(NULL != str);

	if(NULL == dup)
	{
		return NULL;
	}

	dup_start = StrCpy(dup, str);
	
	return dup_start;
}

/* Reviewed By: Denis
 * Lexicographic compare between str1 and str2.
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
 * Lexicographic compare of up to n characters between str1 and str2.
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
 * Lexicographic compare between str1 and str2, case insensitive.
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

/* Reviewed By: Denis
 * copies string src to string dest
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
 * Copies up to n characters from string src to string dest, pads with '\0' if src is shorter than n characters.
 */
char* StrnCpy(char* dest, const char* src, size_t n)
{
	char* p_dest = dest;
	assert(NULL != dest && NULL != src);

	while(n > 0 && '\0' != *src)
	{
		*p_dest = *src;
		++p_dest;
		++src;
		--n;
	}

	while(n > 0)
	{
		*p_dest = '\0';
		++p_dest;
		--n;
	}
	return dest;
}

/* Reviewed By: Denis
 * searches for the first occurrence of a character ch in the string str
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

	if('\0' == ch)
	{
		return (char*)str;
	}

	return NULL;
}

/* Reviewed By: Denis
 * Append src string to the end of dst string.
 */
char* StrCat(char* dst, const char* src)
{
	char* p_dst_end = dst + StrLen(dst);
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
 * Append first n src string characters to the end of dst string.
 */
char* StrnCat(char* dst, const char* src, size_t ssize)
{
	char* p_dst_end = dst + StrLen(dst);
	assert(NULL != dst && NULL != src);

	while('\0' != *src && ssize > 0)
	{
		*p_dst_end = *src;
		++src;
		++p_dst_end;
		--ssize;
	}

	*p_dst_end = '\0';
	return dst;
}

/* Reviewed By: Denis
 * Returns the length of the initial segment of the string str,
 * that consists entirely of characters from the string accept.
 */
size_t StrSpn(const char* str, const char* accept)
{
    const char* start_str = str;
    assert(NULL != str && NULL != accept);

    while ('\0' != *str && NULL != StrChr(accept, *str))
    {
        ++str;
    }

	return str - start_str;
}

/* Reviewed By: Denis
 *  Find the first occurrence of the substring needle in the string haystack.
 * returns a pointer to the beginning of the substring.
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