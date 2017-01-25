/**
 * @file Daemon.c
 * @brief Source file that contains the implementation for our background process computation
 *
 * @authors Maxime Lovino, Thomas Ibanez
 * @date January 25, 2017
 * @version 1.0
 */

#include "Daemon.h"

void incrementalSearch(char **expression, int exprLen, char *searchFolder, char *smartFolder, HashSet *files) {
	logMessage(0, "Deamon Started");
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