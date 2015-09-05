#include "SUBImmediate.h"
#include "ITandHints.h"
#include "ConditionalExecution.h"
#include <assert.h>

/*Subtract Immediate Encoding T1
    SUBS <Rd>,<Rn>,#<imm3>      Outside IT block.
    SUB<c> <Rd>,<Rn>,#<imm3>    Inside IT block.

   31 30 29 28 27 26 25 24 23 22 21 20 19 18 17 16 15 14 13 12 11 10 9 8 7 6 5 4 3 2 1 0
  |0  0   0| 1  1| 1  1|  imm3  |   Rn   |   Rd   |                unused               |

where :
          S             If present, specifies that the instruction updates the flags. Otherwise, the instruction does not
                        update the flags.

          <c><q>        See Standard assembler syntax fields on page A6-7.

          <Rd>          Specifies the destination register. If <Rd> is omitted, this register is the same as <Rn>.

          <Rn>          Specifies the register that contains the first operand. If the SP is specified for <Rn>, see SUB
                        (SP minus immediate) on page A6-26. If the PC is specified for <Rn>, see ADR on page A6-30.

          <const>       Specifies the immediate value to be added to the value obtained from <Rn>. The range of
                        allowed values is 0-7 for encoding T1, 0-255 for encoding T2 and 0-4095 for encoding T4.
                        See Modified immediate constants in Thumb instructions on page A5-15 for the range of
                        allowed values for encoding T3.

          When multiple encodings of the same length are available for an instruction, encoding T3
          is preferred to encoding T4 (if encoding T4 is required, use the ADDW syntax). Encoding T1
          is preferred to encoding T2 if <Rd> is specified and encoding T2 is preferred to encoding T1
          if <Rd> is omitted
*/
void SUBImmediateT1(uint32_t instruction)
{
  uint32_t imm3 = getBits(instruction,24,22);
  uint32_t Rn = getBits(instruction,21,19);
  uint32_t Rd = getBits(instruction,18,16);
  assert(imm3 <= 0b111);
  assert(Rn <= 0b111);
  assert(Rd <= 0b111);

  if(inITBlock())
  {
    if( checkCondition(cond) )
      executeSUBImmediate(Rn, Rd, imm3, 0);
    shiftITState();
  }
 else
    executeSUBImmediate(Rn, Rd, imm3, 1);

  coreReg[PC] += 2;
}



/*Subtract Immediate Encoding T2
    SUBS <Rdn>,#<imm8>          Outside IT block.
    SUB<c> <Rdn>,#<imm8>        Inside IT block.

   31 30 29 28 27 26 25 24 23 22 21 20 19 18 17 16 15 14 13 12 11 10 9 8 7 6 5 4 3 2 1 0
  |0  0   1| 1  1|   Rdn  |          imm8         |                unused               |

where :
          S             If present, specifies that the instruction updates the flags. Otherwise, the instruction does not
                        update the flags.

          <c><q>        See Standard assembler syntax fields on page A6-7.

          <Rd>          Specifies the destination register. If <Rd> is omitted, this register is the same as <Rn>.

          <Rn>          Specifies the register that contains the first operand. If the SP is specified for <Rn>, see ADD
                        (SP plus immediate) on page A6-26. If the PC is specified for <Rn>, see ADR on page A6-30.

          <const>       Specifies the immediate value to be added to the value obtained from <Rn>. The range of
                        allowed values is 0-7 for encoding T1, 0-255 for encoding T2 and 0-4095 for encoding T4.
                        See Modified immediate constants in Thumb instructions on page A5-15 for the range of
                        allowed values for encoding T3.

          When multiple encodings of the same length are available for an instruction, encoding T3
          is preferred to encoding T4 (if encoding T4 is required, use the ADDW syntax). Encoding T1
          is preferred to encoding T2 if <Rd> is specified and encoding T2 is preferred to encoding T1
          if <Rd> is omitted
*/
void SUBImmediateT2(uint32_t instruction)
{
  uint32_t imm8 = getBits(instruction,23,16);
  uint32_t Rdn = getBits(instruction,26,24);
  assert(imm8 <= 011111111);
  assert(Rdn <= 0b111);


  if(inITBlock())
  {
    if( checkCondition(cond) )
      executeSUBImmediate(Rdn, Rdn, imm8, 0);
    shiftITState();
  }
 else
    executeSUBImmediate(Rdn, Rdn, imm8, 1);

  coreReg[PC] += 2;
}


