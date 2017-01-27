/**
 * @file Syscall.c
 * @brief Source file that contains the implementation for system calls wrapper functions used in our program
 *
 * @authors Maxime Lovino, Thomas Ibanez
 * @date January 25, 2017
 * @version 1.0
 */

#include "Syscall.h"

int sfork() {
	return fork();
}

int ssymlink(char* target, char* linkPath) {
	return symlink(target, linkPath);
}

char* sbasename(char* fullPath) {
	return basename(fullPath);
}

int smkdir(char* path) {
	return mkdir(path, 0775);
}

FILE* stouch(char* file) {
	return fopen(file, "w+");
}

int saccess(char* path) {
	return access(path, F_OK) != -1;
}

int sunlink(char* file) {
	if (saccess(file)) {
		return unlink(file);
	}
	return -1;
}

int srmdir(char* path) {
	return rmdir(path);
}

int sgetpwuid(char* userName) {
	return getpwnam(userName)->pw_uid;
}

int sgetgrgid(char* groupName) {
	return getgrnam(groupName)->gr_gid;
}

int slstat(char* name, struct stat* statbuf) {
	return lstat(name, statbuf);
}

DIR* sopendir(char* name) {
	return opendir(name);
}

int schdir(char* name) {
	return chdir(name);
}

int sclosedir(DIR* dp) {
	return closedir(dp);
}

struct dirent* sreaddir(DIR* dir) {
	return readdir(dir);
}

int sS_ISLNK(mode_t m) {
	return S_ISLNK(m);
}

int sS_ISDIR(mode_t m) {
	return S_ISDIR(m);
}

int sS_ISREG(mode_t m) {
	return S_ISREG(m);
}

char* srealpath(char* p, char* buf) {
	return realpath(p, buf);
}
