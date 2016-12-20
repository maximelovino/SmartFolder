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
