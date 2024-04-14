#include <stdio.h>
#include <errno.h>
#include "msString.h"

msString msSetString(char *str) {
    /* Allocate memory for the length of the string and the string itself */
    msString ms;
    if (!(ms = (msString)malloc(sizeof(long int) + strlen(str)))) {
        msError("Failed to allocate memory in msSetString");
    }

    /* Store the length of the string and the string itself */
    *(long int *)ms = strlen(str);
    memcpy((void *)(ms + sizeof(long int)), (void *)str, strlen(str));    

    return ms;
}

char *msGetString(msString ms) {
    /* Allocate memory for the C string */
    char *str;
    if (!(str = (char *)malloc(*(long int *)ms + 1))) {
        msError("Failed to allocate memory in msGetString");
    }

    /* Copy the string and add the null terminator */
    memcpy(str, ms + sizeof(long int), *(long int *)ms);
    str[*(long int *)ms] = '\0';

    return str;
}

void msCopy(msString *dest, msString src) {
    /* Allocate memory for the length of the string and the string itself */
    if (!(*dest = (msString)malloc(sizeof(long int) + *(long int *)src))) {
        msError("Failed to allocate memory in msCopy");
    }

    /* Copy the length of the string and the string itself */
    memcpy((void *)*dest, (void *)src, sizeof(long int) + *(long int *)src);
}

void msConcatenate(msString *dest, msString src) {
    /* Get the lengths of the destination and source strings */
    long int destLen = *(long int *)*dest;
    long int srcLen = *(long int *)src;

    /* Reallocate memory for the destination string to hold the concatenated string */
    if(!(*dest = (msString)realloc(*dest, sizeof(long int) + destLen + srcLen))) {
        msError("Failed to allocate memory in msConcatenate");
        /* Exit handled by msError so not included */
    }

    /* Update the length of the destination string */
    *(long int *)*dest = destLen + srcLen;

    /* Copy the source string to the end of the destination string */
    memcpy(*dest + sizeof(long int) + destLen, src + sizeof(long int), srcLen);
}

long int msLength(msString ms) {
    /* Check if the msString is NULL */
    if (!ms) {
        msError("NULL pointer passed to msLength");
    }

    /* Return the length of the string */
    return *(long int *)ms;
}

int msCompare(msString ms1, msString ms2) {
    /* Extract the lengths of the strings from the start of the msString */
    long int len1 = *(long int *)ms1;
    long int len2 = *(long int *)ms2;

    /* If the lengths are not equal, the strings are not identical */
    if (len1 != len2) {
        return 1;
    }

    /* If the lengths are equal, compare the strings themselves */
    if (memcmp(ms1 + sizeof(long int), ms2 + sizeof(long int), len1) != 0) {
        /* If the strings are not equal, they are not identical */
        return 1;
    }

    /* If both the lengths and the strings are equal, the strings are identical */
    return 0;
}

int msCompareString(msString ms, char *str) {
    /* Extract the length of the msString from the start of the msString */
    long int msLen = *(long int *)ms;

    /* Get the length of the C string using strlen */
    size_t strLen = strlen(str);

    /* If the lengths are not equal, the strings are not identical */
    if (msLen != strLen) {
        return 1;
    }

    /* If the lengths are equal, compare the strings themselves */
    if (memcmp(ms + sizeof(long int), str, msLen) != 0) {
        /* If the strings are not equal, they are not identical */
        return 1;
    }

    /* If both the lengths and the strings are equal, the strings are identical */
    return 0;
}

void msError(char *msg) {
    /* Print the error message, the error number, and the system error message */
    fprintf(stderr, "%s. Error %d: %s\n", msg, errno, strerror(errno));
    exit(1);
}
