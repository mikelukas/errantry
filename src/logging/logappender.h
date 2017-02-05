#ifndef SRC_LOGGING_LOGAPPENDER_H_
#define SRC_LOGGING_LOGAPPENDER_H_

#include <string>

using std::string;

/* Common interface that things that can render log messages can implement.
 * Allows decoupling callers from appender implementation.
 */
class LogAppender
{
	public:
		LogAppender() {};
		virtual ~LogAppender() {}

		virtual void log(const string&) const = 0;
};

#endif
