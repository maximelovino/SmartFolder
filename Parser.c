#include "Parser.h"

int isValidPath(char* path) {
    static regex_t regex;
    if(&regex == NULL) {
        if(regcomp(&regex, FILE_PATH_REGEX, 0)) {
            printf("mdrrr\n");
        }
    }

    return regexec(&regex, path, 0, NULL, 0);
}

int getUID(char* userName) {
    return getpwnam(userName)->pw_uid;
}

int getGID(char* groupName) {
    return getgrnam(groupName)->gr_gid;
}

struct timespec getTimeSpec(char* date) {
    int step = 0;
    struct timespec* t = malloc(sizeof(struct timespec));
    if(step == 0) {
        char year[5];
        strncpy(year, date, 4)
        int yyyy = atoi(year);
        t->tv_sec = (yyyy-1970) * SECONDS_IN_YEAR;
        step++;
    } else if(step == 1) {
        char month[3];
        strncpy(month, date[6], 2);
        int mm = atoi(month);
        t->tv_sec += (mm-1) * SECONDS_IN_MONTH;
        step++;
    } else if(step == 2) {
        char day[3];
        strncpy(day, date[10], 2);
        int dd = atoi(day);
        t->tv_sec += (dd-1) * SECONDS_IN_DAY;
    }
    return t;
}

searchType getSearchType(char* param, char* arg) {

}
