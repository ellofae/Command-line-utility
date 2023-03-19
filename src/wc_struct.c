#include "wc_struct.h"

// Unix wc command flags functionality implementation:
// -l wc flag functionality implementation
int lineCounter(char *filename) {
    FILE *fptr = fopen(filename, "r");
    int c, count = 0;

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
    FILE *fptr = fopen(filename, "r");
    int c, count = 0;

    while ((c = getc(fptr)) != EOF) {
        ++count;
    }

    fclose(fptr);
    return count;
}

// -c wc flag functionality implementation
int byteCounter(char *filename) {
    FILE *fptr = fopen(filename, "r");
    int c, count = 0;

    while ((c = getc(fptr)) != EOF) {
        ++count;
    }

    fclose(fptr);
    return count;
}

// -w wc flag functionality implementation
int wordCounter(char *filename) {
    FILE *fptr = fopen(filename, "r");
    int c, count = 0;

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
    FILE *fptr = fopen(filename, "r");
    int c, count = 0, maxCount = 0;

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