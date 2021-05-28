#pragma once
#include <stdint.h>
#include <stddef.h>
#include <sys/types.h>

#define HAS_RM 0x1
#define HAS_NO_RM 0x0

#define MOD_IS_NO_DISP 0x0
#define MOD_IS_DISP_8 0x1
#define MOD_IS_DISP_32 0x2
#define MOD_IS_REG 0x3

#define REG_M8 "r/m8"
#define REG_8 "r8"
#define REG_16_32 "r16/32"
#define REG_M_16_32 "r/m16/32"
#define IMM8 "imm8"
#define IMM_16_32 "imm16/32"
#define OPCODE_TABLES_SIZE 0x8
#define BUFFER_SIZE_OPCODES 0x100
#define X86_AFRM_TABLE_SIZE 0x100

typedef struct opcode_tables
{
    char **mnemonics;
    char *operand[4];
    uint8_t opcode;
    uint8_t length;
    uint8_t mod_rm;
    uint8_t mul;
} opcode_tables_t;

typedef struct x86_afrm
{
    char *r8;
    char *r16;
    char *r32;
    char *mm;
    char *xmm;
    char **effective_addr;
    uint8_t value;
    uint8_t has_sib;
} x86_afrm_tables_t;


extern const opcode_tables_t OPCODES_TABLES[];
extern const x86_afrm_tables_t X86_AFRM_TABLES[];