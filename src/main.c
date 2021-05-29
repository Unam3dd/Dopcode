#include <stdio.h>
#include "opcodes.h"
#include <stdio.h>

int main(void)
{
    opcodes_info_t info = {0};
    opcode_tables_t table = {0};
    unsigned char opcodes[] = { 0x5, 0x45, 0x56, 0x86, 0x00 };
    char buffer[0x100] = {0};

    if (check_prefix(opcodes, &info))
        printf("Prefix is present !\n");
    
    get_opcode_table(opcodes, &info, &table);

    decode_opcodes(opcodes, buffer, sizeof(buffer), &info, &table);

    printf("%s\n", buffer);


    return (0);
}