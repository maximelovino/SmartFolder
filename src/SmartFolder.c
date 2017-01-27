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
#include <signal.h>

/**
 * Main function of our program, this will run when the program is called
 * @param argc The number of arguments passed to the program
 * @param argv An array of the arguments passed to the program
 * @return An exit code, 0 if everything went well
 */
int main(int argc, char const* argv[]) {
	if (argc > 3) {
		if (isValidPath(argv[1]) && isValidPath(argv[2])) {
			char smartFolderPath[strlen(argv[1]) + 1];
			char* searchPath;
			strcpy(smartFolderPath, argv[1]);
			searchPath = srealpath(argv[2], NULL);
			logMessage(1, "Search path %s", searchPath);
			logMessage(1, "SmartFolder %s", smartFolderPath);
			List* files = initList();
			logMessage(1, "Launching search");
			int k = evaluateAndSearch(&(argv[3]), argc - 3, searchPath, &files);
			if (k == -1) {
				logMessage(3, "Error while searching");
				return 1;
			}
			logMessage(1, "Search results");
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
		int pidToKill = getPID(argv[2]);
		if (pidToKill == -1) {
			logMessage(3, "Couldn't find file with pid for the folder %s", argv[2]);
			_exit(1);
		}
		kill(pidToKill, SIGKILL);

		char* folderPath = getFolderPath(pidToKill);
		if (!folderPath) {
			logMessage(3, "Couldn't find file with path for the folder %s", argv[2]);
			_exit(1);
		}
		logMessage(0, "Starting removal of folder %s", folderPath);
		if (removeFolder(folderPath)) {
			logMessage(1, "SmartFolder %s deleted", argv[2]);
		} else {
			logMessage(3, "SmartFolder wasn't removed");
		}
	} else {
		printf("Usage:\nSmartFolder <LinkDirectory> <SearchDirectory> [searchExpression]\nSmartFolder -d <RunningFolder>\n");
	}

	return 0;
}
