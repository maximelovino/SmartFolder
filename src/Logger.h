#ifndef _LOGGER_H_
#define _LOGGER_H_
#ifndef LOG_LEVEL
#define LOG_LEVEL 0
#endif

#include <stdio.h>
#include <stdarg.h>

void logger(int level, const char* format, ...);

#endif /* end of include guard: _LOGGER_H_ */
