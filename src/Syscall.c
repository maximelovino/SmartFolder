#include "Syscall.h"

int processFork() {
    return fork();
}

int symbolicLink(char* target, char* linkPath){
  return symlink(target,linkPath);
}

char* nameOfFile(char* fullPath){
  return basename(fullPath);
}

int makeDir(char* path) {
  return mkdir(path, 0775);
}

FILE* touch(char* file) {
  return fopen(file, "w+");
}
