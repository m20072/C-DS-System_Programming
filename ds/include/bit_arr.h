#ifndef __BIT_ARR_H__
#define __BIT_ARR_H__
#include <stddef.h>
typedef size_t bit_arr_t;

bit_arr_t BitArrSetOn(bit_arr_t bit_arr, size_t k);
bit_arr_t BitArrSetOff(bit_arr_t bit_arr, size_t k);
bit_arr_t BitArrSetAll(bit_arr_t bit_arr);
bit_arr_t BitArrResetAll(bit_arr_t bit_arr);
bit_arr_t BitArrSetBit(bit_arr_t bit_arr, size_t k, int val);
int BitArrGetVal(bit_arr_t bit_arr, size_t k);
bit_arr_t BitArrFlip(bit_arr_t bit_arr, size_t k);
bit_arr_t BitArrRotateR(bit_arr_t bit_arr);
bit_arr_t BitArrRotateL(bit_arr_t bit_arr);
bit_arr_t BitArrMirror(bit_arr_t bit_arr);
size_t BitArrCountOn(bit_arr_t bit_arr);
size_t BitArrCountOff(bit_arr_t bit_arr);
char* BitArrToString(bit_arr_t bit_arr, char* buffer);

#endif
