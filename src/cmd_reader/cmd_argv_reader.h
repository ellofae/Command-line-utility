#ifndef CMD_ARGV_READER_H
#define CMD_ARGV_READER_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// Cmd-line arguments pointer array
#define CMDAMOUNT 10 // maximum amount of cmd-arguments
#define MAXLEN 12 // maximum length of a cmd-argument

char *cmdBuffer[CMDAMOUNT];
char **cmdPtr;
int nlines;


// Pointer array buffer manager
#define BUFSIZE 4096

char allocBuf[BUFSIZE];
char *allocPtr;

char *allocateBuffer(int n);

// Possible Command-line options
#define WCOPTIONS 5
#define CATOPTIONS 5

// Command-line arguments processing functionality 
int readlines(char *str);

// Comparison function implementation
void stringPointerCopy(char *s, char *t);
#endif