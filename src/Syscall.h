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
#include "Logger.h"

/**
 * fork wrapper
 * @return pid of the child or 0 if you are the child
 */
int sfork();

/**
 * symlink wrapper
 * @param  target   real file
 * @param  linkPath link path
 */
void ssymlink(char* target, char* linkPath);

/**
 * basename wrapper
 * @param  fullPath full path of the file
 * @return          basename of the file
 */
char* sbasename(char* fullPath);

/**
 * mkdir wrapper
 * @param  path path to create
 */
void smkdir(char* path);

/**
 * touch wrapper
 * @param  file file to create
 * @return      FILE* to the file created
 */
FILE* stouch(char* file);

/**
 * access wrapper
 * @param  path file to check
 * @return      1 if the file exists, 0 otherwise
 */
int saccess(char* path);

/**
 * unlink wrapper
 * @param  file file to unlink
 */
void sunlink(char* file);

/**
 * rmdir wrapper
 * @param  path directory to remove
 */
void srmdir(char* path);

/**
 * getpwnam->pw_uid wrapper
 * @param  userName the username to get uid from
 * @return          uid linked to the username
 */
int sgetpwuid(char* userName);

/**
 * getgrnam->gr_gid wrapper
 * @param  groupName groupname to get gid from
 * @return           gid linked to this groupname
 */
int sgetgrgid(char* groupName);

/**
 * lstat wrapper
 * @param  name    file to check
 * @param  statbuf buffer to write info to
 */
void slstat(char* name, struct stat* statbuf);

/**
 * opendir wrapper
 * @param  name directory to open
 * @return      DIR* to the directory
 */
DIR* sopendir(char* name);

/**
 * chdir wrapper
 * @param  name directory to go to
 */
void schdir(char* name);

/**
 * closedir wrapper
 * @param  dp directory to close
 */
void sclosedir(DIR* dp);

/**
 * readdir wrapper
 * @param  dir directory to read
 * @return     dirent entries
 */
struct dirent* sreaddir(DIR* dir);

/**
 * S_ISLNK wrapper
 * @param  m file to check
 * @return   1 if the file is a link, 0 otherwise
 */
int sS_ISLNK(mode_t m);

/**
 * S_ISDIR wrapper
 * @param  m file to check
 * @return   1 if the file is a directory, 0 otherwise
 */
int sS_ISDIR(mode_t m);

/**
 * S_ISREG wrapper
 * @param  m file to check
 * @return   1 if the file is a regular file, 0 otherwise
 */
int sS_ISREG(mode_t m);

/**
 * realpath wrapper
 * @param  p   file to get realpath from
 * @param  buf buffer to write the realpath to (optional)
 * @return     if the buffer is NULL, return the realpath
 */
char* srealpath(char* p, char* buf);

#endif /* end of include guard: _SYSCALL_H_ */
