#include "log.h"

Log* Log::instance = NULL; //singleton instance static initialization

Log::Log(LogAppender* appender)
	: appender(appender)
{

}

Log::~Log()
{
	delete appender;
}

void Log::init(LogAppender* appender)
{
	instance = new Log(appender);
}

const Log* Log::getInstance()
{
	//precondition: init() must be called before this method to initialize the
	//log with an appender.
	//postcondition: returns the singleton instance of the log.

	return instance;
}

const LogAppender* Log::getAppender() const
{
	//postcondition: returns the appender the log is using.

	return appender;
}

void log(const string& msg)
{
	//postcondition: asks the log singleton's appender to log a message.

	Log::getInstance()->getAppender()->log(msg);
}
