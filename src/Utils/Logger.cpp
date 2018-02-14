/*
 * Logger.cpp
 *
 *  Created on: Feb 14, 2018
 *      Author: vassy
 */

#include <Utils/Logger.h>

FILE *Logger::fp = NULL;

bool Logger::init(const char *path)
{
	fp = fopen(path, "w");

	return fp;
}

void Logger::log(const char *mes)
{
	fputs(mes, fp);
	fflush(fp);
}

void Logger::end()
{
	if(fp)
		fclose(fp);
}
