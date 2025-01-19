#include <stddef.h>

char* strdup(const char*);

typedef enum data_type
{
    INT,
    FLOAT,
    STRING
} data_type_t;

typedef struct data
{
    data_type_t type;
    void* data;
} data_t;

/* Print Functions */
void Print(data_t* arr, size_t size);
void PrintInt(void* i_num);
void PrintFloat(void* f_num);
void PrintString(void* str);

/* Add Functions */
void Add(data_t* arr, size_t size, int add_num);
void AddToInt(void* i_num, int add_num);
void AddToFloat(void* f_num, int add_num);
char* AddToStr(void* str, int add_num);

/* Clean-Up functions */
void CleanUp(data_t* arr, size_t size);
char* StrCleanUp(void* str);

/* Helper Functions */
size_t NumDigits(int number);


