#include "Search.h"
#include "List.h"
#include <sys/stat.h>
#include <dirent.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

List* searchDirectory(char* rootDir, searchType type, void* searchArg) {
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
			List* recursiveResult = searchDirectory(entry->d_name, type, searchArg);
			List* r = listUnion(result, recursiveResult);
			deleteList(result);
			deleteList(recursiveResult);
			result = r;
		} else {
			//TODO: Test if the criteria is NULL or the criteria matches the file stats
			int size;
			char* searchString;
			switch (type) {
				case NAME:
					searchString = (char*) searchArg;
					if (strstr(entry->d_name, searchString)) {
						insert(result, entry->d_name);
					}
					break;
				case SIZE_BIGGER:
					size = *((int*) searchArg);
					if (statbuf.st_size > size) {
						insert(result, entry->d_name);
					}
					break;
				case SIZE_SMALLER:
					size = *((int*) searchArg);
					if (statbuf.st_size < size) {
						insert(result, entry->d_name);
					}
					break;
				case SIZE_EQUAL:
					size = *((int*) searchArg);
					if (statbuf.st_size == size) {
						insert(result, entry->d_name);
					}
					break;
				default:
					printf("Haven't done that yet\n");
					break;
			}
		}
	}
	chdir("..");
	closedir(dp);
	return result;
}
