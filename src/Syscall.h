#ifndef _SYSCALL_H_
#define _SYSCALL_H_
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <libgen.h>
#include <stdio.h>

int processFork();
int symbolicLink(char* target, char* linkPath);
int makeDir(char* path);
char* nameOfFile(char* fullPath);
FILE* touch(char* file);
int fileExists(char* path);
#endif /* end of include guard: _SYSCALL_H_ */
