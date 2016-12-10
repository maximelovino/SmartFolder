#include <stdio.h>
#include <stdlib.h>
#include "Logger.h"

int main() {
	logger(0, "%i is a badass number unlike %f",42,2.3);
	logger(1, "%i is a badass number",42);
	logger(2, "%i is a badass number",42);
	return 0;
}
