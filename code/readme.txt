Pending :
    >>> Debugging in get_fields for auipc, lui, jal for the immediate field.

R  - format : 1
I  - format : 2
S  - format : 3
SB - format : 4
U  - format : 5
UJ - format : 6

__ OTHER __ : 0

R format -  add     and     or      sll     slt     sra     srl     sub     xor     mul     div     rem
            1       2       3       4       5       6       7       8       9       10      11      12

I format -  addi    andi    ori     lb      ld      lh      lw      jalr
            1       2       3       4       5       6       7       8

S format -  sb      sw      sd      sh
            1       2       3       4

SB format - beq     bne     bge     blt
            1       2       3       4

U format -  auipc   lui
            1       2

UJ format - jal
            1

opcode-func3-func7-rd-rs1-rs2-immediate

ALU codes:
0   NO USE
1   add
2   and
3   or
4   sll
5   slt
6   sra
7   srl
8   sub
9   xor
10  mul
11  div
12  rem
13  beq
14  bne
15  bge
16  blt
17  lui
18  auipc
19  jal

MuxB:
0   Register
1   immediate

IAG codes:
1   + 4
2   + immediate
3   set to value
4   auipc case