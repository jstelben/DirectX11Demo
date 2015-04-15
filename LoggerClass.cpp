#include "LoggerClass.h"


LoggerClass::LoggerClass()
{
	log4cpp::PropertyConfigurator::configure("log4cpp.properties");
	//LoggerClass::sub1 = log4cpp::Category::getInstance(std::string("sub1"));
	LoggerClass::currentPriority = log4cpp::Priority::DEBUG;
}


LoggerClass::~LoggerClass(void)
{
	//delete LoggerClass::sub1;
}

void LoggerClass::Log(char* message)
{
	//LoggerClass::sub1->log(currentPriority, message);
}

void LoggerClass::SetPriority(LoggerPriority priority)
{
	//LoggerClass::currentPriority = ConvertPriority(priority);
}

log4cpp::Priority::PriorityLevel LoggerClass::ConvertPriority(LoggerPriority priority)
{
	switch(priority)
	{
		case LoggerPriority::Alert:
			{
				return log4cpp::Priority::ALERT;
			}
		case LoggerPriority::Crit:
			{
				return log4cpp::Priority::CRIT;
			}
		case LoggerPriority::Debug:
			{
				return log4cpp::Priority::DEBUG;
			}
		case LoggerPriority::Emergency:
			{
				return log4cpp::Priority::EMERG;
			}
		case LoggerPriority::Error:
			{
				return log4cpp::Priority::ERROR;
			}
		case LoggerPriority::Fatal:
			{
				return log4cpp::Priority::FATAL;
			}
		case LoggerPriority::Info:
			{
				return log4cpp::Priority::INFO;
			}
		case LoggerPriority::Notice:
			{
				return log4cpp::Priority::NOTICE;
			}
		case LoggerPriority::Warn:
			{
				return log4cpp::Priority::WARN;
			}
		default:
			{
				return log4cpp::Priority::DEBUG;
			}
	}
}
