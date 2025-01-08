#ifndef STRING_H_
#define STRING_H_
#include <stddef.h> /* for size_t */


size_t StrLen(const char* str);
char* StrDup(const char* str);
int StrCmp(const char* str1, const char* str2);
int StrnCmp(const char* str1, const char* str2, size_t n);
int StrCaseCmp(const char* str1, const char* str2);
char* StrCpy(char* dest, const char* src);
char* StrnCpy(char* dest, const char* src, size_t n);
char* StrChr(const char* str, int ch);
char* StrCat(char* dst, const char* src);
char* StrnCat(char* dst, const char* src, size_t ssize);
size_t StrSpn(const char* str, const char* accept);
char* StrStr(const char* haystack, const char *needle);

#endif /* STRING_H_ */

