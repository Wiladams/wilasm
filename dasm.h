#pragma once
#ifndef dasm_h
#define dasm_h

typedef struct {
	int m_Operation;
	int operand1;
	int operand2;
	int operand3;
} Instruction;

// Thumb Instruction decode table
// Instruction classes indexed by op

#ifdef __cplusplus
extern "C" {
#endif

int instruction_decode(Instruction *info, uint16_t instruction);

#ifdef __cplusplus
}
#endif

#endif