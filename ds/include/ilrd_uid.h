/******************************************************************************
* File: ilrd_uid.h
*
* Purpose:
*   Provides an interface for ilrd_uid implementation.
*	functions for generating and comparing unique identifiers (UIDs).
*	
* Author:
*   Matan Chen
*
* Review History:
*   - Shani
*
******************************************************************************/

#ifndef __ILRD_UID_H__
#define __ILRD_UID_H__

#include <stddef.h> /* size_t */
#include <netinet/in.h> /* in_addr_t */
#include <time.h> /* time */


/* ilrd_uid_t represents a unique identifier.
 * The fields are for internal use only, avoid direct access or modification.
*/
typedef struct
{
	size_t counter;
	pid_t pid;
	time_t time;
	in_addr_t ip_addr;
} ilrd_uid_t;

/* Represents an invalid UID instance. */
extern const ilrd_uid_t invalid_id;

/*******************************************************************************/
/* Function: CreateUID.
 * Purpose: Generates a unique identifier (UID).
 * Parameters: None. 
 * Returns: A new unique identifier of type ilrd_uid_t.
 * Complexity: O(n), where n being the number of local network interfaces.
 */
ilrd_uid_t CreateUID(void);
/*******************************************************************************/

/*******************************************************************************/
/* Function: CompareUID.
 * Purpose: Compares between two UID instances.
 * Parameters: first UID instance and second UID instance.
 * Returns: 1 if the UIDs are equal, 0 otherwise.
 * Complexity: O(n), where n being the number of local network interfaces.
 */
int CompareUID(const ilrd_uid_t first, const ilrd_uid_t second);
/*******************************************************************************/

#endif
