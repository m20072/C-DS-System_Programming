/******************************************************************************
* File: scheduler.h
*
* Purpose:
*   Provides an interface for scheduler implementation.
*
* Author:
*   Matan Chen
*
* Review History:
*   - Gali
*
******************************************************************************/

#ifndef __SCHEDULER_H__
#define __SCHEDULER_H__

#include "../include/ilrd_uid.h" /* ilrd_uid_t */
#include "../include/task.h" /* job_func_t, cleanup_func_t */

typedef struct scheduler scheduler_t;

/*******************************************************************************/
/* Function: SchedCreate
 * Purpose: Creates and initializes a new scheduler.
 * Receives: None.
 * Returns: A pointer to the new scheduler, or NULL on failure.
 * Complexity: O(1).
 */
scheduler_t* SchedCreate(void);
/*******************************************************************************/

/*******************************************************************************/
/* Function: SchedDestroy
 * Purpose: Destroys the given scheduler and frees all allocated resources.
 * Receives: A pointer to the scheduler.
 * Returns: None.
 * Complexity: O(n).
 */
void SchedDestroy(scheduler_t* scheduler);
/*******************************************************************************/


/*******************************************************************************/
/* Function: SchedAddTask
 * Purpose: Adds a new task to the scheduler.
 * Receives:
 *   - scheduler: A pointer to the scheduler.
 *   - time: Absolute time at which the task should run.
 *   - job_func: Function pointer to the job to be executed.
 *   - job_params: Parameters for the job function.
 *   - cleanup_func: Function pointer to cleanup after the job.
 *   - cleanup_params: Parameters for the cleanup function.
 *   - interval: Time interval for repeating tasks (-1 for non-repeating).
 * Returns: A unique identifier (UID) for the added task, or invalid_uid if failed.
 * Complexity: O(n).
 */
ilrd_uid_t SchedAddTask(scheduler_t* scheduler,
                        time_t time,
                        job_func_t job_func,    
                        void* job_params,
                        cleanup_func_t cleanup_func,
                        void* cleanup_params,
                        ssize_t interval);
/*******************************************************************************/
 
/*******************************************************************************/
/* Function: SchedRemoveTaskByUID
 * Purpose: Removes a task from the scheduler by its unique identifier (UID).
 * Receives:
 *   - scheduler: A pointer to the scheduler.
 *   - uid: The unique identifier of the task to remove.
 * Returns: 0 on success, 1 on failure.
 * Complexity: O(n).
 */
int SchedRemoveTaskByUID(scheduler_t* scheduler, ilrd_uid_t uid);
/*******************************************************************************/

/*******************************************************************************/
/* Function: SchedStart
 * Purpose: Starts executing tasks in the scheduler.
 * Receives: A pointer to the scheduler.
 * Returns: 0 on success, 1 on failure.
 * Complexity: O(n).
 */
int SchedStart(scheduler_t* scheduler);
/*******************************************************************************/

/*******************************************************************************/
/* Function: SchedStop
 * Purpose: Stops execution of any further tasks in the scheduler.
 * Receives: A pointer to the scheduler.
 * Returns: None.
 * Complexity: O(1).
 */
void SchedStop(scheduler_t* scheduler);
/*******************************************************************************/

/*******************************************************************************/
/* Function: SchedClear
 * Purpose: Removes all tasks from the scheduler without destroying it (the scheduler).
 * Receives: A pointer to the scheduler.
 * Returns: None.
 * Complexity: O(n).
 */
void SchedClear(scheduler_t* scheduler);
/*******************************************************************************/

/*******************************************************************************/
/* Function: SchedIsEmpty
 * Purpose: Checks if the scheduler has no tasks.
 * Receives: A pointer to the scheduler.
 * Returns: 1 if empty, 0 otherwise.
 * Complexity: O(1).
 */
int SchedIsEmpty(scheduler_t* scheduler);
/*******************************************************************************/

/*******************************************************************************/
/* Function: SchedCount
 * Purpose: Counts the number of tasks currently in the scheduler.
 * Receives: A pointer to the scheduler.
 * Returns: The number of tasks in the scheduler.
 * Complexity: O(n).
 */
size_t SchedCount(scheduler_t* scheduler);
/*******************************************************************************/

#endif /* __SCHEDULER_H__ */
