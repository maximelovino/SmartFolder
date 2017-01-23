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
		//Do the deletion and _exit the program
		_exit(0);
	}
}
