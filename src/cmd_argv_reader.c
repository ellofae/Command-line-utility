#include "cmd_argv_reader.h"
#include "wc_struct.h"

// Pointer array variables initialisation
// char **cmdPtr = cmdBuffer;
int nlines = 0;

// Buffer manager variable allocation
char *allocPtr = allocBuf;

char *allocateBuffer(int n)
{
    if (allocBuf + BUFSIZE - allocPtr >= n)
    {
        allocPtr += n;
        return allocPtr - n;
    }
    else
    {
        return 0;
    }
}

// Command-line processing functionality initialisation:
// Reading cmd-arguments and writing them into a buffer
int readlines(char *str)
{
    char *p;
    char line[MAXLEN];
    int len = 0;

    if (nlines >= CMDAMOUNT)
    {
        return -1;
    }

    while (len < MAXLEN - 1 && *str != '\0')
    {
        *(line + len++) = *str++;
    }
    *(line + len) = '\0';

    if ((p = allocateBuffer(len + 1)) != 0)
    {
        strcpyPtr(p, line);
        *(cmdBuffer + nlines++) = p;
    }
    else
    {
        return -1;
    }
}

// Processing buffer implementation
int wcIdentifier()
{
    char *wcOptions[WCOPTIONS] = {"-c", "-m", "-l", "-w", "-L"};
    char **cmdPtr = cmdBuffer;

    struct wcStruct wcStructure;
    wcStructure.cFlag = 0;
    wcStructure.mFlag = 0;
    wcStructure.lFlag = 0;
    wcStructure.wFlag = 0;
    wcStructure.bigLFlag = 0;

    int identifier = 0;

    int i, opt;
    for (i = 1; i < nlines - 1; i++)
    {
        for (opt = 0; opt < WCOPTIONS; opt++)
        {
            if (strcmp(*(cmdPtr + i), wcOptions[opt]) == 0)
            {
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

    if (identifier != 0)
    {
        if (wcStructure.lFlag == 1)
        {
            printf(" %d", lineCounter(cmdBuffer[nlines - 1]));
        }
        if (wcStructure.wFlag == 1)
        {
            printf(" %d", wordCounter(cmdBuffer[nlines - 1]));
        }
        if (wcStructure.cFlag == 1)
        {
            printf(" %d", byteCounter(cmdBuffer[nlines - 1]));
        }
        if (wcStructure.mFlag == 1)
        {
            printf(" %d", charCounter(cmdBuffer[nlines - 1]));
        }
        if (wcStructure.bigLFlag == 1)
        {
            printf(" %d", maxWidth(cmdBuffer[nlines - 1]));
        }
    }
    else
    {
        printf(" %d", lineCounter(cmdBuffer[nlines - 1]));
        printf(" %d", wordCounter(cmdBuffer[nlines - 1]));
        printf(" %d", byteCounter(cmdBuffer[nlines - 1]));
    }
    printf(" %s\n", cmdBuffer[nlines - 1]);
}

// Comparison function implementation
void strcpyPtr(char *s, char *t)
{
    while ((*s++ = *t++) != '\0')
        ;
    *s = '\0';
}