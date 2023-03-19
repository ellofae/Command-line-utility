#include "cat.h"
#include "../cmd_reader/cmd_argv_reader.h"

// Processing buffer implementation
int catIdentifier()
{
    char *catOptions[CATOPTIONS] = {"-A", "-E", "-T", "-b", "-n"};
    char **cmdPtr = cmdBuffer;

    struct catStruct catStructure;
    catStructure.bigAFlag = 0;
    catStructure.bigEFlag = 0;
    catStructure.bigTFlag = 0;
    catStructure.bFlag = 0;
    catStructure.nFlag = 0;

    int identifier = 0;

    int i, opt;
    for (i = 1; i < nlines - 1; i++)
    {
        for (opt = 0; opt < CATOPTIONS; opt++)
        {
            if (strcmp(*(cmdPtr + i), catOptions[opt]) == 0)
            {
                char option = *++catOptions[opt];
                identifier = 1;

                switch (option)
                {
                case 'A':
                    catStructure.bigAFlag = 1;
                    break;
                case 'E':
                    catStructure.bigEFlag = 1;
                    break;
                case 'T':
                    catStructure.bigTFlag = 1;
                    break;
                case 'b':
                    catStructure.bFlag = 1;
                    break;
                case 'n':
                    catStructure.nFlag = 1;
                    break;
                default:
                    break;
                }
            }
        }
    }

    if (identifier != 0)
    {
        if (catStructure.bigAFlag == 1)
        {
            showAll(cmdBuffer[nlines - 1]);
        }
        if (catStructure.bigEFlag == 1)
        {
            addEndSign(cmdBuffer[nlines-1]);
        }
        if (catStructure.bigTFlag == 1)
        {
            replaceTabChars(cmdBuffer[nlines-1]);
        }
        if (catStructure.bFlag == 1)
        {
            numberNonEmptyOutput(cmdBuffer[nlines-1]);
        }
        if (catStructure.nFlag == 1)
        {
            numberOutput(cmdBuffer[nlines-1]);
        }
    }
    else
    {
         FILE *fptr;
        if ((fptr = fopen(cmdBuffer[nlines-1], "r")) == NULL) {
            printf("wc: didn't manage to open the file '%s'\n", cmdBuffer[nlines-1]);
            return -1;
        }
        register int c;

        while((c = getc(fptr)) != EOF) {
            printf("%c", c);
        }

        fclose(fptr);
    }
}

// -A cat flag functionality implementation
int showAll(char *filename) {
    FILE *fptr;
    if ((fptr = fopen(filename, "r")) == NULL) {
        printf("wc: didn't manage to open the file '%s'\n", filename);
        return -1;
    }
    register int c;

    while ((c = getc(fptr)) != EOF) {
        if (c == '\t') {
            printf("%s", "^I");
        } else if (c == '\n') {
            printf("%c%c", '$', '\n');
        } else {
            printf("%c", c);
        }
    }

    fclose(fptr);
    return 0;
}

// -E cat flag functionality implementation
int addEndSign(char *filename) {
    FILE *fptr;
    if ((fptr = fopen(filename, "r")) == NULL) {
        printf("wc: didn't manage to open the file '%s'\n", filename);
        return -1;
    }
    register int c;

    while ((c = getc(fptr)) != EOF) {
        if (c == '\n') {
            printf("%c%c", '$', '\n');
        } else {
            printf("%c", c);
        }
    }

    fclose(fptr);
    return 0;
}

// -T cat flag functionality implementation
int replaceTabChars(char *filename) {
    FILE *fptr;
    if ((fptr = fopen(filename, "r")) == NULL) {
        printf("wc: didn't manage to open the file '%s'\n", filename);
        return -1;
    }
    register int c;

    while ((c = getc(fptr)) != EOF) {
       if (c == '\t') {
            printf("%s", "^I");
        } else {
            printf("%c", c);
        }
    }

    fclose(fptr);
    return 0;
}

// -n cat flag functionality implementation
int numberOutput(char *filename) {
    FILE *fptr;
    if ((fptr = fopen(filename, "r")) == NULL) {
        printf("wc: didn't manage to open the file '%s'\n", filename);
        return -1;
    }
    register int c;
    int newLineIdent = 1, count = 1;

    while ((c = getc(fptr)) != EOF) {
        if (newLineIdent == 1) {
            printf("\t%d  ", count);
            ++count;
            newLineIdent = 0;
        }  if (c == '\n') {
            newLineIdent = 1;
        } 
        
        printf("%c", c);
    }

    fclose(fptr);
    return 0;
}

// -b cat flag functionality implementation
int numberNonEmptyOutput(char *filename) {
    FILE *fptr;
    if ((fptr = fopen(filename, "r")) == NULL) {
        printf("wc: didn't manage to open the file '%s'\n", filename);
        return -1;
    }
    register int c;
    int newLineIdent = 1, count = 1;

    while ((c = getc(fptr)) != EOF) {
        if (newLineIdent == 1 && c != '\n') {
            printf("\t%d  ", count);
            ++count;
            newLineIdent = 0;
        }  if (c == '\n') {
            newLineIdent = 1;
        } 
        
        printf("%c", c);
    }

    fclose(fptr);
    return 0;
}


// OPTIMIZATION NOTE:
// pass descriptor to the functions
// open the file outside the functions and pass a descriptor.