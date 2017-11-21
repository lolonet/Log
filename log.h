
// +----------------------------------------------------------------------+
// | Log module                                                           |
// +----------------------------------------------------------------------+
// | Authors:  linyubin                                                   |
// +----------------------------------------------------------------------+
// | Date: 2017-11-20                                                     |
// +----------------------------------------------------------------------+
// | Desc:                                                                |
// | 1. 获取当前时间 localtime_r                                           |
// | 2. 变参函数与 字符串的格式化处理 vsnprintf                             |
// | 3. 采用宏定义处理替换实际的文件，函数和行数                             |
// | 4. 提供日志等级设置                                                   |
// +----------------------------------------------------------------------+
// | History:                                                             |
// +----------------------------------------------------------------------+
// | 5. 提供IO接口，也就是将信息写入到文件中                                 |
// +----------------------------------------------------------------------+
// +----------------------------------------------------------------------+


#ifndef __LOG__
#define __LOG__

#include <time.h>
#include <unistd.h>
#include <cstdarg>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <string>
#include <sys/types.h>
#include <fcntl.h>


enum LOG_LEVEL
{
	LOG_LEVEL_BOOT 		= 1,			// 系统级别错误，如启动问题等
	LOG_LEVEL_ERROR 	= 2,
	LOG_LEVEL_WARN		= 3,
	LOG_LEVEL_DEBUG		= 4,			// 开发测试级别
	// log_level_...
};

extern int _log_level;

// 对外的接口全部用宏定义提供， 采用 do{} while(0) 消除定义域问题
#define log_boot(format, arg...) do{ if (_log_level>=LOG_LEVEL_BOOT) _log_write(LOG_LEVEL_BOOT, __FILE__, __LINE__, __FUNCTION__, format, arg); } while(0);
#define log_error(format, arg...) do{ if (_log_level>=LOG_LEVEL_ERROR) _log_write(LOG_LEVEL_ERROR, __FILE__, __LINE__, __FUNCTION__, format, arg); } while(0);
#define log_warn(format, arg...) do{ if (_log_level>=LOG_LEVEL_WARN) _log_write(LOG_LEVEL_WARN, __FILE__, __LINE__, __FUNCTION__, format, arg); } while(0);
#define log_debug(format, arg...) do { if (_log_level>=LOG_LEVEL_DEBUG) _log_write(LOG_LEVEL_DEBUG, __FILE__, __LINE__, __FUNCTION__, format, arg); } while(0);
#define set_log_level(level) do{ if (_log_level>=LOG_LEVEL_BOOT && _log_level<=LOG_LEVEL_DEBUG) _log_level = level; } while(0);
#define log_init(fileName, filePath, logLevel) do{ _log_init(fileName, filePath, logLevel); } while(0);

// 内部函数实现
int _log_write(int level, const char *file, int line, const char *func, const char *format, ...);
int _log_init(const char *fileName, const char *filePath, int logLevel=LOG_LEVEL_DEBUG);
int _log_mkdir(const char *filePath);

// static int _log_writeToIO();

#endif



