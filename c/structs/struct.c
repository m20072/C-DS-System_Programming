#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "struct.h"

/* Print Functions */
static status_t PrintInt(mixed_data_t* element);
static status_t PrintFloat(mixed_data_t* element);
static status_t PrintString(mixed_data_t* element);

/* Add Functions */
static status_t AddToInt(mixed_data_t* element, int add_num);
static status_t AddToFloat(mixed_data_t* element, int add_num);
static status_t AddToString(mixed_data_t* element, int add_num);

/* Clean-Up functions */
static status_t IntCleanUp(mixed_data_t* element);
static status_t FloatCleanUp(mixed_data_t* element);
static status_t StringCleanUp(mixed_data_t* element);

/* Helper Functions */
static size_t NumDigits(int number);


/* Creates an INT element */
status_t InitInt(mixed_data_t* element, int value)
{
	if (NULL == element)
	{
		fprintf(stderr, "INT element creation failed due to NULL pointer\n");
		return FAILURE;
	}

	*(int*)&element->data = value;
	element->print = &PrintInt;
	element->add_int = &AddToInt;
	element->clean_up = &IntCleanUp;
	return SUCCESS;
}

/* Creates a FLOAT element */
status_t InitFloat(mixed_data_t* element, float value)
{
	if (NULL == element)
	{
		fprintf(stderr, "FLOAT element creation failed due to NULL pointer\n");
		return FAILURE;
	}
	*(float*)&element->data = value;
	element->print = &PrintFloat;
	element->add_int = &AddToFloat;
	element->clean_up = &FloatCleanUp;
	return SUCCESS;
}

/* Creates a STRING element */
status_t InitString(mixed_data_t* element, char* value)
{
	if (NULL == element || NULL == value)
	{
		fprintf(stderr, "STRING element creation failed due to NULL pointer\n");
		return FAILURE;
	}
	
	element->data = (void*)strdup(value);
	if(NULL == element->data)
	{
		fprintf(stderr, "STRING element creation failed due to strdup error\n");
		return FAILURE;
	}
	
	element->print = &PrintString;
	element->add_int = &AddToString;
	element->clean_up = &StringCleanUp;
	return SUCCESS;
}


static status_t PrintInt(mixed_data_t* element)
{
	if(NULL == element)
	{
		return FAILURE;
	}
	printf("%d", *(int*)&element->data);
	return SUCCESS;
}

static status_t PrintFloat(mixed_data_t* element)
{
	if(NULL == element)
	{
		return FAILURE;
	}
    printf("%f", *(float*)&element->data);
    return SUCCESS;
}

static status_t PrintString(mixed_data_t* element)
{   
    if(NULL == element || NULL == element->data)
    {
    	return FAILURE;
	}
	printf("%s", (char*)element->data);
	return SUCCESS;
}

/* Increments the int data by add_num */
static status_t AddToInt(mixed_data_t* element, int add_num)
{
	if(NULL == element)
	{
		return FAILURE;
	}
    *(int*)&element->data += add_num;
    return SUCCESS;
}

/* Increments the float data by add_num */
static status_t AddToFloat(mixed_data_t* element, int add_num)
{
	if(NULL == element)
	{
		return FAILURE;
	}
    *(float*)&element->data += add_num;
    return SUCCESS;
}

/* Appends the int value (converted to string format) to the string */
static status_t AddToString(mixed_data_t* element, int add_num)
{
    size_t digit_count = NumDigits(add_num);
    size_t len = 0;

	if(NULL == element)
	{
		return FAILURE;
	}
	
    if(NULL != element->data)
    {
        len = strlen(element->data);
    }

    element->data = realloc(element->data, (len + digit_count + 1) * sizeof(char)); /* acts as malloc if str is NULL */
    if(NULL == element->data)
    {
        fprintf(stderr, "Memory allocation failed\n");
        return FAILURE;
    }
    
    sprintf((char*)element->data + len, "%d", add_num); /* skip the string and append add_num at the end */
    return SUCCESS;
}

static status_t IntCleanUp(mixed_data_t* element)
{
	(void)element;
	return SUCCESS;
}
static status_t FloatCleanUp(mixed_data_t* element)
{
	(void)element;
	return SUCCESS;
}

static status_t StringCleanUp(mixed_data_t* element)
{
	if(NULL == element || NULL == element->data)
	{
		return FAILURE;
	}
    free(element->data);
    element->data = NULL;
    return SUCCESS;
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
