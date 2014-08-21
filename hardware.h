// Registers
enum {
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
R15 = 15
};

// Special Names for certain registers
enum {
	SP = R13,		// Stack Pointer
	LR = R14,		// Link Register, subroutine return address
	PC = R15		// Program Counter
};

/*
Current Program Status Register (CPSR)

3                   2                   1
 1 0 9 8 7 6 5 4 3 2 1 0 9 8 7 6 5 4 3 2 1 0 9 8 7 6 5 4 3 2 1 0
+---------------------------------------------------------------+
|N|Z|C|V|                                       |I|F|T|  mode   |
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

Interrupt Masks
I - 
F - 

T - Thumb State

mode - Processor mode
*/