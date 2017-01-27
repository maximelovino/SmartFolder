/**
 * @file SysFile.c
 * @brief Source file that contains the implementation for the writing of files about our folder execution
 *
 * @authors Maxime Lovino, Thomas Ibanez
 * @date January 25, 2017
 * @version 1.0
 */

#include "SysFile.h"

int createSysFile(int pid, char* smartFolder) {
	char path[70];
	char pathPIDFile[70];
	char pidval[40];
	sprintf(pidval, "%d", pid);
	strcpy(pathPIDFile, SYSFILE_PATH);
	strcat(pathPIDFile, pidval);
	char* name = strrchr(smartFolder, '/');
	strcpy(path, SYSFILE_PATH);
	strcat(path, name + 1);
	logMessage(0, path);
	if (!saccess(path) && !saccess(pathPIDFile)) {
		FILE* pidFp = stouch(pathPIDFile);
		fprintf(pidFp, "%s", smartFolder);
		FILE* fp = stouch(path);
		fprintf(fp, "%d", pid);
		fclose(fp);
		fclose(pidFp);
		return 0;
	}
	return 1;
}


int getPID(const char* folderName) {
	char fileToOpen[512];
	sprintf(fileToOpen, "%s%s", SYSFILE_PATH, folderName);
	FILE* fp = fopen(fileToOpen, "r");
	if (!fp) {
		return -1;
	}
	char* line = NULL;
	size_t size = 0;
	int pidToKill = -1;
	if (getline(&line, &size, fp) != -1) {
		pidToKill = atoi(line);
		logMessage(0, "The folder is at pid %d", pidToKill);
	}
	if (line) {
		free(line);
	}
	fclose(fp);
	if (!sunlink(fileToOpen)) {
		logMessage(2, "Couldn't delete file %s", fileToOpen);
	} else {
		logMessage(0, "File deleted %s", fileToOpen);
	}
	return pidToKill;
}

char* getFolderPath(int pid) {
	char fileToOpen[512];
	sprintf(fileToOpen, "%s%i", SYSFILE_PATH, pid);
	FILE* fp = fopen(fileToOpen, "r");
	if (!fp) {
		return NULL;
	}
	char* line = NULL;
	size_t size = 0;
	if (getline(&line, &size, fp) != -1) {
		fclose(fp);
		if (!sunlink(fileToOpen)) {
			logMessage(2, "Couldn't delete file %s", fileToOpen);
		} else {
			logMessage(0, "File deleted %s", fileToOpen);
		}
		return line;
	} else {
		return NULL;
	}
}