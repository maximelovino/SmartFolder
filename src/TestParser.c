#include "Parser.h"
#include <stdio.h>

int main(int argc, char const *argv[]) {
    printf("Root has id %i\n", getUID("root"));
    printf("Staff has id %i\n", getGID("staff"));
    printf("Time %li\n", getTimeSpec("2016.10.11")->tv_sec);
    printf("is valid ? %i\n", isValidPath("/usr/whatever/lol/"));
    return 0;
}
