/**
 * @file List.h
 * @brief Header file that contains the definitions for a simple linked List data structure containing Strings
 *
 * @authors Maxime Lovino, Thomas Ibanez
 * @date January 25, 2017
 * @version 1.0
 */

#ifndef _LIST_H_
#define _LIST_H_

#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include "Logger.h"

typedef struct listElement_st {
	char *data;
	struct listElement_st *next;
} ListElement;

typedef struct list_st {
	ListElement *head;
	int size;
} List;

/**
 * Function to initialize an empty List
 * @return A pointer to an empty List
 */
List *initList();

/**
 * Function to insert a String into the List, we insert at the beginning
 * @param l A pointer to the List we want to insert
 * @param element The String we want to insert
 */
void insert(List *l, char *element);

/**
 * Function to remove the element at an index from the List
 * @param l A pointer to the List we want to remove from
 * @param idx The index at which we want to remove
 */
void removeIndex(List *l, int idx);

/**
 * Function to remove a String from the List
 * @param l A pointer to the List we want to remove from
 * @param element The String we want to remove
 */
void removeObject(List *l, char *element);

/**
 * Function to retrieve the index of an element from the List
 * @param l A pointer to the List we want to search in
 * @param element The element we're looking for
 * @return The index of that element in the List, or -1 if it isn't in the List
 */
int searchInList(List *l, char *element);

/**
 * Function to get the value of an element at a specific index
 * @param l A pointer to the List
 * @param idx The index of the element we want
 * @return The value of the element
 */
char *get(List *l, int idx);

/**
 * Function that computes the union between two Lists (logical OR)
 * @param l1 A pointer to the first List
 * @param l2 A pointer to the second List
 * @return A new List that is the union of the two lists
 */
List *listUnion(List *l1, List *l2);

/**
 * Function that computes the intersection between two Lists (logical AND)
 * @param l1 A pointer to the first List
 * @param l2 A pointer to the second List
 * @return A new List that is the intersection of the two Lists
 */
List *listIntersect(List *l1, List *l2);

/**
 * Function that computes the XOR between two Lists (logical XOR)
 * This means the elements contained in only one of the two Lists, but not both
 *
 * @param l1 A pointer to the first List
 * @param l2 A pointer to the second List
 * @return A new List that is the XOR of the two lists
 */
List *listXOR(List *l1, List *l2);

/**
 * Function that computes the complement between the first List and the second (l1 - l2)
 * This means the elements contained in the first List that are NOT in the second one
 * @param l1 A pointer to the first List
 * @param l2 A pointer to the second List
 * @return A new List that is the complement of the two lists
 */
List *listComplement(List *l1, List *l2);

/**
 * Function that all the elements of a List
 * @param l A pointer to the List
 */
void dumpList(List *l);

/**
 * Function that deletes a List and frees the memory
 * @param l A pointer to the List
 */
void deleteList(List *l);

#endif /* end of include guard: _LIST_H_ */
