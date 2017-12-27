//#include "pistache/pistache.h"
// Argh
#include "argh.h"
#include "blog.h"

// Pistache
//#include "pistache/endpoint.h"
//#include "pistache/net.h"

#include <iostream>
#include <string>
#include <map>
#include <functional>

//using namespace Pistache;
using namespace std;

static string htmlroot = "www/html";
static map<string, blog::pageFunc> pagemap;

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

/*class HelloHandler : public Http::Handler {
	public:

	HTTP_PROTOTYPE(HelloHandler)

	void onRequest(const Http::Request& request, Http::ResponseWriter response) {
		cout << "request.resource(): " << request.resource() << endl;
		
		string filepath = htmlroot + 
			(request.resource().back() != '/' ? request.resource() : request.resource() + "index.html");

		Http::serveFile(response, filepath.c_str());
	}
};*/

string read_all(const string& filename)
{
    ifstream is(filename);
    return {istreambuf_iterator<char>(is), istreambuf_iterator<char>()};
}

int main(int argc, char* argv[]) 
{
	argh::parser cmdl({"-p", "--port"});
	cmdl.parse(argc, argv);

	int port;
	cmdl({"-p", "--port"}, 80) >> port;

    crow::SimpleApp app;

    CROW_ROUTE(app, "/")([](){
        return read_all(htmlroot + "/index.html");
    });

    CROW_ROUTE(app, "/css/main.css")([](){
	std::cout << mimetype::getMimeType(htmlroot + "/css/main.css") << std::endl;
		return read_all(htmlroot + "/css/main.css");
	});

	app.loglevel(crow::LogLevel::Debug);
	auto LogHandler = std::make_shared<ExampleLogHandler>();
	crow::logger::setHandler(LogHandler.get());

    app.port(port).multithreaded().run();
}

