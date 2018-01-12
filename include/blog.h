#pragma once
#include "argh.h"
#include "crow/crow_all.h"
#include "mimetype/mimetype.hpp"
#include "termcolor/termcolor.hpp"

#include <fstream>

inline std::string
read_all(const std::string& filename)
{
	std::ifstream t(filename);
	std::string str;

	t.seekg(0, std::ios::end);
	str.reserve(t.tellg());
	t.seekg(0, std::ios::beg);

	str.assign((std::istreambuf_iterator<char>(t)),
			   std::istreambuf_iterator<char>());

	return str;
}

namespace blog
{
using namespace std;

};

