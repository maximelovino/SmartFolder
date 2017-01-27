/**
 * @file Daemon.c
 * @brief Source file that contains the implementation for our background process computation
 *
 * @authors Maxime Lovino, Thomas Ibanez
 * @date January 25, 2017
 * @version 1.0
 */

#include "Daemon.h"

void incrementalSearch(const char** expression, int exprLen, char* searchFolder, char* smartFolder, HashSet* files, List* filesList) {
	logMessage(0, "Daemon Started");
	dumpSet(files);

	while (1) {

		List* result = initList();
		evaluateAndSearch(expression, exprLen, searchFolder, &result);

		HashSet* resultSet = initSet(result->size*result->size);
		putAll(resultSet,result);

		ListElement* tmp = result->head;
		while (tmp) {
			if (!contains(files, tmp->data)) {
				logMessage(0, "New file found: %s", tmp->data);
				put(files, tmp->data);
				insert(filesList,tmp->data);
				if(!makeLink(tmp->data, smartFolder)){
					logMessage(2,"Couldn't create link for %s", tmp->data);
				}
			}
			tmp = tmp->next;
		}

		tmp = filesList->head;
		while(tmp){
			if(!contains(resultSet,tmp->data)){
				logMessage(1, "The file %s doesn't exist anymore", tmp->data);
				removeLink(tmp->data,smartFolder);
				removeObject(filesList,tmp->data);
				removeFromSet(files, tmp->data);

			}
			tmp = tmp->next;
		}
		deleteSet(&resultSet);
		deleteList(result);
		sleep(5);
	}

}
