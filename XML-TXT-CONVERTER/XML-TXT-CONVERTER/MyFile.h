#pragma once
#include <string>
#include <fstream>
#include <vector>
#include "rapidxml.hpp"
class MyFile {
protected:
	std::string filename;
	std::string in_dir;
	std::string out_dir;
public:
	virtual void convert() = 0;
	std::string get_filename();
};