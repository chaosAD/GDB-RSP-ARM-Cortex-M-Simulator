#ifndef MOVRegister_H
#define MOVRegister_H

#include "ARMRegisters.h"
#include "getAndSetBits.h"
#include "StatusRegisters.h"
#include <stdint.h>

void MOVRegisterToRegisterT1(uint32_t instruction);
void MOVRegisterToRegisterT2(uint32_t instruction);
void MOVRegisterT3(uint32_t instruction);
void executeMOVRegister(uint32_t Rm, uint32_t Rd, uint32_t S);

#endif // MOVRegister_H
