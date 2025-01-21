#ifndef __WBO_H__
#define __WBO_H__
#include <stddef.h>

typedef union ptr 
{
    size_t* st;
    char* ch;
    
} ptr_t;

void* MemSet(void* str, int c, size_t n);
void* MemCpy(void *dest_str, const void* src_str, size_t n);
void* MemMove(void *dest_str, const void* src_str, size_t n);

#endif /* __WBO_H__ */
