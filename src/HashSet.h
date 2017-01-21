#ifndef _HASH_SET_
#define _HASH_SET_
#include "Logger.h"
#include "List.h"

typedef struct HashSet {
	char** table;
	int size;
	int filled;
} HashSet;


HashSet* initSet(int size);
void putAll(HashSet* table, List* list);
void expand(HashSet* table);
void put(HashSet* table, char* filePath);
void removeFromSet(HashSet* table, char* filePath);
int contains(HashSet* table, char* filePath);
int searchInSet(HashSet* table, char* filePath);
int hash(char* text);
void deleteSet(HashSet** table);
void dumpSet(HashSet* table);

#endif /* end of include guard: _HASH_SET_ */
