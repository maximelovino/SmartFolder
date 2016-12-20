#ifndef _SYSCALL_H_
#define _SYSCALL_H_
#include <unistd.h>
#include <libgen.h>

int processFork();
int symbolicLink(char* target, char* linkPath);
char* nameOfFile(char* fullPath);

#endif /* end of include guard: _SYSCALL_H_ */
