#include <stdio.h>
#include "cmd_argv_reader.h"
#include "wc_struct.h"

int main(int argc, char **argv)
{
    printf("\nCommand-line arguments:\n");

    int count;
    for (count = 1; count < argc; count++) {
        printf("%d: %s\n", count, argv[count]);
        if (readlines(argv[count]) == -1) {
            return -1;
        }
    }

    for (int i = 0; i < CMDAMOUNT; i++) {
        printf("nlines: %d, cmdBuffer[%d]: %s\n", nlines, i, cmdBuffer[i]);
    }

    //printf("comp: %d\n", strcmp("hello", "bitch"));
    argIdentifier();

    return 0;
}
