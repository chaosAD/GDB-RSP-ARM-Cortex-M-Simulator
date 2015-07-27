#include "unity.h"
#include "ModifiedImmediateConstant.h"
#include "ConditionalExecution.h"
#include "Thumb16bitsTable.h"
#include "StatusRegisters.h"
#include "ARMRegisters.h"
#include "getAndSetBits.h"
#include "getMask.h"
#include "ARMSimulator.h"
#include "ITandHints.h"
#include "ADDImmediate.h"
#include "LSLImmediate.h"
#include "LSRImmediate.h"
#include "MOVRegister.h"
#include "ASRImmediate.h"
#include "MOVImmediate.h"
#include "CMPImmediate.h"
#include "ADDImmediate.h"
#include "SUBImmediate.h"
#include "ADDRegister.h"
#include "SUBRegister.h"
#include "ADDSPRegister.h"
#include "ANDRegister.h"
#include "LSLRegister.h"
#include "LSRRegister.h"
#include "ASRRegister.h"
#include "CMPRegister.h"
#include "CMNRegister.h"
#include "EORRegister.h"
#include "ORRRegister.h"
#include "RORRegister.h"
#include "MVNRegister.h"
#include "BICRegister.h"
#include "ADCRegister.h"
#include "BX.h"
#include "BLXRegister.h"
#include "MULRegister.h"
#include "TSTRegister.h"
#include "RSBImmediate.h"
#include "SBCRegister.h"
#include "UnconditionalAndConditionalBranch.h"
#include "STRRegister.h"
#include "LDRImmediate.h"
#include "MemoryBlock.h"
#include "LDRLiteral.h"
#include "ErrorSignal.h"
#include "CException.h"
#include "SVC.h"
#include "ADDSPRegister.h"
#include "ADDSPImmediate.h"
#include "ADR.h"
#include "STRImmediate.h"



void setUp(void)
{
  initializeSimulator();
}


void tearDown(void)
{
}


/*---------------------------------------------------------------------------------------------------------------------------------------------------*/
  //ADD (SP plus immediate)
  
// test ADD r0,SP,#0xff
void test_ADDSPImmediateT1_given_SP_0x20001000_should_get_r0_is_0x200010ff_xPSR_unchanged(void)
{
  uint32_t instruction = 0xa8ff0000;
  
  coreReg[SP] = 0x20001000;
  ARMSimulator(instruction);

  TEST_ASSERT_EQUAL(0x200010ff, coreReg[0]);
  TEST_ASSERT_EQUAL(0x01000000,coreReg[xPSR]);
}


// test ADD r7,SP,#0xff
void test_ADDSPImmediateT1_given_SP_0x20001000_should_get_r7_is_0x200010ff_xPSR_unchanged(void)
{
  uint32_t instruction = 0xafff0000;
  
  coreReg[SP] = 0x20001000;
  ARMSimulator(instruction);

  TEST_ASSERT_EQUAL(0x200010ff, coreReg[7]);
  TEST_ASSERT_EQUAL(0x01000000,coreReg[xPSR]);
}

