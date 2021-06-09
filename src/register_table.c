#include "dasm.h"
#include <stddef.h>

const register_table_t reg_table[] = {
    {"AL", "AX", "EAX", "MM0", "XMM0", "ES", 0x0},
    {"CL", "CX", "ECX", "MM1", "XMM1", "CS", 0x1},
    {"DL", "DX", "EDX", "MM2", "XMM2", "SS", 0x2},
    {"BL", "BX", "EBX", "MM3", "XMM3", "DS", 0x3},
    {"AH", "SP", "ESP", "MM4", "XMM4", "FS", 0x4},
    {"CH", "BP", "EBP", "MM5", "XMM5", "GS", 0x5},
    {"DH", "SI", "ESI", "MM6", "XMM6", NULL, 0x6},
    {"BH", "DI", "EDI", "MM7", "XMM7", NULL, 0x7},
};