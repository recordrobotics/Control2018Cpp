/*
 * Logger.h
 *
 *  Created on: Feb 14, 2018
 *      Author: vassy
 */

#ifndef SRC_UTILS_LOGGER_H_
#define SRC_UTILS_LOGGER_H_

#include <pthread.h>
#include <stdio.h>

class Logger {
public:
	static bool init(const char *path);
	static void end();

	static void log(const char *format, ...);

	static inline FILE *getFp() { return fp; }

private:
	Logger() { }

	static FILE *fp;
	static pthread_mutex_t mutex;
};

#endif /* SRC_UTILS_LOGGER_H_ */
