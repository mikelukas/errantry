#ifndef SRC_LOGGING_LOG_H_
#define SRC_LOGGING_LOG_H_

#include "logappender.h"

/* Singleton class that can be used to log a message to the console, using
 * a given appender.  Decouples callers who want to log from having to
 * maintain a reference to a concrete appender.
 */
class Log
{
	protected:
		static Log* instance;
		LogAppender* appender;

		Log(LogAppender*);

		const LogAppender* getAppender() const;

	public:
		static void init(LogAppender*);
		static const Log* getInstance();

		virtual ~Log();

		friend void log(const string&);
};

void log(const string&); //Need to redefine log here so that it has global scope, in order to be found when compiling

#endif
