#include "Search.h"

List* searchDirectory(char* rootDir, searchType type, void* searchArg) {
	List* result = initList();

	DIR* dp;
	struct dirent* entry;
	struct stat statbuf;

	if((dp = opendir(rootDir)) == NULL) {
		logMessage(3, "Couldn't open directory %s\n", rootDir);
		return NULL;
	}
	chdir(rootDir);
	while ((entry = readdir(dp)) != NULL) {
		lstat(entry->d_name, &statbuf);
		if (S_ISLNK(statbuf.st_mode)) continue;
		if(S_ISDIR(statbuf.st_mode)) {
			if(strcmp(".", entry->d_name) == 0 || strcmp("..", entry->d_name) == 0) {
				continue;
			}
			List* recursiveResult = searchDirectory(entry->d_name, type, searchArg);
			List* r = listUnion(result, recursiveResult);
			deleteList(result);
			deleteList(recursiveResult);
			result = r;
		} else {

			int size;
			char* searchString;
			uid_t uid;
			gid_t gid;
			int permissions;

			switch (type) {
				case NAME:
					searchString = (char*) searchArg;
					if (strstr(entry->d_name, searchString)) {
						insert(result, realpath(entry->d_name, NULL));
					}
					break;
				case SIZE_BIGGER:
					size = *((int*) searchArg);
					if (statbuf.st_size > size) {
						insert(result, realpath(entry->d_name, NULL));
					}
					break;
				case SIZE_SMALLER:
					size = *((int*) searchArg);
					if (statbuf.st_size < size) {
						insert(result, realpath(entry->d_name, NULL));
					}
					break;
				case SIZE_EQUAL:
					size = *((int*) searchArg);
					if (statbuf.st_size == size) {
						insert(result, realpath(entry->d_name, NULL));
					}
					break;

				case STATUS_DATE_B:
                    if(timeCompare(&(statbuf.st_ctim), (struct timespec*)searchArg) == -1) {
                        insert(result, realpath(entry->d_name, NULL));
                    }
                    break;
				case MODIF_DATE_B:
                    if(timeCompare(&(statbuf.st_mtim), (struct timespec*)searchArg) == -1) {
                        insert(result, realpath(entry->d_name, NULL));
                    }
                    break;
				case USAGE_DATE_B:
                    if(timeCompare(&(statbuf.st_atim), (struct timespec*)searchArg) == -1) {
                        insert(result, realpath(entry->d_name, NULL));
                    }
					break;

				case STATUS_DATE_E:
                    if(timeCompare(&(statbuf.st_ctim), (struct timespec*)searchArg) == 0) {
                        insert(result, realpath(entry->d_name, NULL));
                    }
                    break;
				case MODIF_DATE_E:
                    if(timeCompare(&(statbuf.st_mtim), (struct timespec*)searchArg) == 0) {
                        insert(result, realpath(entry->d_name, NULL));
                    }
                    break;
				case USAGE_DATE_E:
                    if(timeCompare(&(statbuf.st_atim), (struct timespec*)searchArg) == 0) {
                        insert(result, realpath(entry->d_name, NULL));
                    }
					break;

				case STATUS_DATE_A:
                    if(timeCompare(&(statbuf.st_ctim), (struct timespec*)searchArg) == 1) {
                        insert(result, realpath(entry->d_name, NULL));
                    }
					break;
				case MODIF_DATE_A:
                    if(timeCompare(&(statbuf.st_mtim), (struct timespec*)searchArg) == 1) {
                        insert(result, realpath(entry->d_name, NULL));
                    }
					break;
				case USAGE_DATE_A:
                    if(timeCompare(&(statbuf.st_atim), (struct timespec*)searchArg) == 1) {
                        insert(result, realpath(entry->d_name, NULL));
                    }
					break;
				case OWNER:
					uid = *((uid_t*) searchArg);
					if (statbuf.st_uid == uid) {
						insert(result, realpath(entry->d_name, NULL));
					}
					break;
				case GROUP:
					gid = *((gid_t*) searchArg);
					if (statbuf.st_gid == gid) {
						insert(result, realpath(entry->d_name, NULL));
					}
					break;
				case MODE:
					permissions = statbuf.st_mode & (S_IRWXU | S_IRWXG | S_IRWXO);
					//Here we take what's EQUAL to the permission we ask for
          if(permissions == (*(int*)searchArg)) {
              insert(result, realpath(entry->d_name, NULL));
          }
					break;
				default:
					insert(result, realpath(entry->d_name, NULL));
					break;
			}
		}
	}
	chdir("..");
	closedir(dp);

	return result;
}

inline int timeCompare(struct timespec* t1, struct timespec* t2) {
    return t1->tv_sec < t2->tv_sec ? -1 : t1->tv_sec == t2->tv_sec ? 0 : 1;
}
