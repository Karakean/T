#pragma once
#include "MyFile.h"
class MyXML :public MyFile {
public:
	MyXML(std::string filename, std::string in_dir, std::string out_dir);
	void convert() override;
};