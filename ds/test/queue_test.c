/*
*	Writer : Matan Chen
*	Implementation of Queue
*	
*	 
*
*	Reviewed by: 
*
*/

#include <stdio.h>
#include <assert.h>
#include "../include/queue.h"



#define FORMAT		"\x1b[1;32m"
#define UNFORMAT	"\x1b[1;0m"

static void TestQueueCreateDestroy(void)
{
	queue_t* queue = NULL;

	printf("Testing Queue Create/Destroy...");
	queue = QueueCreate();
	assert(NULL != queue);
	
	QueueDestroy(queue);
	printf(FORMAT "\tPASSED\n" UNFORMAT);
}

static void TestQueueEnqueueDequeue()
{
	queue_t* queue = NULL;
	int val = 42;

	printf("Testing Queue Enqueue/Dequque...");
	queue = QueueCreate();
	assert(NULL != queue);
	assert(1 == QueueIsEmpty(queue));

	assert(0 == QueueEnqueue(queue, &val));
	assert(1 == QueueSize(queue));
	assert(0 == QueueIsEmpty(queue));
	assert(val == *(int*)QueuePeek(queue));

	QueueDequeue(queue);
	assert(0 == QueueSize(queue));
	assert(1 == QueueIsEmpty(queue));

	QueueDestroy(queue);
	printf(FORMAT "PASSED\n" UNFORMAT);
}

static void TestQueueAppend()
{
	queue_t* queue1 = NULL;
	queue_t* queue2 = NULL;
	int values1[] = {1, 2, 3};
	int values2[] = {4, 5, 6};
	int expected[] = {1, 2, 3, 4, 5, 6};
	size_t i = 0;

	printf("Testing Queue Append...");
	queue1 = QueueCreate();
	queue2 = QueueCreate();
	assert(NULL != queue1 && NULL != queue2);
	
	for (i = 0; i < 3; ++i)
	{
		QueueEnqueue(queue1, &values1[i]);
		QueueEnqueue(queue2, &values2[i]);
	}
	QueueAppend(queue1, queue2);
	assert(6 == QueueSize(queue1));
	assert(0 == QueueSize(queue2));
	for (i = 0; i < 6; ++i)
	{
		assert(expected[i] == *(int*)QueuePeek(queue1));
		QueueDequeue(queue1);
	}

	QueueDestroy(queue1);
	QueueDestroy(queue2);
	printf(FORMAT "\t\tPASSED\n" UNFORMAT);	
}

int main(void)
{	
	TestQueueCreateDestroy();
	TestQueueEnqueueDequeue();
	TestQueueAppend();

	printf(FORMAT "\nAll tests completed successfully\n" UNFORMAT);
	return 0;
}




/*
int main(void)
{
	int x = 5;
	int y = 4;
	queue_t* queue = QueueCreate();
	printf("queue size is currently: %lu\n", QueueSize(queue));
	printf("is list empty?: %d\n", QueueIsEmpty(queue));
	QueueEnqueue(queue, &x);
	printf("added value: %d\n", *(int*)QueuePeek(queue));
	printf("queue size is currently: %lu\n", QueueSize(queue));
	printf("is list empty?: %d\n", QueueIsEmpty(queue));
	QueueEnqueue(queue, &y);
	printf("added value: %d\n", *(int*)QueuePeek(queue));
	printf("queue size is currently: %lu\n", QueueSize(queue));
	QueueDequeue(queue);
	printf("Dequeue\n");
	printf("queue size is currently: %lu\n", QueueSize(queue));
	QueueDequeue(queue);
	printf("Dequeue\n");
	printf("queue size is currently: %lu\n", QueueSize(queue));
	printf("is list empty?: %d\n", QueueIsEmpty(queue));
	QueueDestroy(queue);
	return 0;
}*/
