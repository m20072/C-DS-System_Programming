#include "serialize_structs.h"
#include <assert.h>
#include <stdio.h>

#define NAME_SIZE 100

typedef enum status_t
{
	SUCCESS,
	FAILURE
} status_t;

typedef struct real_grades
{
	float physics;
	float math;
} real_grades_t;

typedef struct hmn_grades
{
	float sociology;
	float psychology;
} hmn_grades_t;

typedef struct grade
{
	hmn_grades_t hmn_grades;
	real_grades_t real_grades;
	float sports;
} grade_t;

typedef struct student
{
	char f_name[NAME_SIZE];
	char l_name[NAME_SIZE];
	grade_t grades;
} student_t;


status_t SaveStudent(student_t* student, char* file_name)
{
	FILE* fptr = NULL;

	assert(NULL != student && NULL != file_name);
	fptr = fopen(file_name, "wb");
	if(NULL == fptr)
	{
		printf("Failed to open the file\n");	
		return FAILURE;
	}

	if(1 != fwrite(student, sizeof(student_t), 1, fptr))  
	{
		fclose(fptr);
		return FAILURE;
	}

	fflush(fptr);
	fclose(fptr);
	return SUCCESS;
}

status_t LoadStudent(student_t* student, char* file_name)
{
		FILE* fptr = NULL;

	assert(NULL != student && NULL != file_name);
	fptr = fopen(file_name, "rb");
	if(NULL == fptr)
	{
		printf("Failed to open the file\n");	
		return FAILURE;
	}

	if(1 != fread(student, sizeof(student_t), 1, fptr))  
	{
		fclose(fptr);
		return FAILURE;
	}

	fflush(fptr);
	fclose(fptr);
	return SUCCESS;
}

