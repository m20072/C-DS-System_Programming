#include <stddef.h>

char* strdup(const char*);

typedef enum status_t
{
	SUCCESS,
	FAILURE
} status_t;


typedef struct mixed_data mixed_data_t;
typedef status_t (*print_t)(mixed_data_t* element);
typedef status_t (*add_int_t)(mixed_data_t* element, int add_num);
typedef status_t (*clean_up_t)(mixed_data_t* element);

struct mixed_data
{
    void* data;
    print_t print;
	add_int_t add_int;
	clean_up_t clean_up;
};


/* Init functions */
status_t InitInt(mixed_data_t* element, int value);
status_t InitFloat(mixed_data_t* element, float value);
status_t InitString(mixed_data_t* element, char* value);

