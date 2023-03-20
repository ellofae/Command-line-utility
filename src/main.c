#include <stdio.h>
#include "cmd_reader/cmd_argv_reader.h"
#include "wc/wc_struct.h"
#include "cat/cat.h"
#include "grep/grep.h"

int main(int argc, char **argv)
{
    int count;
    for (count = 1; count < argc; count++) {
        if (readlines(argv[count]) == -1) {
            return -1;
        }
    }

    if (strcmp(*cmdBuffer, "wc") == 0) {
        wcIdentifier();
    } else if ((strcmp(*cmdBuffer, "cat") == 0)) {
        catIdentifier();
    } else if ((strcmp(*cmdBuffer, "grep") == 0)) {
        if(nlines > 2) {
            grepIdentifier();
        }
    }

    return 0;
}
