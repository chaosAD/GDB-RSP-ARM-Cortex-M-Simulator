#ifndef LSL_16bitsInstruction_H
#define LSL_16bitsInstruction_H


#include "ARMRegisters.h"
#include "getBits.h"
#include "StatusRegisters.h"
#include <stdint.h>

void LSLImmediate16bitsT1(uint32_t instruction);
void LSLRegisterToRegisterT1(uint32_t instruction);

#endif // LSL_16bitsInstruction_H