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
	if (!saccess(path) && !saccess(pathPIDFile)) {
		FILE* pidFp = stouch(pathPIDFile);
		fprintf(pidFp, "%s", smartFolder);
		FILE *fp = stouch(path);
		fprintf(fp, "%d", pid);
		fclose(fp);
		fclose(pidFp);
		return 1;
	}
	return 0;
}
