/******************************************************************************
* File: bit_arr.h
*
* Purpose:
*   Provides a bit array implementation
*
* Author:
*   Matan Chen
*
* Review History:
*   - Yonatan Fainer
*
******************************************************************************/

#ifndef __BIT_ARR_H__
#define __BIT_ARR_H__
#include <stddef.h> /* for size_t */

typedef size_t bit_arr_t;

/* receives a bit array and returns the bit array with the k'th bit to 1 */
bit_arr_t BitArrSetOn(bit_arr_t bit_arr, size_t k);

/* receives a bit array and returns the bit array with the k'th bit to 0 */
bit_arr_t BitArrSetOff(bit_arr_t bit_arr, size_t k);

/* receives a bit array and returns the bit array with all bits set to 1 */
bit_arr_t BitArrSetAll(bit_arr_t bit_arr);

/*  receives a bit array and returns the bit array with all bits set to 0 */
bit_arr_t BitArrResetAll(bit_arr_t bit_arr);

/*  receives a bit array and returns the bit array with the k'th bit set to val */
bit_arr_t BitArrSetBit(bit_arr_t bit_arr, size_t k, int val);

/* receives a bit array and returns the value of the k'th bit in the bit array */
int BitArrGetVal(bit_arr_t bit_arr, size_t k);

/* receives a bit array and returns the bit array with the k'th bit flipped */
bit_arr_t BitArrFlip(bit_arr_t bit_arr, size_t k);

/* receives a bit array and returns the bit array rotated n times to the right */
bit_arr_t BitArrRotateR(bit_arr_t bit_arr, size_t n);

/* receives a bit array and returns the bit array rotated n times to the left */
bit_arr_t BitArrRotateL(bit_arr_t bit_arr, size_t n);

/* receives a bit array and returns the bit array mirrored */
bit_arr_t BitArrMirror(bit_arr_t bit_arr);

/* receives a bit array and returns the number of 1 bits in the bit array */
size_t BitArrCountOn(bit_arr_t bit_arr);

/* receives a bit array and returns the number of 0 bits in the bit array */
size_t BitArrCountOff(bit_arr_t bit_arr);

/* receives a bit array, fills the buffer with the bit representation of the bit array and returns the start of the buffer */
char* BitArrToString(bit_arr_t bit_arr, char* buffer);

/* receives a bit array and returns the bit array mirrored using a look-up table */
bit_arr_t BitArrMirrorLUT(bit_arr_t bit_arr);

/* receives a bit array and returns the number of 1 bits in the bit array using a look-up table */
size_t BitArrCountOnLUT(bit_arr_t bit_arr);

#endif
