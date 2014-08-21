#include "bitter.h"

#include <limits.h>

// Low level bit manipulations
unsigned short clearbit16(unsigned short value, size_t bit)
{
	// 'bit' MUST be < sizeof(unsigned short) * CHARSIZE
	if (bit >= sizeof(unsigned short) * 8) return value;

	return  ((unsigned short)value & ~((unsigned short)(((unsigned short)1) << bit)));
}


int isset16(unsigned short value, size_t bit)
{
	return	(value & (unsigned short)(((unsigned short)1) << bit)) != 0;
}


unsigned short setbit16(unsigned short value, size_t bit)
{
	return (value | (((unsigned short)1) << (bit)));
}

// Determine whether current machine is bigendian
// for integer values
int IsBigEndian()
{
	int i = 1;
	return !*((char *)&i);
}

bool IsLittleEndian()
{
	return !IsBigEndian();
}