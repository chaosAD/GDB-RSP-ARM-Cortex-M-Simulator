#include "MOV_32bitsInstruction.h"
#include <stdio.h>



/* Move Immediate Encoding T2

MOV{S}<c>.W <Rd>,#<const>

31 30 29 28 27 26 25 24 23 22 21 20 19 18 17 16 15 14 13 12 11 10 9 8 7 6 5 4 3 2 1 0
|1  1  1  1 0 |i| 0  0  0  1  0 |S| 1  1  1  1  0 |  imm3  |    Rd   |     imm8      |

where:
          S         If present, specifies that the instruction updates the flags. Otherwise, the instruction does not
                    update the flags.
                  
          <c><q>    See Standard assembler syntax fields on page A6-7.
          
          <Rd>      Specifies the destination register.
          
          <const>   Specifies the immediate value to be placed in <Rd>. The range of allowed values is 0-255 for
                    encoding T1 and 0-65535 for encoding T3. See Modified immediate constants in Thumb
                    instructions on page A5-15 for the range of allowed values for encoding T2.
                    
          When both 32-bit encodings are available for an instruction, encoding T2 is preferred to
          encoding T3 (if encoding T3 is required, use the MOVW syntax)
*/
void MOVImmediate32bitsT2(uint32_t instruction)
{
  uint32_t ModifiedConstant, modifyControl;
  uint32_t imm8 = getBits(instruction, 7, 0);
  uint32_t Rd = getBits(instruction, 11, 8);
  uint32_t imm3 = getBits(instruction, 14, 12);
  uint32_t statusFlag = getBits(instruction, 20, 20);
  uint32_t i = getBits(instruction, 26, 26);
  uint32_t bit7 = getBits(instruction, 7, 7);
  
  modifyControl = ( imm3 << 1 ) | bit7;
  modifyControl = ( i << 4) | modifyControl;

  ModifiedConstant = ModifyImmediateConstant(modifyControl, imm8);

  coreReg->reg[Rd].data = ModifiedConstant;
  
  if(statusFlag == 1)
  {
    updateZeroFlag(coreReg->reg[Rd].data);
    updateNegativeFlag(coreReg->reg[Rd].data);
  }

}



/* Move Immediate Encoding T3

MOVW<c> <Rd>,#<imm16>

31 30 29 28 27 26 25 24 23 22 21 20 19 18 17 16 15 14 13 12 11 10 9 8 7 6 5 4 3 2 1 0
|1  1  1  1 0 |i| 1  0  0  1  0  0 |   imm4    |0|  imm3   |    Rd   |     imm8      |

This instruction will not affect the status register
largest value for the constant is 65536 which means 16 bits value

16 bits = imm4 | i | imm3 | imm8

where:
          S         If present, specifies that the instruction updates the flags. Otherwise, the instruction does not
                    update the flags.
                  
          <c><q>    See Standard assembler syntax fields on page A6-7.
          
          <Rd>      Specifies the destination register.
          
          <const>   Specifies the immediate value to be placed in <Rd>. The range of allowed values is 0-255 for
                    encoding T1 and 0-65535 for encoding T3. See Modified immediate constants in Thumb
                    instructions on page A5-15 for the range of allowed values for encoding T2.
                    
          When both 32-bit encodings are available for an instruction, encoding T2 is preferred to
          encoding T3 (if encoding T3 is required, use the MOVW syntax)
*/
void MOVImmediate32bitsT3(uint32_t instruction)
{
  uint32_t imm8 = getBits(instruction, 7, 0);
  uint32_t Rd = getBits(instruction, 11, 8);
  uint32_t imm3 = getBits(instruction, 14, 12);
  uint32_t imm4 = getBits(instruction, 19, 16);
  uint32_t i = getBits(instruction, 26, 26);
  
  uint32_t constant;
  
  constant = ( imm3 << 8 ) | imm8;
  constant = ( i << 11 ) | constant;
  constant = ( imm4 << 12) | constant;
 
  coreReg->reg[Rd].data = constant;
  
}




/* Move From Register To Register Encoding T3

MOV{S}<c>.W <Rd>,<Rm>

31 30 29 28 27 26 25 24 23 22 21 20 19 18 17 16 15 14 13 12 11 10 9 8 7 6 5 4 3 2 1 0
|1  1  1  0 1 |0  1| 0  0  1  0 |S| 1  1  1  1 |0  0  0  0 |    Rd   |0 0 0 0|  Rm   |

where:
          S         If present, specifies that the instruction updates the flags. Otherwise, the instruction does not
                    update the flags.
                  
          <c><q>    See Standard assembler syntax fields on page A6-7.
          
          <Rd>      Specifies the destination register.
          
          <const>   Specifies the immediate value to be placed in <Rd>. The range of allowed values is 0-255 for
                    encoding T1 and 0-65535 for encoding T3. See Modified immediate constants in Thumb
                    instructions on page A5-15 for the range of allowed values for encoding T2.
                    
          When both 32-bit encodings are available for an instruction, encoding T2 is preferred to
          encoding T3 (if encoding T3 is required, use the MOVW syntax)
*/
/*
void MOVRegisterToRegister32bitsT3(uint32_t instruction, CoreRegister *coreReg)
{
  uint32_t Rm = getBits(instruction, 3, 0);
  uint32_t Rd = getBits(instruction, 11, 8);
  uint32_t i = getBits(instruction, 20, 20);
  uint32_t statusFlag = getBits(instruction, 20, 20);
  
  coreReg->reg[Rd].data = coreReg->reg[Rm].data;
  
  if(statusFlag == 1)
    updateStatusRegister(coreReg->reg[Rd].data);
  
}
*/