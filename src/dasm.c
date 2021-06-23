#include "../include/dasm.h"
#include <stddef.h>


opcode_table_t *find_opcodes_table(unsigned char *opcodes)
{
    while (*opcodes && *opcodes == 0x66 || *opcodes == 0x67)
        opcodes++;
    
    opcode_table_t *ptr = (opcode_table_t *)op_table;

    while (ptr && ptr->opcode != *opcodes) {

        if (ptr->r && (*opcodes >= ptr->opcode) && (*opcodes <= ptr->opcode + 0x7))
            break;
        
        ptr++;
    }

    return (ptr);
}