#include "MOV_16bitsInstruction.h"
#include <stdio.h>

/*Move Immediate Encoding T1
        MOVS <Rd>,#<imm8>               Outside IT block.
        MOV<c> <Rd>,#<imm8>             Inside IT block.

  Note : This instruction can never move any negative value
  
   31 30 29 28 27 26 25 24 23 22 21 20 19 18 17 16 15 14 13 12 11 10 9 8 7 6 5 4 3 2 1 0
  |0   0  1| 0  0|   Rd   |         imm8          |               unused                |
   
where:
        S         If present, specifies that the instruction updates the flags. Otherwise, the instruction does not
                  update the flags.
                
        <c><q>    See Standard assembler syntax fields on page A6-7.
        
        <Rd>      Specifies the destination register. It can only cover until R7 because of 3 bits
        
        <const>   Specifies the immediate value to be placed in <Rd>. The range of allowed values is 0-255 for
                  encoding T1

*/
void MOVImmediate16bitsT1(uint32_t instruction)
{
	uint32_t imm8 = getBits(instruction, 23, 16);
	uint32_t destinationRegister = getBits(instruction, 26, 24);
	
	coreReg->reg[destinationRegister].data = imm8;
}




/*
  Move Register to Register Encoding T2 
        MOVS <Rd>,<Rm>
        
  Note :  This can only applicable to those registers lower than R7
  
   31 30 29 28 27 26 25 24 23 22 21 20 19 18 17 16 15 14 13 12 11 10 9 8 7 6 5 4 3 2 1 0
  |0  0  0  0  0  0  0  0  0  0 |   Rm   |   Rd   |               unused                |
  
  
  where:
            S       If present, specifies that the instruction updates the flags. Otherwise, the instruction does not
                    update the flags.
            
            <c><q>  See Standard assembler syntax fields on page A6-7.
            
            <Rd>    The destination register. This register can be the SP or PC, provided S is not specified.
                    If <Rd> is the PC, then only encoding T1 is permitted, and the instruction causes a branch to
                    the address moved to the PC. The instruction must either be outside an IT block or the last
                    instruction of an IT block.
                    
            <Rm>    The source register. This register can be the SP or PC.The instruction must not specify S if
                    <Rm> is the SP or PC.
  
*/
void MOVRegisterToRegister16bitsT2(uint32_t instruction)
{
  uint32_t Rm = getBits(instruction, 21, 19);
  uint32_t Rd = getBits(instruction, 18, 16);
  coreReg->reg[Rd].data = coreReg->reg[Rm].data;
  updateZeroFlag(coreReg->reg[Rd].data);
  updateNegativeFlag(coreReg->reg[Rd].data);

}




/*  
  Move Register to Register Encoding T1 
        MOV<c> <Rd>,<Rm>
        
   31 30 29 28 27 26 25 24 23 22 21 20 19 18 17 16 15 14 13 12 11 10 9 8 7 6 5 4 3 2 1 0
  |0  1  0  0  0  1 | 1 0 |D|     Rm     |   Rd   |             unused                  |
    
  where:
            S       If present, specifies that the instruction updates the flags. Otherwise, the instruction does not
                    update the flags.
            
            <c><q>  See Standard assembler syntax fields on page A6-7.
            
            <Rd>    The destination register. This register can be the SP or PC, provided S is not specified.
                    If <Rd> is the PC, then only encoding T1 is permitted, and the instruction causes a branch to
                    the address moved to the PC. The instruction must either be outside an IT block or the last
                    instruction of an IT block.
                    
            <Rm>    The source register. This register can be the SP or PC.The instruction must not specify S if
                    <Rm> is the SP or PC.
                    
            D       is the fourth bit for the Rd, if the address can be reach using 3 bits D = 0, else D = 1
  
*/
void MOVRegisterToRegister16bitsT1(uint32_t instruction)
{
	uint32_t Rm = getBits(instruction, 22, 19);
	uint32_t Rd = getBits(instruction, 18, 16);
  uint32_t D = getBits(instruction, 23, 23);
	
  Rd = ( D << 3 ) | Rd;     // this is to merge the D with Rd to make Rd becomes 4 bits
                            // Eg. new Rd = D Rd2 Rd1 Rd0

	coreReg->reg[Rd].data = coreReg->reg[Rm].data;

}