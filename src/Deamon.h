#ifndef _DEAMON_H_
#define _DEAMON_H_

#include "Parser.h"
#include "Linker.h"
#include <signal.h>

void incrementalSearch(char** expression, int exprLen, char* searchFolder, char* smartFolder, HashSet* files);

void handler(int signum);

#endif /* end of include guard: _DEAMON_H_ */
