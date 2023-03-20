#ifndef CAT_H
#define CAT_H

#include <stdio.h>
#include <fcntl.h>

#define TEMPFILE1 "temp_1.txt"
#define TEMPFILE2 "temp_2.txt"

#define PARAMS 0644

// Unux 'cat' cmd-command structure
struct catStruct {
    int bigAFlag;
    int bigEFlag;
    int bigTFlag;
    int bFlag;
    int nFlag;
};

int catIdentifier(); // Processing buffer
int fileStdout(); // Get data of temporary file to stdout desc.
int filecopy(char *filename1, char *filename2); // copying data from one file into another.

int showAll(); // -A cat flag functionality
int addEndSign(); // -E cat flag functionality
int replaceTabChars(); // -T cat flag functionality
int numberOutput(); // -n cat flag functionality
int numberNonEmptyOutput(); // -b cat flag functionality

#endif