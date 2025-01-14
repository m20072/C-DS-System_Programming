#include <assert.h>
#include <string.h>

char* SpaceReview(char* str);
void TestReviewWhitepace();

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

void TestReviewWhitespace()
{
	char str1[] = "\t \tHello  \tWorld!  \t\t";
	char str2[] = "Hello,\t  my \t\tfriend";

	assert(strcmp(SpaceReview(str1), "Hello World!") == 0);
	assert(strcmp(SpaceReview(str2), "Hello,\tmy friend") == 0);
}

int main()
{
	TestReviewWhitespace();
	return (0);
}

