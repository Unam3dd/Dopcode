#include "opcodes.h"
#include <stdio.h>
#include <string.h>

uint8_t check_prefix(unsigned char *opcodes, opcodes_info_t *info)
{
    const unsigned char prefix[] = {0x0F, 0x66, 0xF2, 0xF3};
    uint8_t i = 0;

    for (i; i < sizeof(prefix); i++) {
        if (*opcodes == prefix[i]) {
            info->prefix = prefix[i];
            return (prefix[i]);
        }
    }

    return (0);
}

void get_opcode_table(unsigned char *opcodes, opcodes_info_t *info, opcode_tables_t *table)
{
    if (info->prefix)
        opcodes++;
    
    uint8_t i = 0;
    
    for (i; i < sizeof(OPCODES_TABLES) / sizeof(OPCODES_TABLES[0]); i++)
        if (*opcodes == OPCODES_TABLES[i].opcode)
            break;
    
    *table = OPCODES_TABLES[i];
}

void get_afrm_table(unsigned char *opcodes, x86_afrm_tables_t *afrm_table)
{    
    uint8_t i = 0;

    for (i; i < sizeof(X86_AFRM_TABLES) / sizeof(X86_AFRM_TABLES[0]); i++) {
        if (opcodes[1] == X86_AFRM_TABLES[i].value)
            break;
    }

    *afrm_table = X86_AFRM_TABLES[i];
}

unsigned char *catprintf(unsigned char *dst, size_t buffer_size, unsigned char *src, size_t n)
{
    char *tmp = dst;

    while (*tmp && buffer_size--)
        tmp++;
    
    while (*src && n--) {
        *tmp++ = hex_tab[*src >> 4];
        *tmp++ = hex_tab[*src++ & 0xF];
    }
    
    *tmp = 0;
    
    return (dst);
}

char *ft_strrev(char *str)
{
    size_t size = strlen(str) - 1, i = 0;
    unsigned char tmp = 0;

    while (i < size) {
        tmp = str[i];
        str[i++] = str[size];
        str[size] = tmp;
        size--;
    }
    
    return (str);
}

