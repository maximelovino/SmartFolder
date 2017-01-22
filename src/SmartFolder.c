#include "Syscall.h"
#include "Parser.h"
#include "List.h"
#include "Linker.h"
#include "Deamon.h"
#include "HashSet.h"
#include "SysFile.h"
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
                //the optimal size of a hashset is n²
                HashSet* set = initSet(files->size*files->size);
                putAll(set, files);
                incrementalSearch(&(argv[3]), argc-3, argv[2], argv[1], set);
              } else if(pid > 0) {
                  logMessage(0,"The child is at process %d", pid);
                if(!createSysFile(pid, argv[1])) {
                  logMessage(3, "A smartFolder with this name already exists");
                }
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
