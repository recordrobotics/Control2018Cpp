/*
 * Logger.h
 *
 *  Created on: Feb 14, 2018
 *      Author: vassy
 */

#ifndef SRC_UTILS_LOGGER_H_
#define SRC_UTILS_LOGGER_H_

#include <stdio.h>

class Logger {
public:
	static bool init(const char *path);
	static void end();

	static void log(const char *mes);

private:
	Logger() { }

	static FILE *fp;
};

#endif /* SRC_UTILS_LOGGER_H_ */
