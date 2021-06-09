#include "../include/hex.h"
#include <stddef.h>

size_t get_hex_size(const char *str)
{
    char *tmp = (char *)str;

    while (*tmp)
        tmp++;
    
    return  ((tmp - str) << 1);
}

char *hex_encoder(char *dst, char *src, size_t size_dst)
{

    if (size_dst < get_hex_size(src))
        return (NULL);
    

    char *tmp = dst;

    while (*src) {
        *tmp++ = hex_tab[*src >> 4];
        *tmp++ = hex_tab[*src++ & 0xF];
    }

    *tmp = 0;

    return (dst);
}

char *hex_decoder(char *dst, char *src, size_t size_dst)
{
    if (size_dst < get_hex_size(src))
        return (NULL);

    char *tmp = dst;

    while (*src) {
        *tmp = DEC_HEX(*src++);
        *tmp <<= 4;
        *tmp++ = DEC_HEX(*src++);
    }

    *tmp = 0;

    return (dst);
}