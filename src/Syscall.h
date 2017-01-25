/**
 * @file Syscall.h
 * @brief Header file that contains the definitions for system calls wrapper functions used in our program
 *
 * @authors Maxime Lovino, Thomas Ibanez
 * @date January 25, 2017
 * @version 1.0
 */

#ifndef _SYSCALL_H_
#define _SYSCALL_H_

#include <unistd.h>
#include <sys/stat.h>
#include <dirent.h>
#include <sys/types.h>
#include <stdlib.h>
#include <libgen.h>
#include <stdio.h>
#include <pwd.h>
#include <grp.h>

int sfork();

int ssymlink(char *target, char *linkPath);

char *sbasename(char *fullPath);

int smkdir(char *path);

FILE *stouch(char *file);

int saccess(char *path);

int sunlink(char *file);

int srmdir(char *path);

int sgetpwuid(char *userName);

int sgetgrgid(char *groupName);

int slstat(char *name, struct stat *statbuf);

DIR *sopendir(char *name);

int schdir(char *name);

int sclosedir(DIR *dp);

struct dirent *sreaddir(DIR *dir);

int sS_ISLNK(mode_t m);

int sS_ISDIR(mode_t m);

int sS_ISREG(mode_t m);

char *srealpath(char *p, char *buf);

#endif /* end of include guard: _SYSCALL_H_ */
