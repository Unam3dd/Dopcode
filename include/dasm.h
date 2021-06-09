#pragma once
#include <stdint.h>

// REGISTER ORDER
#define RM8 0x1
#define R8 0x2
#define R16_32 0x3
#define RM16_32 0x4

// IMMEDIATES
#define IMM8 0xffff5
#define IMM16_32 0xffff6

// RELATIVE
#define REL8 0x7
#define REL16_32 0x8

// PREFIX
#define OPERAND_SIZE_PREFIX 0x66
#define ADDRESS_SIZE_PREFIX 0x67

// MOD
#define IS_NO_DISPLACEMENT 0x0
#define IS_DISPLACEMENT_8 0x1
#define IS_DISPLACEMENT_32 0x2
#define IS_REGISTER 0x3

// REG
#define EAX 0x0
#define AL 0x0


typedef struct opcode_table_t opcode_table_t;
typedef struct register_table_t register_table_t;

struct opcode_table_t
{
    char *mnemonics[8];
    uint32_t op[4];
    uint8_t opcode;
    uint8_t rm_mod;
    uint8_t mul;
    uint8_t r;
};

struct register_table_t
{
    char *r8;
    char *r16;
    char *r32;
    char *mm;
    char *xmm;
    char *sreg;
    uint8_t reg;
};


////////////////////////////////////
//          TABLES                //
////////////////////////////////////

extern const opcode_table_t op_table[];
extern const register_table_t reg_table[];