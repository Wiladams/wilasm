// wlasm.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include "bitter.h"
#include "streamer.h"
#include "tokenizer.h"

#include <stdio.h>
#include <string.h>

void test_16bit()
{
	unsigned short value = 0xff;
	printf("clearbit16(0xff, 0) => %d\n", clearbit16(0xff, 0));
	printf("isset16(0xff, 0) => %d\n", isset16(clearbit16(0xff, 0), 0));
	printf("isset16(0xff, 1) => %d\n", isset16(clearbit16(0xff, 0), 1));
}

void test_endian()
{
	printf("ENDIANNESS: %d\n", ENDIANESS());
	printf("Little ENDIAN: %d\n", WL_LITTLE_ENDIAN);
	printf("BIG ENDIAN: %d\n", WL_BIG_ENDIAN);

}

void test_streamer()
{
	char * str = "The quick\r\nbrown fox\r\njumped over\r\nthe lazy dogs\r\nback";
	char * ptr = str;
	int ptrlen = strlen(ptr);
	unsigned char outbuff[1024];
	int outbufflen = 1024;
	int bytesRead = 0;

	while (int nchars = copyLine(ptr, ptrlen, outbuff, outbufflen, &bytesRead)){
		ptr += bytesRead;
		ptrlen -= bytesRead;
		outbuff[nchars] = 0;

		printf("LINE: %s\n", (char *)outbuff);
	}
}

void printShard(datashard *shard, const char *title)
{
	printf("%s: ", title);

	for (int i = 0; i < shard->m_Length; i++)
	{
		printf("%c", shard->m_Data[i]);
	}

	printf("\n");
}

void printAsmLine(AsmLine *lineinfo)
{
	printf("==== %d ====\n", lineinfo->m_LineNumber);
	//printShard(&lineinfo->m_Source, "LINE");
	printShard(&lineinfo->m_Label, "LABEL");
	printShard(&lineinfo->m_Instruction, "INS");
	printShard(&lineinfo->m_Comment, "COMM");
	printf("------------\n");

}

char *program1 =
";This is a simple program that is used\n"
";To show parts of the tokenizer\n"
";\n"
"\n"
"begin\n"
"			MOV  R5, #10	; Move the immediate value 10, into the R5 register\n"
"label      ADD  R3, R5, R2		;Some comment about a labeled operation\n"
"end\n"; 

char *program2 =
"; Revised form of simple addition in file Prog4_5.s\n"
"; Date:-  1st July 2007\n"
"; Author:- William Adams\n"
"; Revisions:- 3rd July 2007. Use of large immediate values\n"
"; Performs simple addition and illustrates the use of pseudo mnemonics\n"
"\n"
"			AREA Add_Test, CODE, READONLY  ; code module named Add_Test\n"
"			ENTRY                          ; indicate which instruction to run first\n"
"\n"
";      WARNING - insert lines with Reset_Handler for Keil systems\n"
"\n"
"mystart	LDR		r3, =912345			; load first value\n"
"			LDR		r7, =0x3f9836		; load second value\n"
"			ADD		r2, r3, r7			; form the sum of the two values\n"
"stop\n"
"			NOP							; NOPs added to assist in insertion...\n"
"           NOP							; ... a break point\n"
"\n"
"; For ARM systems the next 3 lines return control to the IDE, replace with\n"
"; line BAL stop for other systems\n"
"			MOV		r0, #0x18\n"
"			LDR		r1, =0x20026\n"
"			SWI		0x123456\n"
"			END";


void test_tokenizer(char *inputstr)
{


	int inputstrlen = strlen(inputstr);

	char *ptr = inputstr;
	int ptrlen = inputstrlen;

	char outbuff[1024];
	int outbufflen = 1024;
	int bytesRead = 0;
	int linenumber = 1;

	do {
		int nchars = copyLine(ptr, ptrlen, (unsigned char *)outbuff, outbufflen, &bytesRead);

		ptr += bytesRead;
		ptrlen -= bytesRead;
		outbuff[nchars] = 0;

		// tokenize the line
		AsmLine lineinfo;
		tokenizeAsmLine(&lineinfo, outbuff, nchars, linenumber);

		printAsmLine(&lineinfo);

		linenumber++;
	} while (bytesRead > 0);

}

int _tmain(int argc, _TCHAR* argv[])
{
	//test_16bit();
	//test_endian();
	//test_streamer();
	//test_tokenizer(program1);
	test_tokenizer(program2);

	return 0;
}

