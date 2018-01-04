#include "log.h"
#include "blog.h"

#include <sstream>
#include <string>

#include "boost/date_time/posix_time/posix_time.hpp"

void
ExampleLogHandler::log(std::string message, crow::LogLevel level)
{
	// Remove everthing up to the ']' character
	// Also strip the endline
	//
	// the fact that I can't replace the logger and
	// avoid this is really fucking stupid
	message = message.substr(message.find(']') + 2);
	message = message.substr(0, message.find('\n'));

	std::cout << getLogPrefix(level) << message << std::endl;
}

std::string
ExampleLogHandler::getLogPrefix(crow::LogLevel level)
{
	std::stringstream outStringStr, prefix;

	// Turn on colorization for outputs
	termcolor::colorize(outStringStr);
	termcolor::colorize(prefix);

	// Generate the prefix
	prefix << termcolor::cyan << boost::posix_time::second_clock::local_time()
		   << termcolor::reset << " ";

	// Turn on colorization for outStringStr
	termcolor::colorize(outStringStr);

	// Colorize the output
	switch (level)
	{
	case crow::LogLevel::Debug:
		outStringStr << prefix.str() << termcolor::green << "[ Debug   ] "
					 << termcolor::reset;
		break;

	case crow::LogLevel::Info:
		outStringStr << prefix.str() << termcolor::green << "[ Info    ] "
					 << termcolor::reset;
		break;

	case crow::LogLevel::Warning:
		outStringStr << prefix.str() << termcolor::yellow << "[ Warning ] "
					 << termcolor::reset;
		break;

	case crow::LogLevel::Error:
		outStringStr << prefix.str() << termcolor::red << "[ Error   ] "
					 << termcolor::reset;
		break;

	default:
		break;
	}

	return outStringStr.str();
}
