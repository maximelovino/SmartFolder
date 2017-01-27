#include <stdio.h>
#include <stdlib.h>
#include "Logger.h"

int main() {
	logMessage(0, "%i is a badass number unlike %f", 42, 2.3);
	logMessage(1, "%i is a badass number", 42);
	logMessage(2, "%i is a badass number", 42);
	logMessage(42, "%i is a badass number", 42);
	return 0;
}
