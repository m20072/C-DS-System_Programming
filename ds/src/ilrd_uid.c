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


#include <ifaddrs.h> /*struct ifaddrs, getifaddrs, freeifaddrs */
#include <unistd.h> /* getpid */
#include <time.h> /* time */

#include "../include/ilrd_uid.h"


static size_t counter = 0;
static uint32_t GetIpAddr();
const ilrd_uid_t invalid_id = { 0 };

ilrd_uid_t CreateUID(void)
{
	ilrd_uid_t uid;
	uid.counter = ++counter;
	uid.pid = getpid();
	uid.time = time(NULL);
	uid.ip_addr = GetIpAddr();
	return uid;
}

int CompareUID(const ilrd_uid_t first, const ilrd_uid_t second)
{
	return (first.counter == second.counter
		&& first.pid == second.pid
		&& first.time == second.time
		&& (first.ip_addr == second.ip_addr));
}

static in_addr_t GetIpAddr()
{
    struct ifaddrs* ifap = NULL;
    struct ifaddrs* ifa = NULL;
    struct sockaddr_in* sa = NULL;
    in_addr_t found_ip = 0;
    getifaddrs(&ifap); /* creates a linked list of structures describing the network interfaces of the local system */
    
	for (ifa = ifap; NULL != ifa; ifa = ifa->ifa_next)
    {
		if ((NULL != ifa->ifa_addr) && (AF_INET == ifa->ifa_addr->sa_family) && (69699 == ifa->ifa_flags))
        {
            sa = (struct sockaddr_in*)ifa->ifa_addr;
            found_ip = sa->sin_addr.s_addr;
            break;
        }
    }
    freeifaddrs(ifap);
    return (found_ip);
}