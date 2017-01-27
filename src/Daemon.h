/**
 * @file Daemon.h
 * @brief Header file that contains the definitions for our background process computation
 *
 * @authors Maxime Lovino, Thomas Ibanez
 * @date January 25, 2017
 * @version 1.0
 */

#ifndef _DEAMON_H_
#define _DEAMON_H_

#include "Parser.h"
#include "Linker.h"
#include "HashSet.h"

/**
 * Function that will run in the background and update the SmartFolder
 * @param expression The search expression as an array of terms
 * @param exprLen The number of terms of the expression
 * @param searchFolder The path of the folder that we search in
 * @param smartFolder The path of the SmartFolder
 * @param files An HashSet of the files that already match our expression
 * @param filesList A list of the files already in our SmartFolder
 */
void incrementalSearch(const char** expression, int exprLen, char* searchFolder, char* smartFolder, HashSet* files, List* filesList);

#endif /* end of include guard: _DEAMON_H_ */
