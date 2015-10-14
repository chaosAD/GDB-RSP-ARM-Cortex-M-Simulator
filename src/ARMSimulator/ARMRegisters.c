/*
    GDB RSP and ARM Simulator

    Copyright (C) 2015 Wong Yan Yin, <jet_wong@hotmail.com>,
    Jackson Teh Ka Sing, <jackson_dmc69@hotmail.com>

    This file is part of GDB RSP and ARM Simulator.

    This program is free software, you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY, without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with This program.  If not, see <http://www.gnu.org/licenses/>.
*/



#include "ARMRegisters.h"
#include "getAndSetBits.h"
#include "assert.h"
#include "getMask.h"

#define   SP_INIT_VALUE   0x2001fffc    // for Coocox, keil is init to 0x20001000
#define   LR_INIT_VALUE   0xffffffff

/*
  This function will initialize all the R0 to R15 to zero
  R16 is initialized as 0x01000000

  31 30 29 28 27 26  25 24 23 22 21 20 19 18 17 16 15 14 13 12 11 10 9 8 7 6 5 4 3 2 1 0
 |N |Z |C |V |Q|IT[1:0]|T|  Reserved  |  GE[3:0]  |      IT[7:2]    |      Reserved     |

  [31]	N
        Negative or less than flag:
                                      1 = result negative
                                      0 = result positive.

  [30]	Z
        Zero flag:
                    1 = result of 0
                    0 = nonzero result.

  [29]	C	(unsigned overflow)
        Carry or borrow flag:
                                1 = carry true or borrow false
                                0 = carry false or borrow true.

  [28]	V	(signed overflow)
        Overflow flag:
                        1 = overflow
                        0 = no overflow.

  [24]  T     indicator to show whether in ARM/Thumb state, 1 for Thumb, 0 for ARM

  IT[7:5]     encodes the base condition (that is, the top 3 bits of the condition specified by the IT instruction) for
              the current IT block, if any. It contains 0b000 when no IT block is active.

  IT[4:0]     encodes the number of instructions that are due to be conditionally executed, and whether the
              condition for each is the base condition code or the inverse of the base condition code.
              It contains 0b00000 when no IT block is active.

*/
void initCoreRegister()
{
  int i;
  for(i = 0; i < NUM_OF_CORE_Register; i++)
  {
    if(i == SP)
      coreReg[i] = SP_INIT_VALUE;
    else if(i == LR)
      coreReg[i] = LR_INIT_VALUE;
    else if(i == 16)
      coreReg[i] = 0x01000000;
    else
      coreReg[i] = 0x0;
  }

  for(i = 0; i < NUM_OF_FPUD_Register; i++)
  {
    fpuDoublePrecision[i] = 0;
  }

  for(i = 0; i < NUM_OF_FPUS_Register; i++)
  {
    fpuSinglePrecision[i] = 0;
  }

}



void writeSinglePrecision(int regNum, uint32_t valueToWrite)
{
  assert(regNum >= 0 );
  assert(regNum < 32);
  int DRegNumber;

  fpuSinglePrecision[regNum] = valueToWrite;            // update single precision register

  if(regNum == 0)                                       // update double precision register, get the equivalent reg number for double precision reg
    DRegNumber = 0;
  else
    DRegNumber = regNum / 2;

  if( (regNum+1) % 2 == 0)
  {
    uint64_t dummy = fpuSinglePrecision[regNum];
    uint64_t temp =  (dummy << 32) | (uint64_t)fpuSinglePrecision[regNum-1];
    fpuDoublePrecision[DRegNumber] = temp;
  }
  else
  {
    uint64_t dummy = fpuSinglePrecision[regNum+1];
    uint64_t temp =  (dummy << 32) | fpuSinglePrecision[regNum];
    fpuDoublePrecision[DRegNumber] = temp;
  }

}

void writeDoublePrecision(int regNum, uint64_t valueToWrite)
{
  assert(regNum >= 0 );
  assert(regNum < 16 );
  int SRegNumber;

  fpuDoublePrecision[regNum] = valueToWrite;      //update double precision register

  if(regNum == 0)                                 //update single precision register
    SRegNumber = 0;
  else
    SRegNumber = regNum * 2;
  fpuSinglePrecision[SRegNumber] = getBits(fpuDoublePrecision[regNum], 31, 0);
  fpuSinglePrecision[SRegNumber+1] = fpuDoublePrecision[regNum] >> 32;

}



void writeToCoreRegisters(int regNum, uint32_t valueToWrite)
{
  if(regNum == SP)
    coreReg[regNum] = setBits(valueToWrite,0b00,1,0);     //if the register to write is SP, mask off the last 2 bits
  else if(regNum == PC)
    coreReg[regNum] = setBits(valueToWrite,0b0,0,0);      //if the register to write is PC, mask off the last bit
  else
    coreReg[regNum] = valueToWrite;
}

