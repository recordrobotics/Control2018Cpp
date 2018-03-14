/*
 * Logger.cpp
 *
 *  Created on: Feb 14, 2018
 *      Author: vassy
 */

#include <ctime>
#include <string.h>
#include <stdarg.h>
#include <Utils/Logger.h>

FILE *Logger::fp = NULL;
pthread_mutex_t Logger::mutex;

bool Logger::init(const char *path)
{
	fp = NULL;

	if(pthread_mutex_init(&mutex, NULL) == 0)
		fp = fopen(path, "w");

	return fp;
}

void Logger::log(const char *format, ...)
{
	pthread_mutex_lock(&mutex);
	if(!fp) {
		pthread_mutex_unlock(&mutex);
		return;
	}

	va_list args;
	va_start(args, format);

	time_t rawtime;
	struct tm *timeinfo;

	time(&rawtime);
	timeinfo = localtime(&rawtime);
	char *time = asctime(timeinfo);
	time[strlen(time) - 1] = '\0';

	fprintf(fp, "[ %s ] ", time);
	vfprintf(fp, format, args);
	fputc('\n', fp);

	va_end(args);
	fflush(fp);

	pthread_mutex_unlock(&mutex);
}

void Logger::end()
{
	if(fp)
		fclose(fp);

	pthread_mutex_destroy(&mutex);
}
