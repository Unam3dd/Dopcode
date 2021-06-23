#include <stdio.h>
#include "../include/decoder.h"
#include <stdlib.h>

int main(int argc, char **argv)
{
    unsigned char opcodes[] = { 0xBB, 0x45, 0x65, 0x90, 0x78 };
    char buffer[0x100] = {0};

    decode_opcodes(opcodes, sizeof(opcodes) / sizeof(*opcodes), buffer, sizeof(buffer));

    printf("%s\n", buffer);

    return (0);
}