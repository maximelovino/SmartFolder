#include "Deamon.h"

void incrementalSearch(char** expression, int exprLen, char* searchFolder, char* smartFolder, HashSet* files) {
  logMessage(0, "Deamon Started");
  dumpSet(files);
  while(1) {
    List* result = initList();
    evaluateAndSearch(expression, exprLen, searchFolder, &result);
    sleep(5);
  }
}
