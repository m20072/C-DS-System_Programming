/* Reviewed by Liel */
#ifndef __ATOI_H__
#define __ATOI_H__
char* IntToStringBase10(char* buffer, int num);
int StringToIntBase10(const char* str);
char* Itoa_base(char* buffer, int num, size_t base);
int Atoi_base(const char* str, size_t base);
void PrintLetters(const char* arr1, const char* arr2, const char* arr3, size_t size1, size_t size2, size_t size3);
int CheckLittleEndian();
#endif /* __ATOI_H__ */
