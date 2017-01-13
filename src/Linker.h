#ifndef _LINKER_H_
#define _LINKER_H_

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include "Syscall.h"
#include "Logger.h"
#include "List.h"

int makeLink(char* pathToLink, char* destFolder);
int makeFolder(char* path, List* files);

#endif /* end of include guard: _LINKER_H_ */
