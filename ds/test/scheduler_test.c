/*
*	Writer : Matan Chen
*	Implementation of scheduler test
*	
*	 
*
*	Reviewed by: 
*
*/

#include <stdio.h>
#include <assert.h>
#include <time.h>

#include "../include/scheduler.h"


#define GREEN "\x1b[1;32m"
#define RED "\x1b[1;31m"
#define UNFORMAT "\x1b[1;0m"

void TestStartStop();
void TestNoneRecurringTask();
ssize_t TaskPrint(void* param);
ssize_t TaskStop(void* param);
ssize_t TaskPrintNoneRecurring(void* param);
void TestRemovingTask();
void Cleanup(void* param);

int main(void)
{
	TestRemovingTask();
    TestStartStop();
    TestNoneRecurringTask();
    printf(GREEN "\n✅ All tests completed successfully! ✅\n" UNFORMAT);
    return 0;
}

ssize_t TaskPrint(void* param)
{
    printf("Task executed with value: %d\n", *(int*)param);
    ++*(int*)param;
    return (1);
}

ssize_t TaskPrintNoneRecurring(void* param)
{
    printf("Task executed with value: %d\n", *(int*)param);
    ++*(int*)param;
    return (-1);
}

ssize_t TaskStop(void* param)
{
    printf("Stopping scheduler...\n");
    SchedStop((scheduler_t*)param);
    return -1;
}

void Cleanup(void* param)
{
    printf("Cleaning up task with value: %d\n", *(int*)param);
}

void TestStartStop()
{
    scheduler_t* sched;
    int task1;
    int task2;
    time_t now;
    
    printf("\n--- Testing Start and Stop ---\n");
    sched = SchedCreate();
    assert(sched != NULL);
    
    task1 = 1;
    task2 = -1; /* This task stops the scheduler */
    now = time(NULL);
    
    SchedAddTask(sched, now + 1, TaskPrint, &task1, Cleanup, &task1, 1); /* runs in 1 sec from now and intervals of 1 sec (bcz of return value of taskprint), prints value of param(task1) and increases param(task1) by 1 */
    SchedAddTask(sched, now + 6, TaskStop, sched, Cleanup, &task2, 1); /* runs in 6 seconds from now, intervals -1 (not recurring) and runs taskstop with scheduler as param so it can run SchedStop(param) */
    
    SchedStart(sched);
    
    SchedClear(sched);
    printf("Count: %ld\n", SchedCount(sched));
    assert(SchedIsEmpty(sched) == 1);
    
    now = time(NULL);
    SchedAddTask(sched, now + 1, TaskPrint, &task1, Cleanup, &task1, 1);
    SchedAddTask(sched, now + 6, TaskStop, sched, Cleanup, &task2, 1);
    
    printf("Count: %ld\n", SchedCount(sched));
    
    SchedStart(sched);
    SchedClear(sched);
    
    SchedDestroy(sched);
}

void TestRemovingTask()
{
	scheduler_t* sched = SchedCreate();
	ilrd_uid_t uid;
	int task1 = 1;
	uid = SchedAddTask(sched, 1, TaskPrint, &task1, Cleanup, &task1, 1);
	printf("Count: %ld\n", SchedCount(sched));
	
	printf("TEST ID: %ld\n", uid.counter);
    printf("TEST PID: %d\n", uid.pid);
	SchedRemoveTaskByUID(sched, uid);
	
	printf("Count: %ld\n", SchedCount(sched));
	
	SchedDestroy(sched);
	
}

void TestNoneRecurringTask()
{
    scheduler_t* sched;
    int task1;
    time_t now;
    
    printf("\n--- Testing Recurring Task Time Change ---\n");
    sched = SchedCreate();
    assert(sched != NULL);
    
    task1 = 2;
    now = time(NULL);
    
    SchedAddTask(sched, now + 1, TaskPrintNoneRecurring, &task1, Cleanup, &task1, 2);
    assert(!SchedIsEmpty(sched));
    
    SchedStart(sched);
    
    SchedDestroy(sched);
}

