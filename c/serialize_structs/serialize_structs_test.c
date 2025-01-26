/* Reviewed by Sharona */

#include "serialize_structs.h"
#include <stdio.h>

int main()
{
	FILE* fptr = NULL;
	student_t student1 = { "matan", "chen", {{100,98}, {97,96}, 95} };
	student_t student2 = { 0 };

	fptr = fopen("test.bin", "wb+");
	if(NULL == fptr)
	{
		printf("Failed to open the file\n");	
		return 1;
	}

	SaveStudent(fptr, &student1);
	fflush(fptr);
	rewind(fptr);
	LoadStudent(fptr, &student2);
	fclose(fptr);

	printf("f_name: %s\nl_name: %s\nsports: %f\nmath: %f\nphysics: %f\npsychology: %f\nsociology: %f\n",
	student2.f_name,
	student2.l_name,
	  student2.grades.sports, 
	  student2.grades.real_grades.math,
	  student2.grades.real_grades.physics,
	  student2.grades.hmn_grades.psychology,
	  student2.grades.hmn_grades.sociology);
	return 0;
}
