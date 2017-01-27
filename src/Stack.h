/**
 * @file Stack.h
 * @brief Header file that contains the definitions for a generic Stack data structure
 *
 * @authors Maxime Lovino, Thomas Ibanez
 * @date January 25, 2017
 * @version 1.0
 */


#ifndef _STACK_H_
#define _STACK_H_

#include "Logger.h"
#include <stdlib.h>

typedef struct stackElement_st {
	struct stackElement_st* next;
	void* value;
} stackElement;

typedef struct stack_st {
	stackElement* top;
	int size;
} Stack;

/**
 * Function to initialize an empty Stack
 * @return A pointer to an empty Stack
 */
Stack* initStack();

/**
 * Function to insert an element (push) in the Stack
 * @param s A pointer to the Stack
 * @param element The element we want to insert
 */
void push(Stack* s, void* element);

/**
 * Function to pop the first element of the Stack
 * @param s A pointer to the Stack
 * @return The first element of the Stack
 */
void* pop(Stack* s);

/**
 * Function to check if a Stack is empty
 * @param s A pointer to the Stack
 * @return 1 if the Stack is empty, 0 otherwise
 */
int isEmpty(Stack* s);

/**
 * Function to delete a Stack and free its memory
 * @param s A pointer to the Stack
 */
void deleteStack(Stack* s);

#endif /* end of include guard: _STACK_H_ */
