//#include "pistache/pistache.h"
#include "pistache/endpoint.h"
#include "pistache/net.h"

using namespace Pistache;
//using namespace Pistache::Net;

class HelloHandler : public Http::Handler {
	public:

	HTTP_PROTOTYPE(HelloHandler)

	void onRequest(const Http::Request& request, Http::ResponseWriter response) {
		response.send(Http::Code::Ok, "Hello, World");
	}
};

int main() {
	Pistache::Address addr(Pistache::Ipv4::any(), Pistache::Port(9080));

    auto opts = Http::Endpoint::options().threads(1);
    Http::Endpoint server(addr);
    server.init(opts);
    server.setHandler(std::make_shared<HelloHandler>());
    server.serve();
}
