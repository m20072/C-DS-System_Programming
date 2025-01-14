#include <assert.h>
#include <string.h>

int IsPalindrome(const char* str);
void TestIsPalindrome();

/* Reviewed By: Denis */
int IsPalindrome(const char* str)
{
	const char* p_str_end;
	
	assert(NULL != str);
	
	p_str_end = str + strlen(str) - 1;
	
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

void TestIsPalindrome()
{
	const char* str1 = "12322";
	const char* str2 = "12321";
	const char* str3 = "123421";
	const char* str4 = "123321";
	const char* str5 = "1";
	const char* str6 = "";
	
	assert(IsPalindrome(str1) == 0);
	assert(IsPalindrome(str2) == 1);
	assert(IsPalindrome(str3) == 0);
	assert(IsPalindrome(str4) == 1);
	assert(IsPalindrome(str5) == 1);
	assert(IsPalindrome(str6) == 1);
}


int main()
{
	TestIsPalindrome();
	return (0);
}

