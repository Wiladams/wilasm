#include "streamer.h"

#include <stdint.h>

int copyLine(void *srcbuff, int srclen, unsigned char *outbuff, int outbufflen, int *bytesRead)
{
	size_t nchars = 0;
	size_t bytesconsumed = 0;

	while((bytesconsumed < srclen) && (nchars < outbufflen))
	{
		bytesconsumed += 1;

		if (((unsigned char *)srcbuff)[bytesconsumed-1] == '\n') {
			break;
		} else if (((unsigned char *)srcbuff)[bytesconsumed - 1] != '\r') {
			outbuff[nchars] = ((unsigned char *)srcbuff)[bytesconsumed - 1];
			nchars += 1;
		}
	}

	if (bytesRead)
		*bytesRead = bytesconsumed;
	
	return nchars;
}
