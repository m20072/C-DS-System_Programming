#ifndef __SERIALIZE_STRUCTS_H__
#define __SERIALIZE_STRUCTS_H__

#include <stdio.h>
#define NAME_SIZE 100

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
    real_grades_t real_grades;
	hmn_grades_t hmn_grades;
	float sports;
} grade_t;

typedef struct student
{
	char f_name[NAME_SIZE];
	char l_name[NAME_SIZE];
	grade_t grades;
} student_t;

void SaveStudent(FILE* file, student_t* student);
void LoadStudent(FILE* file, student_t* student);

#endif /* __SERIALIZE_STRUCTS_H__ */
