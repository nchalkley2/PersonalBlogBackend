#include "blog.h"

#include <iostream>
#include <string>
#include <map>
#include <functional>

using namespace std;

static string htmlroot = "www/html";

void SetupIndexPage(crow::SimpleApp& app)
{
    CROW_ROUTE(app, "/")
	([]()
	{
		return read_all(htmlroot + "/index.html");
    });

    CROW_ROUTE(app, "/index.html")
	([]()
	{
		return read_all(htmlroot + "/index.html");
    });
	
    CROW_ROUTE(app, "/css/<path>")
	([](const crow::request& req, crow::response& res, std::string path)
	{
		res.add_header("Content-Type", 
				mimetype::getMimeType(htmlroot + "/css/" + path));
		res.body = read_all(htmlroot + "/css/" + path);
		res.end();
	});
	
    CROW_ROUTE(app, "/img/<path>")
	([](const crow::request& req, crow::response& res, std::string path)
	{
		res.add_header("Content-Type", 
				mimetype::getMimeType(htmlroot + "/img/" + path));
		res.body = read_all(htmlroot + "/img/" + path);
		res.end();
	});

    CROW_ROUTE(app, "/js/<path>")
	([](const crow::request& req, crow::response& res, std::string path)
	{
		res.add_header("Content-Type", 
				mimetype::getMimeType(htmlroot + "/js/" + path));
		res.body = read_all(htmlroot + "/js/" + path);
		res.end();
	});

    CROW_ROUTE(app, "/resume.pdf")
	([](const crow::request& req, crow::response& res)
	{
		res.add_header("Content-Type", 
				mimetype::getMimeType(htmlroot + "/resume.pdf"));
		res.body = read_all(htmlroot + "/resume.pdf");
		res.end();
	});
}
