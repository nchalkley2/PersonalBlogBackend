//#include "pistache/pistache.h"
// Argh
#include "argh.h"
#include "test.h"

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

int main(int argc, char* argv[]) 
{
	argh::parser cmdl({"-p", "--port"});
	cmdl.parse(argc, argv);

	int port;
	cmdl({"-p", "--port"}, 80) >> port;

    crow::SimpleApp app;

    CROW_ROUTE(app, "/")([](){
        return "Hello world";
    });

	//app.
	app.loglevel(crow::LogLevel::Critical);
    app.port(port).multithreaded().run();

	//Pistache::Address addr(Pistache::Ipv4::any(), Pistache::Port(port));

    //auto opts = Http::Endpoint::options().threads(1);
    //Http::Endpoint server(addr);
    //server.init(opts);
    //server.setHandler(std::make_shared<HelloHandler>());
    //server.serve();
}

