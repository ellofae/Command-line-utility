#include <stdio.h>
#include "wc_struct.h"

// Command-line arguments pointer array. Managed by allocBuf buffer.
#define CMDAMOUNT 10 // maximum amount of cmd-arguments
#define MAXLEN 12 // maximum length of a cmd-argument

char *cmdBuffer[CMDAMOUNT];
char **cmdPtr = cmdBuffer;
int nlines = 0;

// Functions prototypes
char *allocateBuffer(int n);
int readlines(char *str);
void strcpyPtr(char *s, char *t);

int main(int argc, char **argv)
{
    printf("\nCommand-line arguments:\n");

    int count;
    for (count = 1; count < argc; count++) {
        printf("%d: %s\n", count, argv[count]);
        if (readlines(argv[count]) == -1) {
            return -1;
        }
    }

    for (int i = 0; i < CMDAMOUNT; i++) {
        printf("nlines: %d, cmdBuffer[%d]: %s\n", nlines, i, cmdBuffer[i]);
    }

    return 0;
}

// Pointer array buffer manager
#define BUFSIZE 4096

char allocBuf[BUFSIZE];
char *allocPtr = allocBuf;

char *allocateBuffer(int n)
{
    if (allocBuf + BUFSIZE - allocPtr >= n) {
        allocPtr += n;
        return allocPtr - n;
    } else {
        return 0;
    }
}

// Additional functionality realisation
int readlines(char *str) {
    char *p;
    char line[MAXLEN];
    int len = 0;

    if (nlines >= CMDAMOUNT) {
        return -1;
    }

    while(len < MAXLEN-1 && *str != '\0') {
        *(line + len++) = *str++;
    }
    *(line + len) = '\0';

    if ((p = allocateBuffer(len+1)) != 0) {
        strcpyPtr(p, line);
        *(cmdBuffer + nlines++) = p;
    } else {
        return -1;
    }
}

void strcpyPtr(char *s, char *t)
{
    while ((*s++ = *t++) != '\0')
        ;
    *s = '\0';
}