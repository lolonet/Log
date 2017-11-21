#include "log.h"

#include <string.h>

int _log_level = LOG_LEVEL_DEBUG;
char _fileName[256] = {};
char _filePath[1024] = {};
int _log_fd = 0;
static char _strLogInfo[1024*1024] = {};			// 单次写入最大是 1024*1024

// Linux 目录以 "/" 分割
int _log_mkdir(const char *filePath)
{
	char *strPath = strdup(filePath);
	char *token = NULL;
	std::string path;
	while( (token=strsep(&strPath, "/")) != NULL )
	{
		if (strlen(token) <=1 )
		{
			path = (std::string)token;
		}
		else
		{
			path = path + "/" + (std::string)token;
			mkdir(path.c_str(), 0755);
		}
	}
	
	free(strPath);			// strdup 有重新分配空间，必须释放

	return 0;
}

int _log_init(const char *fileName, const char *filePath, int logLevel)
{
	if (fileName == NULL || filePath == NULL)
		return -1;

	if (logLevel < LOG_LEVEL_BOOT || logLevel > LOG_LEVEL_DEBUG)
		return -1;

	// 初始化文件路径，递归创建文件夹
	_log_mkdir(filePath);

	// 保存文件名和路径
	strncpy(_fileName, fileName, sizeof(_fileName));
	strncpy(_filePath, filePath, sizeof(_filePath));
	_log_level = logLevel;

	// 创建文件，保留fd
	const int flag = O_CREAT | O_WRONLY | O_APPEND;
	_log_fd = open(fileName, flag, 0755);
	if (_log_fd <= 0)
		printf("ERROR file open error\n");

	return 0;
}

int _log_write(int level, const char *file, int line, const char *func, const char *format, ...)
{
	char str[1024] = {};

	va_list vl = {};
	va_start(vl, format);
	const int size = vsnprintf(str, sizeof(str), format, vl);
	va_end(vl);

	struct tm tm = {};
	time_t now = time(NULL);
	localtime_r(&now, &tm);

	// < 3>[20171118-01:18:15] pid[21193]: Game.cpp(444)[LogUpdateMoney]: for test
	snprintf(_strLogInfo, sizeof(_strLogInfo), "<%d>[%04d%02d%02d-%02d:%02d:%02d] pid[%d] %s(%d)[%s]: %s\n", 
		level, tm.tm_year+1900, tm.tm_mon+1, tm.tm_mday, tm.tm_hour, tm.tm_min, tm.tm_sec, getpid(), 
		file, line, func, str);

	// write to IO 
	write(_log_fd, _strLogInfo, strlen(_strLogInfo));

	return 0;
}


