#include "Search.h"
#include "List.h"
#include <stdlib.h>
#include <stdio.h>

int main(int argc, char const *argv[]) {
	searchType type = SIZE_BIGGER;
	int size = 90000;
    List* issou = searchDirectory(argv[1], type, &size);
    for (int i = 0; i < issou->size; i++) {
        printf("%s\n", get(issou, i));
    }
    return 0;
}
