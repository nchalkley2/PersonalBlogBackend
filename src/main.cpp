// Argh
#include "argh.h"
#include "blog.h"

#include <iostream>
#include <string>
#include <map>
#include <functional>

//using namespace Pistache;
using namespace std;

static string htmlroot = "www/html";

class ExampleLogHandler : public crow::ILogHandler 
{
    public:
    void log(std::string message, crow::LogLevel level) override 
	{
		// Remove everthing up to the ']' character
		// Also strip the endline
		//
		// the fact that I can't replace the logger and
		// avoid this is really fucking stupid
		message = message.substr(message.find(']') + 2);
		message = message.substr(0, message.find('\n'));
		
		// Colorize the output
		switch (level)
		{
		case crow::LogLevel::Debug:
			cout << "ExampleLogHandler ->" << termcolor::green <<
				"[ Debug   ] " << termcolor::reset << message << endl;
			break;

		case crow::LogLevel::Info:
			cout << "ExampleLogHandler ->" << termcolor::green <<
				"[ Info    ] " << termcolor::reset << message << endl;
			break;
		
		case crow::LogLevel::Warning:
			cout << "ExampleLogHandler ->" << termcolor::yellow <<
				"[ Warning ] " << termcolor::reset << message << endl;
			break;

		case crow::LogLevel::Error:
			cout << "ExampleLogHandler ->" << termcolor::red <<
				"[ Error   ] " << termcolor::reset << message << endl;
			break;
			
		default:		
			cout << "ExampleLogHandler ->" << message << endl;
			break;
		}
    }
};

void SetupIndexPage(crow::SimpleApp& app);

int main(int argc, char* argv[]) 
{
	argh::parser cmdl({"-p", "--port"});
	cmdl.parse(argc, argv);

	int port;
	cmdl({"-p", "--port"}, 80) >> port;

    crow::SimpleApp app;

	SetupIndexPage(app);

	app.loglevel(crow::LogLevel::Info);
	auto LogHandler = std::make_shared<ExampleLogHandler>();
	crow::logger::setHandler(LogHandler.get());

    app.port(port).multithreaded().run();
}

