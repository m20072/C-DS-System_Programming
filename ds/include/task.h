/******************************************************************************
* File: task.h
*
* Purpose:
*   Provides an interface for task implementation.
*
* Author:
*   Matan Chen
*
* Review History:
*   - 
*
******************************************************************************/

#ifndef __TASK_H__
#define __TASK_H__

#include <sys/types.h> /* for ssize_t */
#include "ilrd_uid.h" /* for ilrd_uid_t */

/*******************************************************************************/
/* Typedef: job_func_t
 * Purpose: Defines a function pointer type for tasks to perform.
 * Receives: A pointer to parameters for the task.
 * Returns: The next time the task should run. If no next run, returns -1.
 */
typedef ssize_t (*job_func_t)(void* params);
/*******************************************************************************/

/*******************************************************************************/
/* Typedef: cleanup_func_t
 * Purpose: Defines a function type for cleanup after task destruction.
 * Receives: A pointer to parameters for the cleanup function.
 * Returns: None.
 */
typedef void (*cleanup_func_t)(void* params);
/*******************************************************************************/

typedef struct task task_t;

/*******************************************************************************/
/* Function: TaskCreate
 * Purpose: Creates a new task instance.
 * Receives:
 *   - time: Absolute time at which the task should run.
 *   - job_func: Function pointer to the job function.
 *   - job_params: Parameters for the job function.
 *   - cleanup_func: Function pointer to the cleanup function.
 *   - cleanup_params: Parameters for the cleanup function.
 *   - interval: Time interval for repeating tasks (-1 for non-repeating).
 * Returns: A pointer to the created task.
 */
task_t* TaskCreate(time_t time, job_func_t job_func, void* job_params,
                    cleanup_func_t cleanup_func, void* cleanup_params,
                    ssize_t interval);
/*******************************************************************************/

/*******************************************************************************/
/* Function: TaskDestroy
 * Purpose: Destroys the given task and frees allocated resources.
 * Receives: A pointer to the task.
 * Returns: None.
 */
void TaskDestroy(task_t* task);
/*******************************************************************************/

/*******************************************************************************/
/* Function: TaskGetTime
 * Purpose: Retrieves the absolute execution time of the given task.
 * Receives: A pointer to the task.
 * Returns: The absolute execution time of the task.
 */
time_t TaskGetTime(task_t* task);
/*******************************************************************************/

/*******************************************************************************/
/* Function: TaskSetTime
 * Purpose: Sets the absolute execution time of the given task.
 * Receives:
 *   - task: A pointer to the task.
 *   - time: The new absolute execution time to set.
 * Returns: None.
 */
void TaskSetTime(task_t* task, time_t time);
/*******************************************************************************/

/*******************************************************************************/
/* Function: TaskGetUID
 * Purpose: Retrieves the unique identifier (UID) of the given task.
 * Receives: A pointer to the task.
 * Returns: The UID of the task.
 */
ilrd_uid_t TaskGetUID(task_t* task);
/*******************************************************************************/

/*******************************************************************************/
/* Function: TaskRun
 * Purpose: Executes the job function of the task.
 * Receives: A pointer to the task.
 * Returns: The interval for the next execution, or -1 if not to be repeated.
 */
ssize_t TaskRun(task_t* task);
/*******************************************************************************/

/*******************************************************************************/
/* Function: TaskCleanUp
 * Purpose: Executes the cleanup function of the task.
 * Receives: A pointer to the task.
 * Returns: None.
 */
void TaskCleanUp(task_t* task);
/*******************************************************************************/

/*******************************************************************************/
/* Function: TaskGetInterval
 * Purpose: Retrieves the interval of the task.
 * Receives: A pointer to the task.
 * Returns: The interval of the task.
 */
ssize_t TaskGetInterval(task_t* task);
/*******************************************************************************/

/*******************************************************************************/
/* Function: TaskSetInterval
 * Purpose: Sets a new interval for the task.
 * Receives:
 *   - task: A pointer to the task.
 *   - interval: The new interval to set.
 * Returns: None.
 */
void TaskSetInterval(task_t* task, ssize_t interval);
/*******************************************************************************/

#endif /* __TASK_H__ */
