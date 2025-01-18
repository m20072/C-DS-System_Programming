#include <stddef.h> /* size_t */
#include <stdlib.h> /* dynamic allocation */
#include <stdio.h> /* printf */
#include <ctype.h> /* tolower */
#include <assert.h> /* assert */
#include <string.h> /* strlen */


/* Reviewed by Ori */
char* StrLowCaseCpy(char* dest, const char* src);
char* StrLowCaseDup(const char* str);
void Print(const char* str);


void Print(const char* str)
{
	printf("%s\n", str);
}

/* Copies src into dest in lower case */
char* StrLowCaseCpy(char* dest, const char* src)
{
	assert(NULL != dest && NULL != src);
	char* p_dest = dest;

	while('\0' != *src)
	{
		*p_dest = tolower(*src);
		++p_dest;
		++src;
	}
	*p_dest = '\0';
	
	return dest;
}

/* copies str in lowercase into a new dynamically allocated memory space */
char* StrLowCaseDup(const char* str)
{
	assert(NULL != str);

	char* dup = (char*)malloc((strlen(str) + 1) * sizeof(char));
	if(NULL == dup)
	{
		return NULL;
	}

	return StrLowCaseCpy(dup, str);
}

int main(int argc, char **argv, char **envp)
{
	char** pStringsArr = NULL;
	size_t i;
	size_t count = 0;

	(void)argc;
	(void)argv;
	
	while (NULL != envp[count])
	{
		++count;
	}

	pStringsArr = (char**)malloc(count * sizeof(char*));
	if(NULL == pStringsArr)
	{
		exit(1);
	}

	for(i = 0; i < count; ++i)
	{
		pStringsArr[i] = StrLowCaseDup(envp[i]); /* hard to debug, seprate into functions */
	}
	
	for(i = 0; i < count; ++i)
	{
		Print(pStringsArr[i]);
	}
	
	for(i = 0; i < count; ++i)
	{
		free(pStringsArr[i]);
	}

	free(pStringsArr);
	return 0;
}

