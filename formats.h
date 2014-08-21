/*
	Instruction Formats
*/


// 1 Move shifted register
// 0 0 0 Op Offset5 Rs Rd
#define FORM_1_MASK		0xE0000000
#define FORM_2_VALUE	0x00000000

// Op Codes
#define F1_LSL 0
#define F1_LSR 1
#define F1_ASR 2

#define MoveShiftRegister(ins, Op, Offset5, Rs, Rd)

// Operations
// Op
// 00	LSL Rd, Rs, #Offset5
// 01	LSR Rd, Rs, #Offset5
// 11	ASR Rd, Rs, #Offset5


// 2 Add / subtract
// 0 0 0 1 1 I Op Rn / offset3 Rs Rd
#define FORM_2_MASK		0xF8000000
#define FORM_2_VALUE	0x18000000

// Op Codes
#define F2_ADD 0
#define F2_SUB 1
// Immediate Flag
#define F2_Operand_Register		0
#define F2_Operand_Immediate	1

#define AddSubtract(ins, I, Op, RnOffset3, Rs, Rd)

// Operations
// Op  I
// 0   0	ADD Rd, Rs, Rn
// 0   1	ADD Rd, Rs, #Offset3
// 1   0	SUB Rd, Rs, Rn
// 1   1	SUB Rd, Rs, #Offset3


// 3 Move / compare / add / subtract immediate
// 0 0 1 Op Rd Offset8
#define FORM_3_MASK		0xE0000000
#define FORM_3_VALUE	0x20000000
// Op Codes
#define F3_MOV	0
#define F3_CMP	1
#define F3_ADD	2
#define F3_SUB 3

#define MoveCompareAddSubtractImmediate(ins, Op, Rd, Offset8)

// Operations
// Op
// 00	MOV Rd, #Offset8
// 01	CMP Rd, #Offset8
// 10	ADD Rd, #Offset8
// 11	SUB Rd, #Offset8


// 0 1 0 0 0 0 Op Rs Rd
// 4 ALU operations
#define FORM_4_MASK		0xFC000000
#define FORM_4_VALUE	0x40000000

// Op Codes
#define F4_AND	0
#define F4_EOR	1
#define F4_LSL	2
#define F4_LSR	3
#define F4_ASR	4
#define F4_ADC	5
#define F4_SBC	6
#define F4_ROR	7
#define F4_TST	8
#define F4_NEG	9
#define F4_CMP	10
#define F4_CMN	11
#define F4_ORR	12
#define F4_MUL	13
#define F4_BIC	14
#define F4_MVN	15

#define ALUOperations(ins, Op, Rs, Rd)

// Operations
// Op
// 0000	AND Rd, Rs
// 0001 EOR Rds, Rs
// 0010	LSL Rd, Rs
// 0011	LSR Rd, Rs
// 0100 ASR Rd, Rs
// 0101	ADC Rd, Rs
// 0110	SBC Rd, Rs
// 0111 ROR Rd, Rs
// 1000 TST Rd, Rs
// 1001 NEG Rd, Rs
// 1010 CMP Rd, Rs
// 1011 CMN Rd, Rs
// 1100 ORR Rd, Rs
// 1101	MUL Rd, Rs
// 1110	BIC Rd, Rs
// 1111 MVN Rd, Rs


// 5 Hi register operations / branch exchange
// 0 1 0 0 0 1 Op H1 H2 Rs / Hs Rd / Hd
#define FORM_5_MASK		0xFC000000
#define FORM_5_VALUE	0x44000000

// Op Codes
#define F5_OP_ADD	0	// Add
#define F5_OP_CMP	1	// Compare
#define F5_OP_MOV	2	// Move
#define F5_OP_BX	3	// Branch

#define HighRegisterBranchExchange(ins, Op, H1, H2, RsHs, RdHd)

// Operation
// Op  H1  H2
// 00   0   0	UNDEFINED
// 00   0   1	ADD Rd, Hs
// 00   1   0	ADD Hd, Rs
// 00   1   1   ADD Hd, Hs
//
// CMP Ops set CPSR condition codes
// 01   0   0   UNDEFINED
// 01   0   1	CMP Rd, Hs
// 01   1   0   CMP Hd, Rs
// 01   1   1   CMP Hd, Hs
//
// 10   0   0   UNDEFINED
// 10   0   1	MOV Rd, Hs
// 10   1   0   MOV Hd, Rs
// 10   1   1   MOV Hd, Hs
//
// 11   0   0   BX Rs
// 11   0   1   BX Hs

// 6 PC - relative load
// 0 1 0 0 1 Rd Word8
#define FORM_6_MASK		0xF8000000
#define FORM_6_VALUE	0x48000000

#define PCRelativeLoad(ins, Rd, Word8)

// Operation
// LDR Rd, [PC, #Imm]


// 7 Load / store with register offset
// 0 1 0 1 L B 0 Ro Rb Rd
#define FORM_7_MASK		0xF0000000
#define FORM_7_VALUE	0x50000000

// Load or Store flag
#define F7_LSFLAG_TO_MEM	0
#define F7_LSFLAG_FROM_MEM	1

// Byte or Word flag
#define F7_BWFLAG_WORD		0
#define F7_BWFLAG_BYTE		1

#define LoadStoreRegOffset(ins, L, B, Ro, Rb, Rd)

