/******************************************************************************
* File: ilrd_uid.h
*
* Purpose:
*   Provides an interface for ilrd_uid implementation.
*
* Author:
*   Matan Chen
*
* Review History:
*   - 
*
******************************************************************************/

#ifndef __ILRD_UID_H__
#define __ILRD_UID_H__

#include <stddef.h> /* size_t */
#include <netinet/in.h> /* in_addr_t */
#include <time.h> /* time */

typedef struct
{
	size_t count;
	pid_t pid;
	time_t time;
	in_addr_t ip_addr;
} ilrd_uid_t;

extern const ilrd_uid_t invalid_id;
ilrd_uid_t CreateID(void);
int CompareID(const ilrd_uid_t first, const ilrd_uid_t second);

#endif
