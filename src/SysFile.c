#include "SysFile.h"

int createSysFile(int pid, char* smartFolder) {
  char path[70];
  char* name = strrchr(smartFolder, '/');
  strcpy(path, SYSFILE_PATH);
  strcat(path, name+1);
  logMessage(0, path);
  if(!fileExists(path)) {
    FILE* fp = touch(path);
    fprintf(fp, "%d", pid);
    return 1;
  }
  return 0;
}

int deleteSysFile(int pid) {

}
