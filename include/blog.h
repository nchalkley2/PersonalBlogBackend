#pragma once
#include <functional>
#include <map>

#include "crow/crow_all.h"
#include "termcolor/termcolor.hpp"
#include "mimetype/mimetype.hpp"

//#include "pistache/endpoint.h"
//#include "pistache/net.h"


namespace blog
{
	using namespace std;
	//using namespace Pistache;

	//using pageFunc = function<void(const Http::Request&, Http::ResponseWriter)>;
	using pageFunc = function<void()>;
};

