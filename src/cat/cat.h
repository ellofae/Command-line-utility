#ifndef CAT_H
#define CAT_H

#include <stdio.h>

// Unux 'cat' cmd-command structure
struct catStruct {
    int bigAFlag;
    int bigEFlag;
    int bigTFlag;
    int bFlag;
    int nFlag;
};

int catIdentifier(); // Processing buffer

int showAll(char *filename); // -A cat flag functionality
int addEndSign(char *filename); // -E cat flag functionality
int replaceTabChars(char *filename); // -T cat flag functionality
int numberOutput(char *filename); // -n cat flag functionality
int numberNonEmptyOutput(char *filename); // -b cat flag functionality

#endif