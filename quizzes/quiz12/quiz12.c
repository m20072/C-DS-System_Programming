#include <stddef.h>

void MemCopy(void* dest, const void* src, size_t n)
{
    /* ### Write your code below this line ### */
    const size_t word_size = sizeof(size_t);
    const char* src_ch_ptr = (const char*)src;
    const size_t* src_sizet_ptr = (const size_t*)src;
    char* dst_ch_ptr = (char*)dest;
    size_t* dst_sizet_ptr = (size_t*)dest;
    
    size_t src_align_remainder = ((*(size_t*)(&src)) & 0x7);
    
    while((src_align_remainder > 0) && (n > 0)) /* byte by byte till reached alingment or till finished n bytes */
    {
        *dst_ch_ptr++ = *src_ch_ptr++;
        --src_align_remainder;
        --n;
    }
    
    dst_sizet_ptr = (size_t*)dst_ch_ptr;
    src_sizet_ptr = (const size_t*)src_ch_ptr;
    
    while(word_size <= n) /* word chunks */
    {
        *dst_sizet_ptr++ = *src_sizet_ptr++;
        n -= word_size;
    }
    
    src_ch_ptr = (const char*)src_sizet_ptr;
    dst_ch_ptr = (char*)dst_sizet_ptr;
    
        while(n > 0) /* byte by byte till n = 0 */
    {
        *dst_ch_ptr++ = *src_ch_ptr++;
        --src_align_remainder;
        --n;
    }
}

