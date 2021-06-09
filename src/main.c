#include <stdio.h>
#include "../include/decoder.h"

int main(int argc, char **argv)
{
    unsigned char opcodes[] = { 0x04, 0x8 };
    char buffer[0x100] = {0};

    decode_opcodes(opcodes, sizeof(opcodes) / sizeof(*opcodes), buffer, sizeof(buffer));

    printf("%s\n", buffer);

    return (0);
}