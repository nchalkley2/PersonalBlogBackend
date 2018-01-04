#include "blog.h"

#include <functional>
#include <iostream>
#include <map>
#include <string>

#include "boost/filesystem.hpp"
#include <boost/algorithm/string/predicate.hpp>

using namespace std;

static string htmlroot = "www/html";

static void
applyTemplates(crow::mustache::context& x)
{
	std::string head, title;
	head  = read_all(htmlroot + "/template/head.html");
	title = read_all(htmlroot + "/template/title.html");

	x["head"]  = head;
	x["title"] = title;
}

void
SetupIndexPage(crow::SimpleApp& app)
{
	auto indexFunc = []() {
		using namespace boost::filesystem;

		std::string posts;

		path p(htmlroot + "/posts/");
		for (const auto& itr : directory_iterator(p))
		{
			if (is_regular_file(itr.path()))
			{
				// assign current file name to current_file and echo it out to
				// the console.
				if (boost::algorithm::ends_with(itr.path().string(), ".meta"))
					posts += read_all(itr.path().string());
			}
		}

		crow::mustache::context x;
		crow::mustache::template_t pageTemplate(
			read_all(htmlroot + "/index.html"));
		applyTemplates(x);
		x["posts"] = posts;

		return pageTemplate.render(x);
	};

	CROW_ROUTE(app, "/")
	(indexFunc);

	CROW_ROUTE(app, "/index.html")
	(indexFunc);

	CROW_ROUTE(app, "/posts/<path>")
	([](const crow::request& req, crow::response& res, std::string path) {
		res.add_header("Content-Type",
					   mimetype::getMimeType(htmlroot + "/posts/" + path));

		if (mimetype::getMimeType(htmlroot + "/posts/" + path)
			== mimetype::getMimeType(".html"))
		{
			crow::mustache::context x;
			crow::mustache::template_t pageTemplate(
				read_all(htmlroot + "/posts/" + path));
			applyTemplates(x);

			res.body = pageTemplate.render(x);
		}
		else
		{
			res.body = read_all(htmlroot + "/posts/" + path);
		}
		res.end();
	});

	CROW_ROUTE(app, "/css/<path>")
	([](const crow::request& req, crow::response& res, std::string path) {
		res.add_header("Content-Type",
					   mimetype::getMimeType(htmlroot + "/css/" + path));
		res.body = read_all(htmlroot + "/css/" + path);
		res.end();
	});

	CROW_ROUTE(app, "/img/<path>")
	([](const crow::request& req, crow::response& res, std::string path) {
		res.add_header("Content-Type",
					   mimetype::getMimeType(htmlroot + "/img/" + path));
		res.body = read_all(htmlroot + "/img/" + path);
		res.end();
	});

	CROW_ROUTE(app, "/js/<path>")
	([](const crow::request& req, crow::response& res, std::string path) {
		res.add_header("Content-Type",
					   mimetype::getMimeType(htmlroot + "/js/" + path));
		res.body = read_all(htmlroot + "/js/" + path);
		res.end();
	});

	CROW_ROUTE(app, "/resume.pdf")
	([](const crow::request& req, crow::response& res) {
		res.add_header("Content-Type",
					   mimetype::getMimeType(htmlroot + "/resume.pdf"));
		res.body = read_all(htmlroot + "/resume.pdf");
		res.end();
	});
}
