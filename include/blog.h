#pragma once
#include "argh.h"
#include "crow/crow_all.h"
#include "termcolor/termcolor.hpp"
#include "mimetype/mimetype.hpp"

#include <fstream>

static std::string read_all(const std::string& filename)
{
	std::ifstream is(filename);
    return {std::istreambuf_iterator<char>(is), 
		std::istreambuf_iterator<char>()};
}

namespace blog
{
	using namespace std;
};

