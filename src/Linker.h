/**
 * @file Linker.h
 * @brief Header file that contains the definitions for the functions that will take care of the SmartFolder creation as well as the link creation
 *
 * @authors Maxime Lovino, Thomas Ibanez
 * @date January 25, 2017
 * @version 1.0
 */

#ifndef _LINKER_H_
#define _LINKER_H_

#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <dirent.h>
#include "Syscall.h"
#include "Logger.h"
#include "List.h"

/**
 * Function that creates a link for the file and puts the link in the destination folder
 * @param pathToLink The path we want to link to
 * @param destFolder The destination folder for the link
 * @return 1 on succes, 0 otherwise
 */
int makeLink(char* pathToLink, char* destFolder);

/**
 * Function to remove a link
 * @param pathOfFile The path of the file linked by the link we want to remove
 * @param linkFolder The folder where the links are stored
 * @return 1 on success, 0 otherwise
 */
int removeLink(char* pathOfFile, char* linkFolder);

/**
 * Function to add the next suffix to a name (if no suffix, it will add (1), otherwise it will just increment the count)
 * @param name The current name of the file
 */
void nextSuffix(char* name);

/**
 * Function that creates the SmartFolder and links for all files in the list
 * @param path The path of the SmartFolder
 * @param files A list of files to link
 * @return -1 on error, 1 if exists already, 0 otherwise
 */
int makeFolder(char* path, List* files);

/**
 * Function that deletes a folder and all its content
 * @param path The path of the folder to delete
 * @return 1 on success, 0 otherwise
 */
int removeFolder(char* path);

#endif /* end of include guard: _LINKER_H_ */
