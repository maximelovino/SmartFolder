#include "Parser.h"

int isValidPath(char* path) {
    static regex_t regex;
//    if(&regex == NULL) {
        if(regcomp(&regex, FILE_PATH_REGEX, 0)) {
            printf("mdrrr\n");
        }
//    }

    return regexec(&regex, path, 0, NULL, 0);
}

int getUID(char* userName) {
    return getpwnam(userName)->pw_uid;
}

int getGID(char* groupName) {
    return getgrnam(groupName)->gr_gid;
}

struct timespec* getTimeSpec(char* date) {
    int step = 0;
    struct timespec* t = malloc(sizeof(struct timespec));
    if(step == 0) {
        char year[5];
        strncpy(year, date, 4);
        int yyyy = atoi(year);
        t->tv_sec = (yyyy-1970) * SECONDS_IN_YEAR;
        step++;
    } else if(step == 1) {
        char month[3];
        strncpy(month, &(date[6]), 2);
        int mm = atoi(month);
        t->tv_sec += (mm-1) * SECONDS_IN_MONTH;
        step++;
    } else if(step == 2) {
        char day[3];
        strncpy(day, &(date[10]), 2);
        int dd = atoi(day);
        t->tv_sec += (dd-1) * SECONDS_IN_DAY;
    }
    return t;
}

searchType getSearchType(char* param, char* arg) {
    if(strcmp(param, "--name")) {
        return NAME;
    } else if(strcmp(param, "--size")) {
        if(arg[0] == '+')
            return SIZE_BIGGER;
        else if(arg[0] == '-')
            return SIZE_SMALLER;
        else
            return SIZE_EQUAL;
    } else if(strcmp(param, "--dateStatus")) {
        if(arg[0] == '+')
            return STATUS_DATE_A;
        else if(arg[0] == '-')
            return STATUS_DATE_B;
        else
            return STATUS_DATE_E;
    } else if(strcmp(param, "--dateModified")) {
        if(arg[0] == '+')
            return MODIF_DATE_A;
        else if(arg[0] == '-')
            return MODIF_DATE_B;
        else
            return MODIF_DATE_E;
    } else if(strcmp(param, "--dateUsed")) {
        if(arg[0] == '+')
            return USAGE_DATE_A;
        else if(arg[0] == '-')
            return USAGE_DATE_B;
        else
            return USAGE_DATE_E;
    } else if(strcmp(param, "--uid")) {
        return OWNER;
    } else if(strcmp(param, "--gid")) {
        return GROUP;
    } else if(strcmp(param, "--perms")) {
        return MODE;
    }
    return -1;
}


int isBooleanOp(char* word) {
    return (strcmp(word, "and") & strcmp(word, "or") & strcmp(word, "not") & strcmp(word, "xor")) == 0;
}

int isValidSearch(searchType st, char* arg) {
    if(st == NAME) {
        return 1;
    } else if(st == SIZE_SMALLER || st == SIZE_BIGGER || st == SIZE_EQUAL) {
        int starti = (st != SIZE_EQUAL);
        for (int i = starti;arg[i+1]; i++) {
            if(!isdigit(arg[i])) {
                return 0;
            }
        }
        return 1;
    } else if(st == STATUS_DATE_B || st == STATUS_DATE_A || st == MODIF_DATE_B || st == MODIF_DATE_A || st == USAGE_DATE_B || st == USAGE_DATE_A || st == STATUS_DATE_E || st == MODIF_DATE_E || st == USAGE_DATE_E) {
        int starti = !(st == STATUS_DATE_E || st == MODIF_DATE_E || st == USAGE_DATE_E);
        for (int i = starti;arg[i]; i++) {
            if(i == 4+starti || i == 7+starti) {
                //skip separator
                continue;
            }
            if(!isdigit(arg[i])) {
                return 0;
            }
        }
    } else if(st == OWNER || st == GROUP) {
        return 1;
    } else if(st == MODE) {
        if(strlen(arg) == 3) {
            for (int i = 0;arg[i]; i++) {
                if(!isdigit(arg[i])) {
                    return 0;
                }
            }
        }
        return 1;
    }
    return 0;
}

//TODO add test for the NOT boolean operator
int evaluateAndSearch(char** expression, int exprLen, char* folder, HashSet** result) {
    Stack* s = initStack();
    for (int i = 0; i < exprLen;) {
        char* p1 = expression[i];
        if(!isBooleanOp(p1)) {
            searchType st = getSearchType(p1, expression[i+1]);
            if(isValidSearch(st, expression[i+1])) {
                char* op1 = trimArgument(st, expression[i+1]);
                List* l1 = searchDirectory(folder, st, op1);
                push(s, l1);
            } else {
                return -1;
            }

            i += 2;
        } else {
            List* l1 = pop(s);
            List* l2 = pop(s);
            List* l3 = NULL;
            if(strcmp(p1, "and") == 0) {
                l3 = listIntersect(l1, l2);
            } else if(strcmp(p1, "or") == 0) {
                l3 = listUnion(l1, l2);
            } else {
                logMessage(3, "%s", "Operator not supported");
            }
            deleteList(l1);
            deleteList(l2);
            push(s, l3);
            i++;
        }
    }
    List* final = pop(s);
    while(final->head != NULL) {
        char* e0 = get(final, 0);
        removeIndex(final, 0);
        put(result, e0);
    }
    return 0;
}

char* trimArgument(searchType st, char* arg) {
    if(st == SIZE_BIGGER || st == SIZE_SMALLER || st == STATUS_DATE_B || st == STATUS_DATE_A || st == MODIF_DATE_B || st == MODIF_DATE_A || st == USAGE_DATE_B || st == USAGE_DATE_A) {
        char* narg = malloc(strlen(arg));
        strcpy(narg, &(arg[1]));
        return narg;
    }
    return arg;
}
