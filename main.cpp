#include <iostream>
#include <cstring>
#include <cstdio>
#include "log.h"
#include <unistd.h>

int main(int argc, char *argv[])
{
	log_init("./20171121/log/test.log", "./20171121/log/", 3);

	log_debug("for test %s %d", "lolonet", 100);
	log_warn("for test %s %d", "lolonet", 100);
	log_error("for test %s %d", "lolonet", 100);
	log_boot("for test %s %d", "lolonet", 100);


	set_log_level(2);
	log_debug("for test 1 %s %d", "lolonet", 100);			// 被屏蔽了，打不出
	log_error("for test 2 %s %d", "lolonet", 100);

	// 修复不定参数为空时的编译问题
	log_debug("Hello lolonet");

	return 0;
}
