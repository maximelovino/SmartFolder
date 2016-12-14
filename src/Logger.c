#include "Logger.h"

void logger(int level, const char* format, ...){
	if (level >= LOG_LEVEL) {
		va_list args;
		va_start(args, format);
		printf("%s", level == 0 ? "[INFO]" : level == 1 ? "[WARNING]" : "[FATAL]");
		vprintf(format, args);
		printf("\n");
		va_end(args);
	}
}