char *decode_opcodes(unsigned char *opcodes, char *buffer, size_t buffer_size, opcodes_info_t *info, opcode_tables_t *table)
{
    if (info->prefix)
        opcodes++;
    
    x86_afrm_tables_t afrm_table;
    char *ins = table->mnemonics[0];

    if (table->mul)
        ins = table->mnemonics[((opcodes[1] << 2) & 0xFF) >> 5];

    // if Has RM MOD
    if (table->mod_rm) {
        
        uint8_t mod = *(opcodes + 1) >> 6;

        get_afrm_table(opcodes, &afrm_table);

        if ((mod == 3 || mod == 0) && strcmp(table->operand[0], REG_M_16_32) == 0 && strcmp(table->operand[1], REG_16_32) == 0) {

            if (info->prefix == 0x66) {
                snprintf(buffer, buffer_size, "%s %s, %s", ins, afrm_table.effective_addr[1], afrm_table.r16);
                return (buffer);
            }
            
            snprintf(buffer, buffer_size, "%s %s, %s", ins, afrm_table.effective_addr[0], afrm_table.r32);
        }

        if ((mod == 3 || mod == 0) && strcmp(table->operand[0], REG_M8) == 0 && strcmp(table->operand[1], REG_8) == 0)
            snprintf(buffer, buffer_size, "%s %s, %s", ins, afrm_table.effective_addr[2], afrm_table.r8);
        


        if ((mod == 3 || mod == 0) && strcmp(table->operand[0], REG_16_32) == 0 && strcmp(table->operand[1], REG_M_16_32) == 0) {

            if (info->prefix == 0x66) {
                snprintf(buffer, buffer_size, "%s %s, %s", ins, afrm_table.r16, afrm_table.effective_addr[1]);
                return (buffer);
            }
            
            snprintf(buffer, buffer_size, "%s %s, %s", ins,afrm_table.r32, afrm_table.effective_addr[0]);
        }

        if ((mod == 3 || mod == 0) && strcmp(table->operand[0], REG_8) == 0 && strcmp(table->operand[1], REG_M8) == 0)
            snprintf(buffer, buffer_size, "%s %s, %s", ins, afrm_table.r8, afrm_table.effective_addr[0]);
        
        // displacement of 1 byte

        if (mod ==  1 && strcmp(table->operand[0], REG_M_16_32) == 0 && strcmp(table->operand[1], REG_16_32) == 0) {

            if (info->prefix == 0x66) {
                snprintf(buffer, buffer_size, "%s %s, %s %#X]", ins, afrm_table.effective_addr[1], afrm_table.r16, *(opcodes + 2));
                return (buffer);
            }
            
            snprintf(buffer, buffer_size, "%s %s, %s %#X]", ins, afrm_table.effective_addr[0], afrm_table.r32, *(opcodes + 2));
        }

        if (mod == 1 && strcmp(table->operand[0], REG_M8) == 0 && strcmp(table->operand[1], REG_8) == 0)
            snprintf(buffer, buffer_size, "%s %s, %s %#X]", ins, afrm_table.effective_addr[2], afrm_table.r8, *(opcodes + 2));

        if (mod == 1 && strcmp(table->operand[0], REG_16_32) == 0 && strcmp(table->operand[1], REG_M_16_32) == 0) {

            if (info->prefix == 0x66) {
                snprintf(buffer, buffer_size, "%s %s, %s %#X]", ins, afrm_table.r16, afrm_table.effective_addr[1], *(opcodes + 2));
                return (buffer);
            }
            
            snprintf(buffer, buffer_size, "%s %s, %s %#X]", ins,afrm_table.r32, afrm_table.effective_addr[0], *(opcodes + 2));
        }

        if (mod == 1 && strcmp(table->operand[0], REG_8) == 0 && strcmp(table->operand[1], REG_M8) == 0)
            snprintf(buffer, buffer_size, "%s %s, %s %#X]", ins, afrm_table.r8, afrm_table.effective_addr[0], *(opcodes + 2));

        char *value = ft_strrev(opcodes + 2);

        if (mod ==  2 && strcmp(table->operand[0], REG_M_16_32) == 0 && strcmp(table->operand[1], REG_16_32) == 0) {

            if (info->prefix == 0x66) {
                snprintf(buffer, buffer_size, "%s %s, %s", ins, afrm_table.effective_addr[1], afrm_table.r16);
                catprintf(buffer, buffer_size, value, 2);
                strcat(buffer, "]");
                return (buffer);
            }
            
            snprintf(buffer, buffer_size, "%s %s, %s", ins, afrm_table.effective_addr[0], afrm_table.r32);
            catprintf(buffer, buffer_size, value, 4);
            strcat(buffer, "]");
        }

        if (mod == 2 && strcmp(table->operand[0], REG_16_32) == 0 && strcmp(table->operand[1], REG_M_16_32) == 0) {

            if (info->prefix == 0x66) {
                snprintf(buffer, buffer_size, "%s %s, %s", ins, afrm_table.r16, afrm_table.effective_addr[1]);
                catprintf(buffer, buffer_size, value, 2);
                strcat(buffer, "]");
                return (buffer);
            }
            
            snprintf(buffer, buffer_size, "%s %s, %s", ins, afrm_table.r32, afrm_table.effective_addr[0]);
            catprintf(buffer, buffer_size, value, 4);
            strcat(buffer, "]");
        }
    } else {
        // Immediate value

        if (table->operand[1] && strcmp(table->operand[1], IMM8) == 0)
            snprintf(buffer, buffer_size, "%s %s, %#x", ins, table->operand[0], *(opcodes + 1));
        
        if (table->operand[1] && strcmp(table->operand[1], IMM_16_32) == 0) {
            
            if (info->prefix == 0x66)
                table->operand[0]++;

            snprintf(buffer, buffer_size, "%s %s, 0x", ins, table->operand[0]);
            ft_strrev(opcodes + 1);
            catprintf(buffer, buffer_size, opcodes + 1, 4);
        }

        if (table->operand[1] == NULL)
            snprintf(buffer, buffer_size, "%s %s", ins, table->operand[0]);
    }

    return (buffer);
}