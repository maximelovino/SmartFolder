#include "SysFile.h"

int createSysFile(int pid, char *smartFolder) {
	char path[70];
  	char pathPIDFile[70];
	char pidval[40];
	sprintf(pidval,"%d",pid);
	strcpy(pathPIDFile, SYSFILE_PATH);
	strcat(pathPIDFile,pidval);
	char *name = strrchr(smartFolder, '/');
	strcpy(path, SYSFILE_PATH);
	strcat(path, name + 1);
	logMessage(0, path);
	if (!fileExists(path) && !fileExists(pathPIDFile)) {
		FILE* pidFp = touch(pathPIDFile);
		fprintf(pidFp, smartFolder);
		FILE *fp = touch(path);
		fprintf(fp, "%d", pid);
		fclose(fp);
		fclose(pidFp);
		return 1;
	}
	return 0;
}
