#include "log.h"


int __log_level = LOG_LEVEL_DEBUG;

int log_write(int level, const char *file, int line, const char *func, const char *format, ...)
{
	char str[1024] = {};

	va_list vl = {};
	va_start(vl, format);
	const int size = vsnprintf(str, sizeof(str), format, vl);
	va_end(vl);

	struct tm tm = {};
	time_t now = time(NULL);
	localtime_r(&now, &tm);

	printf("<%d>[%04d%02d%02d-%02d:%02d:%02d] pid[%d] %s(%d)[%s]: %s\n", 
		level, tm.tm_year+1900, tm.tm_mon+1, tm.tm_mday, tm.tm_hour, tm.tm_min, tm.tm_sec, getpid(), 
		file, line, func, str);

	// < 3>[20171118-01:18:15] pid[21193]: Game.cpp(444)[LogUpdateMoney]: for test

	return 0;
}

