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

// TABLES
typedef struct opcode_tables
{
    char *mnemonics[7];
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
    char *effective_addr[5];
    uint8_t value;
    uint8_t has_sib;
} x86_afrm_tables_t;

typedef struct x86_afsib
{
    char *r32;
    char *scale_index;
    uint8_t value;
} x86_afsib_tables_t;

typedef struct opcode_info
{
    uint8_t prefix;
} opcodes_info_t;

extern const uint8_t hex_tab[16];
extern const opcode_tables_t OPCODES_TABLES[0xFF];
extern const x86_afrm_tables_t X86_AFRM_TABLES[0x100];
extern const x86_afsib_tables_t X86_AFSIB_TABLES[0x100];

// check if prefix is present
uint8_t check_prefix(unsigned char *opcodes, opcodes_info_t *info);
unsigned char *catprintf(unsigned char *dst, size_t buffer_size, unsigned char *src, size_t n);
char *ft_strrev(char *str);

// get range in opcodes table
void get_opcode_table(unsigned char *opcodes, opcodes_info_t *info, opcode_tables_t *table);
void get_afrm_table(unsigned char *opcodes, x86_afrm_tables_t *afrm_table);
char *decode_opcodes(unsigned char *opcodes, char *buffer, size_t buffer_size, opcodes_info_t *info, opcode_tables_t *table);