#include "Logger.h"

void logMessage(int level, const char* format, ...){
	if (level >= LOG_LEVEL) {
		va_list args;
		va_start(args, format);
		if (level == 0) {
			printf("%s", "[INFO]" );
		}else if (level == 1){
			printf("%s", "[WARNING]");
		}else if (level == 2){
			printf("%s", "[FATAL]");
		}else{
			printf("%s", "[OTHER]");
		}
		vprintf(format, args);
		printf("\n");
		va_end(args);
	}
}
