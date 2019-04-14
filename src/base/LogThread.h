/*
 * LogThread.h
 *
 *  Created on: Apr 13, 2019
 *      Author: fly
 */

#ifndef LOGTHREAD_H_
#define LOGTHREAD_H_
#include <thread>
#include <stdio.h>
#include <stdarg.h>
#include <condition_variable>
#include <mutex>
#include "Buffer.h"
#include "Singleton.h"
#include "LoadIniFile.h"

class LogThread;
enum log_level
{
	FATAL_LEVEL = 0,
	ERROR_LEVEL = 1,
	WARNING_LEVEL = 2,
	INFO_LEVEL = 3,
	DEBUG_LEVEL = 4
};

#define WRITE_LOG(loglevel, format, ...) Singleton<LogThread>::getInstance().formLog(loglevel, __FUNCTION__, __LINE__, __FILE__, format, ## __VA_ARGS__)

#define LOG_ERR(format, ...)    WRITE_LOG(ERROR_LEVEL,  format, ## __VA_ARGS__)
#define LOG_INFO(format, ...)   WRITE_LOG(INFO_LEVEL,  format, ## __VA_ARGS__)
#define LOG_WARN(format, ...)   WRITE_LOG(WARNING_LEVEL, format, ## __VA_ARGS__)
#define LOG_DEBUG(format, ...)  WRITE_LOG(DEBUG_LEVEL, format, ## __VA_ARGS__)
#define LOG_FATAL(format, ...)  WRITE_LOG(FATAL_LEVEL, format, ## __VA_ARGS__)


class LogThread {
	 static const std::string  sLevel[] ;
public:
	LogThread();
	virtual ~LogThread();
	void release();
	void formLog(log_level level,
				const std::string& func,
				int lineNum,
				const std::string& file,
				const char* formatStr, ...) __attribute__((format(printf,6,7)));;

private:
	void loop();
	void flush();
	// TODO reload log level from config file;
	void reset() { loglevel_ = LoadIniFile::loadLogLevel(); }

	static std::string GetTimeStr();
	static std::string GetProcessName();
	void InitLogDir();

	std::thread  logThread_;
	bool		isExit_;
	int			intervalMs_;
	Buffer		buf_;
	int			loglevel_;
	std::string logFile_;
	std::string logPath_;
	FILE*		logFileHandle_;

	std::mutex 	mtx_;
	std::condition_variable cv_;
};

#endif /* LOGTHREAD_H_ */
