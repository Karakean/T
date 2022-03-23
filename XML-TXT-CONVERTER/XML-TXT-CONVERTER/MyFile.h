#pragma once
#include <string>
#include <fstream>
#include <vector>
#include "rapidxml.hpp"
class MyFile {
protected:
	std::string filename;
public:
	virtual void convert() = 0;
};