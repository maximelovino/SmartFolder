#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include "HashSet.h"

void initSet(HashSet* table, int size){
	if (table == NULL) {
		return;
	}
	table->table = calloc(size, sizeof(char*));
	table->size = size;
	table->filled = 0;
}

void expand(HashSet** table){
	HashSet* newTable = malloc(sizeof(HashSet));

	initSet(newTable, (*table)->size * 2);

	for (int i = 0; i < (*table)->size; i++) {
		if ((*table)->table[i] != NULL && strcmp((*table)->table[i], " ") != 0) {
			put(&newTable, (*table)->table[i]);
		}
	}
	deleteSet(table);
	*table = newTable;
}

void put(HashSet** table, char* filePath){
	if ((*table)->filled >= 0.8 * (*table)->size) {
		//printf("We need to expand\n");
		expand(table);
	}

	int hashValue = hash(filePath) % (*table)->size;
	//TODO There has to be a better way
	while ((*table)->table[hashValue] != 0 || ((*table)->table[hashValue] != 0 && strcmp((*table)->table[hashValue], " ") == 0)) {
		hashValue++;
		hashValue %= (*table)->size;
	}
	(*table)->table[hashValue] = malloc(strlen(filePath));
	strcpy((*table)->table[hashValue], filePath);
	(*table)->filled++;
}
void removeFromSet(HashSet* table, char* filePath){
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

int contains(HashSet* table, char* filePath){
	return searchInSet(table, filePath) != -1;
}

int searchInSet(HashSet* table, char* filePath){
	int hashValue = hash(filePath) % table->size;
	while (table->table[hashValue] != NULL) {
		if (strcmp(table->table[hashValue], filePath) ==  0) {
			return hashValue;
		}
		hashValue++;
		hashValue %= table->size;
	}
	return -1;
}

int hash(char* text){
	int hashValue = 0;
	int i = 0;
	while (text[i] != 0) {
		hashValue += (i+1) * text[i];
		i++;
	}
	return hashValue;
}

void deleteSet(HashSet** table){
	for (int i = 0; i < (*table)->size; i++) {
		if ((*table)->table[i] != NULL && strcmp((*table)->table[i]," ") != 0) {
			free((*table)->table[i]);
		}
	}
	free((*table)->table);
	free((*table));
	*table = NULL;
}

void dumpSet(HashSet* table) {
	logMessage(0, "%s\n", "------- HashSet Dump -------");
	for (int i = 0; i < table->size; i++) {
		if(table->table[i] != 0 && strcmp(table->table[i], " ") != 0) {
			logMessage(0, "%s\n", table->table[i]);
		}
	}
	logMessage(0, "%s\n", "----- End of HashSet Dump -----");
}
