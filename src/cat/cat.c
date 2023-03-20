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
        int t1;
        if ((t1 = creat(TEMPFILE1, PARAMS)) == -1) {
            printf("cat: didn't namange to create nessesary temporary file.\n");
            return -1;
        }

        int t2;
        if ((t2 = creat(TEMPFILE2, PARAMS)) == -1) {
            printf("cat: didn't namange to create nessesary temporary file.\n");
            return -1;
        }

        if (filecopy(cmdBuffer[nlines-1], TEMPFILE1) != 0) {
            return -1;
        }

        if (catStructure.bigAFlag == 1)
        {
            showAll();
        }
        if (catStructure.bigEFlag == 1)
        {
            addEndSign();
        }
        if (catStructure.bigTFlag == 1)
        {
            replaceTabChars();
        }
        if (catStructure.bFlag == 1)
        {
            numberNonEmptyOutput();
        }
        if (catStructure.nFlag == 1)
        {
            numberOutput();
        }

        fileStdout();
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

// Get data of the temporary file TEMPFILE1 to stdout descriptor
int fileStdout() {
    FILE *temp;
    if ((temp = fopen(TEMPFILE1, "r")) == NULL) {
        printf("wc: didn't manage to open the file '%s'\n", TEMPFILE1);
        return -1;
    }

    register int c;
    while((c = getc(temp)) != EOF) {
        printf("%c", c);
    }

    remove(TEMPFILE1);
    remove(TEMPFILE2);
}

// Copy data from one temporary file to another
int filecopy(char *filename1, char *filename2) {
    FILE *mainDesc;
    if ((mainDesc = fopen(filename1, "r")) == NULL) {
        printf("wc: didn't manage to open the file '%s'\n", filename1);
        return -1;
   }

   FILE *additionaDesc;
    if ((additionaDesc = fopen(filename2, "w")) == NULL) {
        printf("wc: didn't manage to open the file '%s'\n", filename2);
        return -1;
   }

    register int c;
    while((c = getc(mainDesc)) != EOF) {
        putc(c, additionaDesc);
    }

    fclose(mainDesc);
    fclose(additionaDesc);

    return 0;
}

// -A cat flag functionality implementation
int showAll() {
    FILE *temp_1;
    if ((temp_1 = fopen(TEMPFILE1, "r")) == NULL) {
        printf("wc: didn't manage to open the file '%s'\n", TEMPFILE1);
        return -1;
    }

    FILE *temp_2;
    if ((temp_2 = fopen(TEMPFILE2, "w")) == NULL) {
        printf("wc: didn't manage to open the file '%s'\n", TEMPFILE2);
        return -1;
    }
    register int c;

    while ((c = getc(temp_1)) != EOF) {
        if (c == '\t') {
            fputs("^I", temp_2);
        } else if (c == '\n') {
            fputs("$\n", temp_2);
        } else {
            putc(c, temp_2);
        }
    }

    fclose(temp_1);
    fclose(temp_2);

    filecopy(TEMPFILE2, TEMPFILE1);
    return 0;
}

// -E cat flag functionality implementation
int addEndSign() {
    FILE *temp_1;
    if ((temp_1 = fopen(TEMPFILE1, "r")) == NULL) {
        printf("wc: didn't manage to open the file '%s'\n", TEMPFILE1);
        return -1;
    }

    FILE *temp_2;
    if ((temp_2 = fopen(TEMPFILE2, "w")) == NULL) {
        printf("wc: didn't manage to open the file '%s'\n", TEMPFILE2);
        return -1;
    }
    register int c;

    while ((c = getc(temp_1)) != EOF) {
        if (c == '\n') {
            fputs("$\n", temp_2);
        } else {
            putc(c, temp_2);
        }
    }

    fclose(temp_1);
    fclose(temp_2);

    filecopy(TEMPFILE2, TEMPFILE1);
    
    return 0;
}

// -T cat flag functionality implementation
int replaceTabChars() {
    FILE *temp_1;
    if ((temp_1 = fopen(TEMPFILE1, "r")) == NULL) {
        printf("wc: didn't manage to open the file '%s'\n", TEMPFILE1);
        return -1;
    }

    FILE *temp_2;
    if ((temp_2 = fopen(TEMPFILE2, "w")) == NULL) {
        printf("wc: didn't manage to open the file '%s'\n", TEMPFILE2);
        return -1;
    }
    register int c;

    while ((c = getc(temp_1)) != EOF) {
       if (c == '\t') {
            fputs("^I", temp_2);
        } else {
            putc(c, temp_2);
        }
    }

    fclose(temp_1);
    fclose(temp_2);

    filecopy(TEMPFILE2, TEMPFILE1);
    
    return 0;
}

// -n cat flag functionality implementation
int numberOutput() {
    FILE *temp_1;
    if ((temp_1 = fopen(TEMPFILE1, "r")) == NULL) {
        printf("wc: didn't manage to open the file '%s'\n", TEMPFILE1);
        return -1;
    }

    FILE *temp_2;
    if ((temp_2 = fopen(TEMPFILE2, "w")) == NULL) {
        printf("wc: didn't manage to open the file '%s'\n", TEMPFILE2);
        return -1;
    }
    register int c;
    int newLineIdent = 1, count = 1;

    while ((c = getc(temp_1)) != EOF) {
        if (newLineIdent == 1) {
            putc('\t', temp_2);
            putc(count+'0', temp_2);
            fputs("  ", temp_2);
            ++count;
            newLineIdent = 0;
        }  if (c == '\n') {
            newLineIdent = 1;
        } 
        
        putc(c, temp_2);
    }

    fclose(temp_1);
    fclose(temp_2);

    filecopy(TEMPFILE2, TEMPFILE1);
    
    return 0;
}

// -b cat flag functionality implementation
int numberNonEmptyOutput() {
    FILE *temp_1;
    if ((temp_1 = fopen(TEMPFILE1, "r")) == NULL) {
        printf("wc: didn't manage to open the file '%s'\n", TEMPFILE1);
        return -1;
    }

    FILE *temp_2;
    if ((temp_2 = fopen(TEMPFILE2, "w")) == NULL) {
        printf("wc: didn't manage to open the file '%s'\n", TEMPFILE2);
        return -1;
    }
    register int c;
    int newLineIdent = 1, count = 1;

    while ((c = getc(temp_1)) != EOF) {
        if (newLineIdent == 1 && c != '\n') {
            putc('\t', temp_2);
            putc(count+'0', temp_2);
            fputs("  ", temp_2);
            ++count;
            newLineIdent = 0;
        }  if (c == '\n') {
            newLineIdent = 1;
        } 
        
        putc(c, temp_2);
    }

    fclose(temp_1);
    fclose(temp_2);

    filecopy(TEMPFILE2, TEMPFILE1);
    
    return 0;
}