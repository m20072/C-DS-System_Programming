/******************************************************************************
* File: ilrd_uid.c
*
* Purpose:
*   implements ilrd_uid.h
*   
* Author:
*   Matan Chen
*
* Review History:
*   - 
*
******************************************************************************/


#include <arpa/inet.h> /* struct sockaddr_in */
#include <ifaddrs.h> /*struct ifaddrs, getifaddrs, freeifaddrs */
#include <unistd.h> /* getpid */
#include <time.h> /* time */

#include "../include/ilrd_uid.h"

const ilrd_uid_t invalid_id = { 0 };
static size_t counter = 0;
static uint32_t GetIpAddr();

ilrd_uid_t CreateID(void)
{
	ilrd_uid_t uid;
	uid.count = ++counter;
	uid.pid = getpid();
	uid.time = time(NULL);
	uid.ip_addr = GetIpAddr();
	return uid;
}

int CompareID(const ilrd_uid_t first, const ilrd_uid_t second)
{
	return (first.count == second.count
		&& first.pid == second.pid
		&& first.time == second.time
		&& (first.ip_addr == second.ip_addr));
}

static in_addr_t GetIpAddr()
{
    struct ifaddrs* ifap = NULL;
    struct ifaddrs* ifa = NULL;
    struct sockaddr_in* sa = NULL;
    in_addr_t result = 0;
    getifaddrs(&ifap);
    
	for (ifa = ifap; NULL != ifa; ifa = ifa->ifa_next)
    {
		if ((NULL != ifa->ifa_addr) && (ifa->ifa_addr->sa_family==AF_INET) && (69699 == ifa->ifa_flags))
        {
            sa = (struct sockaddr_in *)ifa->ifa_addr;
            result = sa->sin_addr.s_addr;
            break;
        }
    }
    freeifaddrs(ifap);
    return result;
}
