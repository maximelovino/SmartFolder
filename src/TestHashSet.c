#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "HashSet.h"


int main() {
	HashSet* set = initSet(10);
	for (size_t i = 0; i < 5; i++) {
		char* text = malloc(2 * sizeof(char));
		text[0] = 'a';
		text[1] = (char) 'a' + i;
		put(set, text);
	}
	printf("%d/%d\n", set->filled, set->size);
	put(set, "ae");
	put(set, "ae");
	printf("%d/%d\n", set->filled, set->size);
	put(set, "ae");
	put(set, "ae");
	printf("%d/%d\n", set->filled, set->size);
	dumpSet(set);
	return 0;
}
