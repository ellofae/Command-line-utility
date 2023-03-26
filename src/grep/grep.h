#ifndef GREP_H
#define GREP_H

#include <stdio.h>
#include <string.h>

// Unux 'grep' cmd-command structure
struct grepStruct {
    int iFlag; // --ignore-case
    int cFlag; // count of matching lines
    int vFlag; // count non-matching lines
    int lFlag; // file names that have matches
    int LFlag; // file names that don't have matches
};

int grepIdentifier();
int ignoreCase(char *filename, char *pattern); // -i flag function

int regularGrep(char *filename, char *pattern); // regular grep function
int patternCheck(char *line, char* pattern); // check if pattern is in the line
int patternCheckIgnoreCase(char *line, char *pattern); // check if pattern is in the line (ignore-case)

#endif
