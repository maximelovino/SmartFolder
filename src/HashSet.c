/**
 * @file HashSet.c
 * @brief Source file that contains the implementation for a HashSet data structure containing Strings
 *
 * @authors Maxime Lovino, Thomas Ibanez
 * @date January 25, 2017
 * @version 1.0
 */

#include "HashSet.h"

HashSet *initSet(int size) {
	HashSet *table = malloc(sizeof(HashSet));
	table->table = calloc(size, sizeof(char *));
	table->size = size;
	table->filled = 0;
	return table;
}

void expand(HashSet *table) {
	char **oldTable = table->table;
	table->table = calloc(2 * table->size, sizeof(char *));
	int size = table->size;
	table->size = 2 * table->size;
	table->filled = 0;
	for (int i = 0; i < size; i++) {
		if (oldTable[i] != NULL && strcmp(oldTable[i], " ") != 0) {
			put(table, oldTable[i]);;
		}
	}
}


void putAll(HashSet *table, List *list) {
	ListElement *le = list->head;
	while (le != NULL) {
		put(table, le->data);
		le = le->next;
	}
}

void put(HashSet *table, char *filePath) {
	if (table->filled >= 0.8 * table->size) {
		logMessage(0, "Expanding HashTable");
		expand(table);
	}

	int hashValue = hash(filePath) % table->size;
	//TODO There has to be a better way
	while (table->table[hashValue] != 0 ||
		   (table->table[hashValue] != 0 && strcmp(table->table[hashValue], " ") == 0)) {
		hashValue++;
		hashValue %= table->size;
	}
	table->table[hashValue] = malloc(strlen(filePath) + 1);
	strcpy(table->table[hashValue], filePath);
	table->filled++;
}

void removeFromSet(HashSet *table, char *filePath) {
	int index = searchInSet(table, filePath);
	if (index == -1) {
		return;
	}
	//TODO check if we can free and assign like that
	free(table->table[index]);
	//" " represents a freed cell
	table->table[index] = " ";
	table->filled--;
}

int contains(HashSet *table, char *filePath) {
	return searchInSet(table, filePath) != -1;
}

int searchInSet(HashSet *table, char *filePath) {
	int hashValue = hash(filePath) % table->size;
	while (table->table[hashValue] != NULL) {
		if (strcmp(table->table[hashValue], filePath) == 0) {
			return hashValue;
		}
		hashValue++;
		hashValue %= table->size;
	}
	return -1;
}

int hash(char *text) {
	int hashValue = 0;
	int i = 0;
	while (text[i] != 0) {
		hashValue += (i + 1) * text[i];
		i++;
	}
	return hashValue;
}

void deleteSet(HashSet **table) {
	for (int i = 0; i < (*table)->size; i++) {
		if ((*table)->table[i] != NULL && strcmp((*table)->table[i], " ") != 0) {
			free((*table)->table[i]);
		}
	}
	free((*table)->table);
	free((*table));
	*table = NULL;
}

void dumpSet(HashSet *table) {
	logMessage(0, "%s\n", "------- HashSet Dump -------");
	for (int i = 0; i < table->size; i++) {
		if (table->table[i] != 0 && strcmp(table->table[i], " ") != 0) {
			logMessage(0, "%s\n", table->table[i]);
		}
	}
	logMessage(0, "%s\n", "----- End of HashSet Dump -----");
}
