#include "dasm.h"
#include "bitter.h"

// Given an instruction, decode it, and place the various
// pieces into the Instruction structure.
int instruction_decode(Instruction *info, uint16_t instruction)
{
	int hNib1 = (instruction & 0xf000) >> 12;	// Start by getting bits 12 - 16
	int hNib2 = (instruction & 0x0f00) >> 8;

	switch (hNib) {
		case 0:	// LSL | LSR
			if (BIT11(instruction))
				info->m_Operation = OP_LSR;
			else
				info->m_Operation = OP_LSL;
		break;

		case 1:		// ASR
			// the highest bit of second nibble needs to 
			// be zero
			if (hNib2 & 0x80) return -1;

			info->m_Operation = OP_ASR;
		break;

		case 2:		// MOV | CMP

			break;

		case 3:
			break;
		
		case 4:
			break;

		case 5:			
			break;

		case 6:			// STR | LDR
			break;

		case 7:			// STRB | LDRB
			break;

		case 8:			// STRH | LDRH
			break;
	}
}

