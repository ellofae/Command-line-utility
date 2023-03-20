#include "grep.h"
#include "../cmd_reader/cmd_argv_reader.h"

// Processing buffer implementation
int grepIdentifier()
{
    char *grepOptions[GREPOPTIONS] = {"-i", "-c", "-v", "-l", "-L"};
    char **cmdPtr = cmdBuffer;

    struct grepStruct grepStructure;
    grepStructure.iFlag = 0;
    grepStructure.cFlag = 0;
    grepStructure.vFlag = 0;
    grepStructure.lFlag = 0;
    grepStructure.LFlag = 0;

    int identifier = 0;

    int i, opt;
    for (i = 1; i < nlines - 1; i++)
    {
        for (opt = 0; opt < GREPOPTIONS; opt++)
        {
            if (strcmp(*(cmdPtr + i), grepOptions[opt]) == 0)
            {
                char option = *++grepOptions[opt];
                identifier = 1;

                switch (option)
                {
                case 'i':
                    grepStructure.iFlag = 1;
                    break;
                case 'c':
                    grepStructure.cFlag = 1;
                    break;
                case 'v':
                    grepStructure.vFlag = 1;
                    break;
                case 'l':
                    grepStructure.lFlag = 1;
                    break;
                case 'L':
                    grepStructure.LFlag = 1;
                    break;
                default:
                    break;
                }
            }
        }
    }

    if (identifier != 0)
    {

        if (grepStructure.iFlag == 1)
        {
            
        }
        if (grepStructure.cFlag == 1)
        {
        
        }
        if (grepStructure.vFlag == 1)
        {
            
        }
        if (grepStructure.lFlag == 1)
        {
            
        }
        if (grepStructure.LFlag == 1)
        {
            
        }
    }
    else
    {
        int filesDiff = nlines - 2;
        int i, temp = filesDiff;

        for (i = 0; i < filesDiff; i++) {
            regularGrep(cmdBuffer[nlines-temp--], cmdBuffer[nlines-filesDiff-1]);
        }
    }
}

// Regular grep funcitonality implementation
int regularGrep(char *filename, char *pattern) {
    FILE *fp;
    if ((fp = fopen(filename, "r")) == NULL) {
        printf("grep: didn't manage to open the file '%s'\n", filename);
        return -1;
    }

    register int c;
    char line[1024];

    int newLineIdent = 0, len = 0;
    while((c = getc(fp)) != EOF) {
        *(line + len++) = c;

        if(c == '\n') {
            line[len] = '\0';
            
            len = 0;
            if(patternCheck(line, pattern) == 0) {
                printf("%s", line);
            }
        }
    }

    return 0;
}

// Checking if line has got the pattern 
int patternCheck(char *line, char* pattern) {
    char *patternPtr = pattern;
    int patternLength = 0;

    while((*patternPtr++ != '\0')) {
        ++patternLength;
    }

    int i, j = 0, len = 0;
    for (i = 0; i < strlen(line); i++) {
        if (line[i] == pattern[j]) {
            ++len;
            ++j;

            if (len == patternLength) {
                return 0;
            }
        } else {
            len = 0;
            j = 0;
        }
    }

    return -1;
}


// NOTE: Grep functionality is under development since 21.03.2023