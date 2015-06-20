#include "LSLImmediate.h"
#include <stdint.h>

/*Logical Shift Left Immediate Encoding T1
      LSLS <Rd>,<Rm>,#<imm5>      Outside IT block.
      LSL<c> <Rd>,<Rm>,#<imm5>    Inside IT block
      
   31 30 29 28 27 26 25 24 23 22 21 20 19 18 17 16 15 14 13 12 11 10 9 8 7 6 5 4 3 2 1 0
  |0   0  0| 0  0|      imm5    |   Rm   |    Rd  |               unused                |
   
where:
        S          If present, specifies that the instruction updates the flags. Otherwise, the instruction does not
                   update the flags.
                   Only change C, N and Z flag
                   
        <c><q>     See Standard assembler syntax fields on page A6-7.
        
        <Rd>       Specifies the destination register.
        
        <Rm>       Specifies the register that contains the first operand.
        
        <imm5>     Specifies the shift amount, in the range 0 to 31. See Shifts applied to a register on
                   page A6-12.
*/
void LSLImmediateT1(uint32_t instruction)
{
	uint32_t imm5 = getBits(instruction, 26 , 22);
	uint32_t Rm = getBits(instruction, 21, 19);
  uint32_t Rd = getBits(instruction, 18, 16);
	
  if(imm5 == 0)
    MOVRegisterToRegisterT2(instruction);
  else
  {
    //if(inITblock)
      //executeLSLImmediate(imm5, Rm, Rd, 0);
    //else
      executeLSLImmediate(imm5, Rm, Rd, 1);
  }
}


void executeLSLImmediate(uint32_t immediate, uint32_t Rm, uint32_t Rd, uint32_t S)
{
  int lastBitShifted;
  
  lastBitShifted = getBits(coreReg->reg[Rm].data, 32-immediate, 32-immediate) ;  //this is to get the lastBitShifted out, the value will determine the carry flag
  coreReg->reg[Rd].data = coreReg->reg[Rm].data << immediate;

  if(S == 1)                                                                      //update status register
  {
    updateNegativeFlag(coreReg->reg[Rd].data);
    updateZeroFlag(coreReg->reg[Rd].data);
    if(lastBitShifted == 1)
      setCarryFlag();
    else
      resetCarryFlag();
  }
}