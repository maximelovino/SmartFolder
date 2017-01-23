#include "Deamon.h"

void incrementalSearch(char **expression, int exprLen, char *searchFolder, char *smartFolder, HashSet *files) {
	logMessage(0, "Deamon Started");
	struct sigaction act;
	act.sa_handler = handler;
	act.sa_flags = 0;
	sigemptyset(&act.sa_mask);
	if (sigaction(SIGINT, &act, NULL) == -1) {
		perror("sigaction");
		exit(EXIT_FAILURE);
	}
	dumpSet(files);

	while (1) {
		List *result = initList();
		evaluateAndSearch(expression, exprLen, searchFolder, &result);

		ListElement *tmp = result->head;
		while (tmp) {
			if (!contains(files, tmp->data)) {
				logMessage(0, "New file found: %s", tmp->data);
				put(files, tmp->data);
				makeLink(tmp->data, smartFolder);
				//dumpSet(files);
			}
			tmp = tmp->next;
		}

		deleteList(result);
		sleep(5);
	}

}


void handler(int signum) {
	if (signum == SIGINT){
		char pathTmpFile[1024] = "/tmp/";
		char pidVal[64];
		sprintf(pidVal,"%d",getpid());
		strcat(pathTmpFile, pidVal);
		logMessage(0, "The file to open is %s", pathTmpFile);
		FILE *tmpFile = fopen(pathTmpFile, "r");
		if (!tmpFile) {
			logMessage(3, "A smartFolder with this process doesn't exist");
			_exit(1);
		}
		char* line = NULL;
		unsigned int size = 0;
		char pathOfFolder[1024];
		if (getline(&line,&size,tmpFile)!=-1){
			strcpy(pathOfFolder,line);
			logMessage(0, "The path is %s", pathOfFolder);
		}

		if(line){
			free(line);
		}
		fclose(tmpFile);
		_exit(0);
	}
}
