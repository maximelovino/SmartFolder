#include "Syscall.h"
#include "Parser.h"
#include "List.h"
#include <stdio.h>

int main(int argc, char const *argv[]) {
    //Parse parameters
    if(argc > 3) {
        if(isValidPath(argv[1]) && isValidPath(argv[2])) {
            List set;
            List* files = &set;
            initList(files, 100);
            int k = evaluateAndSearch(&(argv[3]), argc-3, argv[2], &files);
            if(k == -1) {
              logMessage(2, "Error while checking");
            }
            dumpList(files);
        }
    } else if(argc == 2 && strcmp(argv[1], "-d") == 0) {
        //delete folder (bonus feature)
    }

    return 0;
}
