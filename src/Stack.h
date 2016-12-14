#ifndef _STACK_H_
#define _STACK_H_

typedef struct stackElement_st {
    struct stackElement_st* next;
    void* value;
} stackElement;

typedef struct stack_st {
    stackElement* top;
    int size;
} Stack;

Stack* initStack();
void push(Stack* s, void* element);
void* pop(Stack* s);
int isEmpty(Stack* s);
void deleteStack(Stack* s);

#endif /* end of include guard: _STACK_H_ */
