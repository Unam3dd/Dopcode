#pragma once
#include <stdint.h>
#include <sys/types.h>

#define DEC_HEX(byte) ((byte >= '0' && byte <= '9') ? \
                      (byte & 0xF) : (byte >= 'A' && byte <= 'F') ? \
                      (10 + (byte - 'A')) : (byte >= 'a' && byte <= 'f') ? \
                      (10 + (byte - 'a')): 0)

// hex_tab.c
extern const char hex_tab[];

size_t get_hex_size(const char *str);
char *hex_encoder(char *dst, char *src, size_t size_dst);
char *hex_decoder(char *dst, char *src, size_t size_dst);