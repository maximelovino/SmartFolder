#include <stdlib.h>
#include <stdio.h>
#include "List.h"

int main() {
	List* l1 = initList();
	for (int i = 0; i < 10; i++) {
		char ch = 'a';
		char* string = malloc(2);
		string[0] = ch;
		string[1] = (char) (ch + (char) i);
		insert(l1, string);
	}

	List* l2 = initList();
	for (int i = 5; i < 12; i++) {
		char ch = 'a';
		char* string = malloc(2);
		string[0] = ch;
		string[1] = (char) (ch + (char) i);
		insert(l2, string);
	}
	printf("LOL l1 is happening\n");
	for (int i = 0; i < l1->size; i++) {
		printf("%s\n", get(l1, i));
	}
	printf("LOL l2 is happening\n");
	for (int i = 0; i < l2->size; i++) {
		printf("%s\n", get(l2, i));
	}

	printf("intersection\n");
	List* intersectList = listIntersect(l1, l2);
	for (int i = 0; i < intersectList->size; i++) {
		printf("%s\n", get(intersectList, i));
	}
	printf("union\n");
	List* unionList = listUnion(l1, l2);
	for (int i = 0; i < unionList->size; i++) {
		printf("%s\n", get(unionList, i));
	}
	printf("XOR\n");
	List* xorList = listXOR(l1, l2);
	for (int i = 0; i < xorList->size; i++) {
		printf("%s\n", get(xorList, i));
	}
	printf("complement\n");
	List* compList = listComplement(l1, l2);
	for (int i = 0; i < compList->size; i++) {
		printf("%s\n", get(compList, i));
	}
	return 0;
}
