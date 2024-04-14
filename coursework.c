#include <stdio.h>
#include "coursework.h"

int main(int argc, char **argv) {
    unsigned char *arr;  /* Pointer to unsigned char */

    /* Values to store in array */
    unsigned char values1[NUM_BYTES] = {10, 20, 30, 145};
    unsigned char values2[NUM_BYTES] = {200, 210, 220, 230};
    unsigned char values3[NUM_BYTES] = {100, 110, 120, 130};

    /* Initialize array with values and print bytes  */
    initializeAndPrintBytes(values1, NUM_BYTES);
    initializeAndPrintBytes(values2, NUM_BYTES);
    initializeAndPrintBytes(values3, NUM_BYTES);


    char *line = NULL;
    FILE *fileIn = NULL;
    FILE *fileOut = NULL;

    /* Check if the correct number of arguments were provided */
    if(argc != 3) {
        fprintf(stderr, "Usage: %s fileIn fileOut\n", argv[0]);
        free(line); /* Free memory if allocated */
        exit(1);
    }

    /* Open the input file */
    if ((fileIn = fopen(argv[1], "r")) == NULL) {
        fprintf(stderr, "Error opening input file: %s\n", strerror(errno));
        free(line); 
        exit(1);
    }

    /* Get the length of the line */
    fseek(fileIn, 0, SEEK_END);
    long len = ftell(fileIn);
    rewind(fileIn);

    /* Allocate memory for the line */
    if ((line = (char*)malloc(len + 1)) == NULL) {
        OUT_OF_MEMORY();
        free(line); 
        exit(1);
    }

    /* Read the line from the input file */
    if(fgets(line, len + 1, fileIn) == NULL) {
        fprintf(stderr, "Error reading from input file: %s\n", strerror(errno));
        free(line); 
        exit(1);
    }

    /* Close the input file */
    fclose(fileIn);

    /* Reverse the line */
    reverse(line);

    /* Open the output file */
    if ((fileOut = fopen(argv[2], "w")) == NULL) {
        fprintf(stderr, "Error opening output file: %s\n", strerror(errno));
        free(line); 
        exit(1);
    }

  
    /* Attempt to write the reversed line to the output file */
    if(fputs(line, fileOut) == EOF) {
        /* If fputs returns EOF, an error occurred */
        fprintf(stderr, "Error writing to output file: %s\n", strerror(errno));
        free(line); 
        exit(1);
    }

    /* Close the output file */
    fclose(fileOut);

    free(line);
     

    msString ms = msSetString("Hello");
    msString ms2 = msSetString(" World!");
    msString mscopy = NULL;

    char *str = msGetString(ms);
    printf("String |%s| is %d characters long (%p).\n",
    str, msLength(ms), ms); /* Memory leak caused by caling msGetString in printf */
    free(str);
    msCopy(&mscopy, ms);
    str = msGetString(mscopy);
    printf("Copied string |%s| is %d characters long (%p).\n",
    str, msLength(mscopy), mscopy); /* msGetString called in printf here */
    free(str);

    printf ("Compare ms with mscopy : %d\n",msCompare(ms,mscopy));
    printf ("Compare ms with ms2 : %d\n",msCompare(ms,ms2));
    printf ("Compare ms with Hello : %d\n",msCompareString(ms,"Hello"));
    printf ("Compare ms with HelloX : %d\n",msCompareString(ms,"HelloX"));
    printf ("Compare ms with Hella : %d\n",msCompareString(ms,"Hella"));

    msConcatenate (& mscopy , ms2 );
    str = msGetString(mscopy);
    printf ("Concatenated string |%s| is %d characters long (%p).\n" ,
    str, msLength ( mscopy ) , mscopy ); /* msGetString also called here */
    free(str);
    
    /* Free the memory when done */
    free(ms);
    free(ms2);
    free(mscopy);

    /* Additional Testing */
    /* Create an empty string, a string with a single character, and a long string */
    msString msEmpty = msSetString("");
    msString msSingleChar = msSetString("a");
    msString msLong = msSetString("This is a long string for testing purposes.");

    /* Create copies of the above strings */
    msString msCopyEmpty = NULL;
    msString msCopySingleChar = NULL;
    msString msCopyLong = NULL;

    /* Copy the original strings into the new ones */
    msCopy(&msCopyEmpty, msEmpty);
    msCopy(&msCopySingleChar, msSingleChar);
    msCopy(&msCopyLong, msLong);

    /* Compare the original strings with their copies
     *  * These should all return 0, as the strings are identical */
    printf("Compare msEmpty with msCopyEmpty: %d\n", msCompare(msEmpty, msCopyEmpty));
    printf("Compare msSingleChar with msCopySingleChar: %d\n", msCompare(msSingleChar, msCopySingleChar));
    printf("Compare msLong with msCopyLong: %d\n", msCompare(msLong, msCopyLong));

    /* Compare the original strings with equivalent C strings
     *  * These should all return 0, as the strings are identical */
    printf("Compare msEmpty with empty string: %d\n", msCompareString(msEmpty, ""));
    printf("Compare msSingleChar with single character: %d\n", msCompareString(msSingleChar, "a"));
    printf("Compare msLong with long string: %d\n", msCompareString(msLong, "This is a long string for testing purposes."));

    /* Concatenate different strings together */
    msConcatenate(&msCopyEmpty, msSingleChar);
    msConcatenate(&msCopySingleChar, msLong);
    msConcatenate(&msCopyLong, msEmpty);

    /* Print the concatenated strings */
    char *strEmpty = msGetString(msCopyEmpty);
    char *strSingleChar = msGetString(msCopySingleChar);
    char *strLong = msGetString(msCopyLong);

    printf("Concatenated string |%s| is %d characters long (%p).\n", strEmpty, msLength(msCopyEmpty), msCopyEmpty);
    printf("Concatenated string |%s| is %d characters long (%p).\n", strSingleChar, msLength(msCopySingleChar), msCopySingleChar);
    printf("Concatenated string |%s| is %d characters long (%p).\n", strLong, msLength(msCopyLong), msCopyLong);

    /* Free the memory allocated for the strings */
    free(strEmpty);
    free(strSingleChar);
    free(strLong);

    free(msEmpty);
    free(msSingleChar);
    free(msLong);
    free(msCopyEmpty);
    free(msCopySingleChar);
    free(msCopyLong);

    return 0;

}

