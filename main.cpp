#include <iostream>
#include <string>
#include <cstdio>
#include "log.h"

int main(int argc, char *argv[])
{
	log_debug("for test %s %d\n", "lolonet", 100);
	log_warn("for test %s %d\n", "lolonet", 100);
	log_error("for test %s %d\n", "lolonet", 100);
	log_boot("for test %s %d\n", "lolonet", 100);
	// log_debug("Hello lolonet");

	set_log_level(2);
	log_debug("for test 1 %s %d\n", "lolonet", 100);			// 被屏蔽了，打不出
	log_error("for test 2 %s %d\n", "lolonet", 100);


	return 0;
}
