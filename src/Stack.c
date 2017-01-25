/**
 * @file Stack.c
 * @brief Source file that contains the implementation for a generic Stack data structure
 *
 * @authors Maxime Lovino, Thomas Ibanez
 * @date January 25, 2017
 * @version 1.0
 */

#include "Stack.h"

Stack *initStack() {
	Stack *s = malloc(sizeof(Stack));
	s->size = 0;
	s->top = NULL;
	return s;
}

void push(Stack *s, void *element) {
	stackElement *se = malloc(sizeof(stackElement));
	se->next = s->top;
	se->value = element;
	s->top = se;
	s->size++;
}

void *pop(Stack *s) {
	if (!isEmpty(s)) {
		stackElement *se = s->top;
		s->top = s->top->next;
		void *element = se->value;
		free(se);
		s->size--;
		return element;
	}
	logMessage(1, "The stack is empty, so you're popping NULL");
	return NULL;
}

int isEmpty(Stack *s) {
	return s->size == 0;
}

void deleteStack(Stack *s) {
	while (!isEmpty(s)) {
		void *e = pop(s);
		free(e);
	}
	free(s);
}
