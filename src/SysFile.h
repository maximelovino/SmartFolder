/**
 * @file SysFile.h
 * @brief Header file that contains the definitions for the writing of files about our folder execution
 *
 * @authors Maxime Lovino, Thomas Ibanez
 * @date January 25, 2017
 * @version 1.0
 */

#ifndef _SYSFILE_H_
#define _SYSFILE_H_
/**
 * Path in which our files will go
 */
#define SYSFILE_PATH "/tmp/"

#include "Syscall.h"
#include <string.h>
#include "Logger.h"

/**
 * Function that creates the necessary files for the SmartFolder
 * @param pid The pid of the background process of the folder
 * @param smartFolder The path of the folder
 * @return 0 on success, 1 otherwise
 */
int createSysFile(int pid, char* smartFolder);

#endif /* end of include guard: _SYSFILE_H_ */
