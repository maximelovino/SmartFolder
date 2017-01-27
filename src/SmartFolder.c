/**
 * @file SmartFolder.c
 * @brief Main entry point of our program
 *
 * @authors Maxime Lovino, Thomas Ibanez
 * @date January 25, 2017
 * @version 1.0
 */

#include "Syscall.h"
#include "Parser.h"
#include "Linker.h"
#include "Daemon.h"
#include "SysFile.h"

/**
 * Main function of our program, this will run when the program is called
 * @param argc The number of arguments passed to the program
 * @param argv An array of the arguments passed to the program
 * @return An exit code, 0 if everything went well
 */
int main(int argc, char const* argv[]) {
	if (argc > 3) {
		if (isValidPath(argv[1]) && isValidPath(argv[2])) {
			char smartFolderPath[strlen(argv[1])+1];
			char* searchPath;
			strcpy(smartFolderPath, argv[1]);
			searchPath = srealpath(argv[2], NULL);
			logMessage(0, "We search in %s => %s", argv[2], searchPath);
			logMessage(0, "We put in %s => %s", argv[1], smartFolderPath);
			List* files = initList();
			int k = evaluateAndSearch(&(argv[3]), argc - 3, searchPath, &files);
			if (k == -1) {
				logMessage(3, "Error while searching");
				return 1;
			}
			dumpList(files);

			if (makeFolder(smartFolderPath, files) == 0) {
				int pid = sfork();
				if (pid == 0) {
					//the optimal size of a hashset is n²
					HashSet* set = initSet(files->size * files->size);
					putAll(set, files);
					incrementalSearch(&(argv[3]), argc - 3, searchPath, smartFolderPath, set, files);
				} else if (pid > 0) {
					logMessage(0, "The child is at process %d", pid);
					if (createSysFile(pid, smartFolderPath)) {
						logMessage(3, "A smartFolder with this name already exists");
					}
				}
			} else {
				logMessage(3, "Couldn't create SmartFolder");
			}
		}
	} else if (argc == 3 && strcmp(argv[1], "-d") == 0) {
		//TODO modularize this code
		char pathTmpFile[1024];
		strcpy(pathTmpFile, SYSFILE_PATH);
		strcat(pathTmpFile, argv[2]);
		logMessage(0, "The file to open is %s", pathTmpFile);
		FILE* tmpFile = fopen(pathTmpFile, "r");
		if (!tmpFile) {
			logMessage(3, "A smartFolder with this name doesn't exist");
			_exit(1);
		}
		char* line = NULL;
	 	size_t size = 0;
		int pidToKill = 0;
		if (getline(&line, &size, tmpFile) != -1) {
			pidToKill = atoi(line);
			logMessage(0, "The folder is at pid %d", pidToKill);
			kill(pidToKill, SIGKILL);
		}

		fclose(tmpFile);
		if (!sunlink(pathTmpFile)) {
			logMessage(2, "Couldn't delete file %s", pathTmpFile);
			_exit(1);
		} else {
			logMessage(0, "File deleted %s", pathTmpFile);
		}
		char secondFile[1024];
		strcpy(secondFile, SYSFILE_PATH);
		strcat(secondFile, line);
		logMessage(0, "Second file is %s", secondFile);
		FILE* secondFP = fopen(secondFile, "r");
		if (getline(&line, &size, secondFP) != -1) {
			logMessage(0, "Starting removal of folder %s", line);
			removeFolder(line);
			//TODO test this return
		}
		fclose(secondFP);
		if (!sunlink(secondFile)) {
			logMessage(2, "Couldn't delete file %s", secondFile);
			_exit(1);
		} else {
			logMessage(0, "File deleted %s", secondFile);
		}

		if (line) {
			free(line);
		}
	} else {
		printf("Usage:\nSmartFolder <LinkDirectory> <SearchDirectory> [searchExpression]\nSmartFolder -d <RunningFolder>\n");
	}

	return 0;
}
