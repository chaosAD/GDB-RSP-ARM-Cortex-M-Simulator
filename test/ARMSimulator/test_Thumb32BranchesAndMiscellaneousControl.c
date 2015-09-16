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
#include "LDRRegister.h"
#include "REV.h"
#include "SignedAndUnsignedExtend.h"
#include "CBZandCBNZ.h"
#include "PUSH.h"
#include "POP.h"
#include "SUBSPImmediate.h"
#include "LoadAndWriteMemory.h"
#include "Thumb32bitsTable.h"
#include "ShiftOperation.h"
#include "ANDImmediate.h"
#include "TSTImmediate.h"
#include "BICImmediate.h"
#include "ORRImmediate.h"
#include "ORNImmediate.h"
#include "MVNImmediate.h"
#include "EORImmediate.h"
#include "TEQImmediate.h"
#include "CMNImmediate.h"
#include "ADCImmediate.h"
#include "SBCImmediate.h"
#include "MOVT.h"
#include "SignedAndUnsignedSaturate.h"
#include "SignedAndUnsignedBitFieldExtract.h"
#include "BFIandBFC.h"
#include "RRX.h"
#include "RORImmediate.h"
#include "ORNRegister.h"
#include "TEQRegister.h"
#include "RSBRegister.h"
#include "SUBSPRegister.h"
#include "CLZ.h"
#include "NOP.h"
#include "MLA.h"
#include "MLS.h"
#include "SignedUnsignedLongMultiplyDivide.h"


void setUp(void)
{
  initializeSimulator();
}


void tearDown(void)
{
}


/*---------------------------------------------------------------------------------------------------------------------------------------------------*/
  //Conditional Branch T2

//test BCS.W	Here (when condition is met)
//test branch forward
void test_ConditionalBranchT2_given_PC_0x08000018_should_get_PC_0x08000022()
{
  //create test fixture
  setCarryFlag();
  coreReg[PC] = 0x08000018;
  writeInstructionToMemoryGivenByAddress(0xf0808003, 0x08000018);

  //execute
  armStep();

  TEST_ASSERT_EQUAL(0x21000000,coreReg[xPSR]);
  TEST_ASSERT_EQUAL(0x08000022,coreReg[PC]);
}

//test BCS.W	Here (when condition is not met)
//test branch forward
void test_ConditionalBranchT2_given_PC_0x08000018_should_get_PC_0x0800001c()
{
  //create test fixture
  coreReg[PC] = 0x08000018;
  writeInstructionToMemoryGivenByAddress(0xf0808003, 0x08000018);

  //execute
  armStep();

  TEST_ASSERT_EQUAL(0x01000000,coreReg[xPSR]);
  TEST_ASSERT_EQUAL(0x0800001c,coreReg[PC]);
}

//test BCS.W	Here (when condition is met)
//test branch backward
void test_ConditionalBranchT2_given_PC_0x08000018_should_get_PC_0x0800000c()
{
  setCarryFlag();
  //create test fixture
  coreReg[PC] = 0x08000018;
  writeInstructionToMemoryGivenByAddress(0xf4bfaff8, 0x08000018);

  //execute
  armStep();

  TEST_ASSERT_EQUAL(0x21000000,coreReg[xPSR]);
  TEST_ASSERT_EQUAL(0x0800000c,coreReg[PC]);
}



/*---------------------------------------------------------------------------------------------------------------------------------------------------*/
  //Unconditional Branch T2

//test B.W	Here
//test branch forward
void test_UnconditionalBranchT2_given_PC_0x08000018_should_get_PC_0x08000022()
{
  //create test fixture
  coreReg[PC] = 0x08000018;
  writeInstructionToMemoryGivenByAddress(0xf000b803, 0x08000018);

  //execute
  armStep();

  TEST_ASSERT_EQUAL(0x01000000,coreReg[xPSR]);
  TEST_ASSERT_EQUAL(0x08000022,coreReg[PC]);
}

//test B.W	Here
//test branch backward
void test_UnconditionalBranchT2_given_PC_0x08000018_should_get_PC_0x0800000c()
{
  //create test fixture
  coreReg[PC] = 0x08000018;
  writeInstructionToMemoryGivenByAddress(0xf7ffbff8, 0x08000018);

  //execute
  armStep();

  TEST_ASSERT_EQUAL(0x01000000,coreReg[xPSR]);
  TEST_ASSERT_EQUAL(0x0800000c,coreReg[PC]);
}




