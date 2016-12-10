#ifndef _PARSER_H_
#define _PARSER_H_
#define SECONDS_IN_YEAR 3.154e7
#define SECONDS_IN_MONTH 2.628e6
#define SECONDS_IN_DAY 86400
#define FILE_PATH_REGEX "((\\.|\\.\\.)?\\/)?(([A-Z]|[a-z]|[0-9]| |-|_|'|\\.)+\\/?)+"
#include <time.h>
#include <pwd.h>
#include <grp.h>
#include <string.h>
#include <regex.h>
#include <stdlib.h>
#include <stdio.h>
#include "Search.h"
#include "HashSet.h"
#include "List.h"
#include "Stack.h"
#include <ctype.h>

int isValidPath(char* path);
int getUID(char* userName);
int getGID(char* groupName);
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
 * @param  st  The seach type
 * @param  arg The argument
 * @return     1 if the seach is valid, 0 otherwise
 */
int isValidSearch(searchType st, char* arg);

/**
 * Evalutes an expression and searches for matching files
 * @param  expression The expression to search with
 * @param  exprLen    The length of the expression
 * @param  folder     The folder to search from
 * @param  result     A map to put the result of the search
 * @return            0 if the search was ok, 1 otherwise
 */
int evaluateAndSearch(char** expression, int exprLen, char* folder, HashSet* result);

#endif /* end of include guard: _PARSER_H_ */
