#include "../include/utils.h"

// get length of string
size_t string_len(const char *str)
{
    char *tmp = (char *)str;

    while (*tmp)
        tmp++;
    
    return (tmp - str);
}

// string concat
char *strconcat(char *dst, char *src, size_t *buffer_size)
{
    char *tmp = dst;

    while (*tmp && buffer_size--)
        tmp++;
    
    while (*src && buffer_size--)
        *tmp++ = *src++;
    
    *tmp = 0;

    return (dst);
}