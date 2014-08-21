#pragma once
#ifndef tokenizer_h
#define tokenizer_h

typedef struct {
	char *m_Data;
	int m_Length;
} datashard;

typedef struct {
	datashard m_Source;	// The source of the line

	int m_LineNumber;
	datashard m_Label;
	datashard m_Instruction;
	datashard m_Comment;
} AsmLine;

#ifdef __cplusplus
extern "C" {
#endif

int tokenizeAsmLine(AsmLine * lineinfo, char *inputstr, int inputlen, int linenumber);


#ifdef __cplusplus
}
#endif

#endif
