#include "TSTRegister.h"
#include <assert.h>
#include "ARMRegisters.h"
#include "getAndSetBits.h"
#include "StatusRegisters.h"
#include "ADDSPRegister.h"
#include "ModifiedImmediateConstant.h"
#include "ITandHints.h"
#include "ConditionalExecution.h"


/*Test Register Encoding T1
  
  TST<c> <Rn>,<Rm>
      
   31 30 29 28 27 26 25 24 23 22 21 20 19 18 17 16 15 14 13 12 11 10 9 8 7 6 5 4 3 2 1 0
  |0   1  0  0  0  0| 1  0  0  0|   Rm   |   Rn   |             unused                  |

where:
        <c><q>        See Standard assembler syntax fields on page A6-7.
        
        <Rn>          Specifies the register that contains the first operand.
        
        <Rm>          Specifies the register that is optionally shifted and used as the second operand.
        
        <shift>       Specifies the shift to apply to the value read from <Rm>. If <shift> is omitted, no shift is
                      applied and both encodings are permitted. If <shift> is specified, only encoding T2 is
                      permitted. The possible shifts and how they are encoded are described in Shifts applied to a
                      register on page A6-12.
*/
void TSTRegisterT1(uint32_t instruction)
{
  uint32_t Rm = getBits(instruction,21,19);
  uint32_t Rn = getBits(instruction,18,16);

  executeTSTRegister(Rn, Rm);
}





/* Test (register) performs a logical AND operation on a register value and an optionally-shifted register value.
   It updates the condition flags based on the result, and discards the result.

   Input: Rn          register value which will be AND with Rm  
          Rm          register value which will be AND with Rn
*/
void executeTSTRegister(uint32_t Rn, uint32_t Rm)
{
  uint32_t dummy;
  dummy =  coreReg[Rm] & coreReg[Rn];                     
  
  updateZeroFlag(dummy);
  updateNegativeFlag(dummy);
  //only the shifted 1 will update the carryflag
}