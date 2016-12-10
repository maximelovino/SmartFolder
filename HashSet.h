#ifndef _HASH_SET_
#define _HASH_SET_

typedef struct HashSet {
	char** table;
	int size;
	int filled;
} HashSet;


void initMap(HashSet* table, int size);
void expand(HashSet** table);
void put(HashSet** table, char* filePath);
void removeFromTable(HashSet* table, char* filePath);
int contains(HashSet* table, char* filePath);
int searchInMap(HashSet* table, char* filePath);
int hash(char* text);
void deleteTable(HashSet** table);

#endif /* end of include guard: _HASH_SET_ */
