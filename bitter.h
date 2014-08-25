#pragma once

#ifndef bitter_H
#define bitter_H

#include <stdint.h>

static int s_endianess = 0;
#define ENDIANESS() ((s_endianess = 1), (*(unsigned char*) &s_endianess) == 0)
#define WL_LITTLE_ENDIAN (ENDIANESS()==0)
#define WL_BIG_ENDIAN !WL_LITTLE_ENDIAN

// Bit masks for various bits
#define BIT0(x) (x & 0x01)
#define BIT1(x) (x & 0x02)
#define BIT2(x) (x & 0x04)
#define BIT3(x) (x & 0x08)
#define BIT4(x) (x & 0x10)
#define BIT5(x) (x & 0x20)
#define BIT6(x) (x & 0x40)
#define BIT7(x) (x & 0x80)

#define BIT8(x)  (x & 0x0100)
#define BIT9(x)  (x & 0x0200)
#define BIT10(x) (x & 0x0400)
#define BIT11(x) (x & 0x0800)
#define BIT12(x) (x & 0x1000)
#define BIT13(x) (x & 0x2000)
#define BIT14(x) (x & 0x4000)
#define BIT15(x) (x & 0x8000)

#ifdef __cplusplus
extern "C" {
#endif

// Low level bit manipulations
unsigned short clearbit16(unsigned short value, size_t bit);
int isset16(unsigned short value, size_t bit);
unsigned short setbit16(unsigned short value, size_t bit);

#ifdef __cplusplus
}
#endif

#endif
