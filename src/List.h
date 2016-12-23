#ifndef _LIST_H_
#define _LIST_H_

typedef struct listElement_st {
    char* data;
    struct listElement_st* next;
} ListElement;

typedef struct list_st {
    ListElement* head;
    int size;
} List;

List* initList();
void insert(List* l, char* element);
void removeIndex(List* l, int idx);
void removeObject(List* l, char* element);
int searchInList(List* l, char* element);
char* get(List* l, int idx);
List* listUnion(List* l1, List* l2);
List* listIntersect(List* l1, List* l2);
List* listXOR(List* l1, List* l2);
List* listComplement(List* l1, List* l2);
void dumpList(List* l);
void deleteList(List* l);

#endif /* end of include guard: _LIST_H_ */
