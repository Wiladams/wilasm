#pragma once
#ifndef hardware_h
#define hardware_h

/*
Current Program Status Register (CPSR)

   3                   2                   1
 1 0 9 8 7 6 5 4 3 2 1 0 9 8 7 6 5 4 3 2 1 0 9 8 7 6 5 4 3 2 1 0
+---------------------------------------------------------------+
|N|Z|C|V|q|   |j|                               |I|F|T|  mode   |
+---------------------------------------------------------------+

N - Negative; the last ALU operation which changed flags produced
a negative result (the top bit of the 32-bit result was a one)

Z - Zero; the last ALU operation which changed the flags produced
a zero result (every bit of the 32-bit result was zero

C - Carry; the last ALU operation which changed the flags generated a
carry-out, either as a result of an arithmetic operation in the ALU
or from the shifter.

V - Overflow; the last arithmetic ALU operation which changed the flags
generated an overflow into the sign bit.

q - Saturation

j - Jazelle instruction set

Interrupt Masks
I -
F -

T - Thumb State

mode - Processor mode
*/

#define CPSR_N				0x80000000	// Negative
#define CPSR_Z				0x40000000	// Zero
#define CPSR_C				0x20000000	// Carry
#define CPSR_O				0x10000000	// Overflow
#define CPSR_S				0x08000000	// Saturation
#define CPSR_J				0x01000000	// Jazelle

#define CPSR_Interrupt				0x80	// Interrupt
#define CPSR_FastInterrupt			0x40	// Fast Interrupt
#define CPSR_Thumb_Instructions		0x20	// Thumb Instructions

// Modes
// Privileged
#define CPSR_MODE_MASK	0x1f		// Which bits are to be considered for the mode
									// bits 0-4 (5 bits)

#define CPSR_MODE_abt	0x17		// 0b10111 - Abort, failed memory attempt
#define CPSR_MODE_fiq	0x11		// 0b10001 - Fast Interrupt Request, interrupt level
#define CPSR_MODE_irq	0x12		// 0b10010 - Interrupt Request, interrupt level
#define CPSR_MODE_svc	0x13		// 0b10011 - Supervisor, After reset, os kernels
#define CPSR_MODE_sys	0x1F		// 0b11111 - System, User mode with CPSR access
#define CPSR_MODE_und	0x1B		// 0b11011 - Undefined, when unsupported operation is encountered

// Non-Privileged
#define CPSR_MODE_usr	0x10		// 0b10000 - User, Read-only access to CPSR, programs and applications




// Registers
typedef enum _thumb_reg_t {
	R0 = 0,
	R1 = 1,
	R2 = 2,
	R3 = 3,
	R4 = 4,
	R5 = 5,
	R6 = 6,
	R7 = 7,

	R8 = 8,
	R9 = 9,
	R10 = 10,
	R11 = 11,
	R12 = 12,
	R13 = 13,
	R14 = 14,
	R15 = 15,

	// Special Names for certain registers
	IP = 12,
	SP = 13,	// Stack Pointer
	LR = 14,	// Link Register, subroutine return address
	PC = 15,	// Program Counter

	R_INVALID = -1
} thumb_reg_t;



#endif
