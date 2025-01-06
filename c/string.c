#include <stddef.h>
#include <assert.h>
#include <stdio.h>

size_t StrLen(const char* s);
int StrCmp(const char* s1, const char* s2);
char* StrCpy(char* dest, const char* src);
char* StrnCpy(char* dest, const char* src, size_t n);

int main()
{
	char str1[] = "hello";
	char str2[6];
//	printf("%d", StrCmp(str1, str2));
	//printf("%lu", StrLen(str1));
	//printf("%s", strcpy(str2,str1));
	printf("%s", strncpy(str2, str1, 5));

}

char* StrnCpy(char* dest, const char* src, size_t n)
{
	assert(*src && *dest);

	char* pDest = dest;

	while(n > 0 && *src) // if n is shorter than src or reached end of src, stop
	{
		*(pDest++) = *(src++);
		n--;
	}

	while(n > 0)
	{
		*(pDest++) = '\0'; // cant tell if goes outside bound?
		n--;
	}

	return dest;
}


char* StrCpy(char* dest, const char* src)
{
	assert(*dest && *src);
	char* pDest = dest;

	while(*src)
	{
		*pDest = *src;
		pDest++;
		src++;
	}

	return dest;
}

int StrCmp(const char* s1, const char* s2)
{
	assert((*s1)&&(*s2));

	while(*s1 || *s2)	
	{
		if(*s1 > *s2)
			return 1;
		
		if(*s1 < *s2)
			return -1;

		s1++;
		s2++;
	}
	return 0;
}	


size_t StrLen(const char* s)
{
	assert(*s);
	size_t size = 0;
	while(*s) 
	{
		++size;
		++s;
	}

	return size;
}
