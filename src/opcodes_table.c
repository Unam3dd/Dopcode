#include "dasm.h"
#include <stddef.h>


//////////////////////////////////
//      OPCODES TABLES          //
//////////////////////////////////

/* for byte contains the rm mod get the before last one bit in first opcode to get register order

   MOD         REG      R/M
[ 0 | 0]  [ 0 | 0 | 0]  [ 0 | 0 | 0]

d_bit = 0 -> REG SRC example : (MOV R/M, REG)
d_bit = 1 -> REG DST example : (MOV REG, R/M)

0x00, 0xD8

0x00 = 0000 0000 | d_bit = 0
*/

const opcode_table_t op_table[] = {
    { {"ADD"}, {RM8, R8}, 0x0, 0x1, 0x0, 0x0},
    { {"ADD"}, {RM16_32, R16_32}, 0x1, 0x1, 0x0, 0x0},
    { {"ADD"}, {R8, RM8}, 0x2, 0x1, 0x0, 0x0},
    { {"ADD"}, {R16_32, RM16_32}, 0x3, 0x1, 0x0, 0x0},
    { {"ADD"}, {AL, IMM8}, 0x4, 0x0, 0x0, 0x0},
    { {"ADD"}, {EAX, IMM16_32}, 0x5, 0x0, 0x0, 0x0},
    { NULL },
};