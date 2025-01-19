#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>
#include "struct.h"

void PrintInt(void* i_num)
{
    printf("%d, ",*(int*)&i_num); /* avoid warning "cast to smaller type"  */
}

void PrintFloat(void* f_num)
{
    printf("%f, ", *(float*)&f_num); /* avoid error for trying to cast a ptr into a float */
}

void PrintString(void* str)
{
    if(NULL == str)
    {
        return;
    }
    printf("%s, ", (char*)str);
}

void AddToInt(void* i_num, int add_num)
{
    *(int*)i_num += add_num;
}

void AddToFloat(void* f_num, int add_num)
{
    *(float*)f_num += add_num;
}

/* Appends the int value (converted to string format) to the string */
char* AddToStr(void* str, int add_num)
{
    size_t digit_count = NumDigits(add_num);
    size_t len = 0;

    if(NULL != str)
    {
        len = strlen(str);
    }

    str = realloc(str, (len + digit_count + 1) * sizeof(char)); /* acts as malloc if str is NULL */
    if(NULL == str)
    {
        fprintf(stderr, "Memory allocation failed\n");
        exit(1);
    }
    
    sprintf((char*)str + len, "%d", add_num); /* skip the string and append add_num at the end */
    return str;
}

char* StrCleanUp(void* str)
{
    free(str); /* its fine if str is NULL */
    return NULL;
}

/* Traverse through array and run the appropriate print function for each element according to its type */
void Print(data_t* arr, size_t size)
{
    size_t i;
    assert(NULL != arr);

    for(i = 0;i<size;++i)
    {
        switch (arr[i].type) 
        {
            case INT:
                PrintInt(arr[i].data);
                break;

            case FLOAT:
                PrintFloat(arr[i].data);
                break;

            case STRING:
                PrintString(arr[i].data);
                break;
        }
    }
    printf("\n");
}

/* Traverse through array and run the apropriate add function to add the int value to each element */
void Add(data_t* arr, size_t size, int add_num)
{
    size_t i;
    assert(NULL != arr);

    for(i = 0; i < size; ++i)
    {
        switch (arr[i].type) 
        {
            case INT:
                AddToInt(&arr[i].data, add_num);
                break;

            case FLOAT:
                AddToFloat(&arr[i].data, add_num);
                break;

            case STRING:
                arr[i].data = AddToStr(arr[i].data, add_num);
                break;
        }
    }
}

/* Traverse through array and run the apropriate CleanUp function for each element (if applicable) */
void CleanUp(data_t* arr, size_t size)
{
    size_t i;
    assert(NULL != arr);

    for(i = 0; i < size; ++i)
    {
        switch (arr[i].type) 
        {
            case INT:
                break;

            case FLOAT:
                break;

            case STRING:
                arr[i].data = StrCleanUp(arr[i].data);
                break;
        }
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
