#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include <assert.h>

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

char* StrLowCaseCpy(char* dest, const char* src)
{
	char* p_dest = dest;
	assert(NULL != dest && NULL != src);

	while('\0' != *src)
	{
		*p_dest = tolower(*src);
		++p_dest;
		++src;
	}
	*p_dest = '\0';
	
	return dest;
}

char* StrLowCaseDup(const char* str)
{
	char* dup = malloc((StrLen(str) + 1) * sizeof(char));
	
	assert(NULL != str);

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

		pStringsArr = (char**)malloc((count) * sizeof(char*));

		if(NULL == pStringsArr)
			return -1;

	for(i = 0;i<count;++i)
	{
		pStringsArr[i] = StrLowCaseDup(envp[i]);
		printf("%s\n", pStringsArr[i]);
		free(pStringsArr[i]);
	}

	free(pStringsArr);
	return 0;
}

