#include "../include/info.h"

void parse_mod_rm(unsigned char *opcodes, opcode_table_t *table, opcodes_info_t *info)
{
    if (table->rm_mod == 0x0)
        return;
    
    while (*opcodes == 0x66 || *opcodes == 0x67 || *opcodes == 0x0F)
        opcodes++;
    
    info->mod_rm.mod = (opcodes[1] >> 0x6);
    info->mod_rm.reg = ((opcodes[1] << 0x2) & 0xFF) >> 0x5;
    info->mod_rm.r_m = ((opcodes[1] << 0x5) & 0xFF) >> 0x5;
}

void parse_mod_sib(unsigned char *opcodes, opcodes_info_t *info)
{
    if (info->mod_rm.r_m != 0x4)
        return;
    
    while (*opcodes == 0x66 || *opcodes == 0x67 || *opcodes == 0x0F)
        opcodes++;
    

    info->mod_sib.scale = (opcodes[2] >> 0x6);
    info->mod_sib.index = ((opcodes[2] << 0x2) & 0xFF) >> 0x5;
    info->mod_sib.base = ((opcodes[2] << 0x5) & 0xFF) >> 0x5;
}

void parse_opcodes(unsigned char *opcodes, opcode_table_t *table, opcodes_info_t *info)
{
    parse_mod_rm(opcodes, table, info);
    parse_mod_sib(opcodes, info);
}