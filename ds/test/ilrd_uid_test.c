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

static void Test();

int main(void)
{
	Test();
	return 0;
}

void Test()
{
	ilrd_uid_t uid1 = CreateUID();
	ilrd_uid_t uid2 = CreateUID();

	printf("uid1:\n"
       "counter: %lu\n"
       "pid: %u\n"
       "time: %lu\n"
       "ip address in network byte order: %u\n", uid1.counter, uid1.pid, uid1.time, uid1.ip_addr);

	putchar('\n');

	printf("uid2:\n"
       "counter: %lu\n"
       "pid: %u\n"
       "time: %lu\n"
       "ip address in network byte order: %u\n", uid2.counter, uid2.pid, uid2.time, uid2.ip_addr);

	putchar('\n');

	if(CompareUID(uid1, uid2))
	{
		printf("uid1 and uid2 are equal!\n");
	}
	else 
	{
		printf("uid1 and uid2 are not equal!\n");
	}

}