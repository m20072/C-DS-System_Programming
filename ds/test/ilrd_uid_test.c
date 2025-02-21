/*
*	Writer : Matan Chen
*	Implementation of ilrd_uid
*	
*	 
*
*	Reviewed by: 
*
*/

#include <stdio.h>
#include "../include/ilrd_uid.h"


int main(void)
{
	ilrd_uid_t test = CreateID();
	ilrd_uid_t test2 = CreateID();
/*	printf("%u\n", test.ip_addr);*/
	printf("%d", CompareID(test, test2));
	return 0;
}
