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


#ifndef VSTM_H
#define VSTM_H

#include <stdint.h>
#include "ConditionalExecution.h"
#include "ITandHints.h"
#include "StatusRegisters.h"
#include "ARMRegisters.h"
#include "getAndSetBits.h"
#include "getMask.h"
#include <assert.h>
#include <stdio.h>

void VSTM(uint32_t instruction);
void executeIAorDBForStore(uint32_t P, uint32_t U, uint32_t W, uint32_t baseRegisterToWrite, uint32_t singleReg, uint32_t registerList, uint32_t imm32, uint32_t Rn);
void storeFPMultiple(uint32_t address, uint32_t d, uint32_t regs, uint32_t singleReg);

#endif // VSTM_H
