#include <stdio.h>
#include <assert.h>
#include <string.h>
#include "../include/stack.h"

/******************************************************************************
* File: test_stack.c 
*
* Purpose:
*   Comprehensive test suite for generic stack implementation
*
* Notes:
*   - Provides systematic testing of all stack operations
*   - Tests both primitive types and structures
*   - Verifies error conditions and edge cases
*   - Uses assert for validation
*   
* Author:
*   Sharon Salman
*
* Review History:
*   -  Reviewed by Daniel
*
******************************************************************************/

typedef struct
{
    char name[32];
    float grade;
    float grade2;
    float grade3;
} student;

void TestBasicOperations(void)
{
    stack_t *stk = Create(3 , sizeof(int));
    int value1 = 42;
    int value2 = 73;
    int *peek_result;
    size_t initial_size;
    
    assert(NULL != stk);
    assert(0 == Size(stk));
    assert(3 == Capacity(stk));
    assert(1 == IsEmpty(stk));
    

    Push(stk, &value1);
    assert(1 == Size(stk));
    assert(0 == IsEmpty(stk));
    
    peek_result = (int*)Peek(stk);
    assert(42 == *peek_result);
    

    Push(stk, &value2);
    assert(2 == Size(stk));
    peek_result = (int*)Peek(stk);
    assert(73 == *peek_result);
    

    initial_size = Size(stk);
    Pop(stk);
    assert((initial_size - 1) == Size(stk));
    peek_result = (int*)Peek(stk);
    assert(42 == *peek_result);
    
    Destroy(stk);
    printf("Basic operations test passed!\n");
}

void TestStudentStructure(void)
{
    student s1 = {"Sharon", 94.2, 97.4, 67.8};
    student s2 = {"Shani", 97.5, 57.7, 93.6};
    student *peek_result;
    stack_t *stk = Create(2 , sizeof(student));
    

    assert(1 == IsEmpty(stk));
    assert(0 == Size(stk));
    assert(2 == Capacity(stk));
    

    Push(stk, &s1);
    assert(1 == Size(stk));
    peek_result = (student*)Peek(stk);
    assert(0 == strcmp(s1.name, peek_result->name));
    assert(s1.grade == peek_result->grade);
    assert(s1.grade2 == peek_result->grade2);
    assert(s1.grade3 == peek_result->grade3);
    

    Push(stk, &s2);
    assert(2 == Size(stk));
    peek_result = (student*)Peek(stk);
    assert(0 == strcmp(s2.name, peek_result->name));
    assert(s2.grade == peek_result->grade);
    assert(s2.grade2 == peek_result->grade2);
    assert(s2.grade3 == peek_result->grade3);
    

    Pop(stk);
    assert(1 == Size(stk));
    peek_result = (student*)Peek(stk);
    assert(0 == strcmp(s1.name, peek_result->name));
    

    Pop(stk);
    assert(1 == IsEmpty(stk));
    
    Destroy(stk);
    printf("Student structure test passed!\n");
}

int main(void)
{
    printf("\nStarting stack test suite...\n\n");
    
    TestBasicOperations();
    TestStudentStructure();
    
    printf("\nAll tests completed successfully!\n");
    return 0;
}

