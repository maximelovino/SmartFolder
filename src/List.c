/**
 * @file List.c
 * @brief Source file that contains the implementation for a simple linked List data structure containing Strings
 *
 * @authors Maxime Lovino, Thomas Ibanez
 * @date January 25, 2017
 * @version 1.0
 */

#include "List.h"

List* initList() {
	List* l = malloc(sizeof(List));
	l->head = NULL;
	l->size = 0;
	return l;
}

void insert(List* l, char* element) {
	ListElement* le = malloc(sizeof(ListElement));
	le->data = element;
	le->next = l->head;
	l->head = le;
	l->size++;
}

void removeIndex(List* l, int idx) {
	ListElement* le = l->head;
	if (idx == 0) {
		l->head = l->head->next;
		l->size--;
		return;
	}

	for (int i = 0; i < idx - 1; i++) {
		le = le->next;
	}
	le->next = le->next->next;
	l->size--;
}

void removeObject(List* l, char* element) {
	int idx = searchInList(l, element);
	if (idx != -1) {
		removeIndex(l, idx);
	}
}

int searchInList(List* l, char* element) {
	ListElement* le = l->head;
	int i = 0;
	while (le != NULL) {
		if (strcmp(le->data, element) == 0)
			return i;
		le = le->next;
		i++;
	}
	return -1;
}

char* get(List* l, int idx) {
	ListElement* le = l->head;
	for (int i = 0; i < idx; i++) {
		le = le->next;
	}
	return le->data;
}

List* listUnion(List* l1, List* l2) {
	List* newList = initList();
	ListElement* le = l1->head;
	for (int i = 0; i < l1->size; i++) {
		insert(newList, le->data);
		le = le->next;
	}
	le = l2->head;
	for (int i = 0; i < l2->size; i++) {
		if (searchInList(newList, le->data) == -1) {
			insert(newList, le->data);
		}
		le = le->next;
	}
	return newList;
}

List* listIntersect(List* l1, List* l2) {
	List* newList = initList();
	ListElement* le = l1->head;
	for (int i = 0; i < l1->size; i++) {
		if (searchInList(l2, le->data) != -1) {
			insert(newList, le->data);
		}
		le = le->next;
	}
	return newList;
}

List* listXOR(List* l1, List* l2) {
	List* newList = initList();
	ListElement* le = l1->head;

	for (int i = 0; i < l1->size; i++) {
		if (searchInList(l2, le->data) == -1) {
			insert(newList, le->data);
		}
		le = le->next;
	}

	le = l2->head;

	for (int i = 0; i < l2->size; i++) {
		if (searchInList(l1, le->data) == -1) {
			insert(newList, le->data);
		}
		le = le->next;
	}

	return newList;
}

List* listComplement(List* l1, List* l2) {
	List* newList = initList();
	ListElement* le = l1->head;

	for (int i = 0; i < l1->size; i++) {
		if (searchInList(l2, le->data) == -1) {
			insert(newList, le->data);
		}
		le = le->next;
	}
	return newList;
}

void deleteList(List* l) {
	if (l == NULL)
		return;
	while (l->head) {
		ListElement* next = l->head->next;
		free(l->head);
		l->head = next;
	}
	free(l);
}

void dumpList(List* l) {
	ListElement* le = l->head;
	for (int i = 0; i < l->size; i++) {
		logMessage(1, "Index %i => %s ", i, le->data);
		le = le->next;
	}
}
