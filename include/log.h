#pragma once
#include "blog.h"
#include <string>

class ExampleLogHandler : public crow::ILogHandler 
{
private:
	std::string getLogPrefix(crow::LogLevel level);

public:
    void log(std::string message, crow::LogLevel level) override; 
};
