#include <iostream>
#include "consoleappender.h"

using std::cout;
using std::endl;

ConsoleAppender::ConsoleAppender()
	: LogAppender()
{

}

void ConsoleAppender::log(const string& msg) const
{
	//postcondition: msg is written at the bottom of the console, with a line
	//ending applied.

	cout<<msg<<endl;
}
