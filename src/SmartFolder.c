#include "Syscall.h"
#include "Parser.h"
#include "List.h"
#include "Linker.h"
#include "Deamon.h"
#include "HashSet.h"
#include "SysFile.h"
#include <stdio.h>
#include <signal.h>
#include <limits.h>
#include <stdlib.h>

int main(int argc, char const *argv[]) {
	//Parse parameters
	if (argc > 3) {
		if (isValidPath(argv[1]) && isValidPath(argv[2])) {
			char* smartFolderPath[PATH_MAX+1];
			char* searchPath[PATH_MAX+1];
		  realpath(argv[1], smartFolderPath);
		  realpath(argv[2], searchPath);
			List set;
			List *files = &set;
			initList(files, 100);
			int k = evaluateAndSearch(&(argv[3]), argc - 3, searchPath, &files);
			if (k == -1) {
				logMessage(2, "Error while checking");
			}
			dumpList(files);

			if (makeFolder(smartFolderPath, files) == 0) {
				int pid = processFork();
				if (pid == 0) {
					//the optimal size of a hashset is n²
					HashSet *set = initSet(files->size * files->size);
					putAll(set, files);
					incrementalSearch(&(argv[3]), argc - 3, searchPath, smartFolderPath, set);
				} else if (pid > 0) {
					logMessage(0, "The child is at process %d", pid);
					if (!createSysFile(pid, smartFolderPath)) {
						logMessage(3, "A smartFolder with this name already exists");
					}
				}
			} else {
				logMessage(3, "Couldn't create SmartFolder");
			}
		}
	} else if (argc == 3 && strcmp(argv[1], "-d") == 0) {
		//delete folder (bonus feature)
		char pathTmpFile[1024];
		strcpy(pathTmpFile,SYSFILE_PATH);
		strcat(pathTmpFile, argv[2]);
		logMessage(0, "The file to open is %s", pathTmpFile);
		FILE *tmpFile = fopen(pathTmpFile, "r");
		if (!tmpFile) {
			logMessage(3, "A smartFolder with this name doesn't exist");
			_exit(1);
		}
		char* line = NULL;
		unsigned int size = 0;
		int pidToKill = 0;
		if (getline(&line,&size,tmpFile)!=-1){
			pidToKill = atoi(line);
			logMessage(0, "The folder is at pid %d", pidToKill);
			kill(pidToKill,SIGKILL);
		}

		fclose(tmpFile);
		if (removeFile(pathTmpFile) == -1){
			logMessage(2,"Couldn't delete file %s", pathTmpFile);
			_exit(1);
		}else{
			logMessage(0, "File deleted %s", pathTmpFile);
		}
		char secondFile[1024];
		strcpy(secondFile,SYSFILE_PATH);
		strcat(secondFile,line);
		if (removeFile(secondFile) == -1){
			logMessage(2,"Couldn't delete file %s", secondFile);
			_exit(1);
		}else{
			logMessage(0, "File deleted %s", secondFile);
		}
		if(line){
			free(line);
		}
	} else {
		printf("Usage:\nSmartFolder <LinkDirectory> <SearchDirectory> [searchExpression]\nSmartFolder -d <RunningFolder>\n");
	}

	return 0;
}
