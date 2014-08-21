#pragma once
#ifndef streamer_h
#define streamer_h

#ifdef __cplusplus
extern "C" {
#endif

int copyLine(void *srcbuff, int srclen, unsigned char *outbuff, int outbufflen, int *bytesRead);

#ifdef __cplusplus
}
#endif

#endif
