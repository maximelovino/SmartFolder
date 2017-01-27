#include "Linker.h"
#include <stdio.h>

int main() {
	char name[] = "Test";
	printf("%s\n", name);
	for (int i = 0; i < 10; ++i) {
		nextSuffix(name);
		printf("%s\n", name);
	}
	return 0;
}
