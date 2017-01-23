#ifndef _SYSFILE_H_
#define _SYSFILE_H_
#ifndef SYSFILE_PATH
#define SYSFILE_PATH "/tmp/"
#endif
#include "Syscall.h"
#include <string.h>
#include "Logger.h"

int createSysFile(int pid, char* smartFolder);

#endif /* end of include guard: _SYSFILE_H_ */
