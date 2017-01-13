#include "Linker.h"

int makeLink(char* pathToLink, char* destFolder){
  char* fileName = nameOfFile(pathToLink);
  char* linkName = malloc(strlen(destFolder)+strlen(fileName)+1);
  strcpy(linkName, destFolder);
  strcat(linkName, "/");
  strcat(linkName, fileName);
  logMessage(0, "linkname: %s pathToLink: %s destFolder: %s", linkName, pathToLink, destFolder);
  return symbolicLink(pathToLink, linkName);
}

int makeFolder(char* path, List* files) {
  int r = makeDir(path);
  if(r == -1) {
    if(errno == EEXIST) {
      logMessage(3, "Your SmartFolder directory exists already");
      return 1;
    }
    return -1;
  }

  ListElement* e = files->head;
  while(e != NULL) {
    if(makeLink(e->data, path) == 0) {
      e = e->next;
    } else {
      return -1;
    }
  }

  return 0;
}
