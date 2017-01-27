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

/**
 * Function to retrieve the PID of a running folder
 * @param folderName The name of the SmartFolder
 * @return The PID of the process running that Folder, -1 if not found
 */
int getPID(const char* folderName);

/**
 * Function to retrieve the full path of a SmartFolder
 * @param pid The PID of the process running the folder
 * @return The full path of the SmartFolder, NULL if not found
 */
char* getFolderPath(int pid);

#endif /* end of include guard: _SYSFILE_H_ */
