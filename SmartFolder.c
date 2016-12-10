#include "Syscall.h"
#include "Parser.h"
#include <stdio.h>

int main(int argc, char const *argv[]) {
    //Parse parameters
    if(argc > 3) {
        if(isValidPath(argv[1]) && isValidPath(argv[2])) {
            HashSet set;
            HashSet* hashset = &set;
            initMap(hashset, 100);
            evaluateAndSearch(&(argv[3]), argc-3, argv[2], &hashset);
            dumpTable(hashset);
        }
    } else if(argc == 2 && strcmp(argv[1], "-d") == 0) {
        //delete folder (bonus feature)
    }

    return 0;
}
