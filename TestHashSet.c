#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "HashSet.h"


int main(int argc, char const *argv[]) {
	HashTable* set = malloc(sizeof(HashTable));
	init(set,10);
	printf("%d\n", set->table[1]);
	for (size_t i = 0; i < 5; i++) {
		char* text = malloc(2*sizeof(char));
		text[0] = 'a';
		text[1] = (char) 'a'+i;
		insert(&set, text);
	}
	printf("%d/%d\n", set->filled, set->size);
	insert(&set, "ae");
	insert(&set, "ae");
	printf("%d/%d\n", set->filled, set->size);
	insert(&set, "ae");
	insert(&set, "ae");
	printf("%d/%d\n", set->filled, set->size);
	return 0;
}
