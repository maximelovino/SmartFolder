/**
 * @file Linker.c
 * @brief Source file that contains the implementation for the functions that will take care of the SmartFolder creation as well as the link creation
 *
 * @authors Maxime Lovino, Thomas Ibanez
 * @date January 25, 2017
 * @version 1.0
 */

#include "Linker.h"

int makeLink(char *pathToLink, char *destFolder) {
	char *fileName = sbasename(pathToLink);
	char linkName[1024];
	strcpy(linkName, destFolder);
	strcat(linkName, "/");
	strcat(linkName, fileName);
	logMessage(0, "Attempting link creation: %s => %s", pathToLink, linkName);
	return ssymlink(pathToLink, linkName);
}

int makeFolder(char *path, List *files) {
	int r = smkdir(path);
	if (r == -1) {
		if (errno == EEXIST) {
			logMessage(3, "Your SmartFolder directory exists already");
			return 1;
		}
		return -1;
	}
	logMessage(0, "SmartFolder created %s", path);
	ListElement *e = files->head;
	while (e != NULL) {
		if (makeLink(e->data, path) == 0) {
			logMessage(0, "Link created for %s", e->data);
			e = e->next;
		} else {
			return -1;
		}
	}

	return 0;
}

int removeFolder(char *path) {
	DIR *dp = sopendir(path);
	if (dp == NULL) {
		logMessage(3, "Couldn't open directory %s\n", path);
		return -1;
	}

	schdir(path);
	struct dirent *entry;
	struct stat statbuf;
	while ((entry = sreaddir(dp)) != NULL) {
		slstat(entry->d_name, &statbuf);
		if (sS_ISLNK(statbuf.st_mode) || sS_ISREG(statbuf.st_mode)) {
			logMessage(0, "Removing file %s", entry->d_name);
			if (sunlink(entry->d_name) == -1) {
				logMessage(3, "Couldn't delete file %s", entry->d_name);
				return -1;
			}
		}
	}
	sclosedir(dp);
	logMessage(0, "Removing directory %s", path);
	return srmdir(path);
}
