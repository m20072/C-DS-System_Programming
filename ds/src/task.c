/******************************************************************************
* File: task.c
*
* Purpose:
*   implements task.h
*   
* Author:
*   Matan Chen
*
* Review History:
*   - Gil
*
******************************************************************************/
#include <stdlib.h> /* dynamic allocation & free */
#include <string.h> /* memset */
#include <assert.h> /* assert */

#include "../include/task.h" /* own header */

struct task
{
    time_t time;
    ilrd_uid_t uid;
    job_func_t job_func;
    void* job_params;
    cleanup_func_t cleanup_func;
    void* cleanup_params;
    ssize_t interval; /* for non-repeating tasks, set interval to -1 */
};

task_t* TaskCreate(time_t time,
                    job_func_t job_func,
                    void* job_params,
                    cleanup_func_t cleanup_func,
                    void* cleanup_params,
                    ssize_t interval)
{
    task_t* new_task = NULL;

    assert(job_func);
    assert(cleanup_func);

    new_task = (task_t*)calloc(sizeof(task_t), 1);
    if(NULL == new_task)
    {
        return NULL;
    }

    new_task->uid = CreateUID();
    if(CompareUID(new_task->uid, invalid_uid))
    {
        return NULL;
    }
    new_task->time = time;
    new_task->job_func = job_func;
    new_task->job_params = job_params;
    new_task->cleanup_func = cleanup_func;
    new_task->cleanup_params = cleanup_params;
    new_task->interval = interval;

    return (new_task);
}

void TaskDestroy(task_t* task)
{
    assert(NULL != task);
    memset(task, 0, sizeof(task_t));
    free(task);
    task = NULL;
}

time_t TaskGetTime(task_t* task)
{
    assert(NULL != task);
    return (task->time);   
}

void TaskSetTime(task_t* task, time_t time)
{
    assert(NULL != task);
    task->time = time;
}

ilrd_uid_t TaskGetUID(task_t* task)
{
    assert(NULL != task);
    return (task->uid);
}

ssize_t TaskRun(task_t* task)
{
    assert(NULL != task);
    return (task->job_func(task->job_params));
}

void TaskCleanUp(task_t* task)
{
    assert(NULL != task);
    task->cleanup_func(task->cleanup_params);
}

ssize_t TaskGetInterval(task_t* task)
{
    assert(NULL != task);
    return (task->interval);
}

void TaskSetInterval(task_t* task, ssize_t interval)
{
    assert(NULL != task);
    task->interval = interval;
}