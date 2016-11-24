#ifndef _HASH_SET_
#define _HASH_SET_

typedef struct HashTable {
	char** table;
	int size;
	int filled;
} HashTable;


void init(HashTable* table, int size);
void expand(HashTable** table);
void insert(HashTable** table, char* filePath);
void removeFromTable(HashTable* table, char* filePath);
int contains(HashTable* table, char* filePath);
int search(HashTable* table, char* filePath);
int hash(char* text);
void destroy(HashTable** table);

#endif /* end of include guard: _HASH_SET_ */
