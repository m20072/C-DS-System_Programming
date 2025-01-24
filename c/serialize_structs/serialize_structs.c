#include "serialize_structs.h"
#include <assert.h>
#include <stdio.h>

void SaveStudent(FILE* file, student_t* student)
{
	assert(NULL != student && NULL != file);
	fwrite(student, sizeof(student_t), 1, file);
}

void LoadStudent(FILE* file, student_t* student)
{
	assert(NULL != student && NULL != file);
	fread(student, sizeof(student_t), 1, file);
}