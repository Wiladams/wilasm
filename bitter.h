#ifndef bitter_H
#define bitter_H

#include <stdint.h>

static int s_endianess = 0;
#define ENDIANESS() ((s_endianess = 1), (*(unsigned char*) &s_endianess) == 0)
#define WL_LITTLE_ENDIAN (ENDIANESS()==0)
#define WL_BIG_ENDIAN !WL_LITTLE_ENDIAN

bool IsCurrentMachineBigEndian();
bool IsCurrentMachineLittleEndian();

// Low level bit manipulations
unsigned short clearbit16(unsigned short value, size_t bit);
int isset16(unsigned short value, size_t bit);
unsigned short setbit16(unsigned short value, size_t bit);

#endif
