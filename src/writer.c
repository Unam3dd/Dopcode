#include "../include/decoder.h"
#include <stdio.h>

const write_table_mod_t wtm[] = {
    { IS_NO_DISPLACEMENT, &write_table_mod_callback_no_displacment},
    { IS_DISPLACEMENT_8, &write_table_mod_callback_displacement_8},
    { IS_DISPLACEMENT_32, &write_table_mod_callback_displacement_32},
    { IS_REGISTER, &write_table_mod_callback_register},
};

/////////////////////////////////////
//      WRITE FUNCTIONS RM        //
///////////////////////////////////

void write_table_mod_callback_no_displacment(unsigned char *opcodes, size_t opcodes_size, decode_inst_t *inst)
{
    char *p_ptr = "DWORD";

    if ((*opcodes == 0x66) && (inst->dst[1] == 'X'))
        p_ptr = "WORD";
    
    if (*opcodes != 0x66 && (inst->dst[1] == 'L' || inst->dst[1] == 'H'))
        p_ptr = "BYTE";
    
    snprintf(inst->buffer, inst->buffer_size, "%s %s, %s [%s]", inst->mnemonic, inst->src, p_ptr, inst->dst);
}


void write_table_mod_callback_displacement_8(unsigned char *opcodes, size_t opcodes_size, decode_inst_t *inst)
{
    char *p_ptr = "DWORD";
    
    if ((*opcodes == 0x66) && (inst->dst[1] == 'X'))
        p_ptr = "WORD";
    
    if (*opcodes != 0x66 && (inst->dst[1] == 'L' || inst->dst[1] == 'H'))
        p_ptr = "BYTE";
    
    snprintf(inst->buffer, inst->buffer_size, "%s %s, %s [%s + 0x%x]", inst->mnemonic, inst->src, p_ptr, inst->dst, opcodes[opcodes_size - 1]);
}

void write_table_mod_callback_displacement_32(unsigned char *opcodes, size_t opcodes_size, decode_inst_t *inst)
{
    char *p_ptr = "DWORD";
    
    if ((*opcodes == 0x66) && (inst->dst[1] == 'X'))
        p_ptr = "WORD";
    
    if (*opcodes != 0x66 && (inst->dst[1] == 'L' || inst->dst[1] == 'H'))
        p_ptr = "BYTE";
    
    unsigned char *data = (opcodes + 0x2);

    if ((inst->info_ptr->mod_rm.r_m == 0x4) || (inst->info_ptr->mod_rm.r_m == 0x5) && inst->info_ptr->mod_rm.mod != 0x3)
        data++;
    
    snprintf(inst->buffer, inst->buffer_size, "%s %s, %s [%s + 0x%x%x%x%x]", inst->mnemonic, inst->src, p_ptr, inst->dst, data[3], data[2], data[1], data[0]);
}

void write_table_mod_callback_register(unsigned char *opcodes, size_t opcodes_size, decode_inst_t *inst)
{    
    snprintf(inst->buffer, inst->buffer_size, "%s %s, %s", inst->mnemonic, inst->src, inst->dst);
}