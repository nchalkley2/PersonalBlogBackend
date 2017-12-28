#include "blog.h"
#include "log.h"

#include <string>
#include <sstream>

void ExampleLogHandler::log(std::string message, crow::LogLevel level)
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

std::string ExampleLogHandler::getLogPrefix(crow::LogLevel level)
{	
	std::stringstream outStringStr;
	std::string prefix = "";
	
	termcolor::colorize(outStringStr);

	// Colorize the output
	switch (level)
	{
	case crow::LogLevel::Debug:
		outStringStr << prefix << termcolor::green <<
			"[ Debug   ] " << termcolor::reset;
		break;

	case crow::LogLevel::Info:
		outStringStr << prefix << termcolor::green <<
			"[ Info    ] " << termcolor::reset;
		break;
	
	case crow::LogLevel::Warning:
		outStringStr << prefix << termcolor::yellow <<
			"[ Warning ] " << termcolor::reset;
		break;

	case crow::LogLevel::Error:
		outStringStr << prefix << termcolor::red <<
			"[ Error   ] " << termcolor::reset;
		break;
		
	default:		
		break;
	}

	return outStringStr.str();
}	
