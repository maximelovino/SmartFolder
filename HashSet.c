#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include "HashSet.h"

void init(HashTable* table, int size){
	if (table == NULL) {
		return;
	}
	table->table = malloc(size*sizeof(char*));
	table->size = size;
	table->filled = 0;
}

void expand(HashTable** table){
	HashTable* newTable = malloc(sizeof(HashTable));

	init(newTable, (*table)->size * 2);

	for (int i = 0; i < (*table)->size; i++) {
		if ((*table)->table[i] != NULL && strcmp((*table)->table[i], " ") != 0) {
			insert(&newTable, (*table)->table[i]);
		}
	}
	destroy(table);
	*table = newTable;
}

void insert(HashTable** table, char* filePath){
	if ((*table)->filled > 0.8 * (*table)->size) {
		expand(table);
	}
	int hashValue = hash(filePath) % (*table)->size;
	while ((*table)->table[hashValue] != NULL || strcmp((*table)->table[hashValue], " ") == 0) {
		hashValue++;
		hashValue %= (*table)->size;
	}
	(*table)->table[hashValue] = malloc(strlen(filePath));
	strcpy((*table)->table[hashValue], filePath);
	(*table)->filled++;
}
void removeFromTable(HashTable* table, char* filePath){
	int index = search(table, filePath);
	if (index == -1) {
		return;
	}
	//TODO check if we can free and assign like that
	free(table->table[index]);
	//" " represents a freed cell
	table->table[index] = " ";
	table->filled--;
}
int contains(HashTable* table, char* filePath){
	return search(table, filePath) != -1;
}
int search(HashTable* table, char* filePath){
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

void destroy(HashTable** table){
	for (int i = 0; i < (*table)->size; i++) {
		if ((*table)->table[i] != NULL && strcmp((*table)->table[i]," ") != 0) {
			free((*table)->table[i]);
		}
	}
	free((*table)->table);
	free((*table));
	*table = NULL;
}
