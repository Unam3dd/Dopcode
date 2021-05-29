#include "../include/opcodes.h"

const opcode_tables_t OPCODES_TABLES[] =  {
    { {"ADD"}, {REG_M8, REG_8, NULL, NULL}, 0x00, 0x2, HAS_RM, 0x0},
    { {"ADD"}, {REG_M_16_32, REG_16_32, NULL, NULL}, 0x01, 0x2, HAS_RM, 0x0},
    { {"ADD"}, {REG_8, REG_M8, NULL, NULL}, 0x02, 0x2, HAS_RM, 0x0},
    { {"ADD"}, {REG_16_32, REG_M_16_32, NULL, NULL}, 0x03, 0x5, HAS_RM, 0x0},
    { {"ADD"}, {"AL", IMM8, NULL, NULL}, 0x04, 0x2, HAS_NO_RM, 0x0},
    { {"ADD"}, {"EAX", IMM_16_32, NULL, NULL}, 0x05, 0x4, HAS_NO_RM, 0x0},
    { {"PUSH"},{"ES", NULL, NULL, NULL}, 0x06, 0x1, HAS_NO_RM, 0x0},
    { {"POP"}, {"ES", NULL, NULL, NULL}, 0x07, 0x1, HAS_NO_RM, 0x0},
};