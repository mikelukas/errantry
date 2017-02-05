#ifndef SRC_LOGGING_CONSOLEAPPENDER_H_
#define SRC_LOGGING_CONSOLEAPPENDER_H_

#include "logappender.h"

/* When log is called, messages are written to the console on the bottom line */
class ConsoleAppender: public LogAppender
{
	public:
		ConsoleAppender();
		virtual ~ConsoleAppender() {}

		virtual void log(const string&) const;
};

#endif
