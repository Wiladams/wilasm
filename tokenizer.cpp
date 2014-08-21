#include "tokenizer.h"
#include <ctype.h>


datashard * datashard_init(datashard *shard, char *data, int length)
{
	shard->m_Data = data;
	shard->m_Length = length;

	return shard;
}

AsmLine * AsmLine_init(AsmLine *lineinfo, char *inputstr, int inputlen, int linenumber)
{
	lineinfo->m_Source.m_Data = inputstr;
	lineinfo->m_Source.m_Length = inputlen;
	lineinfo->m_LineNumber = linenumber;

	datashard_init(&lineinfo->m_Label, (char *)0, 0);
	datashard_init(&lineinfo->m_Instruction, (char *)0, 0);
	datashard_init(&lineinfo->m_Comment, (char *)0, 0);

	return lineinfo;
}

// A label must begin in the first column
// and continues until there is whitespace
int AsmLine_getLabel(AsmLine *lineinfo)
{
	int offset=0;

	// If the length of the line is > 0
	// and the first character is not alpha
	// then return immediately with a length of '0'
	if ((lineinfo->m_Source.m_Length > 0) && !isalpha(lineinfo->m_Source.m_Data[offset]))
		return offset;

	// Since the first character was alpha
	// read until we find a space, or the end
	// of the line.
	while (!isspace(lineinfo->m_Source.m_Data[offset]) && (offset < lineinfo->m_Source.m_Length)) {
		offset++;
	}

	lineinfo->m_Label.m_Data = lineinfo->m_Source.m_Data;
	lineinfo->m_Label.m_Length = offset;

	return offset;
}

/*
	An instruction might be: operation, pseudo operation, directive
	It must NOT start in the first column
	It continues until either a ';' is found, or end of line
*/
int AsmLine_getInstruction(AsmLine *lineinfo, int beginoffset)
{
	// skip leading whitespace
	int offset = beginoffset;
	while (isspace(lineinfo->m_Source.m_Data[offset]) && (offset < lineinfo->m_Source.m_Length)) {
		offset++;
	}

	// If we read to the end, and there was nothing but whitespace
	// then there was not an instruction on this line
	if (offset >= lineinfo->m_Source.m_Length) return offset;

	// If we're here, we hit something other than whitespace, so we 
	// assume it's either the start of an instruction, or comment
	// read until a ';' or end of line
	int begininstruction = offset;
	while ((lineinfo->m_Source.m_Data[offset] != ';') && (offset < lineinfo->m_Source.m_Length)) {
		offset++;
	}

	// Now stuff the instruction
	lineinfo->m_Instruction.m_Data = &lineinfo->m_Source.m_Data[begininstruction];
	lineinfo->m_Instruction.m_Length = offset - begininstruction;

	return offset;
}

/*
	A comment begins anywhere on a line and is indicated
	with a ';'.  It continues to the end of the line.
*/
int AsmLine_getComment(AsmLine *lineinfo, int beginoffset)
{
	int offset = beginoffset;


	// skip leading whitespace
	while (isspace(lineinfo->m_Source.m_Data[offset]) && (offset < lineinfo->m_Source.m_Length)) {
		offset++;
	}

	// If we read to the end, and there was nothing but whitespace
	// then there was not a comment
	if (offset >= lineinfo->m_Source.m_Length) return offset;


	// If the next character isn't ';', then it's not a comment
	if (lineinfo->m_Source.m_Data[offset] != ';') return offset;

	// Mark the beginning of the comment
	offset += 1;
	int begincomment = offset;

	// Read to the end of the line
	while (isprint(lineinfo->m_Source.m_Data[offset]) && (offset < lineinfo->m_Source.m_Length)) {
		offset++;
	}

	lineinfo->m_Comment.m_Data = &lineinfo->m_Source.m_Data[begincomment];
	lineinfo->m_Comment.m_Length = offset - begincomment;

}

int tokenizeAsmLine(AsmLine * lineinfo, char *inputstr, int inputlen, int linenumber)
{
	if (!lineinfo) return 0;

	AsmLine_init(lineinfo, inputstr, inputlen, linenumber);

	// Get the label if there is one
	int labelend = AsmLine_getLabel(lineinfo);

	// Get the instruction, if there is one
	int instructionend = AsmLine_getInstruction(lineinfo, labelend);

	// Get the comment, if there is one
	int commentend = AsmLine_getComment(lineinfo, instructionend);

	return 1;
}
