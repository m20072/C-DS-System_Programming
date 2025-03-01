/******************************************************************************
* File: scheduler.c
*
* Purpose:
*   implements scheduler.h
*   
* Author:
*   Matan Chen
*
* Review History:
*   - Gali
*
******************************************************************************/

#include <stdlib.h> /* dynamic allocations & free */
#include <assert.h> /* assert */
#include <unistd.h> /* sleep */

#include "../include/p_queue.h" /* priority queue */
#include "../include/scheduler.h" /* own header */


#define MAX_WAIT_TIME(a) ((a > 0) ? a : 0)

struct scheduler
{  
    p_queue_t* pq;
    volatile int is_running;
};

static int CmpTime(const void* task1, const void* task2);
static int IsUIDMatch(const void* p_task, const void* p_uid);


scheduler_t* SchedCreate(void)
{
    scheduler_t* scheduler = (scheduler_t*)calloc(sizeof(scheduler_t), 1);
    if(NULL == scheduler)
    {
        return NULL;
    }

    scheduler->pq = PQCreate(CmpTime);
    if(NULL == scheduler->pq)
    {
        free(scheduler);
        scheduler = NULL;
        return (NULL);
    }
    /*scheduler->is_running = 0;*/
    return (scheduler);
}

void SchedDestroy(scheduler_t* scheduler)
{
    assert(NULL != scheduler);

    SchedClear(scheduler); /* for each element, free the task and then remove from queue */
    PQDestroy(scheduler->pq); /* destroy the empty queue */
    scheduler->pq = NULL;
    free(scheduler);
    scheduler = NULL;
}

ilrd_uid_t SchedAddTask(scheduler_t* scheduler,
                        time_t time,
                        job_func_t job_func,    
                        void* job_params,
                        cleanup_func_t cleanup_func,
                        void* cleanup_params,
                        ssize_t interval)
{
    task_t* new_task = NULL;

    assert(NULL != scheduler);
    assert(NULL != job_func);
    assert(NULL != cleanup_func);

    new_task = TaskCreate(time, job_func, job_params, cleanup_func, cleanup_params, interval);
    if(NULL == new_task)
    {
        return (invalid_uid);
    }
    if(1 == PQEnqueue(scheduler->pq, new_task))
    {
        free(new_task);
        new_task = NULL;
        return (invalid_uid);
    }

    return (TaskGetUID(new_task));
}

int SchedRemoveTaskByUID(scheduler_t* scheduler, ilrd_uid_t uid)
{
    task_t* tmp_task = NULL;
    assert(NULL != scheduler);
    tmp_task = (task_t*)PQRemove(scheduler->pq, IsUIDMatch, &uid);
    if(NULL == tmp_task) /* if reached tail */
    {
        return (1);
    }
    TaskCleanUp(tmp_task); /* might be a task that ran job func and re-enqueued, so need clean-up */
    TaskDestroy(tmp_task);
    return (0);
}

void SchedClear(scheduler_t* scheduler)
{
    task_t* curr_task = NULL;
    assert(NULL != scheduler);
    while(!SchedIsEmpty(scheduler))
    {
        curr_task = (task_t*)PQPeek(scheduler->pq);
        TaskCleanUp(curr_task);
        TaskDestroy(curr_task);
        PQDequeue(scheduler->pq);
    }
}

int SchedIsEmpty(scheduler_t* scheduler)
{
    assert(NULL != scheduler);
    return (PQIsEmpty(scheduler->pq));
}

size_t SchedCount(scheduler_t* scheduler)
{
    assert(NULL != scheduler);
    return (PQCount(scheduler->pq));
}

int SchedStart(scheduler_t* scheduler)
{
    task_t* first_task = NULL;

    assert (NULL != scheduler);
    scheduler->is_running = 1;

    while(!SchedIsEmpty(scheduler) && (1 == scheduler->is_running))
    {
        first_task = (task_t*)PQPeek(scheduler->pq); /* Peek will not occur on empty list, (while not empty) */
        sleep(MAX_WAIT_TIME(TaskGetTime(first_task) - time(NULL))); /* When time arg is NULL, the call cannot fail. */

        /* Dequeue the task and then run it while setting its interval to the return value of taskRun */
        PQDequeue(scheduler->pq);
        TaskSetInterval(first_task, TaskRun(first_task));

        /* if interval was set to -1, destroy the task without enqueueing */
        if(-1 == TaskGetInterval(first_task))
        {
            TaskCleanUp(first_task);
            TaskDestroy(first_task);
        }
        else
        {
            TaskSetTime(first_task, time(NULL) + (time_t)TaskGetInterval(first_task));
            /* if a task failed to re-enqueue, clear scheduler and return 1 to indicate failure */
            if(0 != PQEnqueue(scheduler->pq, first_task))
            {
                TaskCleanUp(first_task);
                TaskDestroy(first_task);
                SchedClear(scheduler);
                scheduler->is_running = 0;
                return (1);
            }
        }
    }
    scheduler->is_running = 0;
    return (0);
}

void SchedStop(scheduler_t* scheduler)
{
    assert(NULL != scheduler);
    scheduler->is_running = 0;
}

static int CmpTime(const void* task1, const void* task2)
{
    return (TaskGetTime((task_t*)task1) - TaskGetTime((task_t*)task2));
}

static int IsUIDMatch(const void* p_task, const void* p_uid)
{
    return (CompareUID(TaskGetUID((task_t*)p_task), *(const ilrd_uid_t*)p_uid)); /* should cast p_task to const task_t* but taskgetuid is not const func so doesnt work atm */
}