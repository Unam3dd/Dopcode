#pragma once
#include "dasm.h"

typedef struct mod_rm_t mod_rm_t;
typedef struct mod_sib_t mod_sib_t;
typedef struct opcodes_info_t opcodes_info_t;

struct mod_rm_t
{
    uint8_t mod;
    uint8_t reg;
    uint8_t r_m;
};

struct mod_sib_t
{
    uint8_t scale;
    uint8_t index;
    uint8_t base;
};

struct opcodes_info_t
{
    uint8_t prefix;
    mod_rm_t mod_rm;
    mod_sib_t mod_sib;
};

/////////////////////////////////////////
//            FUNCTIONS
/////////////////////////////////////////
void parse_mod_rm(unsigned char *opcodes, opcode_table_t *table, opcodes_info_t *info);
void parse_mod_sib(unsigned char *opcodes, opcodes_info_t *info);
void parse_opcodes(unsigned char *opcodes, opcode_table_t *table, opcodes_info_t *info);