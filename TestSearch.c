#include "Search.h"
#include "List.h"
#include <stdlib.h>
#include <stdio.h>
#include <time.h>

int main(int argc, char const *argv[]) {
	searchType type = MODE;
	int lel = 777;
    List* issou = searchDirectory(argv[1], type, &lel);
    for (int i = 0; i < issou->size; i++) {
        printf("%s\n", get(issou, i));
    }
    return 0;
}
