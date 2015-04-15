#pragma once
#include "log4cpp/Category.hh"
#include "log4cpp/Appender.hh"
#include "log4cpp/FileAppender.hh"
#include "log4cpp/OstreamAppender.hh"
#include "log4cpp/Layout.hh"
#include "log4cpp/BasicLayout.hh"
#include "log4cpp/Priority.hh"
#include <log4cpp/PropertyConfigurator.hh>

#include "Enums.h"


static class LoggerClass
{
public:
	LoggerClass();
	~LoggerClass(void);
	static void Log(char*);
	static void SetPriority(LoggerPriority);

private:
	static log4cpp::Priority::PriorityLevel ConvertPriority(LoggerPriority);

	static log4cpp::Category* sub1;
	static log4cpp::Priority::PriorityLevel currentPriority;
};

