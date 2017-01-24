#include "Linker.h"

int makeLink(char *pathToLink, char *destFolder) {
	char *fileName = nameOfFile(pathToLink);
	char linkName[1024];
	strcpy(linkName, destFolder);
	strcat(linkName, "/");
	strcat(linkName, fileName);
	logMessage(0, "linkname: %s pathToLink: %s destFolder: %s", linkName, pathToLink, destFolder);
	return symbolicLink(pathToLink, linkName);
}

int makeFolder(char *path, List *files) {
	logMessage(0, "Dir we're creating is %s", path);
	int r = makeDir(path);
	if (r == -1) {
		if (errno == EEXIST) {
			logMessage(3, "Your SmartFolder directory exists already");
			return 1;
		}
		return -1;
	}

	ListElement *e = files->head;
	while (e != NULL) {
		if (makeLink(e->data, path) == 0) {
			e = e->next;
		} else {
			return -1;
		}
	}

	return 0;
}

int removeFolder(char *path) {
	DIR *dp = opendir(path);
	if (dp == NULL) {
		logMessage(3, "Couldn't open directory %s\n", path);
		return -1;
	}
	chdir(path);
	struct dirent *entry;
	struct stat statbuf;
	while ((entry = readdir(dp)) != NULL) {
		logMessage(0, "We found this %s", entry->d_name);
		lstat(entry->d_name, &statbuf);
		if (S_ISLNK(statbuf.st_mode) || S_ISREG(statbuf.st_mode)) {
			logMessage(0, "Removing %s", entry->d_name);
			removeFile(entry->d_name);
		}
	}
	closedir(dp);
	logMessage(0, "Removing directory %s", path);
	return removeDirectory(path);
}