/* Prints the bytes of a memory location */
void printBytes(void *ptr, int numBytes) {
    unsigned char *p = (unsigned char*)ptr;  /* Cast to unsigned char pointer */
    printf("Starting at memory address %p:\n", p);  /* Print memory address */

    /* Print each byte's value */
    int i;
    for(i = 0; i < numBytes; i++) {
        printf("%03d: %d\n", i+1, p[i]);
    }


}

/* Helper function to initialize an array, print its bytes, and free the memory */
void initializeAndPrintBytes(unsigned char *values, int numBytes) {
    /* Allocate memory for array */
    unsigned char *arr = (unsigned char *)malloc(numBytes * sizeof(unsigned char));
    if (arr == NULL) { /* Check if memory allocation successful */
        OUT_OF_MEMORY();
        exit(1);
    }

    /* Copy values into array */
    int i;
    for(i = 0; i < numBytes; i++) {
        arr[i] = values[i];
    }

    /* Display array bytes */
    printBytes(arr, numBytes);

    /* Release allocated memory */
    free(arr);

}

/* Function to reverse a string */ 
void reverse(char *str) {
    /* Get the length of the string */
    int len = strlen(str);
    
    /* Loop over the first half of the string */
    int i;
    for(i = 0; i < len / 2; i++) {
        /* Swap the current character with the corresponding character from the end */
        char temp = str[i];
        str[i] = str[len - i - 1];
        str[len - i - 1] = temp;
    }
}
