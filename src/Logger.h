/**
 * @file Logger.h
 * @brief Header file that contains the definitions for logging to the console
 *
 * @authors Maxime Lovino, Thomas Ibanez
 * @date January 25, 2017
 * @version 1.0
 */

#ifndef _LOGGER_H_
#define _LOGGER_H_
/**
 * Here you can set the desired level of logging you want in the console
 * We will output anything over that level
 */
#ifndef LOG_LEVEL
#define LOG_LEVEL 0
#endif

#include <stdio.h>
#include <stdarg.h>

/**
 * Function to log a message of the specified level.
 * Levels are the following:
 * <br>0 for Debug level
 * <br>1 for Info level
 * <br>2 for Warning level
 * <br>3 for Fatal level
 *
 * @param level The level of the message
 * @param format String format of the message (like in printf for example)
 * @param ... Variables to insert into the String format (like in printf)
 */
void logMessage(int level, const char* format, ...);

#endif /* end of include guard: _LOGGER_H_ */
