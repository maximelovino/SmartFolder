#ifndef _SEARCH_H_
#define _SEARCH_H_
#include "List.h"
#include <sys/stat.h>

/**
 * Searches recursivly through directories beneath a certain directory
 * @param  rootDir      The directory to start from
 * @param  filePattern  A file name pattern to match or NULL
 * @param  searchSize   A file size to compare or 0 (in bytes)
 * @param  sizeOP       the file size comparaison to make (-1 = smaller, 0 = equal, 1 = larger)
 * @param  creationDate The creation date of the file or NULL
 * @param  modDate      The last modification date of the file or NULL
 * @param  useDate      The last use of the file or NULL
 * @param  userOwner    The user who owns the file or NULL
 * @param  groupOwner   The group who owns the file or NULL
 * @param  mode         The access mode of the file or NULL
 * @return              A list of matching files (all NULL values will be considered matching)
 */
List* searchDirectory(char* rootDir, char* filePattern, int searchSize, int sizeOP, struct timespec* creationDate, struct timespec* modDate, struct timespec* useDate, uid_t* userOwner, gid_t* groupOwner, mode_t* mode);

//This file may also contain comparators functions for mode, time etc..
#endif /* end of include guard: _SEARCH_H_ */
