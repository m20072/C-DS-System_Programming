#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stddef.h>
#include <assert.h>

typedef enum op
{
	REMOVE,
	COUNT,
	EXIT,
	ADDBEGIN,
	DEFAULT,
	SIZE
}op_t;

typedef struct handler
{
	char* op_name;
	int (*p_compare)(const char*, const char*); /* op_name, user_input*/
	op_t (*p_do)(const char*, const char*); /* user_input, file_name */
} handler_t;

int Cmp(const char* op_name, const char* user_input);
op_t DelFile(const char* user_input, const char* file_name);
op_t NumLines(const char* user_input, const char* file_name);
op_t Exit(const char* user_input, const char* file_name);
op_t AddBegin(const char* user_input, const char* file_name);
op_t AddEnd(const char* user_input, const char* file_name);

int Cmp(const char* op_name, const char* user_input)
{
	assert(NULL != op_name && NULL != user_input);
	return strncmp(op_name, user_input, strlen(op_name));
}

op_t DelFile(const char* user_input, const char* file_name)
{
	assert(NULL != user_input && NULL != file_name);
	(void)user_input;
	
	if(0 != remove(file_name))
	{
		printf("Failed to delete file\n");
		exit(1);
	}
	
	printf("Deleted file %s\n", file_name);
	
	return REMOVE;
}

op_t NumLines(const char* user_input, const char* file_name)
{
	FILE* fptr;
	size_t num_lines = 0;
	int ch;
	
	assert(NULL != user_input && NULL != file_name);
	(void)user_input;
	fptr =  fopen(file_name, "r");
	
		
	if(NULL == fptr)
	{
		printf("Failed to open the file\n");
		exit(0);
	}
	
	while(0 == feof(fptr)) /* while not end of file */
	{
		ch = fgetc(fptr);
  		if(ch == '\n')
  		{
    			++num_lines;
  		}
  	}
 
  	fclose(fptr);
  	printf("Number of lines is: %lu\n", num_lines);
  	return COUNT;
}

op_t Exit(const char* user_input, const char* file_name)
{
	assert(NULL != user_input && NULL != file_name);
	(void)file_name;
	(void)user_input;
	return EXIT;
}

op_t AddBegin(const char* user_input, const char* file_name)
{
	FILE* fptr;
	char* buffer;
	size_t file_size;
	
	assert(NULL != user_input && NULL != file_name);
	fptr = fopen(file_name, "r+");
	++user_input; /* ignore < */
	
	if(NULL == fptr)
	{
		printf("Failed to open the file\n");	
		exit(-1);
	}
	
	fseek(fptr, 0, SEEK_END); /* go to end of file */
	file_size = ftell(fptr) - 1; /* returns position in file, -1 to get size of file */
	fseek(fptr, 0, SEEK_SET);
	
	buffer = (char*)malloc((file_size));
	
	if(NULL == buffer)
	{
		printf("Memory allocation failed\n");
		exit(-1);
	}
	
	if(0 == fread(buffer, file_size, 1, fptr)) /* read the entire file into the buffer */
	{
		printf("File reading failed\n");
		exit(-1);
	}
	
	/* Rewrite contents into the file*/
	fseek(fptr, 0, SEEK_SET);
	fwrite(user_input, strlen(user_input), 1, fptr);
	fputc('\n', fptr);
	fwrite(buffer, file_size, 1, fptr);
	fflush(fptr);
	free(buffer);
	fclose(fptr);
	
	return ADDBEGIN;
}

op_t AddEnd(const char* user_input, const char* file_name)
{
	FILE* fptr;
	
	assert(NULL != user_input && NULL != file_name);
	fptr =  fopen(file_name, "a");
	
	if(NULL == fptr)
	{
		printf("Failed to open the file\n");
		exit(-1);
	}
	
	fputc('\n', fptr);
	fputs(user_input, fptr);
	fflush(fptr);
	fclose(fptr);
	
	return DEFAULT;
}

int main(int argc, char **argv)
{
	char user_input[255];
	int i;
	op_t is_running;
	handler_t handler_arr[5] = { {"-remove", &Cmp, &DelFile}, {"-count", &Cmp, &NumLines}, {"-exit", &Cmp, &Exit}, {"<", &Cmp, &AddBegin }, {"", &Cmp, &AddEnd} };
	
	if(2 != argc)
	{
		printf("Please provide a single file name parameter\n");
		return 0;
	}	
	
	do
	{
		fgets(user_input, sizeof(user_input), stdin);
		user_input[strlen(user_input) - 1] = '\0'; /* replace \n from fgets with \0*/
		
		for(i = 0;i<SIZE;++i)
		{
			if(0 == handler_arr[i].p_compare(handler_arr[i].op_name, user_input))
			{
				break;
			}
		}
		
		is_running = handler_arr[i].p_do(user_input, argv[1]);
		
	} while(EXIT != is_running);
	
	/*do while EXIT != handler_arr[i].p_do(user_input, argv[1])*/
	return 0;
}
