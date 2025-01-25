#ifndef __EXAM_H__
#define __EXAM_H__

#include <stddef.h>

int FlipDigitsInNum(int num);

unsigned char MirrorByte(unsigned char byte);

int FlipBit(int val, unsigned int n);

unsigned char CountSetBits(unsigned char byte);

unsigned char RotateLeft(unsigned char byte, unsigned int nbits);

void SwapIntPtr(int** ptr1, int** ptr2);

size_t Strlen(const char* str);
char Strcmp(const char* str1, const char* str2);
char* Strcpy(char* dst, const char* src);
char* Strncpy(char* dst, const char* src, size_t n);
char* Strcat(char* dst, const char* src);

unsigned long GetNFibonacciElement(unsigned int n);

char* IntToString(int num, char* buffer);

unsigned int Mult8(unsigned int num);


void IntSwap1(int* num1, int* num2);
void IntSwap2(int* num1, int* num2);
void IntSwap3(int* num1, int* num2);

#endif /* __EXAM_H__ */
