// Argh
#include "blog.h"
#include "index.h"
#include "log.h"

#include <iostream>
#include <string>

using namespace std;

static string htmlroot = "www/html";

int
main(int argc, char* argv[])
{
	argh::parser cmdl({ "-p", "--port" });
	cmdl.parse(argc, argv);

	int port;
	cmdl({ "-p", "--port" }, 80) >> port;

	crow::SimpleApp app;

	SetupIndexPage(app);

	app.loglevel(crow::LogLevel::Info);
	auto LogHandler = std::make_shared<ExampleLogHandler>();
	crow::logger::setHandler(LogHandler.get());

	app.port(port).multithreaded().run();
}

