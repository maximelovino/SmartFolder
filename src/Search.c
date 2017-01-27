/**
 * @file Search.c
 * @brief Source file that contains the implementation of our Search (crawler)
 *
 * @authors Maxime Lovino, Thomas Ibanez
 * @date January 25, 2017
 * @version 1.0
 */

#include "Search.h"

List* searchDirectory(const char* rootDir, searchType type, const void* searchArg) {
	List* result = initList();

	DIR* dp;
	struct dirent* entry;
	struct stat statbuf;
	logMessage(0, "Root dir %s", rootDir);
	if ((dp = sopendir(rootDir)) == NULL) {
		logMessage(3, "Couldn't open directory %s\n", rootDir);
		return NULL;
	}
	if(!schdir(rootDir)) {
		logMessage(3, "Couldn't change directory %s\n", rootDir);
		return NULL;
	}

	while ((entry = sreaddir(dp)) != NULL) {

		if(!slstat(entry->d_name, &statbuf)) {
			logMessage(3, "Couldn't stat file %s\n", entry->d_name);
			continue;
		}
		if (sS_ISLNK(statbuf.st_mode)) continue;
		if (sS_ISDIR(statbuf.st_mode)) {
		  if (strcmp(".", entry->d_name) == 0 || strcmp("..", entry->d_name) == 0 || entry->d_name[0] == '.') {
				continue;
			}
			List* recursiveResult = searchDirectory(entry->d_name, type, searchArg);
			if(recursiveResult != NULL) {
				List* r = listUnion(result, recursiveResult);
				deleteList(result);
				deleteList(recursiveResult);
				result = r;
			}
		} else {

			int size;
			char* searchString;
			unsigned int uid;
			unsigned int gid;
		 	mode_t perms;

			switch (type) {
				case NAME:
					searchString = (char*) searchArg;
					if (strstr(entry->d_name, searchString)) {
						insert(result, srealpath(entry->d_name, NULL));
					}
					break;
				case SIZE_BIGGER:
					size = *((int*) searchArg);
					if (statbuf.st_size > size) {
						insert(result, srealpath(entry->d_name, NULL));
					}
					break;
				case SIZE_SMALLER:
					size = *((int*) searchArg);
					if (statbuf.st_size < size) {
						insert(result, srealpath(entry->d_name, NULL));
					}
					break;
				case SIZE_EQUAL:
					size = *((int*) searchArg);
					if (statbuf.st_size == size) {
						insert(result, srealpath(entry->d_name, NULL));
					}
					break;

				case STATUS_DATE_B:
					if (timeCompare(&(statbuf.st_ctim), (struct timespec*) searchArg) == -1) {
						insert(result, srealpath(entry->d_name, NULL));
					}
					break;
				case MODIF_DATE_B:
					if (timeCompare(&(statbuf.st_mtim), (struct timespec*) searchArg) == -1) {
						insert(result, srealpath(entry->d_name, NULL));
					}
					break;
				case USAGE_DATE_B:
					if (timeCompare(&(statbuf.st_atim), (struct timespec*) searchArg) == -1) {
						insert(result, srealpath(entry->d_name, NULL));
					}
					break;

				case STATUS_DATE_E:
					if (timeCompare(&(statbuf.st_ctim), (struct timespec*) searchArg) == 0) {
						insert(result, srealpath(entry->d_name, NULL));
					}
					break;
				case MODIF_DATE_E:
					if (timeCompare(&(statbuf.st_mtim), (struct timespec*) searchArg) == 0) {
						insert(result, srealpath(entry->d_name, NULL));
					}
					break;
				case USAGE_DATE_E:
					if (timeCompare(&(statbuf.st_atim), (struct timespec*) searchArg) == 0) {
						insert(result, srealpath(entry->d_name, NULL));
					}
					break;

				case STATUS_DATE_A:
					if (timeCompare(&(statbuf.st_ctim), (struct timespec*) searchArg) == 1) {
						insert(result, srealpath(entry->d_name, NULL));
					}
					break;
				case MODIF_DATE_A:
					if (timeCompare(&(statbuf.st_mtim), (struct timespec*) searchArg) == 1) {
						insert(result, srealpath(entry->d_name, NULL));
					}
					break;
				case USAGE_DATE_A:
					if (timeCompare(&(statbuf.st_atim), (struct timespec*) searchArg) == 1) {
						insert(result, srealpath(entry->d_name, NULL));
					}
					break;
				case OWNER:
					uid = *((unsigned int*) searchArg);
					if (statbuf.st_uid == uid) {
						insert(result, srealpath(entry->d_name, NULL));
					}
					break;
				case GROUP:
					gid = *((unsigned int*) searchArg);
					if (statbuf.st_gid == gid) {
						insert(result, srealpath(entry->d_name, NULL));
					}
					break;
				case MODE:
					perms = *((unsigned long*) searchArg);
					unsigned int permsMask = statbuf.st_mode & (S_IRWXU | S_IRWXG | S_IRWXO);
					if (perms == permsMask) {
						insert(result, srealpath(entry->d_name, NULL));
					}
					break;
				default:
					insert(result, srealpath(entry->d_name, NULL));
					break;
			}
		}

	}
	schdir("..");
	//TODO check return
	sclosedir(dp);
	//TODO check return
	return result;
}

int timeCompare(struct timespec* candidate, struct timespec* searchTime) {
	if (candidate->tv_sec >= searchTime->tv_sec && candidate->tv_sec < searchTime->tv_sec + SECONDS_IN_DAY) {
		return 0;
	} else if (candidate->tv_sec < searchTime->tv_sec) {
		return -1;
	} else {
		return 1;
	}
}
