#include "SysFile.h"

int createSysFile(int pid, char* smartFolder) {
  char str[65];
  char path[70];
  strcpy(path, SYSFILE_PATH);
  sprintf(str, "%d", pid);
  strcat(path, str);
  logMessage(0, path);
  FILE* fp = touch(path);
  //write
  fprintf(fp, "%s", smartFolder);
}

int deleteSysFile(int pid) {

}
