#include "cmd_argv_reader.h"
#include "wc_struct.h"

// Pointer array variables initialisation
//char **cmdPtr = cmdBuffer;
int nlines = 0;

// Buffer manager variable allocation
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

// Command-line processing functionality initialisation:
// Reading cmd-arguments and writing them into a buffer
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

// Processing buffer
int argIdentifier() {
    if (strcmp(*cmdBuffer, "wc") == 0) {
        char *wcOptions[WCOPTIONS] = {"-c", "-m", "-l", "-w", "-L"};
        char **cmdPtr = cmdBuffer;
        struct wcStruct wcStructure;

        int identifier = 0;

        int i, opt;
        for (i = 1; i < nlines; i++) {
            for (opt = 0; opt < WCOPTIONS; opt++) { 
                if (strcmp(*(cmdPtr+i), wcOptions[opt]) == 0) {
                    char option = *++wcOptions[opt];
                    identifier = 1;
                    
                    switch (option)
                    {
                    case 'c':
                        wcStructure.cFlag = 1;
                        break;
                    case 'm':
                        wcStructure.mFlag = 1;
                        break;
                    case 'l':
                        wcStructure.lFlag = 1;
                        break;
                    case 'w':
                        wcStructure.wFlag = 1;
                        break;
                    case 'L':
                        wcStructure.bigLFlag = 1;
                        break;
                    default:
                        break;
                    }
                }
            }
        }

        if (identifier != 0) {
            printf("c: %d\nm: %d\nl: %d\nw: %d\nL: %d\n", wcStructure.cFlag, wcStructure.mFlag, wcStructure.lFlag,
        wcStructure.wFlag, wcStructure.bigLFlag);
        } else {
            printf("no options provided (default case)\n");
        }
    }
}

void strcpyPtr(char *s, char *t)
{
    while ((*s++ = *t++) != '\0')
        ;
    *s = '\0';
}