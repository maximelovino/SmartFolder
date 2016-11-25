#include "Stack.h"
#include <stdlib.h>
#include <stdio.h>

int main(int argc, char const *argv[]) {
    Stack* s = initStack();

    for (size_t i = 0; i < 10; i++) {
        int* k = malloc(4);
        *k = i;
        push(s, (void*) k);
    }

    while (!isEmpty(s)) {
        printf("%i\n", *((int*)pop(s)));
    }

    return 0;
}
