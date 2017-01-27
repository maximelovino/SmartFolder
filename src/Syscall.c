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
	if(v == -1) {
		logMessage(3, "fork failed !");
		_exit(1);
	}
	return v;
}

inline void ssymlink(char* target, char* linkPath) {
	if(symlink(target, linkPath) == -1) {
		logMessage(3, "symlink failed ! %s %s", target, linkPath);
		_exit(1);
	}
}

inline char* sbasename(char* fullPath) {
	char* name = basename(fullPath);
	if(name == NULL) {
		logMessage(3, "basename failed ! %s", fullPath);
		_exit(1);
	}
	return name;
}

inline void smkdir(char* path) {
	int r = mkdir(path, 0775);
	if(r != 0) {
		logMessage(3, "mkdir failed ! %s", path);
		_exit(1);
	}
}

inline FILE* stouch(char* file) {
	FILE* fp = fopen(file, "w+");
	if(fp == NULL) {
		logMessage(3, "touch failed ! %s", file);
		_exit(1);
	}
	return fp;
}

inline int saccess(char* path) {
	return access(path, F_OK) != -1;
}

inline void sunlink(char* file) {
	if (saccess(file)) {
		int i = unlink(file);
		if(i == 0) return;
	}
	logMessage(3, "unlink failed ! %s", file);
	_exit(1);
}

inline void srmdir(char* path) {
	int i = rmdir(path);
	if(i != 0) {
		logMessage(3, "rmdir failed ! %s", path);
		_exit(1);
	}
}

inline int sgetpwuid(char* userName) {
	return getpwnam(userName)->pw_uid;
}

inline int sgetgrgid(char* groupName) {
	return getgrnam(groupName)->gr_gid;
}

inline int slstat(char* name, struct stat* statbuf) {
	int i = lstat(name, statbuf);
	if(i != 0) {
		logMessage(3, "lstat failed ! %s", name);
		_exit(1);
	}
}

inline DIR* sopendir(char* name) {
	DIR* dp = opendir(name);
	if(dp == NULL) {
		logMessage(3, "opendir failed ! %s", name);
		_exit(1);
	}
	return dp;
}

inline void schdir(char* name) {
	if(chdir(name) != 0) {
		logMessage(3, "chdir failed ! %s", name);
		_exit(1);
	}
}

inline void sclosedir(DIR* dp) {
	if(closedir(dp) != 0) {
		logMessage(3, "closedir failed !");
		_exit(1);
	}
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

inline char* srealpath(char* p, char* buf) {
	return realpath(p, buf);
}
