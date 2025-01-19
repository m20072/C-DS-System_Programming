#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>
#include "struct.h"

void PrintInt(mixed_data_t* element)
{
	printf("%d, ", *(int*)&element->data); /* avoid warning "cast to smaller type"  */
}

void PrintFloat(mixed_data_t* element)
{
    printf("%f, ", *(float*)&element->data); /* avoid error for trying to cast a ptr into a float */
}

void PrintString(mixed_data_t* element)
{   
    if(NULL == element->data)
    {
    	return;
	}
	printf("%s, ", (char*)element->data); /* ternary if instead */
}

/* Increments the int data by add_num */
void AddToInt(mixed_data_t* element, int add_num)
{
    *(int*)&element->data += add_num;
}

/* Increments the float data by add_num */
void AddToFloat(mixed_data_t* element, int add_num)
{
    *(float*)&element->data += add_num;
}

/* Appends the int value (converted to string format) to the string */
void AddToStr(mixed_data_t* element, int add_num)
{
    size_t digit_count = NumDigits(add_num);
    size_t len = 0;

    if(NULL != element->data)
    {
        len = strlen(element->data);
    }

    element->data = realloc(element->data, (len + digit_count + 1) * sizeof(char)); /* acts as malloc if str is NULL */
    if(NULL == element->data)
    {
        fprintf(stderr, "Memory allocation failed\n");
        exit(1);
    }
    
    sprintf((char*)element->data + len, "%d", add_num); /* skip the string and append add_num at the end */
}

void IntCleanUp(mixed_data_t* element)
{
	(void)element;/* empty function */
}
void FloatCleanUp(mixed_data_t* element)
{
	(void)element; /* empty function */
}

void StrCleanUp(mixed_data_t* element)
{
    free(element->data); /* its fine if str is NULL */
    element->data = NULL;
}

/* Traverse through array and run the appropriate print function for each element according to its type */
void Print(mixed_data_t* arr, size_t size)
{
    size_t i;
    assert(NULL != arr);

    for(i = 0; i < size; ++i)
    {
    	arr[i].print(&arr[i]);
    }
    printf("\n");
}

/* Traverse through array and run the apropriate add function to add the int value to each element */
void Add(mixed_data_t* arr, size_t size, int add_num)
{
    size_t i;
    assert(NULL != arr);

    for(i = 0; i < size; ++i)
    {
    	arr[i].add(&arr[i], add_num);
    }
}

/* Traverse through array and run the apropriate CleanUp function for each element (if applicable) */
void CleanUp(mixed_data_t* arr, size_t size)
{
    size_t i;
    assert(NULL != arr);

    for(i = 0; i < size; ++i)
    {
    	arr[i].clean_up(&arr[i]);
    }
}

/* counts the number of digits in a number provided as argument */
size_t NumDigits(int number)
{
    size_t count = 0;
    while(0 != number)
    {
        number /= 10;
        ++count;
    }
    return count;
}
