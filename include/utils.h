#pragma once
#include <sys/types.h>

// get length of string
size_t string_len(const char *str);

// string concat
char *strconcat(char *dst, char *src, size_t *buffer_size);