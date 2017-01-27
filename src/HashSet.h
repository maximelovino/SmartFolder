/**
 * @file HashSet.h
 * @brief Header file that contains the definitions for a HashSet data structure containing Strings
 *
 * @authors Maxime Lovino, Thomas Ibanez
 * @date January 25, 2017
 * @version 1.0
 */

#ifndef _HASH_SET_
#define _HASH_SET_

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include "Logger.h"
#include "List.h"

typedef struct HashSet {
	char** table;
	int size;
	int filled;
} HashSet;

/**
 * Initialisation function for a HashSet
 * @param size The initial size of the set
 * @return A pointer to a HashSet of the correct size
 */
HashSet* initSet(int size);

/**
 * Function to insert all elements of a list in a HashSet
 * @param table A pointer to the HashSet where we want to insert
 * @param list The list that we want to insert
 */
void putAll(HashSet* table, List* list);

/**
 * Function that expands the size of an HashSet
 * @param table A pointer to the HashSet we want to expand
 */
void expand(HashSet* table);

/**
 * Function to insert a String in the HashSet
 * @param table A pointer to the HashSet we want to insert in
 * @param filePath The String we want to insert
 */
void put(HashSet* table, char* filePath);

/**
 * Function to remove a String from the HashSet
 * @param table A pointer to the HashSet we want to remove from
 * @param filePath The String we want to remove
 */
void removeFromSet(HashSet* table, char* filePath);

/**
 * Function to check if a String is contained in the HashSet
 * @param table A pointer to the HashSet we want to check in
 * @param filePath The String we want to check
 * @return 1 if the String is in the HashSet, 0 otherwise
 */
int contains(HashSet* table, char* filePath);

/**
 * Function to get the value of the index in the HashSet of a String
 * @param table A pointer to the HashSet we want to find in
 * @param filePath The String we want to find
 * @return The index of the String in the HashSet
 */
int searchInSet(HashSet* table, char* filePath);

/**
 * Hashing function for a String
 * @param text The String we want to hash
 * @return The hash of the String
 */
int hash(char* text);

/**
 * Function to delete a HashSet and free the memory
 * @param table A double pointer to the HashSet we want to delete
 */
void deleteSet(HashSet** table);

/**
 * Function to log all of the HashSet content
 * @param table A pointer to the HashSet we want to log
 */
void dumpSet(HashSet* table);

#endif /* end of include guard: _HASH_SET_ */