// Operation
// L  B
// 0  0  STR  Rd, [Rb, Ro]
// 0  1  STRB Rd, [Rb, Ro]
// 1  0  LDR  Rd, [Rb, Ro]
// 1  1  LDRB Rd, [Rb, Ro]


// 0 1 0 1 H S 1 Ro Rb Rd
// 8 Load / store sign - extended byte / halfword
#define FORM_8_MASK		0xF0000000
#define FORM_8_VALUE	0x50000000

#define F8_SIGN_NOT_EXTENDED	0
#define F8_SIGN_EXTENDED		1

#define LoadStoreSignExtended(ins, H, S, Ro, Rb, Rd)
// S  H
// 0  1  STRH Rd, [Rb, Ro]
// 0  1  LDRH Rd, [Rb, Ro]
// 1  0  LDSB Rd, [Rb, Ro]
// 1  1  LDSH Rd, [Rb, Ro]
//


// 9 Load / store with immediate offset
// 0 1 1 B L Offset5 Rb Rd
#define FORM_9_MASK		0xE0000000
#define FORM_9_VALUE	0x60000000

#define F9_STORE_TO_MEM		0
#define F9_LOAD_FROM_MEM	1

#define F9_TRANSFER_WORD	0
#define F9_TRANSFER_BYTE	1

// Operations
// L  B
// 0  0	STR  Rd, [Rb, #Imm]
// 1  0	LDR  Rd, [Rb, #Imm]
// 0  1	STRB Rd, [Rb, #Imm]
// 1  1	LDRB Rd, [Rb, #Imm]



// 10 Load / store halfword
// 1 0 0 0 L Offset5 Rb Rd
#define FORM_10_MASK	0xF0000000
#define FORM_10_VALUE	0x80000000

#define F10_STORE_TO_MEM	0
#define F10_LOAD_FROM_MEM	1

// Operations
// L
// 0	STRH Rd, [Rb, #Imm]
// 1	LDRH Rd, [Rb, #Imm]


// 11 SP - relative load / store
// 1 0 0 1 L Rd Word8
#define FORM_11_MASK	0xF0000000
#define FORM_11_VALUE	0x90000000

#define F11_STORE_TO_MEM	0
#define F11_LOAD_FROM_MEM	1

// Operations
// L
// 0	STR Rd, [SP, #Imm]
// 1	LDR Rd, [SP, #Imm]



// 12 Load address
// 1 0 1 0 SP Rd Word8
#define FORM_12_MASK	0xF0000000
#define FORM_12_VALUE	0xA0000000

#define F12_SOURCE_PC	0
#define F12_SOURCE_SP	1

// Operations
// SP
// 0	ADD Rd, PC, #Imm
// 1	ADD Rd, SP, #Imm

// 13 Add offset to stack pointer
// 1 0 1 1 0 0 0 0 S SWord7
#define FORM_13_MASK	0xFF000000
#define FORM_13_VALUE	0xB0000000

#define F13_OFFSET_POSITIVE	0
#define F13_OFFSET_NEGATIVE	1

// Operations
// S
// 0	ADD SP, #Imm
// 1	ADD SP, #-Imm


// 14 Push / pop registers
// 1 0 1 1 L 1 0 R Rlist
#define FORM_14_MASK	0xF0000000
#define FORM_14_VALUE	0xB0000000

#define F14_NO_STORE	0
#define F14_STORE		1

#define F14_STORE_TO_MEM	0
#define F14_LOAD_FROM_MEM	1

// Operations
// L  R
// 0  0	PUSH {Rlist}
// 0  1	PUSH {Rlist, LR}
// 1  0	POP {Rlist}
// 1  1 POP {Rlist, PC}


// 15 Multiple load / store
// 1 1 0 0 L Rb Rlist
#define FORM_15_MASK	0xF0000000
#define FORM_15_VALUE	0xC0000000

#define F15_STORE_TO_MEM	0
#define F15_LOAD_FROM_MEM	1

// Operations
// L
// 0	STMIA Rb!, {Rlist}
// 1	LDMIA Rb!, {Rlist}


// 16 Conditional branch
// 1 1 0 1 Cond Soffset8
#define FORM_16_MASK	0xF0000000
#define FORM_16_VALUE	0xD0000000

// Operations
// Cond
// 0000	BEQ label
// 0001	BNE label
// 0010 BCS label
// 0011 BCC label
// 0100 BMI label
// 0101 BPL label
// 0110	BVS label
// 0111	BVC label
// 1000	BHI	label
// 1001 BLS label
// 1010	BGE label
// 1011 BLT label
// 1100 BGT label
// 1101 BLE label
// 1110 UNDEFINED

// 17 Software Interrupt
// 1 1 0 1 1 1 1 1 Value8
#define FORM_17_MASK	0xFF000000
#define FORM_17_VALUE	0xDF000000

// Operations
// SWI Value8


// 18 Unconditional branch
// 1 1 1 0 0 Offset11
#define FORM_18_MASK	0xF8000000
#define FORM_18_VALUE	0xE0000000

// Operations
// B label



// 19 Long branch with link
// 1 1 1 1 H Offset
#define FORM_19_MASK	0xF0000000
#define FORM_19_VALUE	0xF0000000

#define F19_OFFSET_HIGH	0
#define F19_OFFSET_LOW	1

// Operations
// H
// 0	BL label