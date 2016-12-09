#ifndef _PARSER_H_
#define _PARSER_H_
#define SECONDS_IN_YEAR 3.154e7
#define SECONDS_IN_MONTH 2.628e6
#define SECONDS_IN_DAY 86400
#define FILE_PATH_REGEX "((\.|\.\.)?\/)?(([A-Z]|[a-z]|[0-9]| |-|_|'|\.)+\/?)+"
#include <time.h>
#include <pwd.h>
#include <grp.h>
#include <string.h>
#include <regex.h>

int isValidPath(char* path);
int getUID(char* userName);
int getGID(char* groupName);
struct timespec getTimeSpec(char* date);
searchType getSearchType(char* param, char* arg);

#endif /* end of include guard: _PARSER_H_ */
