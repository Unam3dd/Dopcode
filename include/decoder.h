#pragma once
#include "dasm.h"
#include "info.h"
#include <sys/types.h>
#include <stddef.h>

#define DECODE_MNEMONIC(opcode) ((opcode << 0x2) & 0xFF) >> 0x5

typedef struct write_table_mod_t write_table_mod_t;

typedef struct decode_inst
{
    opcode_table_t *table_ptr;
    opcodes_info_t *info_ptr;
    char *mnemonic;
    char *dst;
    char *src;
    char *buffer;
    size_t buffer_size;
} decode_inst_t;

struct write_table_mod_t
{
    uint8_t id;
    void (*func)(unsigned char *, size_t opcodes_size, decode_inst_t *);
};

extern const write_table_mod_t wtm[0x4];

// Decode functions
opcode_table_t *find_opcodes_table(unsigned char *opcodes);
char *decode_opcodes(unsigned char *opcodes, size_t size_opcodes, char *buffer, size_t buffer_size);
void decode_mnemonics(unsigned char *opcodes, size_t size_opcodes, decode_inst_t *inst);
void decode_operand(unsigned char *opcodes, size_t size_opcodes, decode_inst_t *inst);

// Parse REGISTER/MEMORY MOD
void parse_rm_mod(unsigned char *opcodes, size_t size_opcodes, decode_inst_t *inst);
void parse_rm_mod_register_rm(unsigned char *opcodes, size_t size_opcodes, decode_inst_t *inst);


// Write functions R/M MOD
void write_table_mod_callback_no_displacment(unsigned char *opcodes, size_t opcodes_size, decode_inst_t *inst);
void write_table_mod_callback_displacement_8(unsigned char *opcodes, size_t opcodes_size, decode_inst_t *inst);
void write_table_mod_callback_displacement_32(unsigned char *opcodes, size_t opcodes_size, decode_inst_t *inst);
void write_table_mod_callback_register(unsigned char *opcodes, size_t opcodes_size, decode_inst_t *inst);


// Parse Immediate
void parse_imm(unsigned char *opcodes, size_t size_opcodes, decode_inst_t *inst);

// Parse R
void parse_r(unsigned char *opcodes, size_t size_opcodes, decode_inst_t *inst);