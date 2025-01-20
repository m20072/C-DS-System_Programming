/******************************************************************************
* File: wbo_test.c
*
* Purpose:
*   Test suite for wbo.h
*
* Notes:
*   - <insert notes here>
*   
* Author:
*   Shani Zuniga
*
******************************************************************************/

#include <stdio.h>						/* printf */
#include <stdlib.h>						/* malloc, free */
#include <assert.h>                     /* assert */
#include <string.h>						/* memset */
#include "wbo.h"						/* own header */

void TestMemSet(void)
{
	char* src1 = NULL;
	char* src2 = NULL;
	size_t i = 0;
	const unsigned char values[] = { 0, 'a'};
	const size_t size = 100;

	src1 = (char*) malloc(size);
	src2 = (char*) malloc(size);
	assert(NULL != src1 && NULL != src2);

	for (i = 0; i < sizeof(values); i++) {
		memset(src1, 'U', size);
		memset(src2, 'U', size);

		MemSet(src1 + 1, values[i], size - 1);
		memset(src2 + 1, values[i], size - 1);

		assert(0 == memcmp(src1, src2, size));
	}
	
	free(src1);
	free(src2);
}

void TestMemCpy(void)
{
	unsigned char* src = NULL;
	unsigned char* dest1 = NULL;
	unsigned char* dest2 = NULL;
	const size_t size = 128;
	
	src = (unsigned char*) malloc(size);
	dest1 = (unsigned char*) malloc(size);
	dest2 = (unsigned char*) malloc(size);
	assert(NULL != src);
	assert(NULL != dest1 && NULL != dest2);
	
	memset(src, 'U', size / 2);
	memset(src + (size / 2), 'T', size / 2);

	memcpy(dest1, src, size);
	MemCpy(dest2, src, size);
	assert(0 == memcmp(dest1, dest2, size));

	free(src);
	free(dest1);
	free(dest2);
}

void TestMemMove(void)
{
	unsigned char* src1 = NULL;
	unsigned char* src2 = NULL;
	const size_t size = 20;

	src1 = (unsigned char*) malloc(size);
	src2 = (unsigned char*) malloc(size);
	assert(NULL != src1 && NULL != src2);
	
	memset(src1, 0, size);
	memset(src2, 0, size);
	sprintf((char*) src1, "abcdefghijk");
	sprintf((char*) src2, "abcdefghijk");
	
	/* test s1 > s2 */
	memmove(src1 + 5, src1, 6);
	MemMove(src2 + 5, src2, 6);
	assert(0 == memcmp(src1, src2, size));

	memset(src1, 0, size);
	memset(src2, 0, size);
	sprintf((char*) src1, "abcdefghijk");
	sprintf((char*) src2, "abcdefghijk");

	/* test s1 < s2 */
	memmove(src1, src1 + 5, 6);
	MemMove(src2, src2 + 5, 6);
	assert(0 == memcmp(src1, src2, size));

	free(src1);
	free(src2);
}

int main(void)
{	
	printf("Beginning wbo.h tests...\n\n");
	
	TestMemSet();
	TestMemCpy();
	TestMemMove();

	printf("\nAll tests completed successfully\n");
	return 0;
}
