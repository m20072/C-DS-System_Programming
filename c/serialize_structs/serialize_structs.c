#include "serialize_structs.h"

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
	
}

