#ifndef WC_STRUCT_H
#define WC_STRUCT_H

#include <stdio.h>

// Unux 'wc' cmd-command structure
struct wcStruct {
    int cFlag;
    int mFlag;
    int lFlag;
    int wFlag;
    int bigLFlag;
};

int lineCounter(char *filename); // -l wc flag functionality
int charCounter(char *filename); // -m wc flag functionality
int byteCounter(char *filename); // -c wc flag functionality
int wordCounter(char *filename); // -w wc flag functionality
int maxWidth(char *filename); // -L wc flag functionality

int wcIdentifier(); // Processing buffer
void stringPointerCopy(char *s, char *t); // Comparison helper function

#endif