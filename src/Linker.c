/**
 * @file Linker.c
 * @brief Source file that contains the implementation for the functions that will take care of the SmartFolder creation as well as the link creation
 *
 * @authors Maxime Lovino, Thomas Ibanez
 * @date January 25, 2017
 * @version 1.0
 */

#include "Linker.h"

int makeLink(char* pathToLink, char* destFolder) {
	char* fileName = sbasename(pathToLink);
	char linkName[1024];
	sprintf(linkName,"%s/%s",destFolder,fileName);
	while (saccess(linkName)){
		nextSuffix(linkName);
	}
	logMessage(0, "Attempting link creation: %s => %s", pathToLink, linkName);
	return ssymlink(pathToLink, linkName);
}

int removeLink(char* pathOfFile, char* linkFolder){
	char* base = sbasename(pathOfFile);

	char linkName[1024];
	sprintf(linkName, "%s/%s",linkFolder,base);
	logMessage(0, "Trying to remove %s", linkName);

	while (srealpath(linkName, NULL) && !(saccess(linkName) && (strcmp(srealpath(linkName, NULL),pathOfFile) == 0))){
		nextSuffix(linkName);
	}
	logMessage(0, "Found the link %s", linkName);
	sunlink(linkName);
	return 0;
}

void nextSuffix(char* name){
	char* firstPar = strrchr(name,'(');
	if (firstPar){
		char suffix[40];
		firstPar++;
		strcpy(suffix,firstPar);
		suffix[strlen(suffix)-1] = 0;
		int suffixValue = atoi(suffix);
		suffixValue++;
		firstPar--;
		sprintf(firstPar,"(%i)",suffixValue);
	}else{
		strcat(name,"(1)");
	}
}

int makeFolder(char* path, List* files) {
	int r = smkdir(path);
	if (!r) {
		if (errno == EEXIST) {
			logMessage(3, "Your SmartFolder directory exists already");
			return 1;
		}
		return -1;
	}
	logMessage(0, "SmartFolder created %s", path);
	ListElement* e = files->head;
	while (e != NULL) {
		if (makeLink(e->data, path)) {
			logMessage(0, "Link created for %s", e->data);
			e = e->next;
		} else {
			return -1;
		}
	}

	return 0;
}

int removeFolder(char* path) {
	DIR* dp = sopendir(path);
	if (dp == NULL) {
		logMessage(3, "Couldn't open directory %s\n", path);
		return -1;
	}

	if(!schdir(path)){
		logMessage(2, "Couldn't move to dir %s", path);
		return 0;
	}

	struct dirent* entry;
	struct stat statbuf;
	while ((entry = sreaddir(dp)) != NULL) {
		if(!slstat(entry->d_name, &statbuf)){
			logMessage(2,"Couldn't stat %s",entry->d_name);
		}
		if (sS_ISLNK(statbuf.st_mode) || sS_ISREG(statbuf.st_mode)) {
			logMessage(0, "Removing file %s", entry->d_name);
			if (!sunlink(entry->d_name)) {
				logMessage(3, "Couldn't delete file %s", entry->d_name);
				return -1;
			}
		}
	}
	if(!sclosedir(dp)){
		logMessage(2, "Couldn't close dir %s", path);
	}
	logMessage(0, "Removing directory %s", path);
	return srmdir(path);
}
