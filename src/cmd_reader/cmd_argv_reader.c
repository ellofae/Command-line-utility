#include "cmd_argv_reader.h"
#include "../wc/wc_struct.h"

// Pointer array variables initialisation
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
        stringPointerCopy(p, line);
        *(cmdBuffer + nlines++) = p;
    }
    else
    {
        return -1;
    }
}

// Comparison function implementation
void stringPointerCopy(char *s, char *t)
{
    while ((*s++ = *t++) != '\0')
        ;
    *s = '\0';
}