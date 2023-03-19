#include "wc_struct.h"
#include "../cmd_reader/cmd_argv_reader.h"

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

// Unix wc command flags functionality implementation:
// -l wc flag functionality implementation
int lineCounter(char *filename) {
    FILE *fptr;
    if ((fptr = fopen(filename, "r")) == NULL) {
        printf("wc: didn't manage to open the file '%s'\n", filename);
        return -1;
    }
    register int c;
    int count = 0;

    while ((c = getc(fptr)) != EOF) {
        if (c == '\n') {
            ++count;
        }
    }

    fclose(fptr);
    return count;
}

// -m wc flag functionality implementation
int charCounter(char *filename) {
    FILE *fptr;
    if ((fptr = fopen(filename, "r")) == NULL) {
        printf("wc: didn't manage to open the file '%s'\n", filename);
        return -1;
    }
    register int c;
    int count = 0;

    while ((c = getc(fptr)) != EOF) {
        ++count;
    }

    fclose(fptr);
    return count;
}

// -c wc flag functionality implementation
int byteCounter(char *filename) {
    FILE *fptr;
    if ((fptr = fopen(filename, "r")) == NULL) {
        printf("wc: didn't manage to open the file '%s'\n", filename);
        return -1;
    }
    register int c;
    int count = 0;

    while ((c = getc(fptr)) != EOF) {
        ++count;
    }

    fclose(fptr);
    return count;
}

// -w wc flag functionality implementation
int wordCounter(char *filename) {
    FILE *fptr;
    if ((fptr = fopen(filename, "r")) == NULL) {
        printf("wc: didn't manage to open the file '%s'\n", filename);
        return -1;
    }
    register int c;
    int count = 0;

    while ((c = getc(fptr)) != EOF) {
        if (c == ' ' || c == '\n') {
            ++count;
        }
    }

    fclose(fptr);
    return count;
}

// -L wc flag functionality implementation
int maxWidth(char *filename) {
    FILE *fptr;
    if ((fptr = fopen(filename, "r")) == NULL) {
        printf("wc: didn't manage to open the file '%s'\n", filename);
        return -1;
    }
    register int c;
    int count = 0, maxCount = 0;

    while ((c = getc(fptr)) != EOF) {
        if (c != '\n') {
            ++count;
        } else {
            if (count > maxCount) {
                maxCount = count;
                count = 0;
            }
        }
    }

    fclose(fptr);
    return maxCount;
}