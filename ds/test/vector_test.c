/*
*	Writer : Ofir Hasson
*	Implementation of dynamic vector
*	Vector : dynamic array - array that is grows on demand by a growth factor
*	pushing and popping elements to the back when we dont have enough space or we have a lot of extra space we change the size of the array 	
*
*	Reviewed by: 
*
*/


#include <stdio.h> /* printf */
#include <string.h> /* strcmp */
#include <assert.h> /* assert */
#include "../include/vector.h"



typedef struct
{
	int x;
	float f;
	double d;
	char c;
}s_t;

void CheckVectorTypes();
void CheckVectorStructs();
void SuccessPrint();

int main()
{
	CheckVectorTypes();
	CheckVectorStructs();
	SuccessPrint();
	
	return (0);
}

void CheckVectorTypes()
{
	vector_t* v = VectorCreate(4,3);
	int x = 5;
	float f = 9.5;
	char* str = "aa";
	size_t i = 0;
	
	/* test regular push*/
	assert(0 == VectorPushBack(v,&x));
	assert(0 == VectorPushBack(v,&f));
	assert(0 == VectorPushBack(v,str));
	assert(5 == *(int*)VectorAccessElement(v,0));
	assert(9.5 == *(float*)VectorAccessElement(v,1));
	assert(0 == strcmp((char*)VectorAccessElement(v,2),"aa"));
	assert(8 == VectorCapacity(v));
	
	/* test element change*/
	*(int*)VectorAccessElement(v,0) = 9;
	assert(9 == *(int*)VectorAccessElement(v,0));
	
	/* test increase capacity */
	for(i = 0 ; i < 20 ; ++i)
	{
		assert(0 == VectorPushBack(v,&x));
	}
	assert(23 == VectorSize(v));
	assert(32 == VectorCapacity(v));
	
	/* test push after increase capacity */
	assert(5 == *(int*)VectorAccessElement(v,22));
	
	/* test regular pop */
	VectorPopBack(v);
	VectorPopBack(v);
	assert(21 == VectorSize(v));
	assert(32 == VectorCapacity(v));
	assert(5 == *(int*)VectorAccessElement(v,20));
	
	/* test decrease capacity */
	for(i = 0 ; i < 14 ; ++i)
	{
		VectorPopBack(v);
	}
	assert(7 == VectorSize(v));
	assert(16 == VectorCapacity(v));
	
	/* test reserve */
	VectorReserve(v,50);
	assert(7 == VectorSize(v));
	assert(50 == VectorCapacity(v));
	
	/* test reserve lower capacity */
	VectorReserve(v,30);
	assert(7 == VectorSize(v));
	assert(50 == VectorCapacity(v));
	
	/* test shrink */
	VectorShrink(v);
	assert(7 == VectorSize(v));
	assert(14 == VectorCapacity(v));
	
	/* test illeagal access*/
	assert(NULL == VectorAccessElement(v,14));
	
	/* test pop over capacity*/
	for(i = 0 ; i < 20 ; ++i)
	{
		VectorPopBack(v);
	}
	
	/* test shrink empty vector */
	VectorShrink(v);
	
	/* test destroy */
	VectorDestroy(v);
	
}

void CheckVectorStructs()
{
	vector_t* v = VectorCreate(sizeof(s_t),3);
	s_t s1 = {6, 7.8, 9.5, 'u'};
	s_t s2 = {5, 0.6, 84.6, 'g'};
	s_t s3 = {56, 3.9, 8.2, 'y'};
	size_t i = 0;
	
	/* test regular push*/
	assert(0 == VectorPushBack(v,&s1));
	assert(0 == VectorPushBack(v,&s2));
	assert(0 == VectorPushBack(v,&s3));
	assert(6 == ((s_t*)VectorAccessElement(v,0)) -> x);
	assert(0.6f == ((s_t*)VectorAccessElement(v,1)) -> f);
	assert(8.2 == ((s_t*)VectorAccessElement(v,2)) -> d);
	assert('u' == ((s_t*)VectorAccessElement(v,0)) -> c);
	assert(8 == VectorCapacity(v));
	
	/* test element change*/
	((s_t*)VectorAccessElement(v,0)) -> x = 9;
	assert(9 == ((s_t*)VectorAccessElement(v,0)) -> x);
	
	/* test increase capacity */
	for(i = 0 ; i < 20 ; ++i)
	{
		assert(0 == VectorPushBack(v,&s1));
	}
	assert(23 == VectorSize(v));
	assert(32 == VectorCapacity(v));
	
	/* test push after increase capacity */
	assert(6 == ((s_t*)VectorAccessElement(v,22)) -> x);
	
	/* test regular pop */
	VectorPopBack(v);
	VectorPopBack(v);
	assert(21 == VectorSize(v));
	assert(32 == VectorCapacity(v));
	assert(6 == ((s_t*)VectorAccessElement(v,19)) -> x);
	
	/* test decrease capacity */
	for(i = 0 ; i < 14 ; ++i)
	{
		VectorPopBack(v);
	}
	assert(7 == VectorSize(v));
	assert(16 == VectorCapacity(v));
	
	/* test reserve */
	VectorReserve(v,50);
	assert(7 == VectorSize(v));
	assert(50 == VectorCapacity(v));
	
	/* test reserve lower capacity */
	VectorReserve(v,30);
	assert(7 == VectorSize(v));
	assert(50 == VectorCapacity(v));
	
	/* test shrink */
	VectorShrink(v);
	assert(7 == VectorSize(v));
	assert(14 == VectorCapacity(v));
	
	/* test illeagal access*/
	assert(NULL == VectorAccessElement(v,14));
	
	/* test pop over capacity*/
	for(i = 0 ; i < 20 ; ++i)
	{
		VectorPopBack(v);
	}
	
	/* test shrink empty vector */
	VectorShrink(v);
	
	/* test destroy */
	VectorDestroy(v);
	
}

void SuccessPrint()
{
	printf("🙂️🙂️🙂️🙂️🙂️🙂️🙂️🙂️🙂️🙂️\n");
	printf("🙂️🙂️🙂️🙂️🙂️🙂️🙂️🙂️🙂️🙂️\n");
	printf("🙂️🙂️🙂️🙂️🙂️🙂️🙂️🙂️🙂️🙂️\n");
	printf("🙂️🙂️🙂️🙂️🙂️🙂️🙂️🙂️🙂️🙂️\n");
	printf("🙂️🙂️🙂️🙂️🙂️🙂️🙂️🙂️🙂️🙂️\n");
	printf("🙂️🙂️🙂️🙂️🙂️🙂️🙂️🙂️🙂️🙂️\n");
}





/*int main(void)
{
	int x = 1;
	vector_t* vector = VectorCreate(sizeof(int), 2);
	VectorPushBack(vector, &x);
	++x;
	VectorPushBack(vector, &x);
	++x;
	VectorPushBack(vector, &x);
	printf("%d\n", *(int*)VectorAccessElement(vector, 0));
	printf("%d\n", *(int*)VectorAccessElement(vector, 1));
	printf("%d\n", *(int*)VectorAccessElement(vector, 2));

	VectorPopBack(vector);
	printf("%d\n", *(int*)VectorAccessElement(vector, 1));
	

	VectorPopBack(vector);
	printf("%d\n", *(int*)VectorAccessElement(vector, 0));

	VectorShrink(vector);

	return 0;
}
*/
