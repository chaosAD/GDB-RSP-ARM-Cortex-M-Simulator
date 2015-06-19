#include "CMP_16bitsInstruction.h"
#include <stdio.h>

/*Compare Immediate Encoding T1

    CMP<c> <Rn>,#<imm8>
       
   31 30 29 28 27 26 25 24 23 22 21 20 19 18 17 16 15 14 13 12 11 10 9 8 7 6 5 4 3 2 1 0
  |0   0  1| 0 1|   Rn    |         imm8          |                unused               |
  
  where:
          <c><q>      See Standard assembler syntax fields on page A6-7.
          
          <Rn>        Specifies the register that contains the operand. This register is allowed to be the SP.
          
          <const>     Specifies the immediate value to be added to the value obtained from <Rn>. The range of
                      allowed values is 0-255 for encoding T1. See Modified immediate constants in Thumb
                      instructions on page A5-15 for the range of allowed values for encoding T2.
*/
void CMPImmediate16bitsT1(uint32_t instruction)
{
	uint32_t imm8 = getBits(instruction, 23 , 16);
  uint32_t Rn = getBits(instruction, 26, 24);
  
  //normal subtracting won't work
  uint32_t temp = coreReg->reg[Rn].data - imm8;
  //printf("imm8 : %x\n", imm8);
  //printf("imm8 : %x\n", ~imm8);
  //imm8 = ~imm8 + 0x00000001;                           //2's complement
  //printf("imm8 : %x\n", imm8);
  //uint32_t temp = coreReg->reg[Rn].data + imm8;
  
  updateZeroFlag(temp);
  updateCarryFlagSubtraction(temp , imm8);
  updateNegativeFlag(temp);
}

