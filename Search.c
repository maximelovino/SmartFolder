#include "Search.h"
#include "List.h"
#include <sys/stat.h>
#include <dirent.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>

List* searchDirectory(char* rootDir, char* filePattern, int searchSize, int sizeOP, struct timespec* creationDate, struct timespec* modDate, struct timespec* useDate, uid_t* userOwner, gid_t* groupOwner, mode_t* mode) {
    List* result = initList();
    DIR* dp;
    struct dirent* entry;
    struct stat statbuf;
    if((dp = opendir(rootDir)) == NULL) {
        fprintf(stderr, "Couldn't open directory %s\n", rootDir);
        return NULL;
    }
    chdir(rootDir);
    while ((entry = readdir(dp)) != NULL) {
        lstat(entry->d_name, &statbuf);
        if(S_ISDIR(statbuf.st_mode)) {
            if(strcmp(".", entry->d_name) == 0 || strcmp("..", entry->d_name) == 0) {
                continue;
            }
            printf("We need to go deeper for %s\n", entry->d_name);
            List* recursiveResult = searchDirectory(entry->d_name, filePattern, searchSize, sizeOP, creationDate, modDate, useDate, userOwner, groupOwner, mode);
            List* r = listUnion(result, recursiveResult);
            deleteList(result);
            deleteList(recursiveResult);
            result = r;
        } else {
            //TODO: Test if the criteria is NULL or the criteria matches the file stats
            insert(result, entry->d_name);
        }
    }
    chdir("..");
    closedir(dp);
    return result;
}
