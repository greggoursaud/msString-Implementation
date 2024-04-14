#ifndef MSSTRING_H
#define MSSTRING_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include "msString.h"

#define NUM_BYTES 4  /* Number of bytes to allocate */
#define OUT_OF_MEMORY() \
    do { fprintf(stderr, "Out of memory: error %d: %s\n", errno, strerror(errno)); } while (0)

/* Function Prototypes */
void printBytes(void *ptr, int numBytes);
void initializeAndPrintBytes(unsigned char *values, int numBytes);
void reverse(char *str);

#endif /* MSTRING_H */
