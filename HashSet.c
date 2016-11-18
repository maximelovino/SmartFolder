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
}
void expand(HashTable* table){

}

void insert(HashTable* table, char* filePath){
	if (table->filled > 0.8 * table->size) {
		expand(table);
	}
	int hash = hash(filePath) % table->size;
	while (table->table[hash] != NULL) {
		hash++;
		hash %= table->size;
	}
	table->table[hash] = malloc(strlen(filePath));
	strcpy(table->table[hash], filePath);
	table->filled++;
}
void remove(HashTable* table, char* filePath){
	int index = search(table, filePath);
	if (index == -1) {
		return;
	}
	free(table->table[index]);
	table->table[index] = NULL;
	table->filled--;
}
int contains(HashTable* table, char* filePath){
	return search(table, filePath) != -1;
}
int search(HashTable* table, char* filePath){
	int hash = hash(filePath) % table->size;
	while (table->table[hash] != NULL) {
		if (strcmp(table->table[hash], filePath) ==  0) {
			return hash;
		}
		hash++;
		hash %= table->size;
	}
	return -1;
}

int hash(char* text){
	int hash = 0;
	int i = 0;
	while (text[i] != 0) {
		hash += (i+1) * text[i];
		i++;
	}
	return hash;
}

void destroy(HashTable** table){
	
}
