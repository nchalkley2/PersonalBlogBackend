#include "blog.h"

#include <iostream>
#include <string>
#include <map>
#include <functional>

#include "boost/filesystem.hpp"

using namespace std;

static string htmlroot = "www/html";

void SetupIndexPage(crow::SimpleApp& app)
{
	auto indexFunc = []()
	{
		using namespace boost::filesystem;

		std::string posts;

		path p(htmlroot + "/posts/meta/");
		directory_iterator end_itr;
		for (directory_iterator itr(p); itr != end_itr; ++itr)
		{
			if (is_regular_file(itr->path())) 
			{
            	// assign current file name to current_file and echo it out to the console.
            	//string current_file = itr->path().string();
            	//cout << current_file << endl;
				posts += read_all(itr->path().string());
        	}
		}
		
		crow::mustache::context x;
		crow::mustache::template_t pageTemplate(read_all(htmlroot + "/index.html"));
		x["posts"] = posts;

		return pageTemplate.render(x);
	};

    CROW_ROUTE(app, "/")
	(indexFunc);

    CROW_ROUTE(app, "/index.html")
	(indexFunc);

	CROW_ROUTE(app, "/posts/<path>")
	([](const crow::request& req, crow::response& res, std::string path)
	{
		res.add_header("Content-Type", 
				mimetype::getMimeType(htmlroot + "/posts/" + path));
		res.body = read_all(htmlroot + "/posts/" + path);
		res.end();
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
