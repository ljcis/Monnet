/*
 ***   关于程序./ini/目录下，配置文件的统一读取与设置
 */

#ifndef LOADINIFILE_H
#define LOADINIFILE_H

#include <string>

enum DAEMON_PROCESS         // 监控程序状态
{
    ENUM_DAEMON_NOSTART_NOCLOSE = 0,            // 不启动 + 不关闭
    ENUM_DAEMON_START_CLOSE     = 1,            // 启动 + 关闭
    ENUM_DAEMON_NOSTART_CLOSE   = 2,            // 不启动 + 关闭,
    ENUM_DAEMON_START_NOCLOSE   = 3             // 启动 + 不关闭
};

class LoadIniFile
{
public:
    static int loadLogLevel();                         // 读取日志等级开关
    static void setLogLevel( int level );
};

#endif // LOADINIFILE_H
