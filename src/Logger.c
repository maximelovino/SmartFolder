#include "Logger.h"

void logMessage(int level, const char* format, ...){
	if (level >= LOG_LEVEL) {
		va_list args;
		va_start(args, format);
		if (level == 0) {
			fprintf(stderr,"%s", "[DEBUG]" );
		}else if (level == 1){
			fprintf(stderr,"%s", "[INFO]");
		}else if (level == 2){
			fprintf(stderr,"%s", "[WARNING]");
		}else{
			fprintf(stderr,"%s", "[FATAL]");
		}
		vfprintf(stderr,format, args);
		fprintf(stderr,"\n");
		va_end(args);
	}
}