/* SUB Immediate Encoding T3

SUB{S}<c>.W <Rd>,<Rn>,#<const>

31 30 29 28 27 26 25 24 23 22 21 20 19 18 17 16 15 14 13 12 11 10 9 8 7 6 5 4 3 2 1 0
|1  1  1  1 0 |i||0| 1  1  0  1 |S|      Rn    |0|  imm3   |    Rd   |     imm8      |

where :
          S             If present, specifies that the instruction updates the flags. Otherwise, the instruction does not
                        update the flags.

          <c><q>        See Standard assembler syntax fields on page A6-7.

          <Rd>          Specifies the destination register. If <Rd> is omitted, this register is the same as <Rn>.

          <Rn>          Specifies the register that contains the first operand. If the SP is specified for <Rn>, see SUB
                        (SP minus immediate) on page A6-248. If the PC is specified for <Rn>, see ADR on page A6-30.

          <const>       Specifies the immediate value to be subtracted from the value obtained from <Rn>. The range
                        of allowed values is 0-7 for encoding T1, 0-255 for encoding T2 and 0-4095 for encoding
                        T4. See Modified immediate constants in Thumb instructions on page A5-15 for the range
                        of allowed values for encoding T3.

        When multiple encodings of the same length are available for an instruction, encoding T3
        is preferred to encoding T4 (if encoding T4 is required, use the SUBW syntax). Encoding T1
        is preferred to encoding T2 if <Rd> is specified and encoding T2 is preferred to encoding T1
        if <Rd> is omitted.
*/
void SUBImmediateT3(uint32_t instruction)
{
  uint32_t imm8 = getBits(instruction, 7, 0);
  uint32_t Rd = getBits(instruction, 11, 8);
  uint32_t Rn = getBits(instruction, 19, 16);
  uint32_t imm3 = getBits(instruction, 14, 12);
  uint32_t statusFlag = getBits(instruction, 20, 20);

  uint32_t i = getBits(instruction, 26, 26);
  uint32_t bit7 = getBits(instruction, 7, 7);
  uint32_t temp = (i << 3 ) | imm3;
  uint32_t modifyControl = (temp << 1) | getBits(imm8,7,7);

  uint32_t ModifiedConstant = ModifyImmediateConstant(modifyControl, imm8);

  if(inITBlock())
  {
    if( checkCondition(cond) )
      executeSUBImmediate(Rn, Rd, ModifiedConstant, statusFlag);
    shiftITState();
  }
  else
    executeSUBImmediate(Rn, Rd, ModifiedConstant, statusFlag);

  coreReg[PC] += 4;
}


/* SUB Immediate Encoding T4

SUBW<c> <Rd>,<Rn>,#<imm12>

31 30 29 28 27 26 25 24 23 22 21 20 19 18 17 16 15 14 13 12 11 10 9 8 7 6 5 4 3 2 1 0
|1  1  1  1 0 |i||1| 0  1  0  1 |0|      Rn    |0|  imm3   |    Rd   |     imm8      |

where :
          S             If present, specifies that the instruction updates the flags. Otherwise, the instruction does not
                        update the flags.

          <c><q>        See Standard assembler syntax fields on page A6-7.

          <Rd>          Specifies the destination register. If <Rd> is omitted, this register is the same as <Rn>.

          <Rn>          Specifies the register that contains the first operand. If the SP is specified for <Rn>, see SUB
                        (SP minus immediate) on page A6-248. If the PC is specified for <Rn>, see ADR on page A6-30.

          <const>       Specifies the immediate value to be subtracted from the value obtained from <Rn>. The range
                        of allowed values is 0-7 for encoding T1, 0-255 for encoding T2 and 0-4095 for encoding
                        T4. See Modified immediate constants in Thumb instructions on page A5-15 for the range
                        of allowed values for encoding T3.

        When multiple encodings of the same length are available for an instruction, encoding T3
        is preferred to encoding T4 (if encoding T4 is required, use the SUBW syntax). Encoding T1
        is preferred to encoding T2 if <Rd> is specified and encoding T2 is preferred to encoding T1
        if <Rd> is omitted.
*/
void SUBImmediateT4(uint32_t instruction)
{

}


/* This instruction subtracts an immediate value from a register value, and writes the result to the destination

   Input: Rn          register value which will be added with immediate
          Rd          destination register
          immediate   immediate value which will be added with Rn
          S           if set will affect the status register
*/
void executeSUBImmediate(uint32_t Rn, uint32_t Rd, uint32_t immediate, uint32_t S)
{
  uint32_t backupRn = coreReg[Rn];
  uint32_t temp = coreReg[Rn] - immediate;            //get the result of Rn - immediate
  coreReg[Rd] = temp;

  if(S == 1)
  {
    updateZeroFlag(coreReg[Rd]);
    updateNegativeFlag(coreReg[Rd]);
    updateOverflowFlagSubtraction(backupRn, immediate,temp);
    updateCarryFlagSubtraction(backupRn, immediate);
  }
}