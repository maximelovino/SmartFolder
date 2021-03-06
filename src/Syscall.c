/**
 * @file Syscall.c
 * @brief Source file that contains the implementation for system calls wrapper functions used in our program
 *
 * @authors Maxime Lovino, Thomas Ibanez
 * @date January 25, 2017
 * @version 1.0
 */

#include "Syscall.h"

inline int sfork() {
	int v = fork();
	if (v == -1) {
		logMessage(3, "fork failed !");
		_exit(1);
	}
	return v;
}

inline int ssymlink(char* target, char* linkPath) {
	return !(symlink(target, linkPath) == -1);
}

inline char* sbasename(char* fullPath) {
	char* name = basename(fullPath);
	if (name == NULL) {
		logMessage(3, "basename failed ! %s", fullPath);
		_exit(1);
	}
	return name;
}

inline int smkdir(char* path) {
	int r = mkdir(path, 0775);
	return r == 0;
}

inline FILE* stouch(char* file) {
	FILE* fp = fopen(file, "w+");
	if (fp == NULL) {
		logMessage(3, "touch failed ! %s", file);
		_exit(1);
	}
	return fp;
}

inline int saccess(char* path) {
	return access(path, F_OK) != -1;
}

inline int sunlink(char* file) {
	return unlink(file) == 0;
}

inline int srmdir(char* path) {
	int i = rmdir(path);
	return i == 0;
}

inline int sgetpwuid(const char* userName) {
	return getpwnam(userName)->pw_uid;
}

inline int sgetgrgid(const char* groupName) {
	return getgrnam(groupName)->gr_gid;
}

inline int slstat(const char* name, struct stat* statbuf) {
	return lstat(name, statbuf) == 0;
}

inline DIR* sopendir(const char* name) {
	DIR* dp = opendir(name);
	return dp;
}

inline int schdir(const char* name) {
	return chdir(name) == 0;
}

inline int sclosedir(DIR* dp) {
	return closedir(dp) == 0;
}

inline struct dirent* sreaddir(DIR* dir) {
	return readdir(dir);
}

inline int sS_ISLNK(mode_t m) {
	return S_ISLNK(m);
}

inline int sS_ISDIR(mode_t m) {
	return S_ISDIR(m);
}

inline int sS_ISREG(mode_t m) {
	return S_ISREG(m);
}

inline char* srealpath(const char* p, char* buf) {
	return realpath(p, buf);
}
