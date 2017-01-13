#include "Syscall.h"
#include "Parser.h"
#include "List.h"
#include "Linker.h"
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
            if(makeFolder(argv[1], files) == 0) {
              int pid = processFork();
              if(pid == 0) {

              } else if(pid > 0) {
                createSysFile(pid, argv[1]);
              }
            } else {
              logMessage(3, "Couldn't create SmartFolder");
            }
        }
    } else if(argc == 2 && strcmp(argv[1], "-d") == 0) {
        //delete folder (bonus feature)
    }else{
      printf("Usage: SmartFolder <LinkDirectory> <SearchDirectory> [searchExpression]\n");
    }

    return 0;
}
