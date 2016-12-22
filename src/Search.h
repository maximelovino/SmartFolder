#ifndef _SEARCH_H_
#define _SEARCH_H_
#include "List.h"
#include <sys/stat.h>


typedef enum {NAME, SIZE_SMALLER, SIZE_EQUAL, SIZE_BIGGER, STATUS_DATE_B, STATUS_DATE_E, STATUS_DATE_A, MODIF_DATE_B, MODIF_DATE_E, MODIF_DATE_A, USAGE_DATE_B, USAGE_DATE_E, USAGE_DATE_A, OWNER, GROUP, MODE} searchType;

/**
 * Searches recursivly through directories beneath a certain directory
 * @param  rootDir      The directory to start from
 * @param  type     	The type of search to perform
 * @param  searchArg	The argument for the search
 * @return              A list of matching files
 */
List* searchDirectory(char* rootDir, searchType type, void* searchArg);

/**
 * Compares 2 timespecs
 * @param  t1 the first timespec
 * @param  t2 the second timespec
 * @return    -1 if t1 < t2, 0 if t1 = t2 and 1 if t1 > t2
 */
int timeCompare(struct timespec* t1, struct timespec* t2);
#endif /* end of include guard: _SEARCH_H_ */
