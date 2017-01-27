/**
 * @file Daemon.c
 * @brief Source file that contains the implementation for our background process computation
 *
 * @authors Maxime Lovino, Thomas Ibanez
 * @date January 25, 2017
 * @version 1.0
 */

#include "Daemon.h"

void incrementalSearch(char** expression, int exprLen, char* searchFolder, char* smartFolder, HashSet* files) {
	logMessage(0, "Deamon Started");
	dumpSet(files);

	while (1) {
		List* result = initList();
		evaluateAndSearch(expression, exprLen, searchFolder, &result);

		ListElement* tmp = result->head;
		while (tmp) {
			if (!contains(files, tmp->data)) {
				logMessage(0, "New file found: %s", tmp->data);
				put(files, tmp->data);
				makeLink(tmp->data, smartFolder);
				//dumpSet(files);
			}
			tmp = tmp->next;
		}
		for (int i = 0; i < files->size; i++) {
			if (files->table[i] != 0 && strcmp(files->table[i], " ") != 0) {
				if (searchInList(result, files->table[i])==-1){
					logMessage(0, "The file %s doesn't match anymore", files->table[i]);
					//remove from set, and call function to remove link
					removeFromSet(files, files->table[i]);
				}
			}
		}
		deleteList(result);
		sleep(5);
	}

}