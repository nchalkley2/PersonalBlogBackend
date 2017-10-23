//#include "pistache/pistache.h"
// Argh
#include "argh.h"

// Pistache
#include "pistache/endpoint.h"
#include "pistache/net.h"

#include <iostream>
#include <string>

using namespace Pistache;

class HelloHandler : public Http::Handler {
	public:

	HTTP_PROTOTYPE(HelloHandler)

	void onRequest(const Http::Request& request, Http::ResponseWriter response) {
		std::cout << "request.resource(): " << request.resource() << std::endl;
		response.send(Http::Code::Ok, "Hello, World");
	}
};

int main(int argc, char* argv[]) 
{
	argh::parser cmdl({"-p", "--port"});
	cmdl.parse(argc, argv);

	std::cout << cmdl("port").str() << std::endl;
	

	int port;
	cmdl({"-p", "--port"}, 80) >> port;

	Pistache::Address addr(Pistache::Ipv4::any(), Pistache::Port(port));

    auto opts = Http::Endpoint::options().threads(1);
    Http::Endpoint server(addr);
    server.init(opts);
    server.setHandler(std::make_shared<HelloHandler>());
    server.serve();
}
