#include "../include/decoder.h"
#include <stddef.h>

// DEBUG
#include <stdio.h>

char *decode_opcodes(unsigned char *opcodes, size_t size_opcodes, char *buffer, size_t buffer_size)
{
    opcodes_info_t info = {0};
    opcode_table_t *TABLE_PTR = NULL;
    decode_inst_t inst = {0};

    TABLE_PTR = find_opcodes_table(opcodes);

    parse_opcodes(opcodes, TABLE_PTR, &info);

    inst.table_ptr = TABLE_PTR;
    inst.info_ptr = &info;
    inst.buffer = buffer;
    inst.buffer_size = buffer_size;

    // check multiple mnemonics instructions

    decode_mnemonics(opcodes, size_opcodes, &inst);

    decode_operand(opcodes, size_opcodes, &inst);

    return (buffer);
}

void decode_mnemonics(unsigned char *opcodes, size_t size_opcodes, decode_inst_t *inst)
{
    inst->mnemonic = inst->table_ptr->mnemonics[0];

    if (inst->table_ptr->mul == 0x0)
        return;
    
    // Skip prefix
    while ((*opcodes == 0x66 || *opcodes == 0x67) && size_opcodes--)
        opcodes++;
    
    inst->mnemonic = inst->table_ptr->mnemonics[DECODE_MNEMONIC(opcodes[1])];
}

void decode_operand(unsigned char *opcodes, size_t size_opcodes, decode_inst_t *inst)
{
    // Has R/M mod
    if (inst->table_ptr->rm_mod) {
        parse_rm_mod(opcodes, size_opcodes, inst);
    } else if (inst->table_ptr->r) {
        // Opcodes + R
    } else {
        parse_imm(opcodes, size_opcodes, inst);
    }
}


////////////////////////////////
// Parse REGISTER/MEMORY MOD //
//////////////////////////////

void parse_rm_mod(unsigned char *opcodes, size_t size_opcodes, decode_inst_t *inst)
{
    parse_rm_mod_register_rm(opcodes, size_opcodes, inst);

    for (uint8_t i = 0x0; i < sizeof(wtm) / sizeof(wtm[0]); i++) {
        if (inst->info_ptr->mod_rm.mod == wtm[i].id)
            wtm[i].func(opcodes, size_opcodes, inst);
    }
}

void parse_rm_mod_register_rm(unsigned char *opcodes, size_t size_opcodes, decode_inst_t *inst)
{
    // TODO : If Effective address is 0x4 the byte follows the rm mod btye is sib byte
    // Here no need to calculate the d_bit because the table already gives us the register order
    if (inst->table_ptr->op[0] == R8 && inst->table_ptr->op[1] == RM8) {
        
        inst->src = reg_table[inst->info_ptr->mod_rm.reg].r8;
        inst->dst = reg_table[inst->info_ptr->mod_rm.r_m].r8;

    } else if (inst->table_ptr->op[0] == RM8 && inst->table_ptr->op[1] == R8) {
        
        inst->src = reg_table[inst->info_ptr->mod_rm.r_m].r8;
        inst->dst = reg_table[inst->info_ptr->mod_rm.reg].r8;

    } else if (inst->table_ptr->op[0] == R16_32 && inst->table_ptr->op[1] == RM16_32) {

        inst->src = (*opcodes == 0x66) ? reg_table[inst->info_ptr->mod_rm.reg].r16 : reg_table[inst->info_ptr->mod_rm.reg].r32;
        inst->dst = (*opcodes == 0x66) ? reg_table[inst->info_ptr->mod_rm.r_m].r16 : reg_table[inst->info_ptr->mod_rm.r_m].r32;

        if (inst->info_ptr->mod_rm.r_m == 0x4 && inst->info_ptr->mod_rm.mod != 0x3)
            inst->dst = reg_table[inst->info_ptr->mod_sib.base].r32;
    
    } else if (inst->table_ptr->op[0] == RM16_32 && inst->table_ptr->op[1] == R16_32) {
        inst->src = (*opcodes == 0x66) ? reg_table[inst->info_ptr->mod_rm.r_m].r16 : reg_table[inst->info_ptr->mod_rm.r_m].r32;
        inst->dst = (*opcodes == 0x66) ? reg_table[inst->info_ptr->mod_rm.reg].r16 : reg_table[inst->info_ptr->mod_rm.reg].r32;

        if (inst->info_ptr->mod_rm.r_m == 0x4 && inst->info_ptr->mod_rm.mod != 0x3)
            inst->dst = reg_table[inst->info_ptr->mod_sib.base].r32;
    }
}


/////////////////////////////
// Parse Immediate         //
/////////////////////////////

void parse_imm(unsigned char *opcodes, size_t size_opcodes, decode_inst_t *inst)
{
    char *reg_ptr = NULL;

    if ((inst->table_ptr->op[0] == 0x0) && (inst->table_ptr->op[1] == IMM8))
        printf("%s %s, %X", inst->mnemonic, reg_table[inst->table_ptr->op[0]].r8, opcodes[size_opcodes - 1]);
}