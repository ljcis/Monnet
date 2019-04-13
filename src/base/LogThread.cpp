/*
 * LogThread.cpp
 *
 *  Created on: Apr 13, 2019
 *      Author: fly
 */

#include "LogThread.h"
#include <unistd.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <dirent.h>
#include <pwd.h>
#include <functional>
#include <iostream>

const std::string  LogThread::sLevel[] = {"FATAL","ERROR", "WARN", "INFO", "DEBUG"};

LogThread::LogThread() :
		isExit_(false),
		intervalMs_(1000),
		loglevel_(3)
{
	// TODO Auto-generated constructor stub
	InitLogDir();
	std::thread temp(std::bind(&LogThread::loop, this));
	logThread_.swap(temp);
}

LogThread::~LogThread() {
	// TODO Auto-generated destructor stub
	release();
}

void LogThread::release() {
	isExit_ = true;
	logThread_.join();

	if(logFileHandle_){
		fclose(logFileHandle_);
		logFileHandle_ = NULL;
	}
}

void LogThread::loop() {
	while(!isExit_){
		flush();
		::usleep(intervalMs_ * 1000);
	}
}

void LogThread::flush() {
	size_t len = buf_.readable();
	char buf[len] = {0};
	if(buf_.pop(buf, len) > 0){
		fwrite(buf, sizeof(char), len, logFileHandle_);
	}
}

std::string LogThread::GetTimeStr()
{
    char sTimes[32] = {0};
    time_t now = {0};
    struct tm *ptime = NULL;
    time(&now);
    ptime = localtime(&now);

    sprintf(sTimes, "%04d.%02d.%02d-%02d:%02d:%02d",
        (1900+ptime->tm_year), (1+ptime->tm_mon), ptime->tm_mday,
        ptime->tm_hour, ptime->tm_min, ptime->tm_sec);

    return std::string(sTimes);
}

void LogThread::formLog(log_level level,
						const std::string& func,
						int lineNum,
						const std::string& file,
						const char* formatStr, ...) {
	if(level > loglevel_) return;
	std::string subfile;
	if(file.rfind('/')!=std::string::npos)
	{
		subfile = file.substr(file.rfind('/')+1);
	}
	else
	{
		subfile = file;
	}

	char buf[128] = {0};
	sprintf(buf, "[%s [%s] %s %s:%d ] ", GetTimeStr().c_str(), sLevel[level].c_str(), func.c_str(), subfile.c_str(), lineNum);
	char buf2[128] = {0};
	va_list p_list;
	va_start(p_list, formatStr);
	vsprintf(buf2, formatStr, p_list);
	va_end(p_list);
	strncat(buf2, "\r\n", 2);
	std::string logMsg = std::string(buf) + std::string(buf2);

	if(level == FATAL_LEVEL) {
		fwrite(logMsg.c_str(), sizeof(char), logMsg.size(), logFileHandle_);
		abort();
	}

	buf_.fill(logMsg.c_str(), logMsg.size());
}

std::string LogThread::GetProcessName() {
    char processPath[512] = {0};
    int len;
    std::string sProcessPath;
    std::string sProcessName;

    if((len = readlink("/proc/self/exe", processPath, sizeof(processPath))) <=0)
    {
        return sProcessName;
    }

    sProcessPath = std::string(processPath, len);

    size_t pos = sProcessPath.find_last_of("/");

    sProcessName = sProcessPath.substr(pos + 1);

    return sProcessName;
}

void LogThread::InitLogDir() {
	std::string sUser;
	struct passwd *pwd;

	pwd = getpwuid( getuid() );
	if(NULL == pwd)
	{
		perror("getpwuid error");
		sUser = "null";
	}
	else
	{
		sUser = pwd->pw_name;
		sUser = "_" + sUser;
	}
	logFile_ = (GetProcessName() + sUser +".log");
	logPath_ = "./log/";

	int i,len;
	len = logPath_.size();

	DIR *dp = NULL;

	if(NULL == (dp = opendir(logPath_.c_str())))
	{
		for(i = 0; i < len; i++)
		{
			if(logPath_[i] == '/')
			{
				logPath_[i] = '\0';
				if( access(logPath_.c_str(),0) != 0)
				{
					mkdir(logPath_.c_str(),0777);
				}
				logPath_[i] = '/';
			}
		}
	}

	if(NULL != dp)
	{
		closedir(dp);
		dp = NULL;
	}

	logPath_ += logFile_;
	logFileHandle_ = fopen(logPath_.c_str(), "a+");

	umask(0);
	chmod(logPath_.c_str(), 0666);
}
