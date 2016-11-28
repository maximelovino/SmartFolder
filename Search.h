#ifndef _SEARCH_H_
#define _SEARCH_H_
#include "List.h"
#include <sys/stat.h>


typedef enum {NAME, SIZE_SMALLER, SIZE_EQUAL, SIZE_BIGGER, CREATION_DATE, MODIF_DATE, USAGE_DATE, OWNER, GROUP, MODE} searchType;

/**
 * Searches recursivly through directories beneath a certain directory
 * @param  rootDir      The directory to start from
 * @param  type     	The type of search to perform
 * @param  searchArg	The argument for the search
 * @return              A list of matching files
 */
List* searchDirectory(char* rootDir, searchType type, void* searchArg);

//This file may also contain comparators functions for mode, time etc..
#endif /* end of include guard: _SEARCH_H_ */
