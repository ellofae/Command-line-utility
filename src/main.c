#include <stdio.h>
#include "cmd_argv_reader.h"
#include "wc_struct.h"

int main(int argc, char **argv)
{
    int count;
    for (count = 1; count < argc; count++) {
        if (readlines(argv[count]) == -1) {
            return -1;
        }
    }

    //printf("comp: %d\n", strcmp("hello", "bitch"));
    if (strcmp(*cmdBuffer, "wc") == 0) {
        wcIdentifier();
    }

    return 0;
}
