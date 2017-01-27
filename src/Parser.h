/**
 * @file Parser.h
 * @brief Header file that contains the definitions of our Parser
 *
 * @authors Maxime Lovino, Thomas Ibanez
 * @date January 25, 2017
 * @version 1.0
 */

#ifndef _PARSER_H_
#define _PARSER_H_
/**
 * This is the Regular Expression that will be used to check the validity of a path
 */
#define FILE_PATH_REGEX "((\\.|\\.\\.)?\\/)?(([A-Z]|[a-z]|[0-9]| |-|_|'|\\.)+\\/?)+"

#include <time.h>
#include <string.h>
#include <regex.h>
#include <stdlib.h>
#include <stdio.h>
#include "Search.h"
#include "List.h"
#include "Stack.h"
#include "Logger.h"
#include "Syscall.h"
#include <ctype.h>

/**
 * Function to check if a path is valid
 * @param path The path we want to check
 * @return 1 if the path is valid, 0 otherwise
 */
int isValidPath(char* path);

/**
 * Function to convert a date in YYYY-MM-DD format to a timespec
 * @param date The date as a String in the format YYYY-MM-DD
 * @return The date as a a pointer of struct timespec
 */
struct timespec* getTimeSpec(char* date);

/**
 * Converts a search word to a searchType
 * @param  param the search word
 * @param  arg   the parameter linked to the search word
 * @return       the corresponding searchType or -1 if no match exists
 */
searchType getSearchType(char* param, char* arg);

/**
 * Checks if a word is a boolean operator
 * @param  word the word to check
 * @return      1 if it is a boolean operator, 0 otherwise
 */
int isBooleanOp(char* word);

/**
 * Checks if a searchType has proper argument linked to it
 * @param  st  The search type
 * @param  arg The argument
 * @return     1 if the search is valid, 0 otherwise
 */
int isValidSearch(searchType st, char* arg);

/**
 * Evaluates an expression and searches for matching files
 * @param  expression The expression to search with (as an array of terms)
 * @param  exprLen    The length of the expression
 * @param  folder     The folder to search from
 * @param  result     A List to put the results of the search in
 * @return            0 if the search was ok, 1 otherwise
 */
int evaluateAndSearch(char** expression, int exprLen, char* folder, List** result);

/**
 * Function that returns a generic pointer to an argument for a search of a certain type
 * It will actually return the pointer for the correct type depending on the search
 * @param st The type of search
 * @param arg The argument as a string
 * @return A pointer to the argument in the correct type
 */
void* prepareArgument(searchType st, char* arg);

/**
 * Converts a size with its Unit suffix (K, M, G, T) to the correct size
 * @param sizeAsString The size with its suffix
 * @return The size as an integer value
 */
int getSize(char* sizeAsString);

/**
 * Removes the + or - before a search argument if necessary
 * @param  st  searchType
 * @param  arg argument to trim
 * @return     Trimmed argument
 */
char* trimArgument(searchType st, char* arg);

#endif /* end of include guard: _PARSER_H_ */
