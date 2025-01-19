#include <stddef.h>

char* strdup(const char*);

typedef struct mixed_data mixed_data_t;
typedef void (*PrintPtr)(mixed_data_t* element);
typedef void (*AddPtr)(mixed_data_t* element, int add_num);
typedef void (*CleanUpPtr)(mixed_data_t* element);

struct mixed_data
{
    void* data;
    PrintPtr print;
	AddPtr add;
	CleanUpPtr clean_up;
};

/* Print Functions */
void Print(mixed_data_t* arr, size_t size);
void PrintInt(mixed_data_t* element);
void PrintFloat(mixed_data_t* element);
void PrintString(mixed_data_t* element);

/* Add Functions */
void Add(mixed_data_t* arr, size_t size, int add_num);
void AddToInt(mixed_data_t* element, int add_num);
void AddToFloat(mixed_data_t* element, int add_num);
void AddToStr(mixed_data_t* element, int add_num);

/* Clean-Up functions */
void CleanUp(mixed_data_t* arr, size_t size);
void IntCleanUp(mixed_data_t* element);
void FloatCleanUp(mixed_data_t* element);
void StrCleanUp(mixed_data_t* element);

/* Helper Functions */
size_t NumDigits(int number);


