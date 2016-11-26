#include "Search.h"
#include "List.h"
#include <stdlib.h>

int main(int argc, char const *argv[]) {
    List* issou = searchDirectory(argv[1], NULL, 0, 0, NULL, NULL, NULL, NULL, NULL, NULL);
    for (int i = 0; i < issou->size; i++) {
        printf("%s\n", get(issou, i));
    }
    return 0;
}
