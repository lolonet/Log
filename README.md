# Log 独立的日志模块

## 提供工具类日志全局函数，格式化输出日志信息到指定文件

### 主要开发步骤
1. 获取当前时间 localtime_r, 具体到秒
2. 变参函数与 字符串的格式化处理 vsnprintf
3. 采用宏定义处理，替换实际的文件名，函数名和行数，采用 do {} while(0) 避免定义域问题
4. 提供日志等级设置，实现日志开关控制
5. 提供IO接口，就是将信息写入到文件中，加入定时器的话，可以实现按天分割日志
6. 对宏定义进行修改，修复不定参数为空，编译报错的情况
7. 对不定参数加上编译验证处理，__attribute__, 编译加上 -Wall
8. 对日志文件加上 O_LARGEFILE 参数，支持大文件处理，对32位机器生效，64位无需此参数

### 日志信息输出实例
<2>[20170812-09:34:26] pid[12806] main.cpp(19)[main]: for test 2 lolonet 100
